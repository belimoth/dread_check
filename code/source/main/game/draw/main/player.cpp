#include "../../draw/split.h"

#include "../../../../data/gfx.h"
#include "../../../game/draw.h"
#include "../../../game.h"
#include "../../player.h"

#include <zed/app.h>
#include <zed/camera.h>
#include <zed/xmath.h>
#include <zed/platform/d3d11.h>

void game_draw_player_body( game_player &player, int i ) {
	zed_camera camera = game.data.camera[ player.i ];

	float3 position = player.object.position;
	float3 rotation = camera.rotation; rotation.x = 0;
	float3 handle;

	switch ( player.stance ) {
		case stance_prone:
		case stance_dive_prone:
		rotation.x = 90;
		handle = { 0, camera.position.y - player.object.position.y - 1.5f, 0 };
		if ( i == player.i ) handle.y -= 0.3;
		break;

		case stance_supine:
		case stance_dive_supine:
		case stance_slide_supine:
		rotation.x = -90;
		handle = { 0, camera.position.y - player.object.position.y - 1.5f, 0 };
		if ( i == player.i ) handle.y -= 0.3;
		break;

		// todo
		case stance_side_left:
		case stance_dive_left:
		break;

		// todo
		case stance_side_right:
		case stance_dive_right:
		break;

		default:
		handle = { 0, camera.position.y - player.object.position.y - 1.5f, 0 };
		if ( i == player.i ) handle.z -= 0.3;
	}

	game_draw_per_object_set_for_player( position, handle, rotation, {} );
	zed_mesh_draw( mesh_player );

	switch ( player.stance ) {
		case stance_sail:
		game.draw.per_object.matrix_world = game.draw.per_object.matrix_world * translate( 0, 2, 0 );
		game_draw_per_object_update();
		zed_mesh_draw( mesh_chute );
		break;
	}
}

matrix get_hand_handle( game_player &player ) {
	float3 position = player.object.position;
	position.y += game_player_get_height( player );
	float3 handle = { 0.1, -0.1, 0.2 };

	if ( player.torso == torso_aim ) {
		handle = { 0.0, -0.044, 0.1 };
	} else if ( player.hands.goofy ) {
		handle = { -0.1, -0.1, 0.2 };
	}

	float3 gun_rotation = player.gun_rig_0.rotation;

	float3 rotation = {};
	rotation.x = -70;

	//

	matrix temp = identity;

	temp = temp * zed_camera_get_rotation_matrix( rotation     );
	temp = temp * translate                     ( handle       );
	temp = temp * zed_camera_get_rotation_matrix( gun_rotation );
	temp = temp * translate                     ( position     );

	return temp;
}

matrix get_hand_handle_left( game_player &player ) {
	float3 position = player.object.position;
	position.y += game_player_get_height( player );
	float3 handle = { -0.1, -0.1, 0.2 };

	if ( player.torso == torso_aim ) {
		handle = { 0.0, -0.044, 0.1 };
	} else if ( player.hands.goofy ) {
		handle = { 0.1, -0.1, 0.2 };
	}

	float3 gun_rotation = player.gun_rig_1.rotation;

	float3 rotation = {};
	rotation.x = -70;

	//

	matrix temp = identity;

	temp = temp * zed_camera_get_rotation_matrix( rotation     );
	temp = temp * translate                     ( handle       );
	temp = temp * zed_camera_get_rotation_matrix( gun_rotation );
	temp = temp * translate                     ( position     );

	return temp;
}

matrix get_item_handle( game_player &player, bool offhand, bool goofy = false ) {
	game_item &item = game_player_hands_get_item( player );

	float3 position = player.object.position;
	position.y += game_player_get_height( player );
	float3 handle = { 0.1, -0.1, 0.2 };

	if ( player.torso == torso_aim ) {
		handle = { 0.0, -0.044, 0.1 };
	} else if ( goofy ) {
		handle = { -0.1, -0.1, 0.2 };
	} else if ( player.hands.which and player.hands.j == player.hands.k ) {
		handle = { 0, -0.1, 0.2 };
	}

	float3 rotation = {};
	float3 gun_rotation = {};
	rotation.y += -90.0;

	if ( offhand ) {
		handle.z += player.rig.recoil_1 * -0.01;
		gun_rotation = player.gun_rig_1.rotation;
	} else {
		handle.z += player.rig.recoil_0 * -0.01;
		gun_rotation = player.gun_rig_0.rotation;

		float reload_tilt = player.rig.reload;
		if ( item.type.i == item_wi_1897_shotgun and player.action == action_reload and item.slide == slide_open and item.chamber == chamber_empty ) reload_tilt *= -1;
		rotation.x += -90.0 * reload_tilt;

		if ( player.torso == torso_hold  ) handle.y += 0.15;
		if ( player.torso == torso_hold  ) rotation.z -= -70;
		if ( player.torso == torso_throw ) rotation.y += -70;
	}

	matrix temp = identity;

	temp = temp * zed_camera_get_rotation_matrix( rotation     );
	temp = temp * translate                     ( handle       );
	temp = temp * zed_camera_get_rotation_matrix( gun_rotation );
	temp = temp * translate                     ( position     );

	return temp;
}

matrix get_knife_handle( game_player &player, bool offhand, bool goofy = false ) {
	float3 position = player.object.position;
	position.y += game_player_get_height( player );
	float3 handle = { 0.1, -0.1, 0.2 };

	if ( player.torso == torso_aim ) {
		handle = { 0.0, -0.044, 0.1 };
	} else if ( goofy ) {
		handle = { -0.1, -0.1, 0.2 };
	} else if ( player.hands.which and player.hands.j == player.hands.k ) {
		handle = { 0, -0.1, 0.2 };
	}

	float3 rotation = {};
	float3 gun_rotation = {};

	rotation.x +=  10.0;
	rotation.y +=  90.0;
	rotation.z +=  90.0;

	if ( offhand ) {
		handle.z += player.rig.recoil_1 * 0.05;
		gun_rotation = player.gun_rig_1.rotation;
	} else {
		handle.z += player.rig.recoil_0 * 0.05;
		gun_rotation = player.gun_rig_0.rotation;

		if ( player.torso == torso_hold  ) handle.y += 0.15;
		if ( player.torso == torso_hold  ) rotation.z -= -70;
		if ( player.torso == torso_throw ) rotation.y += -70;
	}

	matrix temp = identity;

	temp = temp * zed_camera_get_rotation_matrix( rotation     );
	temp = temp * translate                     ( handle       );
	temp = temp * zed_camera_get_rotation_matrix( gun_rotation );
	temp = temp * translate                     ( position     );

	return temp;
}

matrix get_light_handle( game_player &player, bool offhand, bool goofy = false ) {
	float3 position = player.object.position;
	position.y += game_player_get_height( player );
	float3 handle = { 0.1, -0.1, 0.2 };

	if ( player.torso == torso_aim ) {
		handle = { 0.0, -0.044, 0.1 };
	} else if ( goofy ) {
		handle = { -0.1, -0.1, 0.2 };
	} else if ( player.hands.which and player.hands.j == player.hands.k ) {
		handle = { 0, -0.1, 0.2 };
	}

	float3 rotation = {};
	float3 gun_rotation = {};

	rotation.x += 180.0;
	rotation.z += 180.0;

	if ( offhand ) {
		handle.z += player.rig.recoil_1 * 0.05;
		gun_rotation = player.gun_rig_1.rotation;
	} else {
		handle.z += player.rig.recoil_0 * 0.05;
		gun_rotation = player.gun_rig_0.rotation;
		if ( player.torso == torso_hold  ) handle.y += 0.15;
		if ( player.torso == torso_hold  ) rotation.z -= -70;
		if ( player.torso == torso_throw ) rotation.y += -70;
	}

	matrix temp = identity;

	temp = temp * zed_camera_get_rotation_matrix( rotation     );
	temp = temp * translate                     ( handle       );
	temp = temp * zed_camera_get_rotation_matrix( gun_rotation );
	temp = temp * translate                     ( position     );

	return temp;
}

matrix get_bag_handle( game_player &player ) {
	float3 position = player.object.position;
	position.y += game_player_get_height( player );
	float3 handle = { 0, -0.4, 0.5 };

	float3 rotation = {};
	float3 gun_rotation = {};

	rotation.x += 0;
	rotation.y += 0;
	rotation.z += 0;

	handle.z += player.rig.recoil_0 * 0.05;
	gun_rotation = player.gun_rig_0.rotation;
	if ( player.torso == torso_hold  ) handle.y += 0.15;
	if ( player.torso == torso_hold  ) rotation.z -= -70;
	if ( player.torso == torso_throw ) rotation.y += -70;

	matrix temp = identity;

	temp = temp * zed_camera_get_rotation_matrix( rotation     );
	temp = temp * translate                     ( handle       );
	temp = temp * zed_camera_get_rotation_matrix( gun_rotation );
	temp = temp * translate                     ( position     );

	return temp;
}

void game_draw_player_item( game_player &player ) {
	game_item &item = game_player_hands_get_item( player );

	game.draw.per_object.matrix_world = get_item_handle( player, false, player.hands.goofy );
	game_draw_per_object_update();

	switch ( item.type.i ) {
		case item_bag:
		game.draw.per_object.matrix_world = get_bag_handle( player );
		game_draw_per_object_update();
		zed_mesh_draw( mesh_bag );
		break;

		case item_torch:
		game.draw.per_object.matrix_world = get_light_handle( player, false, player.hands.goofy );
		game_draw_per_object_update();
		zed_mesh_draw( mesh_light );
		break;

		case item_sword:
		game.draw.per_object.matrix_world = get_knife_handle( player, false, player.hands.goofy );
		game_draw_per_object_update();
		zed_mesh_draw( mesh_knife );
		break;

		case item_us_1917_revolver:
		zed_mesh_draw( mesh_revolver );
		break;

		case item_wi_1897_shotgun:

		if ( item.slide == slide_open or player.action == action_slide_open ) {
			zed_mesh_draw( mesh_shotgun_open );
		} else {
			zed_mesh_draw( mesh_shotgun );
		}

		break;

		case item_ak_1947:
		zed_mesh_draw( mesh_ak47 );
		break;
	}

	if ( ( player.torso == torso_grab and player.hands.k == 0 ) or ( player.torso == torso_throw and item.type.i == item_none ) ) {
		game.draw.per_object.matrix_world = get_hand_handle_left( player );
		game_draw_per_object_update();
		zed_mesh_draw( mesh_hand );
	}

	if ( ( player.torso == torso_throw or player.torso == torso_hold ) and item.type.i == item_none ) {
		game.draw.per_object.matrix_world = get_hand_handle( player );
		game_draw_per_object_update();
		zed_mesh_draw( mesh_hand_right );
	}

	if ( ( player.hands.which or player.torso == torso_grab ) and not ( player.hands.which and player.hands.j == player.hands.k )  ) {
		game.draw.per_object.matrix_world = get_item_handle( player, true, not player.hands.goofy );
		game_draw_per_object_update();

		switch ( player.hands.belt[ player.hands.k ].type.i ) {
			case item_torch:
			game.draw.per_object.matrix_world = get_light_handle( player, true, not player.hands.goofy );
			game_draw_per_object_update();
			zed_mesh_draw( mesh_light );
			break;

			case item_sword:
			game.draw.per_object.matrix_world = get_knife_handle( player, true, not player.hands.goofy );
			game_draw_per_object_update();
			zed_mesh_draw( mesh_knife );
			break;

			case item_us_1917_revolver:
			zed_mesh_draw( mesh_revolver );
			break;

			case item_wi_1897_shotgun:

			if ( item.slide == slide_open or player.action == action_slide_open ) {
				zed_mesh_draw( mesh_shotgun_open );
			} else {
				zed_mesh_draw( mesh_shotgun );
			}

			break;

			case item_ak_1947:
			zed_mesh_draw( mesh_ak47 );
			break;
		}
	}
}

void game_draw_player() {
	for ( int j = 0; j < (int)split + 1; j++ ) {
		game_player &player = game.data.player[j];
		game_draw_set_camera_i game_draw_player_body( player, i );

		switch ( player.stance ) {
			case stance_reach:
			case stance_run:
			case stance_jump:
			case stance_fall:
			case stance_sail:
			case stance_trip:
			case stance_dive_prone:
			case stance_dive_supine:
			case stance_dive_left:
			case stance_dive_right:
			case stance_slide_prone:
			case stance_slide_supine:
			case stance_slide_left:
			case stance_slide_right:
			break;

			default:
			game_draw_set_camera_i game_draw_player_item( player );
		}
	}
}
