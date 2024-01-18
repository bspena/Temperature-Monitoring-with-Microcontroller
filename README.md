# Temperature-Monitoring-with-Microcontroller
The project consists of an ambient temperature meter on the STM32F401 Nucleo-64 microcontroller. When the *Pushbutton* is pressed, the software takes the temperature and humidity values from the [DHT11 Temperature and Humidity Sensor Module](https://components101.com/sensors/dht11-temperature-sensor) and shows them on the [16x2 LCD Display Module](https://circuitdigest.com/article/16x2-lcd-display-module-pinout-datasheet), if the temperature exceeds a maximum value (chosen by the user) the LED on the microcontroller lights up.

## Jumper Connections 
![Links](/Jumper_Connections.png)

DHT11
GND: ground
VCC: alimentazione +5V
OUTPUT: output

Display
VSS: massa
VDD: alimentazione a +5V
VO: pin che regola il contrasto del display
RS: pin che seleziona due tipi di registri. Il registro dati che contiene le informazioni che verranno visualizzate sul display e il registro istruzioni dove il controller del display preleva le prossime istruzioni che devono essere eseguire
R/W: pin di lettura/scrittura che seleziona la modalità di lettura (1) o di scrittura (0)
E: enable pin che deve essere tenuto alto per eseguire operazioni di lettura e di scrittura
D0-D7: pin usati per inviare dati al display
A:  anodo connesso a +5V per regolare la retroilluminazione dei display
K:  catodo connesso a massa per regola la retroilluminazione del display



## Environment Configuration
### GPIO
Sono stati usati i seguenti GPIO : 
* PA1 : pin Data del DHT11 (modalutà *GPIO_Output*)
* PA5 : led del microcontrollore (modalutà *GPIO_Output*)
* PC13 : PushButton (modalutà *GPIO_EXTI13*)
* PA6 : D7 display (modalutà *GPIO_Output*)
* PA7 : D6 display (modalutà *GPIO_Output*)
* PB6 : D5 display (modalutà *GPIO_Output*)
* PC7 : D4 display (modalutà *GPIO_Output*)
* PB4 : E display (modalutà *GPIO_Output*)
* PB5 : RS display (modalutà *GPIO_Output*)

### Interrupt
Abbiamo settato il PushButton in modalità *External Interrupt Mode with Rising edge trigger detection* : alla pressione del pulsante lo stato della linea di interruzione passa da 0 ad 1 e di conseguenza scatta l’interruzione.
Affinché l’NVIC serva l’interruzione, connessa al PushButton, dobbiamo abilitare l’apposita linea di interruzione. Nel nostro caso la linea di interruzione connessa al PushButton è la linea EXTI13.

### Timer
Il timer è stato utilizzato per creare un ritardo di 1 microsecondo per il corretto funzionamento del display LCD.

Ritardo https://controllerstech.com/create-1-microsecond-delay-stm32/

Abbiamo settato il Timer1 (contatore a 16 bit) che ha come clock Source il clock interno della scheda (CK_INT) che lavora ad una frequenza di 84MHz collegato al bus APB2.
E’ stato utilizzato un prescaler che rappresenta un divisore di frequenza ed è stato settato al valore massimo di frequenza della scheda. La differenza di 1 è stata aggiunta perché il prescaler aggiunge automaticamente un’unità al valore inserito (84-1+1=84).
Il timer inoltre è configurato in modalità up counting mode, ovvero il contatore parte da zero e si incrementa fino a un certo valore fissato.
Il counter period definisce il valore massimo che il timer può raggiungere ed è settato a 0xffff-1 = 65534.


## Folder Structure
The workspace contains two folders, where:
* Inc : file .h
* Src : file .c

## Notes
* Da notare che per il display è stata usata la modalità a 4-bit
* Il nome e la posizione di alcuni pin potrebbe variare tra i vari componenti
* E' possibile aggiungere un potenziometro per modificare la luminosità del display
* [Controllo rottura](https://piratelearner.com/en/bookmarks/how-to-check-whether-16x2-lcd-working-or-not/16/)
* [Codice Display](https://controllerstech.com/interface-lcd-16x2-with-stm32-without-i2c/)
* [Codice DHT11](https://www.youtube.com/watch?v=09C1dyXvSbg&t=687s)

