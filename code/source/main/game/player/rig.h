#pragma once

struct game_player_rig {
	float bob_y;
	float reload;
	float recoil_0;
	float recoil_speed_0;
	float recoil_1;
	float recoil_speed_1;
	float posture = 1.0;
};

struct game_gun_rig {
	float3 rotation;
	float  turn_speed;
	float  turn_speed_x;
};
