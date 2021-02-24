#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

void main(void){
  int PLL1=24000000;//24MHz
  int PLL2=120000000;//120MHz
  
  uint32_t freq = SysCtlClockFreqSet(SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480 | SYSCTL_XTAL_25MHZ, PLL1);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D3 = PF4, LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilitação
  
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0); // LEDs D4 como saída
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0); // LEDs D4 apagado
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
  
  while(1){
    /*
          Conta para SysCtlDelay
          1/24MHz = 41,67ns -> 41,67ns*3 = 125ns -> 125ns*8.000.000=1
    */
          GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0, 1);
          SysCtlDelay(8000000); 
          GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0, 0);
          SysCtlDelay(8000000);
          
  } // while
} // main
/*
1. Para diferentes níveis de otimização do compilador C não houve mudança devido ao uso da função SysCtlDelay, nela cada
contagem roda 3 instruções em assembly, por isso não há otimização
2. Para frequência de clock (PLL) de 120MHz, o LED pisca 5 vezes mais rápido devido à frequência de clock 5 vezes maior
*/