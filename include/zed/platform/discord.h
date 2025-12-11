#pragma once

#include <discord/discord_game_sdk.h>
#pragma comment( lib, "discord_game_sdk.dll.lib" )

struct zed_discord {
	struct zed_discord_app {
		struct IDiscordCore  *core;
		struct IDiscordUsers *users;
	} app;

	IDiscordCoreEvents events;
} discord;


void zed_discord_init() {
	DiscordCreateParams params = {};
	params.client_id  = 905933381362143233; // todo
	params.flags      = DiscordCreateFlags_Default;
	params.events     = &discord.events;
	params.event_data = &discord.app;

	DiscordCreate( DISCORD_VERSION, &params, &discord.app.core );
}
