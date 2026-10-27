#pragma once

enum game_player_stance {
	stance_none = 0,

	stance_prone  = 1,
	stance_crawl  = 2,
	stance_crouch = 3,
	stance_stalk  = 4,
	stance_walk   = 5,
	stance_reach  = 6,

	stance_supine,
	stance_side_left,
	stance_side_right,

	stance_run,
	stance_jog,
	stance_jump,
	stance_skid,
	stance_trip,
	stance_sail,
	stance_fall,

	stance_slide_prone,
	stance_slide_supine,
	stance_slide_left,
	stance_slide_right,

	stance_dive_prone,
	stance_dive_supine,
	stance_dive_left,
	stance_dive_right,
};
