#include "S32K144.h"

// Mapping following S32K144 EVB

#define LED_PORT		IP_PORTD	// PORTD
#define LED_RED_PIN		15			// Red LED on PD15
#define LED_GREEN_PIN	16			// Green LED on PD16

#define BTN_PORT	IP_PORTC	// PORTC
#define BTN1_PIN	12			// Button 1 on PC12
#define BTN2_PIN	13			// Button 2 on PC13

#define DISABLED_MUX	0
#define GPIO_MUX		1

// Interrupt edge selection
typedef enum {
    PORT_INTERRUPT_DISABLED = 0b0000,
    PORT_INTERRUPT_LOGIC0   = 0b1000,
    PORT_INTERRUPT_RISING   = 0b1001,
    PORT_INTERRUPT_FALLING  = 0b1010,
    PORT_INTERRUPT_EITHER   = 0b1011
} PortInterrupt_Type;



// Enable clock for PORT
void PORT_EnableClock(PORT_Type *port);

// Configure Pin Type
void PORT_SetPinMux(PORT_Type *port, uint32_t pin, uint32_t mux);

typedef void (*PortCallback)(void);   // Function pointer type for callback



// Enable Port interrupt
void PORT_EnableInterrupt(PORT_Type *port, uint32_t pin, PortInterrupt_Type irqc, PortCallback cb);

// ISR handlers (Port C for buttons)
void PORTC_IRQHandler(void);
