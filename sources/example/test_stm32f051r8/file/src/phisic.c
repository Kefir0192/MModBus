#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"



//------------------------------------------------------
// Initialize oscillator
//------------------------------------------------------
void Oscillator_Init(void)
{

}

//------------------------------------------------------
// Initialization GPIO
//------------------------------------------------------
void Port_Init(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    GPIOC->MODER |= (GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
}


