/* Programa para envio de Mensagem
  Blog Eletrogate https://blog.eletrogate.com/guia-basico-dos-modulos-tx-rx-rf-433mhz
  Arduino UNO - IDE 1.8.5 - Modulo TX RF 433 MHz
  Gustavo Murta   6/setembro/2018
  Baseado em https://github.com/adafruit/RadioHead/tree/master/examples/ask
*/
#include <RHReliableDatagram.h>                      // biblioteca Radiohead reliableDatagram
#include <RH_ASK.h>                                  // biblioteca Radiohead ASK
#include <SPI.h>                                     // biblioteca SPI
#define TX_ADDRESS 1                                 // endereço do transmissor
#define RX_ADDRESS 2                                 // endereço do recept
RH_ASK driver;                                       // instância RH ASK
RHReliableDatagram gerente(driver, TX_ADDRESS);      // configurando o gerenciador
uint8_t count = 1;                                   // contador
uint8_t data[40] = "Mensagem de teste";                // mensagem a ser enviada
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];                 // buffer da mensagem
void setup()
{
  Serial.begin(9600);                                // inicializa console serial 9600 bps
  if (!gerente.init())                               // se a inicialização do gerenciador falhar
    Serial.println("Falha na inicializacao");        // print na console serial
}
void loop()
{
  int numero,i;
  if(Serial.available() > 0){
     numero = Serial.readBytesUntil (13,data,40);
    data[numero] = 0;
    Serial.print("Transmitindo mensagem n. ");                // print na console serial
    Serial.println(count);                                    // print do contador 
    for(i = 0; i < strlen(data); i++){
      Serial.write(data[i]);
    }
    if (!gerente.sendtoWait(data, sizeof(data), RX_ADDRESS))  // se gerenciador enviar mensagem 
    {
      count++;                                                // incrementa contador 
    }
    delay(500);
  }
                                                 // atraso 0,5 segundo
}