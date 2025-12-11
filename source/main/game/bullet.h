#pragma once

struct game_bullet {
	matrix alignas(32) m;
	float3 alignas(16) p0;
	// float3 alignas(16) r;
	float t;
};

struct game_shine {
	matrix alignas(32) m;
	float3 alignas(16) p0;
	// float3 alignas(16) r;
	float t;
};

struct game_flash {
	matrix alignas(32) m;
};
