#pragma once

enum game_ammo_type {
	ammo_type_none = 0,

	ammo_type_9_19mm,
	ammo_type_45acp,
	ammo_type_11_23mm = ammo_type_45acp,

	ammo_type_556_45mm,
	ammo_type_762_39mm,
	ammo_type_762_51mm,

	ammo_type_30_06,
	ammo_type_762_63mm = ammo_type_30_06,
};

enum game_ammo {
	ammo_none = 0,
	ammo_9mm,
	ammo_45acp,
	ammo_556_45mm,
	ammo_762_39mm,
	ammo_762_51mm,
	ammo_762_63mm,
	ammo_12ga_bird,
	ammo_12ga_buck,
	ammo_12ga_slug,
	ammo_max
};

string ammo_name( game_ammo ammo ) {
	switch( ammo ) {
		case ammo_none     : return "";
		case ammo_9mm      : return "9mm";
		case ammo_45acp    : return "45ACP";
		case ammo_556_45mm : return "556";
		case ammo_762_39mm : return "762S";
		case ammo_762_51mm : return "762";
		case ammo_762_63mm : return "30-06";
		case ammo_12ga_bird: return "BIRD";
		case ammo_12ga_buck: return "BUCK";
		case ammo_12ga_slug: return "SLUG";
	}

	return "--";
}
