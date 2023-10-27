objects=asm.bin asm.elf asm.o
asm.bin:asm.elf
	arm-linux-objcopy -O binary -S $< $@
asm.elf:asm.o
	arm-linux-ld -Ttext 0x30000000 -o $@ $^ 
%.o:%.s
	arm-linux-gcc -c -o $@ $<
clean:
	rm -f $(objects)
