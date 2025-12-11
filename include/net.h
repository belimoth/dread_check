#pragma once

#include <zed.h>

#include <enet/enet.h>
#pragma comment( lib, "enet.lib" )
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "winmm.lib" )

struct {
	ENetPeer *peer;
	ENetHost *client;
	ENetHost *server;

	ENetAddress address;
} net;

void net_init() {
	// todo assert result == 0
	enet_initialize();
}

void net_init_server() {
	net.address.host = ENET_HOST_ANY;
	net.address.port = 4444;

	// note 32 clients, 2 channels
	net.server = enet_host_create( &net.address, 32, 2, 0, 0 );
}

void net_init_client() {
	net.client = enet_host_create( 0, 1, 2, 0, 0 );
}

void net_step() {
	ENetEvent event;

	while ( enet_host_service( net.client, &event, 0 ) > 0 ) {
		switch ( event.type ) {
			case ENET_EVENT_TYPE_CONNECT: {
				break;
			}

			case ENET_EVENT_TYPE_DISCONNECT: {
				break;
			}

			case ENET_EVENT_TYPE_RECEIVE: {
				enet_packet_destroy( event.packet );
				break;
			}
		}
	}
}

void net_send_reliable( handle data, uint size ) {
	ENetPacket *packet = enet_packet_create( data, size, ENET_PACKET_FLAG_RELIABLE );
	enet_peer_send( net.peer, 0, packet );
	enet_host_flush( net.server ); // note was "host"
}

void net_step_1() {
	ENetEvent event;

	while ( enet_host_service( net.client, &event, 1000 ) > 0 ) {
		switch ( event.type ) {
			case ENET_EVENT_TYPE_CONNECT:
				// app_debug_say(
				// 	"A new client connected from %x:%u.\n",
				// 	event.peer->address.host,
				// 	event.peer->address.port
				// );

				event.peer->data = "Client information";

				break;

			case ENET_EVENT_TYPE_RECEIVE:
				// app_debug_say(
				// 	"A packet of length %zu containing %s was received from %s on channel %i.\n",
				// 	event.packet->dataLength,
				// 	(char *)event.packet->data,
				// 	(char *)event.peer->data,
				// 	event.channelID
				// );

				enet_packet_destroy( event.packet );

				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				// app_debug_say( "%s disconnected.\n", (char *)event.peer->data );

				event.peer->data = {};

				break;
		}
	}
}
