#pragma once

#include <zed/xmath.h>

//

// 8 feet per tile in meters
const float wolf_scale = 2.4384;

enum wolf_compass_4 {
	wolf_4e = 0,
	wolf_4n = 1,
	wolf_4w = 2,
	wolf_4s = 3,
};

enum wolf_compass_8 {
	wolf_8e  = 0,
	wolf_8ne = 1,
	wolf_8n  = 2,
	wolf_8nw = 3,
	wolf_8w  = 4,
	wolf_8sw = 5,
	wolf_8s  = 6,
	wolf_8se = 7,
};

//

struct wolf_cell {
	float color;
	float t;
	float d;
	int   c;
	int   a;
	int   s;
};

struct wolf_sprite {
	float3 position;
	int color;
};

struct wolf_enemy {
	float3 position;
	int color;
	int face;
	int frame;
};

struct wolf_t {
	wolf_cell   grid[64 * 64] = {};
	wolf_sprite sprite[1024]  = {};
	int         sprite_i;
	wolf_enemy  enemy[1024]   = {};
	int         enemy_i;
} wolf;

int frame_dead = 5;

struct wolf_pc_t {
	float3 position;
} wolf_pc;

enum wolf_item {
	wolf_item_food_dog     = 29 - 23,
	wolf_item_key_gold     = 43 - 23,
	wolf_item_key_silver   = 44 - 23,
	wolf_item_food         = 47 - 23,
	wolf_item_ifak         = 48 - 23,
	wolf_item_ammo         = 49 - 23,
	wolf_item_gun_mach     = 50 - 23,
	wolf_item_gun_mini     = 51 - 23,
	wolf_item_loot_cross   = 52 - 23,
	wolf_item_loot_chalice = 53 - 23,
	wolf_item_loot_chest   = 54 - 23,
	wolf_item_loot_crown   = 55 - 23,
	wolf_item_extra_life   = 56 - 23,
};

enum wolf_object {
	wolf_object_start_n       = 19,
	wolf_object_start_e       = 20,
	wolf_object_start_s       = 21,
	wolf_object_start_w       = 22,

	wolf_object_pool_water    = 23,
	wolf_object_oil_drum      = 24,
	wolf_object_table_chairs  = 25,
	wolf_object_floor_lamp    = 26,
	wolf_object_chandelier    = 27,
	wolf_object_skeleton_hang = 28,
	wolf_object_food_dog      = 29,
	wolf_object_column_white  = 30,
	wolf_object_plant_green   = 31,
	wolf_object_skeleton      = 32,
	wolf_object_sink          = 33,
	wolf_object_plant_brown   = 34,
	wolf_object_vase          = 35,
	wolf_object_table         = 36,
	wolf_object_ceiling_light = 37,
	wolf_object_junk_brown    = 38,
	wolf_object_armor         = 39,
	wolf_object_cage_empty    = 40,
	wolf_object_cage_skeleton = 41,
	wolf_object_bones_0       = 42,
	wolf_object_key_gold      = 43,
	wolf_object_key_silver    = 44,
	wolf_object_bed           = 45,
	wolf_object_basket        = 46,
	wolf_object_food          = 47,
	wolf_object_ifak          = 48,
	wolf_object_ammo          = 49,
	wolf_object_gun_mach      = 50,
	wolf_object_gun_mini      = 51,
	wolf_object_loot_cross    = 52,
	wolf_object_loot_chalice  = 53,
	wolf_object_loot_chest    = 54,
	wolf_object_loot_crown    = 55,
	wolf_object_extra_life    = 56,
	wolf_object_bones_blood   = 57,
	wolf_object_barrel        = 58,
	wolf_object_well_water    = 59,
	wolf_object_well_empty    = 60,
	wolf_object_pool_blood    = 61,
	wolf_object_flag          = 62,
	wolf_object_aardwolf      = 63,
	wolf_object_bones_1       = 64,
	wolf_object_bones_2       = 65,
	wolf_object_bones_3       = 66,
	wolf_object_junk_blue     = 67,
	wolf_object_stove         = 68,
	wolf_object_rack          = 69,
	wolf_object_vines         = 70,

	//

	wolf_object_turn_e  =  90,
	wolf_object_turn_ne =  91,
	wolf_object_turn_n  =  92,
	wolf_object_turn_nw =  93,
	wolf_object_turn_w  =  94,
	wolf_object_turn_sw =  95,
	wolf_object_turn_s  =  96,
	wolf_object_turn_se =  97,

	//

	wolf_object_door_secret =  98,
	wolf_object_door_final  =  99,

	//

	wolf_object_guard_0        = 108,
	wolf_object_guard_0_idle_e = 108,
	wolf_object_guard_0_idle_n = 109,
	wolf_object_guard_0_idle_w = 110,
	wolf_object_guard_0_idle_s = 111,
	wolf_object_guard_0_move_e = 112,
	wolf_object_guard_0_move_n = 113,
	wolf_object_guard_0_move_w = 114,
	wolf_object_guard_0_move_s = 115,

	//

	wolf_object_officer_0_idle_e = 116,
	wolf_object_officer_0_idle_n = 117,
	wolf_object_officer_0_idle_w = 118,
	wolf_object_officer_0_idle_s = 119,
	wolf_object_officer_0_move_e = 120,
	wolf_object_officer_0_move_n = 121,
	wolf_object_officer_0_move_w = 122,
	wolf_object_officer_0_move_s = 123,

	//

	wolf_object_guard_dead = 124,

	//

	wolf_object_ss_0_idle_e = 126,
	wolf_object_ss_0_idle_n = 127,
	wolf_object_ss_0_idle_w = 128,
	wolf_object_ss_0_idle_s = 129,
	wolf_object_ss_0_move_e = 130,
	wolf_object_ss_0_move_n = 131,
	wolf_object_ss_0_move_w = 132,
	wolf_object_ss_0_move_s = 133,

	//

	wolf_object_dog_0_move_e = 138,
	wolf_object_dog_0_move_n = 139,
	wolf_object_dog_0_move_w = 140,
	wolf_object_dog_0_move_s = 141,

	//

	wolf_object_guard_1_idle_e = 144,
	wolf_object_guard_1_idle_n = 145,
	wolf_object_guard_1_idle_w = 146,
	wolf_object_guard_1_idle_s = 147,
	wolf_object_guard_1_move_e = 148,
	wolf_object_guard_1_move_n = 149,
	wolf_object_guard_1_move_w = 150,
	wolf_object_guard_1_move_s = 151,

	//

	wolf_object_officer_1_idle_e = 152,
	wolf_object_officer_1_idle_n = 153,
	wolf_object_officer_1_idle_w = 154,
	wolf_object_officer_1_idle_s = 155,
	wolf_object_officer_1_move_e = 156,
	wolf_object_officer_1_move_n = 157,
	wolf_object_officer_1_move_w = 158,
	wolf_object_officer_1_move_s = 159,

	//

	wolf_object_fake_hitler = 160,

	//

	wolf_object_ss_1_idle_e = 162,
	wolf_object_ss_1_idle_n = 163,
	wolf_object_ss_1_idle_w = 164,
	wolf_object_ss_1_idle_s = 165,
	wolf_object_ss_1_move_e = 166,
	wolf_object_ss_1_move_n = 167,
	wolf_object_ss_1_move_w = 168,
	wolf_object_ss_1_move_s = 169,

	//

	wolf_object_dog_1_move_e = 174,
	wolf_object_dog_1_move_n = 175,
	wolf_object_dog_1_move_w = 176,
	wolf_object_dog_1_move_s = 177,

	//

	wolf_object_hitler      = 178,
	wolf_object_fettgesicht = 179,

	//

	wolf_object_guard_2_idle_e = 180,
	wolf_object_guard_2_idle_n = 181,
	wolf_object_guard_2_idle_w = 182,
	wolf_object_guard_2_idle_s = 183,
	wolf_object_guard_2_move_e = 184,
	wolf_object_guard_2_move_n = 185,
	wolf_object_guard_2_move_w = 186,
	wolf_object_guard_2_move_s = 187,

	//

	wolf_object_officer_2_idle_e = 188,
	wolf_object_officer_2_idle_n = 189,
	wolf_object_officer_2_idle_w = 190,
	wolf_object_officer_2_idle_s = 191,
	wolf_object_officer_2_move_e = 192,
	wolf_object_officer_2_move_n = 193,
	wolf_object_officer_2_move_w = 194,
	wolf_object_officer_2_move_s = 195,

	//

	wolf_object_dr_schabbs  = 196,
	wolf_object_gretel      = 197,

	//

	wolf_object_ss_2_idle_e = 198,
	wolf_object_ss_2_idle_n = 199,
	wolf_object_ss_2_idle_w = 200,
	wolf_object_ss_2_idle_s = 201,
	wolf_object_ss_2_move_e = 202,
	wolf_object_ss_2_move_n = 203,
	wolf_object_ss_2_move_w = 204,
	wolf_object_ss_2_move_s = 205,

	//

	wolf_object_dog_2_move_e = 210,
	wolf_object_dog_2_move_n = 211,
	wolf_object_dog_2_move_w = 212,
	wolf_object_dog_2_move_s = 213,

	//

	wolf_object_hans       = 214,
	wolf_object_giftmacher = 215,

	//

	wolf_object_mutant_0_idle_e = 216,
	wolf_object_mutant_0_idle_n = 217,
	wolf_object_mutant_0_idle_w = 218,
	wolf_object_mutant_0_idle_s = 219,
	wolf_object_mutant_0_move_e = 220,
	wolf_object_mutant_0_move_n = 221,
	wolf_object_mutant_0_move_w = 222,
	wolf_object_mutant_0_move_s = 223,

	//


	wolf_object_ghost_red    = 224,
	wolf_object_ghost_yellow = 225,
	wolf_object_ghost_pink   = 226,
	wolf_object_ghost_blue   = 227,

	//

	wolf_object_mutant_1_idle_e = 234,
	wolf_object_mutant_1_idle_n = 235,
	wolf_object_mutant_1_idle_w = 236,
	wolf_object_mutant_1_idle_s = 237,
	wolf_object_mutant_1_move_e = 238,
	wolf_object_mutant_1_move_n = 239,
	wolf_object_mutant_1_move_w = 240,
	wolf_object_mutant_1_move_s = 241,

	//

	wolf_object_mutant_2_idle_e = 252,
	wolf_object_mutant_2_idle_n = 253,
	wolf_object_mutant_2_idle_w = 254,
	wolf_object_mutant_2_idle_s = 255,
	wolf_object_mutant_2_move_e = 256,
	wolf_object_mutant_2_move_n = 257,
	wolf_object_mutant_2_move_w = 258,
	wolf_object_mutant_2_move_s = 259,
};

enum wolf_enemy_type {
	wolf_enemy_guard       =  0,
	wolf_enemy_officer     =  1,
	wolf_enemy_ss          =  2,
	wolf_enemy_dog         =  3,
	wolf_enemy_fake_hitler =  4,
	wolf_enemy_mutant      =  5,
	wolf_enemy_ghost       =  6,

	//

	wolf_enemy_hitler      =  7,
	wolf_enemy_fettgesicht =  8,
	wolf_enemy_dr_schabbs  =  9,
	wolf_enemy_gretel      = 10,
	wolf_enemy_hans        = 11,
	wolf_enemy_giftmacher  = 12,
};
