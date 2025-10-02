#include <Port.h>
#include <GPIO.h>
#include <stdint.h>

// ADC channel (PTB0 = ADC0_SE4)
#define ADC_CHANNEL		4
#define	ADC_PORT		IP_PORTB
#define ADC_PIN			0

void ADC_Init(void);
uint16_t ADC_Read(void);

void PORT_Init(void);
void LED_Control(uint16_t adcValue);
void turnOnLED(uint32_t LEDPin);
void turnOffLEDs(void);

int main(void) {
	uint16_t adcResult;
	uint16_t voltage;		// milli-volts

	PORT_Init();
	ADC_Init();

	while(1)
	{
		adcResult = ADC_Read();

		voltage = (adcResult * 5000UL) / 4096;

		LED_Control(voltage);

		// Small delay
		for(volatile int i = 0; i < 100000; i++);
	}
}



void ADC_Init(void)
{
	// Enable clock for ADC0
	IP_PCC->PCCn[PCC_ADC0_INDEX] = PCC_PCCn_CGC_MASK;

	// Configure ADC0
	IP_ADC0->SC1[0] = ADC_SC1_ADCH(31);  // Disable module initially

	// Configuration register 1
	// - 12-bit resolution
	// - Bus clock input
	// - Divide by 1
	IP_ADC0->CFG1 = ADC_CFG1_MODE(1) |    // 12-bit conversion
				 ADC_CFG1_ADICLK(0);   // Bus clock: Alternate clock 1

	// Configuration register 2
	IP_ADC0->CFG2 = ADC_CFG2_SMPLTS(12);  // Sample time: 12 clock cycles

	// Status and control register 2
	IP_ADC0->SC2 = 0;  // Reset Software trigger

	// Status and control register 3
	IP_ADC0->SC3 = ADC_SC3_AVGE_MASK |    // Hardware average enable
				ADC_SC3_AVGS(3);       // 32 samples averaged
}

uint16_t ADC_Read(void)
{
	// Start conversion on selected channel
	IP_ADC0->SC1[0] = ADC_SC1_ADCH(ADC_CHANNEL);

	// Wait for conversion complete
	while(!(IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK));

	// Return conversion result
	return IP_ADC0->R[0];
}

void PORT_Init(void)
{
	// Enable clock for PORTD
	PORT_EnableClock(LED_PORT);
	// Enable clock for PORTB
	PORT_EnableClock(ADC_PORT);

	// Configure PB0 as ADC
	PORT_SetPinMux(ADC_PORT, ADC_PIN, DISABLED_MUX);

	// Configure LEDs (PD0, PD15, PD16) as output
	PORT_SetPinMux(LED_PORT, LED_RED_PIN, GPIO_MUX);
	GPIO_SetPinDirection(LED_GPIO, LED_RED_PIN, SET_OUTPUT);
	PORT_SetPinMux(LED_PORT, LED_GREEN_PIN, GPIO_MUX);
	GPIO_SetPinDirection(LED_GPIO, LED_GREEN_PIN, SET_OUTPUT);
	PORT_SetPinMux(LED_PORT, LED_BLUE_PIN, GPIO_MUX);
	GPIO_SetPinDirection(LED_GPIO, LED_BLUE_PIN, SET_OUTPUT);

	turnOffLEDs();
}

void LED_Control(uint16_t voltage)
{
	turnOffLEDs();

	if(voltage > 3750)
	{
		turnOnLED(LED_RED_PIN);
	}
	else if(voltage > 2500)
	{
		turnOnLED(LED_GREEN_PIN);
	}
	else if(voltage > 1250)
	{
		turnOnLED(LED_BLUE_PIN);
	}

	// else: 0-1250 mV = No LED (all remain off, do nothing more)
}

void turnOnLED(uint32_t LEDPin)
{
	IP_PTD->PCOR = (1 << LEDPin);
}

void turnOffLEDs(void)
{
	IP_PTD->PSOR |= (1 << LED_RED_PIN) | (1 << LED_GREEN_PIN) | (1 << LED_BLUE_PIN);
}
