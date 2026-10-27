#include <zed.h>

#include <zed/platform/windows.h>

#include <hidusage.h>

// https://docs.microsoft.com/en-us/windows-hardware/drivers/hid/hid-usages

void raw_input_init() {
	uint32_t flags = 0;

	// todo this causes "busy" cursor when cursor is visible
	// flags |= RIDEV_NO_LEGACY;

	RAWINPUTDEVICE rid[2] = {};

	rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	rid[0].usUsage     = HID_USAGE_GENERIC_MOUSE;
	rid[0].dwFlags     = flags;
	rid[0].hwndTarget  = 0;

	rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
	rid[1].usUsage     = HID_USAGE_GENERIC_KEYBOARD;
	rid[1].dwFlags     = flags;
	rid[1].hwndTarget  = 0;

	RegisterRawInputDevices( rid, 2, sizeof( rid[0] ) );
}

void raw_input_exit() {
	uint32_t flags = 0;

	flags |= RIDEV_REMOVE;

	RAWINPUTDEVICE rid[2] = {};
	rid[0].usUsagePage    = HID_USAGE_PAGE_GENERIC;
	rid[0].usUsage        = HID_USAGE_GENERIC_MOUSE;
	rid[0].dwFlags        = flags;
	rid[0].hwndTarget     = 0;

	rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
	rid[1].usUsage     = HID_USAGE_GENERIC_KEYBOARD;
	rid[1].dwFlags     = flags;
	rid[1].hwndTarget  = 0;

	RegisterRawInputDevices( rid, 2, sizeof( rid[0] ) );
}
