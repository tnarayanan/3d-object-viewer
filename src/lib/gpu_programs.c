#include "gpu_programs.h"
#include "gpu.h"
#include "strings.h"
#include "malloc.h"
#include "printf.h"
#include "assert.h"
#include "ff.h"

static gpu_program_t *all_programs[64];
static int num_programs = 0;
static FATFS fs;

void gpu_programs_init(void) {
    f_mount(&fs, "", 0);
}

gpu_program_t *gpu_program_add(const char *name, char *program, size_t nbytes) {
    for (int i = 0; i < num_programs; i++) {
        gpu_program_t *curr_prog = all_programs[i];
        if (strcmp(curr_prog->name, name) == 0) {
            printf("\nERROR: GPU program with name '%s' already exists.\n", name);
            assert(0); // end program execution
            return NULL;
        }
    }

    gpu_program_t *prog = malloc(sizeof(*prog));
    prog->name = name;
    prog->nbytes = nbytes;

    unsigned int handle = gpu_mem_alloc(nbytes, 8, 4);
    char *program_addr = (char *) gpu_mem_lock(handle);

    prog->program = program_addr;
    prog->handle = handle;

    memcpy(program_addr, program, nbytes);
    all_programs[num_programs++] = prog;

    return prog;
}

gpu_program_t *gpu_program_add_from_file(const char *name, const char *filepath) {
    FIL fil;
    FRESULT fr;
    
    fr = f_open(&fil, filepath, FA_READ);
    assert(!fr);
    size_t nbytes = f_size(&fil);
    
    char *program = malloc(nbytes);
    for (int i = 0; i < nbytes; i++)
        f_read(&fil, &program[i], 1, NULL);

    gpu_program_t *prog = gpu_program_add(name, program, nbytes);
    free(program);
    return prog;
}

unsigned int gpu_program_run(const char *name, unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3, unsigned int r4, unsigned int r5) {
    for (int i = 0; i < num_programs; i++) {
        gpu_program_t *prog = all_programs[i];
        if (strcmp(prog->name, name) == 0) {
            return gpu_execute_code((unsigned int) prog->program, r0, r1, r2, r3, r4, r5);
        }
    }
    printf("\nERROR: no such GPU program named '%s'. Did you forget to call gpu_program_add?\n", name);
    assert(0); // end program execution
    return 1;
}

unsigned int gpu_program_run_no_params(const char *name) {
    return gpu_program_run(name, 0, 0, 0, 0, 0, 0);
}
