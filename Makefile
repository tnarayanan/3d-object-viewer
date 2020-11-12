# TODO: replace `<your-project-moduleN>` with the modules that you implement for
# your project.
MY_MODULES = <your-project-module1>.o \
			 <your-project-module2>.o \
			 # ...


# Paths to binaries.
# TODO: replace `<your-project-app>` with the name of your project's
# application (suffix excluded).
# TODO: replace `<your-project-tests>` with the name of your project's tests
# (suffix excluded).
APPLICATION = build/bin/<your-project-app>.bin
TEST 		= build/bin/<your-project-tests>.bin

# Use order-only prerequisite to create the build directory.
# https://www.cmcrossroads.com/article/making-directories-gnu-make
# This comment is floating all alone because a previous edition of this
# Makefile had a macro for the build directory, but that has since been
# removed.

# Object files needed to build the application binary.
OBJECTS = $(addprefix build/obj/, $(MY_MODULES) start.o cstart.o)

# C compiler.
CFLAGS_EXTRA = -Werror
CFLAGS 	= -I$(CS107E)/include -Iinclude -Og -g -Wall -std=c99 -ffreestanding $(CFLAGS_EXTRA)
CFLAGS += -mapcs-frame -fno-omit-frame-pointer -mpoke-function-name -Wpointer-arith
LDFLAGS	= -nostdlib -T src/boot/memmap -L$(CS107E)/lib
LDLIBS 	= -lpi -lgcc # TODO: link against any other libraries that you need for your project.

# Search for .c and .s files in the src directory's subdirectories.
# https://www.cmcrossroads.com/article/basics-vpath-and-vpath
vpath %.c src/apps src/boot src/lib src/tests
vpath %.s src/apps src/boot src/lib src/tests


all: $(APPLICATION) $(TEST) 

# Ensure that `make <file>.<ext>` builds `<file>.<ext>` in `build/<ext>/`.
%.bin: build/bin/%.bin ;
%.elf: build/elf/%.elf ;
%.o: build/obj/%.o ;
%.list: build/list/%.list ;

# Build *.bin from *.elf.
build/bin/%.bin: build/elf/%.elf | build
	arm-none-eabi-objcopy $< -O binary $@

# Build *.elf from *.o.
build/elf/%.elf: build/obj/%.o $(OBJECTS) | build
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

# Build *.o from *.c.
build/obj/%.o: %.c | build
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

# Build *.o from *.s.
build/obj/%.o: %.s | build
	arm-none-eabi-as $< -o $@

# Build *.list from *.o.
build/list/%.list: build/obj/%.o | build
	arm-none-eabi-objdump --no-show-raw-insn -d $< > $@

# Create build directory and its subdirectories.
build:
	mkdir -p build/obj build/elf build/bin build/list
	
# Build and run the application binary.
install: $(APPLICATION) | build
	rpi-install.py -p $<

# Build and run the test binary.
test: $(TEST) | build
	rpi-install.py -p $<

# Remove the build directory (i.e. all the binary files).
clean:
	rm -rf build

# Identify targets that don't create a file.
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: all clean install test %.bin %.elf %.list %.o

# Prevent make from removing intermediate build artifacts.
.PRECIOUS: build/bin/%.bin build/elf/%.elf build/list/%.list build/obj/%.o

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
