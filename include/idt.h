#ifndef IDT_H
#define IDT_H

#include "type.h"

struct IDT
{
  u16 base_low;  // lower 16 bits 0-15 of the address to jump to when this interrupt fires
  u16 segment_selector;  // code segment selector in GDT
  u8  zero;  // unused, always be zero
  u8  type;  // types trap, interrupt gates
  u16 base_high;  // upper 16 bits 16-31 of the address to jump to
} __attribute__((packed));


struct IDT_PTR
{
   u16 limit_size;  // limit size of all IDT segments
   struct IDT* base_address;  // base address of the first IDT segment
} __attribute__((packed));

extern struct IDT idt_entries[16];
extern struct IDT_PTR idt_first;

extern void init_idt();

#endif
