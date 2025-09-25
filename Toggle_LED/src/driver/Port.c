#include "Port.h"
#include "GPIO.h"

// Store callback function addresses for each pin of each port?
static PortCallback portC_callbacks[32] = {0};

// Enable clock for PORT
void PORT_EnableClock(PORT_Type *port)
{
    if (port == IP_PORTA)
        IP_PCC->PCCn[PCC_PORTA_INDEX] |= PCC_PCCn_CGC_MASK;
    else if (port == IP_PORTB)
    	IP_PCC->PCCn[PCC_PORTB_INDEX] |= PCC_PCCn_CGC_MASK;
    else if (port == IP_PORTC)
    	IP_PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;
    else if (port == IP_PORTD)
    	IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
    else if (port == IP_PORTE)
    	IP_PCC->PCCn[PCC_PORTE_INDEX] |= PCC_PCCn_CGC_MASK;
}

// Configure Pin Type
void PORT_SetPinMux(PORT_Type *port, uint32_t pin, uint32_t mux)
{
    port->PCR[pin] = ((port->PCR[pin] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(mux));
}

void PORT_EnableInterrupt(PORT_Type *port, uint32_t pin, PortInterrupt_Type irqc, PortCallback cb)
{
    // Configure MUX = GPIO
    port->PCR[pin] = (port->PCR[pin] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(1);

    // Set pin as input
    GPIO_SetPinDirection(BTN_GPIO, pin, SET_INPUT);

    // Set interrupt type
    port->PCR[pin] = (port->PCR[pin] & ~PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(irqc);

    // Save callback function for interrupt
    if (port == IP_PORTC) {
        portC_callbacks[pin] = cb;
        NVIC_EnableIRQ(PORTC_IRQn);
    }
}

// ISR for PORTC
void PORTC_IRQHandler(void)
{
    uint32_t flags = IP_PORTC->ISFR;    // Get all interrupt flags
    for (uint32_t pin = 0; pin < 32; pin++) {
        if (flags & (1 << pin)) {
            IP_PORTC->ISFR |= (1 << pin);  // Clear flag by write 1 to the flag
            if (portC_callbacks[pin]) {
                portC_callbacks[pin](); // Call user callback function
            }
        }
    }
}

// NVIC_EnableIRQ function
void NVIC_EnableIRQ(uint32_t deviceInterrupt)
{
	NVIC_ICPR1 = (1 << (deviceInterrupt % 32)); // Clear pending
	NVIC_ISER1 = (1 << (deviceInterrupt % 32)); // Enable IRQ
}
