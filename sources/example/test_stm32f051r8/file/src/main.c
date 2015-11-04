#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"



//------------------------------------------------------
// Hardware initialization
//------------------------------------------------------
void Hardware_Init(void)
{
    // Initialize oscillator
    Oscillator_Init();
    // Initialization GPIO
    Port_Init();
    __enable_irq();
}

//------------------------------------------------------
// MAIN
//------------------------------------------------------
int main(void)
{
    // Hardware initialization
    Hardware_Init();

    while(1) {


    }
}

