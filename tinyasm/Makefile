NAME=gpu_blink

$(NAME).bin: ../$(NAME).s ../build.c asm.c
	gcc ../build.c -o build
	./build

clean:
	rm *.bin build
