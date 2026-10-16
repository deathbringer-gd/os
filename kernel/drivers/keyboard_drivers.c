#include <stdint.h>

//for all responses, ACK = 0xFA and Resend = 0xFE
#define TURN_ON_LEDS_COMMAND 0xED // set 0 - scroll lock, set 1 - numlock, set 2 - capslock
/*
set 0 - get current scancode set, 1-3 - get scancode set 1-3
0xFA (ACK) or 0xFE (Resend) if scan code is being set
0xFA (ACK) then the scan code set number, or 0xFE (Resend) if you're getting the scancode.

scancode set 1 - 0x43
scancode set 2 - 0x41
scancode set 3 - 0x3F
*/
#define GET_SET_CURRENT_SCANCODE 0xF0
#define ECHO 0xEE // response 0xEE = echo, good for device removal detection and diagnostics
#define IDENTIFY_KEYBOARD 0xF2 // response ACK then sometimes more ID bytes
#define SET_KEY_REPEAT_AND_DELAY_BEFORE_REPEAT 0xF3
#define ENABLE_SCANNING 0xF4
#define DISABLE_SCANNING 0xF5 
#define SET_DEFAULT_PARAMS 0xF6
#define SET_ALL_KEYS_AUTOREPEAT_ONLY 0xF7
#define SET_ALL_KEYS_MAKE_RELEASE 0xF8
#define SET_ALL_KEYS_MAKE_ONLY 0xF9
#define SET_ALL_KEYS_AUTOREPEAT_MAKE_RELEASE 0xFA
#define SET_SPECIFIC_KEY_AUTOREPEAT_ONLY 0xFB //send scancode key with it
#define SET_SPECIFIC_KEY_MAKE_RELEASE_ONLY 0xFC //send scancode key with it
#define SET_SPECIFIC_KEY_MAKE_ONLY 0xFD //send scancode key with it
#define RESEND_LAST_BYTE 0xFE
#define RESET_AND_START_SELF_TEST 0xFF


static inline uint8_t in_bound(uint16_t port) {
	uint8_t value;

	__asm__ volatile ("in_bound %1, %0" : "=a"(value) : "Nd"(port));

	return value;
}

