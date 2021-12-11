# Exercise 3
1. Investigate project board
Look at the documents for the board you are considering for your final project (or any ST Discovery Board), draw the hardware block diagram for the board. For peripherals, note the
communication paths (SPI, I2C, etc).

![image](./top_layout.png)

Look at the datasheet for the processor and other documents. Answer these questions:
 
* **What kind of processor is it?**

  - STM32L-DISCOVERY/newer 32L152CDISCOVERY board has **STM32L152RBT6**/**STM32L152RCT6** CPU which is low power ARM M3 32 bit processor operating at 32 MHz[^1] [^2].


* **How much Flash and RAM does it have? Any other memory types?**

    - 128K/256K bytes of Flash ("medium/+ density device") and 16 Kbytes of RAM
    - 4 Kbytes of EEPROM
    - 80 byte backup register as part of the real-time clock


 
* **Does it have any special peripherals? (List 3-5 that you noted as being interesting.)**
  - common peripherals: USB, USART (3x), SPI, I2C (2x), DAC (12 bit), ADC

  - comparators / reference voltage

  - SD multimedia interface
  - capacitive sensing channels (20x)
  - Real Time Clock
  - LCD voltage (step-up) generator

* **Does it have a floating point unit?**
  - There isn't any floating-point hardware in Cortex-M3, but support for C float and double are provided in software by most compilers/libraries.
 
* **If it has an ADC, what are the features?**
  - It has 12-bit ADC, 20 channels
  - sampling time depends on the supply voltage and if its direct or multiplexed input, can be 0.25 to 1us


  **Look at one application note for this processor.**
  [^4] AN3216 explains power supply, clock and boot configuration

  [^5] explains basics of surface sensors

  ![image](./cap_sensors.png)



[^1]: Discovery kits for STM32L151/152 line Data brief

[^2]: ([cpu docs](https://www.st.com/en/microcontrollers-microprocessors/stm32l152rb.html#documentation))

[^3]: Ultra-low-power 32-bit MCU ARM®-based Cortex®-M3, 128KB Flash, 16KB SRAM, 4KB EEPROM, LCD, USB, ADC, DAC Datasheet

[^4]: AN3216 Getting started with STM32L1xxx hardware development 

[^5]: AN4312 Design with surface sensors for touch sensing applications on MCUs