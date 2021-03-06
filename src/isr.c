#include "isr.h"
#define NULL 0
static struct registers* current_regs = NULL;

// if no interrupt found then push interrupt no into stack
// for int instruction
void isr_0()
{
  asm volatile("\tcli");
  asm volatile("\tpush $0");
  asm volatile("\tpush $0");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_1()
{
  asm volatile("\tcli");
  asm volatile("\tpush $1");
  asm volatile("\tpush $1");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_2()
{
  asm volatile("\tcli");
  asm volatile("\tpush $2");
  asm volatile("\tpush $2");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_3()
{
  asm volatile("\tcli");
  asm volatile("\tpush $3");
  asm volatile("\tpush $3");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_4()
{
  asm volatile("\tcli");
  asm volatile("\tpush $4");
  asm volatile("\tpush $4");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_5()
{
  asm volatile("\tcli");
  asm volatile("\tpush $5");
  asm volatile("\tpush $5");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_6()
{
  asm volatile("\tcli");
  asm volatile("\tpush $6");
  asm volatile("\tpush $6");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_7()
{
  asm volatile("\tcli");
  asm volatile("\tpush $7");
  asm volatile("\tpush $7");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_8()
{
  asm volatile("\tcli");
  asm volatile("\tpush $8");
  asm volatile("\tpush $8");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_9()
{
  asm volatile("\tcli");
  asm volatile("\tpush $9");
  asm volatile("\tpush $9");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_10()
{
  asm volatile("\tcli");
  asm volatile("\tpush $10");
  asm volatile("\tpush $10");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_11()
{
  asm volatile("\tcli");
  asm volatile("\tpush $11");
  asm volatile("\tpush $11");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_12()
{
  asm volatile("\tcli");
  asm volatile("\tpush $12");
  asm volatile("\tpush $12");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_13()
{
  asm volatile("\tcli");
  asm volatile("\tpush $13");
  asm volatile("\tpush $13");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_14()
{
  asm volatile("\tcli");
  asm volatile("\tpush $14");
  asm volatile("\tpush $14");
  asm volatile("\tjmp common_isr_stub_handler");
}

void isr_15()
{
  asm volatile("\tcli");
  asm volatile("\tpush $15");
  asm volatile("\tpush $15");
  asm volatile("\tjmp common_isr_stub_handler");
}

// this is common for all isrn
// it saves processor state, segments, flags
// some info automatically saved by processor itself
void common_isr_stub_handler()
{
  // save all registers
  asm volatile("\tpusha");
  // save ds segment
  asm volatile("\tmov %ds, %eax");
  asm volatile("\tpush %eax");
  // load new data segment for handling interrupt
  asm volatile("\tmov $0x10, %eax");
  asm volatile("\tmov %eax, %ds");
  asm volatile("\tmov %eax, %es");
  asm volatile("\tmov %eax, %fs");
  asm volatile("\tmov %eax, %gs");
  // call common interrupt handler
  asm volatile("\tcall isr_handler");
  // get original ds segment
  asm volatile("\tpop %eax");
  // set its value to other segments
  asm volatile("\tmov %eax, %ds");
  asm volatile("\tmov %eax, %es");
  asm volatile("\tmov %eax, %fs");
  asm volatile("\tmov %eax, %gs");
  // restore all registers
  asm volatile("\tpopa");
  // restore stack space pushed by isr_n() routines
  // by pushing its isr number into stack
  asm volatile("\tadd $8, %esp");
  // store interrupt which was cleared by isr_n()
  asm volatile("\tsti");
  // return after handling interrupt
  asm volatile("\tiret");
}


void isr_handler(struct registers regs)
{
  current_regs = (struct registers*)&regs;
  switch(regs.int_no){
    case 0:
      isr_0_handler();
      break;
    case 1:
      isr_1_handler();
      break;
    case 2:
      isr_2_handler();
      break;
    case 3:
      isr_3_handler();
      break;
    case 4:
      isr_4_handler();
      break;
    case 5:
      isr_5_handler();
      break;
    case 6:
      isr_6_handler();
      break;
    case 7:
      isr_7_handler();
      break;
    case 8:
      isr_8_handler();
      break;
    case 9:
      isr_9_handler();
      break;
    case 10:
      isr_10_handler();
      break;
    case 11:
      isr_11_handler();
      break;
    case 12:
      isr_12_handler();
      break;
    case 13:
      isr_13_handler();
      break;
    case 14:
      isr_14_handler();
      break;
    case 15:
      isr_15_handler();
      break;
    default:
      
      break;
  }
  current_regs = NULL;
} 

void isr_0_handler()
{
  
}

void isr_1_handler()
{
  
}

void isr_2_handler()
{
  
}

void isr_3_handler()
{
  
}

void isr_4_handler()
{
 
}

void isr_5_handler()
{
  
}

void isr_6_handler()
{

}

void isr_7_handler()
{
 
}

void isr_8_handler()
{
  
}

void isr_9_handler()
{
  
}

void isr_10_handler()
{

}

void isr_11_handler()
{
  
}

void isr_12_handler()
{
  
}

void isr_13_handler()
{
 
}

void isr_14_handler()
{
  
}

void isr_15_handler()
{
  
}



