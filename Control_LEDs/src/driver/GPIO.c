#include "GPIO.h"

// Set pin as input/output
void GPIO_SetPinDirection(GPIO_Type *gpio, uint32_t pin, uint32_t output)
{
    if (output)
        gpio->PDDR |= (1 << pin);  // Output
    else
        gpio->PDDR &= ~(1 << pin); // Input
}

// Write to pin
void GPIO_WritePin(GPIO_Type *gpio, uint32_t pin, uint32_t value)
{
    if (value)
        gpio->PSOR = (1 << pin);  // Set = 1
    else
        gpio->PCOR = (1 << pin);  // Clear = 0
}

// Toggle pin
void GPIO_TogglePin(GPIO_Type *gpio, uint32_t pin)
{
    gpio->PTOR = (1 << pin);
}

// Read from pin
uint32_t GPIO_ReadPin(GPIO_Type *gpio, uint32_t pin)
{
    return (gpio->PDIR >> pin) & 1;
}
