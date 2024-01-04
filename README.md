# Temperature-Monitoring-with-Microcontroller
Il fine del progetto è quello di riprodurre il funzionamento di un misuratore di tempertura ambientale sul microcontrollore STM32F401 Nucleo-64. Alla pressione del bottone,il software preleva i valori di temperatura e umidità dal sensore di temperatura DHT11 e li mostra sul display LCD1602, se la temperatura supera un valore massimo(scelto dall’utente) si accende il led presente sul microcontrollore.

## Protocolli
Due protocolli :
* Un protocollo seriale per il sensore di temperatura : Attraverso il protocollo seriale, il sensore comunica di essere attivo e invia i dati al microcontrollore
* Un protocollo parallelo per il display : Al contrario per il display è stata adottata una connessione parallela nota come ‘modalità 4-bit’.  Questo perché per la comunicazione tra display e microcontrollore sono stati usati solo 4 pin dato.

## Configurazione 

![Links](/Links.png)



## Run 
ambiente STM32CubeIDE