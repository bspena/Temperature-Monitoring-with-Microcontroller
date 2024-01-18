# Temperature-Monitoring-with-Microcontroller
The project consists of an ambient temperature meter on the STM32F401 Nucleo-64 microcontroller. When the *Pushbutton* is pressed, the software takes the temperature and humidity values from the [DHT11 Temperature and Humidity Sensor Module](https://components101.com/sensors/dht11-temperature-sensor) and shows them on the [16x2 LCD Display Module](https://circuitdigest.com/article/16x2-lcd-display-module-pinout-datasheet), if the temperature exceeds a maximum value (chosen by the user) the *LED* on the microcontroller lights up.

## Jumper Connections 
![Links](/Jumper_Connections.png)

* Red jumper: +5V
* Blue Jumper: Ground
* Green Jumper: Data pin

The LCD Display works in the *4-bit mode*


## Environment Configuration
### GPIO
I used two GPIOs modes:
* GPIO_Output: mode used for display and DHT11 data pins and for the the LED on the microcontroller
* GPIO_EXTI13: mode used for the PushButton

### Interrupt
I set the PushButton as *External Interrupt Mode with Rising edge trigger detection* mode. When the button is pressed, the state of the interrupt line goes from 0 to 1 and the interruption is triggered. In order for the NVIC to serve the interrupt (connected to the PushButton), I enable the EXTI13 interrupt line.

### Timer
To make the display work, I used Timer1 to create a 1 microsecond [delay](https://controllerstech.com/create-1-microsecond-delay-stm32/) and it is configured in *up counting mode*  i.e. the counter starts from zero and increases up to a certain set value. The counter period is set to 0xffff-1 = 65534 and the prescaler is set to the maximum frequency value of the board. The prescaler adds a unit to the entered value, so The value must be decremented by one (84-1+1=84).

## Folder Structure
The workspace contains two folders, where:
* Inc : heades file
* Src : C file

## Notes
* The name and location of some pins may vary between components
* It is possible to add a potentiometer to change the brightness of the display
* [How to check wheter LCD display working or not](https://piratelearner.com/en/bookmarks/how-to-check-whether-16x2-lcd-working-or-not/16/)

## Refernces
* [LCD Display Code](https://controllerstech.com/interface-lcd-16x2-with-stm32-without-i2c/)
* [DHT11 Code](https://www.youtube.com/watch?v=09C1dyXvSbg&t=687s)

