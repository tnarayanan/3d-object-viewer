#ifndef GPU_PROGRAMS_H
#define GPU_PROGRAMS_H

#include <stddef.h>

/*
 * This module provides an interface to load and execute GPU programs.
 * It includes support for loading programs from memory and from files
 * on the Raspberry Pi's storage.
 *
 * Author: Tejas Narayanan <tejasn100@gmail.com>
 * Date: Mar 10 2021
 */

typedef struct {
	const char *name;
	unsigned int handle;
	char *program;
	size_t nbytes;
} gpu_program_t;

void gpu_programs_init(void);

/*
 * `gpu_program_add`
 *
 * Add a program from memory to the GPU.
 *
 * @param name		the name to refer to this program by
 * @param program	a pointer to first instruction of the program
 * @param nbytes	the number of bytes in the program
 *
 * @return			a pointer to a gpu_program_t referring to the program
 */
gpu_program_t *gpu_program_add(const char *name, char *program, size_t nbytes);

/*
 * `gpu_program_add_from_file`
 *
 * Add a program from a file to the GPU.
 *
 * @param name		the name to refer to this program by
 * @param program	the filepath of the program file in the Raspberry Pi's storage	
 *
 * @return			a pointer to a gpu_program_t referring to the program
 */
gpu_program_t *gpu_program_add_from_file(const char *name, const char *filepath);

/*
 * `gpu_program_run`
 *
 * Runs a previously-loaded program on the GPU. 
 *
 * @param name	the name to of the program to run
 * @param r0	optional parameter to program
 * @param r1	optional parameter to program
 * @param r2	optional parameter to program
 * @param r3	optional parameter to program
 * @param r4	optional parameter to program
 * @param r5	optional parameter to program
 *
 * @return		the output of the program
 */
unsigned int gpu_program_run(const char *name, unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3, unsigned int r4, unsigned int r5);

/*
 * `gpu_program_run_no_params`
 *
 * Runs a previously-loaded program on the GPU with no parameters.
 *
 * @param name	the name to of the program to run
 *
 * @return		the output of the program
 */
unsigned int gpu_program_run_no_params(const char *name);

#endif
