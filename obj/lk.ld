ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{

	. = 1M;
 

	.text BLOCK(4K) : ALIGN(4K)
	{
	        *(.multiboot)
		*(.text)
		*(.rodata)
	}
 
	
	

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
 

	.bss BLOCK(4K) : ALIGN(4K)
	{
		
		*(.bss)
	}
 

}
