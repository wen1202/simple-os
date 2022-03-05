
# sudo apt-get install g++ binutils libc6-dev-i386
# sudo apt-get install VirtualBox grub-legacy xorriso

GCCPARAMS = $  -std=gnu99 -ffreestanding -m32 -O2 -Wall -Wextra -Iinclude
ASPARAMS = --32
LDPARAMS = -m elf_i386

objects = obj/loader.o \
          obj/kernel.o \
	  obj/gdt.o \
	  obj/font.o \
	  obj/idt.o \
	  obj/isr.o \
	  obj/load_idt.o

run: mykernel.iso
obj/%.o: src/%.c
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<


obj/%.o: src/%.asm
	mkdir -p $(@D)
	nasm -felf32   -o $@ $<
mykernel.bin: lk.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

mykernel.iso: mykernel.bin
	rm -rf iso
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp mykernel.bin iso/boot/mykernel.bin
	
	echo ''		  > iso/boot/grub/grub.cfg
	echo 'set timeout=0'                     >> iso/boot/grub/grub.cfg 
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo 'set gfxmode=800x600x32'		 >> iso/boot/grub/grub.cfg
	echo 'set gfxpayload=keep'               >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/mykernel.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue -o os2.iso iso
	

	

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

.PHONY: clean
clean:
	rm -rf obj mykernel.bin mykernel.iso
