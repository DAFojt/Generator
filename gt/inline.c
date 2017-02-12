__inline__ void set_imask_ccr(unsigned char mask)
{
  if(mask==1) asm("orc.b #128, ccr");    //mask==0
  else asm("andc.b #127, ccr");
}

__inline__  void no_operation(void)
{
   asm ("nop");
}
