#pragma once

#include <zed.h>
// #include <zed/platform/curl.h>

#include <stdlib.h>

struct itch_t {
	char user[32];
} itch;

void itch_init() {
	string itch_key = getenv( "ITCHIO_API_KEY" );
	string url = "https://itch.io/api/1/jwt/me";
	// zed_curl_get( url, itch_key );
}

void itch_detect() {
	// todo
	// detect whether draugb has been installed with the itch app
	// detect whether draugb has been launched with the itch app
}
