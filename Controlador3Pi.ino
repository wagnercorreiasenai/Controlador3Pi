#include <HardwareSerial.h>

HardwareSerial SerialPort(2);  // use UART2
int ledStatus = 2;

char bufferSerial[100];
int idxBufferSerial = 0;

void setup() {
  //Ativa a serial
  SerialPort.begin(9600, SERIAL_8N1, 16, 17);
  Serial.begin(9600);

  pinMode(ledStatus, OUTPUT);
  digitalWrite(ledStatus, HIGH);
}

void enviarComando(char comando[100]) {
  digitalWrite(ledStatus, LOW);
  SerialPort.print(comando);
  Serial.print(comando);
  digitalWrite(ledStatus, HIGH);
}

void lerSerial() {
  if (Serial.available()) {
    char texto = Serial.read();
    gerenciarBuffer(texto);
  }
}

void gerenciarBuffer(char c) {

  bool zerarBuffer = false;

  //Incrementa o buffer
  if (c != '\n') {
    bufferSerial[idxBufferSerial] = c;
    idxBufferSerial++;
    zerarBuffer = false;
  } else {
    zerarBuffer = true;
  }

  if (zerarBuffer) {
    bufferSerial[idxBufferSerial] = '\n';
    enviarComando(bufferSerial);
    memset(bufferSerial, 0, strlen(bufferSerial));
    idxBufferSerial = 0;
  }
}

void loop() {
  //lerSerial();
  //teste de comandos
  SerialPort.println("andg");
  delay(4000);
  SerialPort.println("andf35");
  delay(8000);
  SerialPort.println("ande1");
  delay(2000);
  SerialPort.println("andd1");
  delay(2000);
  SerialPort.println("andf23");
  delay(5000);
}
