#ifndef GPU_H
#define GPU_H

#include <stddef.h>

/*
 * This module provides an interface to communicate with the GPU.
 * It includes support for sending arbitrary requests to the GPU,
 * and also contains methods for commonly-used GPU requests as a
 * convenience.
 *
 * Author: Tejas Narayanan <tejasn100@gmail.com>
 * Date: Mar 10 2021
 */

/*
 * `gpu_send_mailbox_request`
 *
 * Send a mailbox request to the GPU with the given tag and arguments.
 *
 * @param tag	the tag associated with the request
 * @param argc	the number of arguments needed by the request
 * @param ...	variable arguments to the request. Must have exactly `argc` arguments
 *
 * @return		the output of the request
 */
unsigned int gpu_send_mailbox_request(unsigned int tag, int argc, ...);

/*
 * `gpu_mem_alloc`
 *
 * Allocates dynamic memory on the GPU. Must call gpu_mem_lock before
 * using memory.
 *
 * @param nbytes	number of bytes to allocate
 * @param align		alignment of the memory address
 * @param flags		memory allocation flags (see https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface#allocate-memory)
 *
 * @return			handle of the memory address
 */
unsigned int gpu_mem_alloc(size_t nbytes, size_t align, unsigned int flags);

/*
 * `gpu_mem_lock`
 *
 * Locks allocated dynamic memory buffer in-place on the GPU.
 * Must be called before modifying memory.
 *
 * @param handle	handle of the memory address to lock
 *
 * @return			a pointer to the memory address
 */
void *gpu_mem_lock(unsigned int handle);

/*
 * `gpu_mem_unlock`
 *
 * Unlocks allocated dynamic memory on the GPU. Must call gpu_mem_lock before next use.
 *
 * @param handle	handle of the memory address to unlock
 *
 * @return			status code (0 = success)
 */
unsigned int gpu_mem_unlock(unsigned int handle);

/*
 * `gpu_mem_free`
 *
 * Frees previously-allocated dynamic memory on the GPU.
 *
 * @param handle	handle of the memory address to free
 *
 * @return			status code (0 = success)
 */
unsigned int gpu_mem_free(unsigned int handle);

/*
 * `gpu_execute_code`
 *
 * Executes code at the given memory location on the GPU.
 *
 * @param code	memory address of first instruction of code
 * @param r0	optional parameter to program
 * @param r1	optional parameter to program
 * @param r2	optional parameter to program
 * @param r3	optional parameter to program
 * @param r4	optional parameter to program
 * @param r5	optional parameter to program
 *
 * @return		the output of the program
 */
unsigned int gpu_execute_code(unsigned int code, unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3, unsigned int r4, unsigned int r5);

/*
 * `gpu_get_serial_num`
 *
 * Get the serial number of the Raspberry Pi. Serves as a test function for GPU communication.
 *
 * @return	the serial number of the Raspberry Pi
 */
unsigned int gpu_get_serial_num(void);

#endif
