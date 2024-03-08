# stm32-programming-from-scratch
STM32 Embedded Programming, learn to program from scratch

## Environment
- Keil C (MDK-Arm version 5.39)
- STM32F103C8
- ST-Link v2
## References
- [STM32F103x8 Datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf)
- [RM0008 Reference Manual](https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [STM32F1-STM32F103C8T6-Blue-Pill-schematics.pdf](https://github.com/nambhd/stm32-programming-from-scratch/files/14504723/STM32F1-STM32F103C8T6-Blue-Pill-schematics.pdf)

## Projects
### Led blink
- Port I/O C clock enable
- Configure PC13 as Output push-pull
- Using super loop to toogle PC13 (via ODR - Port output data register)
### Basic GPIO input/output
- Port I/O A,C clock enable
- Configure PA0 as Input with pull-up/pull-down
- Configure PC13 as Output push/pull
- Inside super loop:
  - Read PA0 and toogle pin PC13 depends on PA0 state
### Basic GPIO input/output library
Implement basic GPIO library:
- Init GPIO port
- Read PIN
- Write PIN
- Toggle PIN
