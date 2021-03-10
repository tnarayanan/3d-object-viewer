#ifndef GPU_PROGRAMS_H
#define GPU_PROGRAMS_H

#include <stddef.h>

typedef struct {
	const char *name;
	unsigned int handle;
	char *program;
	size_t nbytes;
} gpu_program_t;

void gpu_programs_init(void);

gpu_program_t *gpu_program_add(const char *name, char *program, size_t nbytes);

gpu_program_t *gpu_program_add_from_file(const char *name, const char *filepath);

unsigned int gpu_program_run(const char *name, unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3, unsigned int r4, unsigned int r5);

unsigned int gpu_program_run_no_params(const char *name);

#endif
