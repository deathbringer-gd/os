
//for all responses, ACK = 0xFA and Resend = 0xFE
#define TURN_ON_LEDS_COMMAND 0xED // set 0 - scroll lock, set 1 - numlock, set 2 - capslock
#define GET_SET_CURRENT_SCANCODE 0xF0 // set 0 - get current scancode set, 1-3 - get scancode set 1-3
#define ECHO 0xEE // response 0xEE = echo, good for device removal detection and diagnostics