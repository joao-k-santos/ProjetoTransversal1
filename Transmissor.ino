#include <VirtualWire.h>

#include <VirtualWire.h>

// Código de funcionamento Transmissor RF
// Projeto de comunicação sem fio Arduino
 
#include <VirtualWire.h>; // Inclui biblioteca necessária para comunicação
 
void setup() {
Serial.begin(9600);      // Configura a comunicação serial em 9600
 
vw_set_tx_pin(12);        // Configura o pino Digital utilizado pelo Módulo
vw_setup(2000);          // Bits per segundo
 
Serial.println("Digite o texto que deseja Enviar ..."); //Imprime na Porta Serial
}
 
void loop() {
char data[40];
int numero;
 
if (Serial.available())  {
numero = Serial.readBytesUntil (13, data, 40);
data[numero] = 0;
Serial.print("Enviado : ");    // Imprime na porta serial a mensagem em destaque
Serial.println(data);          // Imprime o valor enviado
 
send(data);                    // Envia o valor para o receptor
}
}
 
void send (char *message) {
vw_send((uint8_t *)message, strlen(message));
vw_wait_tx();                  // Aguarda o envio de dados
}