#include "../../game.h"
#include "../player.h"
#include "constants.h"

#include <zed/xmath.h>

void game_player_update_turn_speed_temp() {

}

void game_player_steering_step( game_player &player ) {
	game_item &item = game_player_hands_get_item( player );
	{
		float target_speed = 0;

		switch ( player.stance ) {
			case stance_reach:
			case stance_walk:
			case stance_stalk:
			target_speed = turn_speed_walk;
			break;

			case stance_crouch:
			case stance_crawl:
			target_speed = turn_speed_hide;
			break;

			case stance_prone:
			case stance_supine:
			case stance_side_left:
			case stance_side_right:
			case stance_fall:
			target_speed = turn_speed_flat;
			break;

			case stance_sail:
			case stance_run:
			target_speed = turn_speed_run;
			break;

			case stance_jog:
			target_speed = turn_speed_jog;
			break;
		}

		if ( player.torso == torso_aim and item.type.i != item_none ) {
			target_speed = turn_speed_aim;
		}

		target_speed *= player.pad.joy_1.x + player.pad.gyro.x;
		player.turn_speed = converge( player.turn_speed, target_speed, turn_accel );
	}

	//

	if ( player.stance == stance_jump        ) return;
	if ( player.stance == stance_fall        ) return;
	if ( player.stance == stance_dive_prone  ) return;
	if ( player.stance == stance_dive_supine ) return;
	if ( player.stance == stance_dive_left   ) return;
	if ( player.stance == stance_dive_right  ) return;

	//

	float target_speed = move_speed_walk;

	switch ( player.stance ) {
		case stance_reach:
		target_speed = move_speed_none;
		break;

		case stance_walk:
		target_speed = move_speed_walk;
		break;

		case stance_stalk:
		case stance_crouch:
		target_speed = move_speed_hide;
		break;

		case stance_crawl:
		case stance_prone:
		case stance_supine:
		case stance_side_left:
		case stance_side_right:
		target_speed = move_speed_flat;
		break;

		case stance_run:
		target_speed = move_speed_run;
		break;

		case stance_jog:
		target_speed = move_speed_jog;
		break;

		case stance_skid:
		case stance_slide_prone:
		case stance_slide_supine:
		case stance_slide_left:
		case stance_slide_right:
		target_speed = move_speed_none;
		break;

		case stance_sail:
		target_speed = cos( dtor( game.data.camera[ player.i ].rotation.x ) ) * 0.2; // 0.05; // 0.1; // 0.2;
		break;
	}

	if ( player.torso == torso_aim ) target_speed = move_speed_aim;

	//

	float move_accel = move_accel_walk;

	switch ( player.stance ) {
		case stance_reach:
		move_accel = move_accel_skid;
		break;

		case stance_walk:
		case stance_stalk:
		move_accel = move_accel_walk;
		break;

		case stance_crouch:
		case stance_crawl:
		move_accel = move_accel_hide;
		break;

		case stance_prone:
		case stance_supine:
		case stance_side_left:
		case stance_side_right:
		move_accel = move_accel_flat;
		break;

		case stance_run:
		move_accel = move_accel_run;
		break;

		case stance_jog:
		move_accel = move_accel_jog;
		break;

		case stance_skid:
		move_accel = move_accel_skid;
		break;

		case stance_slide_prone:
		case stance_slide_supine:
		case stance_slide_left:
		case stance_slide_right:
		move_accel = move_accel_slide;
		break;
	}

	if ( player.torso == torso_aim ) move_accel = move_accel_aim;

	//

	float3 temp = { player.pad.joy_0.x, player.pad.joy_0.y, 0 };
	if ( player.stance == stance_sail ) temp.y = 1;
	temp = normalize( temp );
	float3 target_velocity = temp * target_speed;
	target_velocity.z = player.object.velocity.z;

	if ( player.did_sprint ) {
		player.object.velocity = target_velocity;
	} else {
		float2 diff = target_velocity - player.object.velocity;

		if ( length( diff ) <= move_accel ) {
			player.object.velocity = target_velocity;
		} else {
			float2 accel = normalize( diff ) * move_accel;
			player.object.velocity = player.object.velocity + accel;
		}
	}
}
