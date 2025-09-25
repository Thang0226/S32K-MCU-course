#include "S32K144.h"
#include <stdint.h>

// Mapping following S32K144 EVB

#define LED_GPIO	IP_PTD
#define BTN_GPIO	IP_PTC

#define SET_OUTPUT	1
#define SET_INPUT	0

// Set pin as input/output
void GPIO_SetPinDirection(GPIO_Type *gpio, uint32_t pin, uint32_t output);

// Write to pin
void GPIO_WritePin(GPIO_Type *gpio, uint32_t pin, uint32_t value);

// Toggle pin
void GPIO_TogglePin(GPIO_Type *gpio, uint32_t pin);

// Read from pin
uint32_t GPIO_ReadPin(GPIO_Type *gpio, uint32_t pin);
