#include<multiboot.h>
#include<gdt.h>
#include<type.h>
#define GDT_LENGTH 5

    #define red   0xFF0000
    #define green 0x00FF00
    #define blue  0x0000FF
    #define greengreen 0xa8e6cf
    #define gray 0xd9d5cd 
    #define black 0x000000
    #define white 0xFFFFFF
void puts(char *s);


gdt_entry_t gdt_entries[GDT_LENGTH];
gdt_ptr_t gdt_ptr;
static void gdt_set_gate(i32 num, u32 base, u32 limit, u8 access, u8 gran);

extern u32 stack;




void kernelMain(unsigned int* addr){
    
    multiboot_info_t *mbi;
    mbi = (multiboot_info_t *) addr;
    u32 width = mbi->framebuffer_width;
    u32 height = mbi->framebuffer_height;
    u32 pitch=mbi->framebuffer_pitch;
    unsigned int *screen  = (unsigned int*)mbi->framebuffer_addr;
    typedef struct {
    unsigned int magic;
    unsigned int version;
    unsigned int headersize;
    unsigned int flags;
    unsigned int numglyph;
    unsigned int bytesperglyph;
    unsigned int height;
    unsigned int width;
    unsigned char glyphs;
} __attribute__((packed)) psf2_t;
extern volatile unsigned char _binary_font_psf_start;


void puts(char *s)
{
    psf2_t *font = (psf2_t*)&_binary_font_psf_start;
    int x,y,kx=0,line,mask,offs,px,py;
    int bpl=(font->width+7)/8;
    while(*s) {
        unsigned char *glyph = (unsigned char*)&_binary_font_psf_start + font->headersize + 
            (*s>0&&*s<font->numglyph?*s:0)*font->bytesperglyph;
        offs = (kx * (font->width+1) * 4);
        int row=0;

        for(y=0;y<font->height;y++) {
            line=offs; mask=1<<(font->width-1);
            for(x=0;x<font->width;x++) {
                *((unsigned int*)((unsigned long int)screen+line))=((int)*glyph) & (mask)?0xa8e6cf:0;
                mask>>=1; line+=4;
            }
            *((unsigned int*)((unsigned long int)screen+line))=0; glyph+=bpl; offs+=pitch;
        }
        s++; kx++;
    }
}
    
    init_gdt();
    puts("welcom % world!><???{{{{{{{{{"); 
   

    
}

// 初始化全局描述符表
void init_gdt()
{
	
	gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH - 1;
	gdt_ptr.base = (u32)&gdt_entries;

	
	gdt_set_gate(0, 0, 0, 0, 0);             
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 	// 指令段
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); 	// 数据段
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); 	// 用户模式代码段
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); 	// 用户模式数据段

	
	gdt_flush((u32)&gdt_ptr);
}


typedef struct
{
	uint16_t limit_low;     // 段界限   15～0
	uint16_t base_low;      // 段基地址 15～0
	uint8_t  base_middle;   // 段基地址 23～16
	uint8_t  access;        // 段存在位、描述符特權级、描述符类型、描述符子类别
	uint8_t  granularity; 	// 其他標誌、段界限 19～16
	uint8_t  base_high;     // 段基地址 31～24
} __attribute__((packed)) gdt_entry_t;
*/
static void gdt_set_gate(i32 num, u32 base, u32 limit, u8 access, u8 gran)
{
	gdt_entries[num].base_low     = (base & 0xFFFF);
	gdt_entries[num].base_middle  = (base >> 16) & 0xFF;
	gdt_entries[num].base_high    = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low    = (limit & 0xFFFF);
	gdt_entries[num].granularity  = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access       = access;
}


