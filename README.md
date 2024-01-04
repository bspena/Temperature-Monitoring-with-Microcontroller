# Temperature-Monitoring-with-Microcontroller
Il fine del progetto è quello di riprodurre il funzionamento di un misuratore di tempertura ambientale sul microcontrollore STM32F401 Nucleo-64. Alla pressione del bottone,il software preleva i valori di temperatura e umidità dal [DHT11 Temperature Sensor Module](https://components101.com/sensors/dht11-temperature-sensor) e li mostra sul [16x2 LCD Display Module](https://circuitdigest.com/article/16x2-lcd-display-module-pinout-datasheet), se la temperatura supera un valore massimo(scelto dall’utente) si accende il led presente sul microcontrollore.

## Collegamenti 
![Links](/Links.png)
* I collegamenti in rosso rappresentano l’alimentazione a +5V
* Il collegamento in nero rappresenta il collegamento a massa
* I collegamento in giallo rappresentano i collegamenti ai pin di controllo del display
* I collegamento in azzurro rappresentano i collegamenti con i pin dati del display
* Il collegamento in verde rappresenta il collegamento con il pin dato del sensore di temperatura

Da notare che per il display è stata usata la modalità a 4-bit

## Configurazione dei GPIO
Sono stati usati i seguenti GPIO : 
* PA1 : pin Data del DHT11 (modalutà *GPIO_Output*)
* PA5 : led del microcontrollore (modalutà *GPIO_Output*)
* PC3 : PushButton (modalutà interuzione)
* PA6 : D7 display (modalutà *GPIO_Output*)
* PA7 : D6 display (modalutà *GPIO_Output*)
* PB6 : D5 display (modalutà *GPIO_Output*)
* PC7 : D4 display (modalutà *GPIO_Output*)
* PB4 : E display (modalutà *GPIO_Output*)
* PB5 : RS display (modalutà *GPIO_Output*)

## Configurazione dell'interruzione
Abbiamo settato il PushButton in modalità External Interrupt Mode with Rising edge trigger detection: alla pressione del pulsante lo stato della linea di interruzione passa da 0 ad 1 e di conseguenza scatta l’interruzione.
Affinché l’NVIC serva l’interruzione, connessa al PushButton, dobbiamo abilitare l’apposita linea di interruzione. Nel nostro caso la linea di interruzione connessa al PushButton è la linea EXTI13.


## Configurazione del timer
Il timer è stato utilizzato per creare un ritardo di 1 microsecondo per il corretto funzionamento del display LCD.
Abbiamo settato il Timer1 (contatore a 16 bit) che ha come clock Source il clock interno della scheda (CK_INT) che lavora ad una frequenza di 84MHz collegato al bus APB2.
E’ stato utilizzato un prescaler che rappresenta un divisore di frequenza ed è stato settato al valore massimo di frequenza della scheda. La differenza di 1 è stata aggiunta perché il prescaler aggiunge automaticamente un’unità al valore inserito (84-1+1=84).
Il timer inoltre è configurato in modalità up counting mode, ovvero il contatore parte da zero e si incrementa fino a un certo valore fissato.
Il counter period definisce il valore massimo che il timer può raggiungere ed è settato a 0xffff-1 = 65534.


## Run 
ambiente STM32CubeIDE