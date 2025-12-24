#include <zed.h>

#include <xxhash.h>
#pragma comment( lib, "xxhash.lib" )
#include <xxhashct/xxh64.hpp>

uint64_t zed_hash( string text ) {
	uint64_t seed = 0;
	uint64_t hash = XXH64( text, strlen( text ), seed );
	return hash;
}
