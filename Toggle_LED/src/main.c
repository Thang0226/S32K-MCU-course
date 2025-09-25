#include <Port.h>
#include <GPIO.h>

// Callback functions
void Button1_Callback(void);
void Button2_Callback(void);

int main(void) {

	// Enable clock for PORTC and PORTD
	PORT_EnableClock(LED_PORT);
	PORT_EnableClock(BTN_PORT);

	// Configure LEDs (PD15, PD16) as output
	PORT_SetPinMux(LED_PORT, LED_RED_PIN, GPIO_MUX);
	PORT_SetPinMux(LED_PORT, LED_GREEN_PIN, GPIO_MUX);
	IP_PTD->PDDR |= (1 << 15) | (1 << 16);		// Turn off LEDs

	// Configure Buttons PTC12 & PTC13 as GPIOs with rising edge interrupt
	PORT_EnableInterrupt(BTN_PORT, BTN1_PIN, PORT_INTERRUPT_RISING, Button1_Callback);
	PORT_EnableInterrupt(BTN_PORT, BTN2_PIN, PORT_INTERRUPT_RISING, Button2_Callback);

	while(1)
	{}
}



void Button1_Callback(void)
{
    // Handle Button 1 pressed (PTC12 rising edge)
    GPIO_TogglePin(LED_GPIO, LED_RED_PIN);
}

void Button2_Callback(void)
{
    // Handle Button 2 pressed (PTC13 rising edge)
	GPIO_TogglePin(LED_GPIO, LED_GREEN_PIN);
}
