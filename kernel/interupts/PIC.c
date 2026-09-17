#include <stdint.h>
#include <stddef.h>

#define PIC_MASTER = 0x20
#define PIC_SLAVE = 0xA0
#define PIC_MASTER_COMMAND = PIC_MASTER
#define PIC_SLAVE_COMMAND = PIC_SLAVE
#define PIC_MASTER_DATA = PIC_MASTER + 1
#define PIC_SLAVE_DATA = PIC_SLAVE + 1

void init_pic(void) {
    
}

static void inline out_bound(uint16_t port, uint8_t value) {
    
}