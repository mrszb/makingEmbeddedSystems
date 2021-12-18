# Exercise 4
On your final project board, make blinky for yourself. Then add a button to turn the LED on and off. Bonus points for making the button cause an interrupt. Triple bonus points for debouncing the button signal.

What are the hardware registers that cause the LED to turn on and off? (From the processor manual, don’t worry about initialization.) What are the button registers that you read? Can you read that memory directly and see the button change in a debugger or by printing out the associated memory?

 ![image](./blinky.png)

I do not have final board yet but I found "Blue Pill" board and tried my first ARM bare metal programming ...

[**->see project repo here<-**](https://github.com/mrszb/blue_pill_button_blinky)

# Hardware
Blue Pill - STM32F103C8 board

- Button (input) connected between Port/Pin C15 and GND, pulled up by external resistor (could not figure out how to turn on the internal pull-up)
- Output Port/Pin C13 has attached external LED (against GND) and internal (against power)
- Output Port/Pin C14 .. attached oscilloscope for debugging


# Control Registers
originally I tried to put together memory mapped registers by adding offsets from the manual ...

```
//#define base_clock 0x40021000
//#define base_gpioc 0x40011000
//
///* clock enable reg */
//#define offset_APB2 0x18
///* port C clock */
//#define IOPCEN (1<<4)
//
//#define offset_GPIOx_CRH 4
//#define offset_GPIOx_ODR 0x0c
//
//uint32_t *apb2 = (uint32_t *) (base_clock + offset_APB2);
//uint32_t *gpioc_h = (uint32_t *) (base_gpioc + offset_GPIOx_CRH);
//uint32_t *gpioc_out = (uint32_t *) (base_gpioc + offset_GPIOx_ODR);

```

... but there is a better way:

```
#define GPIOC_BASE      (PERIPH_BASE + 0x11000) // GPIOC base address is 0x40011000

typedef struct
{
	uint32_t CRL;      /* GPIO port configuration register low,      Address offset: 0x00 */
	uint32_t CRH;      /* GPIO port configuration register high,     Address offset: 0x04 */
	uint32_t IDR;      /* GPIO port input data register,             Address offset: 0x08 */
	uint32_t ODR;      /* GPIO port output data register,            Address offset: 0x0C */
	uint32_t BSRR;     /* GPIO port bit set/reset register,          Address offset: 0x10 */
	uint32_t BRR;      /* GPIO port bit reset register,              Address offset: 0x14 */
	uint32_t LCKR;     /* GPIO port configuration lock register,     Address offset: 0x18 */
} GPIO_type;
```

in main(void) of the [**->main.c<-**](https://github.com/mrszb/blue_pill_button_blinky/blob/main/Src/main.c)
- set up Pin 15 as input 
- Pins 13, 14 as output
- init_systick setup interrupt handler to be called every 1ms


I can sample the button state and see it in the debugger:

```
// get latest sample
bool btn_fresh_sample = ((GPIOC->IDR & (1<<15)) == 0);
```

![image](./debug_sys_tick.png)

# Debouncing
Button is **sampled in 1ms intervals** (**btn_fresh_sample**) and values are stored in circular queue (ring buffer).

First phase is **low pass filtering** done by integration - doing **running_total** of the values in the queue.
The implemetation is quite efficient - it requires to bump running total up or down if sample into the queue is not  the same value as the oldest sample leaving the circular queue.

Second phase is **hysteresis.**
One need 2/3 of the samples of button down to register as button down event (running_total < queue_length/3)
Once button is considered pressed one need at least 2/3 of the samples in queue button down to register as button down event

```
//////////////////////////////////////////////////////////
// circular queue holds sampled button values
// using running total and 1/3, 2/3 hysteresis to debounce

#define DebounceQLen  18
#define LowerThr (DebounceQLen/3)
#define UpperThr (DebounceQLen/3)*2

volatile bool DebounceCircularQueue[DebounceQLen],
	*p_debounce;
```


```
// debouncing routine
// point to last recorded sample, overwrite with new sample ...
bool btn_oldest_sample = *p_debounce;
*p_debounce = btn_fresh_sample;

// rotate pointer forward
p_debounce ++;
if (p_debounce >= DebounceCircularQueue + DebounceQLen)
    p_debounce = DebounceCircularQueue;

if (btn_fresh_sample != btn_oldest_sample)
{
    // if sample out not same as sample in we need to update
    // running total
    if (btn_fresh_sample)
        running_total++;
    else
        running_total--;
}

if  (button_pressed)
{
    if (running_total < LowerThr)
        button_pressed = false;
        // BTN UP EVENT
}
else
{
    if (running_total > UpperThr)
        button_pressed = true;
        // BTN DOWN EVENT
}

```
# Button events 
Latest version has circular queue storing events.


```
typedef enum BtnActions {BTN_UP = 1, BTN_DOWN = 2} BtnAction;

typedef struct BtnEvents
{
	BtnAction action;
	uint32_t systick_time;
} BtnEvent;


#define KeybQLen  10
volatile BtnEvent evtQueue[KeybQLen];
volatile BtnEvent *pQOut,*pQIn;
```
Interrupt routine pushes them in ..

```
	if ( newEvt.action !=0 )
	{
		*pQIn = newEvt;
		newEvt.systick_time = systick_uptime_millis;
		BtnEvent *pNextQIn = (pQIn >= evtQueue+KeybQLen-1) ?
		    evtQueue : pQIn+1;

		if (pNextQIn != pQOut)
			pQIn = pNextQIn;
	}

```

... query_btn_event pops them out in the main program.

```
bool query_btn_event(BtnEvent* evt)
{
#if GENERATES_EVENTS
	// get oldest event out of keyboard queue

	if (pQOut == pQIn)
		return false;

	*evt = *pQOut;
	pQOut++;

	if (pQOut >= evtQueue + KeybQLen)
		pQOut = evtQueue;

	return true;

#endif
	return false;
}
```

Post class research:
- [^1] [^2] **ARM Interrupt Handler can be regular C routine**
- [^3] there is a lock-free implementation of ring buffer for single producer (interrupt handler) and single consumer (main) which I hope looks like my blinky (?)


[^1]: [cpu docs](https://www.sciencedirect.com/topics/engineering/systick-interrupt)

[^2]: [The Definitive Guide to the ARM Cortex-M0](https://www.sciencedirect.com/book/9780123854773/the-definitive-guide-to-the-arm-cortex-m0

[^3]: [Thread optimized Ring Buffer](http://landenlabs.com/code/ring/ring.html)

