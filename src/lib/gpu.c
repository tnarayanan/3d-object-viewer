#include "gpu.h"
#include "mailbox.h"
#include "assert.h"
#include <stdbool.h>
#include <stdarg.h>

/*unsigned int gpu_mem_alloc(size_t nbytes, size_t align, unsigned int flags) {
    int i = 0;
    unsigned int request[32];
    request[i++] = 0; // size
    request[i++] = 0;

    request[i++] = 0x3000c; // tag
    request[i++] = 12; // size of buffer
    request[i++] = 12; // size of data
    request[i++] = nbytes;
    request[i++] = align;
    request[i++] = flags;

    request[i++] = 0;
    
}*/

static unsigned int send_mailbox_request(unsigned int tag, int argc, ...) {
    va_list args;
    va_start(args, argc);

    int i = 0;
    volatile unsigned int request[32] __attribute__ ((aligned(16)));
    request[i++] = 0; // size
    request[i++] = 0;

    request[i++] = tag; // tag
    request[i++] = argc * sizeof(unsigned int); // size of buffer
    request[i++] = argc * sizeof(unsigned int); // size of data

    for (int k = 0; k < argc; k++) {
        request[i++] = va_arg(args, unsigned int);
    }

    request[i++] = 0;

    request[0] = i * sizeof(unsigned int); // set size

    bool success = mailbox_write(MAILBOX_TAGS_ARM_TO_VC, (unsigned int) &request);
    assert(success);
    mailbox_read(MAILBOX_TAGS_ARM_TO_VC);
    assert(request[1] == 0x80000000);
    return request[5];
}

unsigned int gpu_get_serial_num(void) {
    return send_mailbox_request(0x10004, 2, 0, 0);
}

unsigned int gpu_mem_alloc(size_t nbytes, size_t align, unsigned int flags) {
    return send_mailbox_request(0x3000c, 3, nbytes, align, flags);
}

unsigned int gpu_mem_free(unsigned int handle) {
    return send_mailbox_request(0x3000f, 1, handle);
}

void *gpu_mem_lock(unsigned int handle) {
    return (void *) send_mailbox_request(0x3000d, 1, handle);
}

unsigned int gpu_mem_unlock(unsigned int handle) {
    return send_mailbox_request(0x3000e, 1, handle);
}

unsigned int gpu_execute_code(unsigned int code, unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3, unsigned int r4, unsigned int r5) {
    return send_mailbox_request(0x30010, 7, code, r0, r1, r2, r3, r4, r5);
}
