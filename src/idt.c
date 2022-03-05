#include "idt.h"
#include "isr.h"

struct IDT idt_entries[16];
struct IDT_PTR idt_first;

extern void load_idt(struct IDT*);

void set_idt_gate(int intnum, u32 isr)
{
  idt_entries[intnum].base_low = isr & 0xffff;
  idt_entries[intnum].segment_selector = 0x08;
  idt_entries[intnum].zero = 0;
  idt_entries[intnum].type = 0x8E;
  idt_entries[intnum].base_high = (isr >> 16) & 0xffff;
}

void init_idt()
{
  set_idt_gate(0, (u32)isr_0);
  set_idt_gate(1, (u32)isr_1);
  set_idt_gate(2, (u32)isr_2);
  set_idt_gate(3, (u32)isr_3);
  set_idt_gate(4, (u32)isr_4);
  set_idt_gate(5, (u32)isr_5);
  set_idt_gate(6, (u32)isr_6);
  set_idt_gate(7, (u32)isr_7);
  set_idt_gate(8, (u32)isr_8);
  set_idt_gate(9, (u32)isr_9);
  set_idt_gate(10, (u32)isr_10);
  set_idt_gate(11, (u32)isr_11);
  set_idt_gate(12, (u32)isr_12);
  set_idt_gate(13, (u32)isr_13);
  set_idt_gate(14, (u32)isr_14);
  set_idt_gate(15, (u32)isr_15);

  idt_first.limit_size = sizeof(idt_entries) - 1;
  idt_first.base_address = (struct IDT*)&idt_entries;

  load_idt((struct IDT*)&idt_first);
}

