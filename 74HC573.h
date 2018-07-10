#ifndef __74HC573_H
#define __74HC573_H

#include "configuration.h"

void _74HC573_SendByte(u8 u8Data)
{
  P4OUT = u8Data;
}

u8 _74HC573_EnCode(u8 u8Data,bool bDot)
{
  u8 u8Code = 0x00;
  
  switch(u8Data)
  {
  case 0: u8Code = 0x3F;break;
  case 1: u8Code = 0x06;break;
  case 2: u8Code = 0x5B;break;
  case 3: u8Code = 0x4F;break;
  case 4: u8Code = 0x66;break;
  case 5: u8Code = 0x6D;break;
  case 6: u8Code = 0x7D;break;
  case 7: u8Code = 0x07;break;
  case 8: u8Code = 0x7F;break;
  case 9: u8Code = 0x6F;break;
  default: ;
  }
  
  if(bDot)
  {
    u8Code |= 0x80;
  }
  
  return u8Code;
}

void _74HC573_Display(u8* au8DisplayNumber, u8 u8DisplayMask, u8 u8DisplayDot, u8 u8DisplayShift)
{
  u8 u8Mask = 0x01;
  u8 u8CurrentNumber = 0;
  
  while(1)
  {
    if(u8DisplayShift & u8Mask)
    {
      break;
    }
    else
    {
      u8CurrentNumber++;
      u8Mask = u8Mask << 1;
    }
  }
  
  if(u8DisplayMask & u8Mask)
  {
    _74HC573_SendByte(_74HC573_EnCode(au8DisplayNumber[u8CurrentNumber],u8DisplayDot & u8Mask));
  }
  else
  {
    _74HC573_SendByte(0x00);
  }
  
  P6OUT |= PX_6_Location;
  P6OUT &= ~PX_6_Location;
  
}

#endif // __74HC595_H
