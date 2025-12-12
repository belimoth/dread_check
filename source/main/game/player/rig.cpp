#include "../../../data/sfx.h"
#include "../../game.h"
#include "../player.h"
#include "constants.h"

#include <zed/app/audio.h>
#include <zed/random.h>

struct motion_result {
	float x;
	float v;
};

motion_result motion_spring( float x, float v, float xt, float zeta, float omega, float h = 1 ) {
	float f    = 1 + 2 * h * zeta;
	float oo   = omega * omega;
	float hoo  = h * oo;
	float hhoo = h * hoo;
	float di   = 1 / ( f + hhoo );
	float dx   = f * x + h * v + hhoo * xt;
	float dv   = v + hoo * ( xt - x );

	motion_result result = {};
	result.x = dx * di;
	result.v = dv * di;

	return result;
}

motion_result motion_sprint_2( float x, float v, float xt, float f, float pd, float td = 1, float h = 1 ) {
	float omega = 2 * math_pi * f;
	float zeta  = ln( pd ) / ( -omega * td ); // todo maybe divide by 60 for "frames"
	return motion_spring( x, v, xt, zeta, omega, h );
}

void game_player_gun_rig_step( game_player &player ) {
	zed_camera &camera = game.data.camera[ player.i ];

	{
		game_item &item = game_player_hands_get_item( player );
		game_item_mass w = item.type.mass;

		if ( w.stiffness == 0 ) {
			player.gun_rig_0.rotation.x = camera.rotation.x;
			player.gun_rig_0.rotation.y = camera.rotation.y;
		} else {
			float dx = camera.rotation.x - player.gun_rig_0.rotation.x;
			player.gun_rig_0.turn_speed_x = lerp( player.gun_rig_0.turn_speed_x, dx * w.stiffness, w.damping );
			player.gun_rig_0.rotation.x += player.gun_rig_0.turn_speed_x;

			dx = camera.rotation.y - player.gun_rig_0.rotation.y;
			player.gun_rig_0.turn_speed = lerp( player.gun_rig_0.turn_speed, dx * w.stiffness, w.damping );
			player.gun_rig_0.rotation.y += player.gun_rig_0.turn_speed;
		}
	}

	{
		game_item &item = player.hands.belt[ player.hands.k ];
		game_item_mass w = item.type.mass;

		if ( w.stiffness == 0 ) {
			player.gun_rig_1.rotation.x = camera.rotation.x;
			player.gun_rig_1.rotation.y = camera.rotation.y;
		} else {
			float dx = camera.rotation.x - player.gun_rig_1.rotation.x;
			player.gun_rig_1.turn_speed_x = lerp( player.gun_rig_1.turn_speed_x, dx * w.stiffness, w.damping );
			player.gun_rig_1.rotation.x += player.gun_rig_1.turn_speed_x;

			dx = camera.rotation.y - player.gun_rig_1.rotation.y;
			player.gun_rig_1.turn_speed = lerp( player.gun_rig_1.turn_speed, dx * w.stiffness, w.damping );
			player.gun_rig_1.rotation.y += player.gun_rig_1.turn_speed;
		}
	}
}

void game_player_rig_step( game_player &player ) {
	zed_camera &camera = game.data.camera[ player.i ];

	//

	player.trigger = player.pad.rt;

	//

	float posture_previous = player.rig.posture;

	switch ( player.stance ) {
		case stance_reach:
		player.rig.posture = converge( player.rig.posture, 1.4, 0.4 * 1 / time_hide );
		break;

		case stance_walk:
		case stance_jog:
		case stance_run:
		case stance_skid:
		player.rig.posture = converge( player.rig.posture, 1.0, 1.0 * 1 / time_hide );
		break;

		case stance_stalk:
		player.rig.posture = converge( player.rig.posture, 0.5, 1.0 * 1 / time_hide );
		break;

		case stance_crouch:
		player.rig.posture = converge( player.rig.posture, 0.0, 1.0 * 1 / time_hide );
		break;

		case stance_crawl:
		player.rig.posture = converge( player.rig.posture, -0.5, 1.0 * 1 / time_hide );
		break;

		case stance_prone:
		case stance_supine:
		case stance_side_left:
		case stance_side_right:
		// case stance_dive_prone:
		// case stance_dive_supine:
		// case stance_dive_left:
		// case stance_dive_right:
		player.rig.posture = converge( player.rig.posture, -1.0, 1.0 * 1 / time_hide );
		break;

		case stance_slide_prone:
		case stance_slide_supine:
		case stance_slide_left:
		case stance_slide_right:
		player.rig.posture = converge( player.rig.posture, -1.0, 4.0 * 1 / time_hide );
		break;

		case stance_dive_prone:
		case stance_dive_supine:
		case stance_dive_left:
		case stance_dive_right:
		player.rig.posture = -1.0;
		break;
	}

	// posture_penalty += abs( player.rig.posture - posture_previous ) * 0.5;
	// if ( player.rig.posture == posture_previous ) posture_penalty = 0;

	// head bob

	float t_previous = player.t;
	player.t += 1;

	float bob_rate   = game_player_get_bob_rate  ( player );
	float bob_amount = game_player_get_bob_amount( player );

	// todo, reimplement in terms of actual movement speed

	switch ( player.stance ) {
		case stance_walk:
		case stance_stalk:
		case stance_crouch:
		case stance_crawl:
		case stance_prone:
		case stance_supine:
		case stance_side_left:
		case stance_side_right:
		bob_amount = bob_amount * player.pad.joy_0.magnitude;
		break;
	}

	player.rig.bob_y = abs( sin( player.t * bob_rate * math_pi / 180 ) ) * bob_amount - bob_amount * 0.5;

	//

	// if ( player.move_speed > 0 ) {
	if ( player.object.velocity.x != 0 or player.object.velocity.y != 0 ) {
		if ( (uint)( t_previous * bob_rate ) % 180 > (uint)( player.t * bob_rate ) % 180 ) {
			switch ( player.stance ) {
				case stance_crouch:
				case stance_crawl:
				case stance_prone:
				case stance_supine:
				case stance_side_left:
				case stance_side_right:
				case stance_slide_prone:
				case stance_slide_supine:
				case stance_slide_left:
				case stance_slide_right:
				break;

				default:
				zed_play_sound( sfx_foot[ sfx_foot_i ], -30, zed_random_get_float( -1.0, 1.0 ) );
				int r = zed_random_get( 1, 3 );
				sfx_foot_i = ( sfx_foot_i + r ) % 4;
			}
		}
	}

	// stress

	player.t_stress_damage_flash = max( 0.0, player.t_stress_damage_flash - 0.05 );

	// recoil

	if ( player.rig.recoil_0 > 0 ) {
		player.rig.recoil_speed_0 = lerp( player.rig.recoil_speed_0, ( player.rig.recoil_0 - 0 ) * 0.1, 0.2 );
		player.rig.recoil_0       = converge( player.rig.recoil_0, 0, player.rig.recoil_speed_0 );
	}

	if ( player.rig.recoil_1 > 0 ) {
		player.rig.recoil_speed_1 = lerp( player.rig.recoil_speed_1, ( player.rig.recoil_1 - 0 ) * 0.1, 0.2 );
		player.rig.recoil_1       = converge( player.rig.recoil_1, 0, player.rig.recoil_speed_1 );
	}

	//

	camera.position = player.object.position;
	camera.position.y += game_player_get_height( player ) + player.rig.bob_y;

	camera.rotation.x += -player.pad.joy_1.y * 1.0; // was 0.8;
	camera.rotation.x = min( camera.rotation.x,  90.0 );
	camera.rotation.x = max( camera.rotation.x, -90.0 );

	camera.rotation.y += player.turn_speed;
}
