#pragma once

struct game_player_vitals {
	int health;
	int stress;
	int exertn;
	int nerves;
	int hunger;
	int thirst;
	int malady;
};

int cost_sprint  =  20; // 50; //   0; // 200;
int cost_jump    =  20; // 50; // 300;
int cost_jog_p   =   2;
int cost_jog_n   =  -2;
int cost_run     =   3;
int cost_walk    =  -1;
int rest_jog     = 100;
int cost_breath  =   2;
int nerves_ratio = 500;
int cost_skid    =   2;

int exertn_max = 1000;
