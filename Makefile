# TODO: edit MY_MODULES to list modules in src/lib build into your project
# TODO: edit APPLICATION to name of project application from src/apps
# TODO: edit TEST to name of unit test program from src/tests

MY_MODULES = project-module.o

# Targets for this makefile
APPLICATION = build/project-app.bin
TEST 	    = build/project-tests.bin

all: $(APPLICATION) $(TEST)

# Object files needed to build the application binary.
OBJECTS = $(addprefix build/, $(MY_MODULES) start.o cstart.o)

# Flags for compile and link
export warn = -Wall -Wpointer-arith -Wwrite-strings -Werror \
        -Wno-error=unused-function -Wno-error=unused-variable \
        -fno-diagnostics-show-option
export freestanding = -ffreestanding -nostdinc \
		-isystem $(shell arm-none-eabi-gcc -print-file-name=include)
CFLAGS	= -I$(CS107E)/include -Og -g -std=c99 $$warn $$freestanding
CFLAGS += -mapcs-frame -fno-omit-frame-pointer -mpoke-function-name
LDFLAGS	= -nostdlib -T src/boot/memmap -L$(CS107E)/lib
LDLIBS 	= -lpi -lgcc

# Rules and recipes for all build steps

# Extract binary from elf
build/%.bin: build/%.elf | build
	arm-none-eabi-objcopy $< -O binary $@

# Link objects into elf executable
build/%.elf: build/%.o $(OBJECTS) | build
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compile C file to object
build/%.o: %.c | build
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

# Assemble asm to object
build/%.o: %.s | build
	arm-none-eabi-as $< -o $@

# Disassemble object file to asm listing
build/%.list: build/%.o | build
	arm-none-eabi-objdump --no-show-raw-insn -d $< > $@

# Create build directory
build:
	mkdir -p build

# Build and run the application binary
run: $(APPLICATION)
	rpi-run.py -p $<

# Build and run the test binary
test: $(TEST)
	rpi-run.py -p $<

# Remove the build directory (i.e. all the binary files).
clean:
	rm -rf build

# The section below allows organizing files in subdirectories
# source files stored in src/, build products in build/ and so on.
# order-only prerequisite ensures build directory is created on demand
# https://www.cmcrossroads.com/article/making-directories-gnu-make

# Use vpath to search for .c and .s files
# https://www.cmcrossroads.com/article/basics-vpath-and-vpath
vpath %.c src/apps src/boot src/lib src/tests
vpath %.s src/apps src/boot src/lib src/tests

# Ensure that `make <file>` builds in `build/`
%.bin: build/%.bin ;
%.elf: build/%.elf ;
%.o: build/%.o ;
%.list: build/%.list ;

# Identify targets that don't create a file.
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: all clean run test %.bin %.elf %.list %.o

# Prevent make from removing intermediate build artifacts.
.PRECIOUS: build/%.bin build/%.elf build/%.list build/%.o

# Disable all built-in rules.
# https://www.gnu.org/software/make/manual/html_node/Suffix-Rules.html
.SUFFIXES:

define CS107E_ERROR_MESSAGE
ERROR - CS107E environment variable is not set.

Review instructions for properly configuring your shell.
https://cs107e.github.io/guides/install/userconfig#env

endef

ifndef CS107E
$(error $(CS107E_ERROR_MESSAGE))
endif

