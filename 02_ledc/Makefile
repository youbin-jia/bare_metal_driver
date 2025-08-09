objs := start.o main.o

ledc.bin:$(objs)
	arm-none-linux-gnueabihf-ld -Timx6ul.lds -o ledc.elf $^
	arm-none-linux-gnueabihf-objcopy -O binary -S ledc.elf $@
	arm-none-linux-gnueabihf-objdump -D -m arm ledc.elf > ledc.dis
	
%.o:%.s
	arm-none-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<
	
%.o:%.S
	arm-none-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<
	
%.o:%.c
	arm-none-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<
	
clean:
	rm -rf *.o ledc.bin ledc.elf ledc.dis
	
	
