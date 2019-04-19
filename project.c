// Hunter Johnson
// Arthur Henry
// CDA | Spring 2019
#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
  // check if A and B are equal
  *Zero = ((A - B) == 0) ? 1 : 0;

  switch(ALUControl)
  {
    case 0x0:
      *ALUresult = A + B;
      break;
    case 0x1:
      *ALUresult = A - B;
      break;
    case 0x2:
      *ALUresult = ((int)A < (int)B) ? 1 : 0;
      break;
    case 0x3:
      *ALUresult = A < B ? 1 : 0;
      break;
    case 0x4:
      *ALUresult = A & B;
      break;
    case 0x5:
      *ALUresult = A | B;
      break;
    case 0x6:
      *ALUresult = B << 16;
      break;
    case 0x7:
      *ALUresult = ~A;
      break;
  }
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
  unsigned index = PC >> 2;

  // If not byte addressed, halt.
  if(PC % 4 != 0)
      return 1;

  // Fetch the instruction addressed by PC from Mem and write it to instruction.
  *instruction = Mem[index];
  return 0;
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
  // shift instruction by 26 to get the first 6 bits
  // then store in opcode
  *op = (instruction >> 26) & 0x0000003f; 
    
  // shift instruction by 21 then AND with 0x1f to get the first 5 bits
  // then store in register 1
  *r1 = (instruction >> 21) & 0x0000001F;
    
  // shift instruction by 16 then AND with 0x1f to extract the first 5 bits
  // then store in register 2
  *r2 = (instruction >> 16) & 0x0000001F;
    
  // shift instruction by 11 then AND with 0x1f to extract the first 5 bits
  // then store in register 3
  *r3 = (instruction >> 11) & 0x0000001F;
    
  // AND with 0x3f to extract the first 6 bits
  *funct = instruction & 0x0000003F;
    
  // AND with 0xffff to extract the first 16 bits
  *offset = instruction & 0X0000FFFF;
    
  // AND with 0x3ffffff to extract the first 26 bits
  *jsec = instruction & 0x03FFFFFF;
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
  return 0;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
  // Read the registers addressed by r1, r2 in Reg and assign them the data 1 and 2 respectively
  *data1 = Reg[r1];
  *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
  // Check if sign bit is 1
  if ((offset >> 15) == 1)
    *extended_value = offset | 0xffff0000;
  else
    *extended_value = offset & 0x0000ffff; // maintain positive value
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
  unsigned char ALUControl = ALUOp;

  switch(ALUOp)
  {
    case 0x0: // don't cares | add
    case 0x1: // subtraction
    case 0x2: // slt signed
    case 0x3: // slt unsigned
    case 0x4: // AND
    case 0x5: // OR
    case 0x6: // shift extended_value left 16 bits
      break;
    case 0x7: // r-type instructions
      switch(funct)
      {
        case 0x20: // add
          ALUControl = 0x0;
          break;
        case 0x24: // AND
          ALUControl = 0x4;
          break;
        case 0x25: // OR
          ALUControl = 0x5;
          break;
        case 0x2a: // slt signed
          ALUControl = 0x2;
          break;
        case 0x2b: // slt unsigned
          ALUControl = 0x3;
          break;
        default: // any others
          return 1;
      }
      break;
    default:
      return 1;
  }

  ALU(data1, (ALUSrc == 1) ? extended_value : data2, ALUControl, ALUresult, Zero);

  return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
  return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

