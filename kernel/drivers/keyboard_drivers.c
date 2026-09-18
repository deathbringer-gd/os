
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
#define ENABLE_SCANNING 0xF3 // enables keyboard sending scancodes
#