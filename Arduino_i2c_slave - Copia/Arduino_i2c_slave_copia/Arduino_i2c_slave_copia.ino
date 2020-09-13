#include <Wire.h>
#include <NewPing.h>

#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define TRIGGER_PIN_FRONT 2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_FRONT 3  // Arduino pin tied to echo pin on the ultrasonic sensor.

NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#define BUFFER_LENGTH 32
byte InBuffer[BUFFER_LENGTH], OutBuffer[BUFFER_LENGTH];
bool InError, OutError;
byte InLength, OutLength;
char b1;
bool error_flag = false;
byte distance[4];
/******************************************************************/
/* Il pacchetto che viene scambiato è così composto:              */
/* Byte       Descrizione                                         */
/* da 0 a N-1 Dati utili del pacchetto                            */
/* N          Numero dei byte che costituiscono i dati utili      */
/* N+1        Somma di controllo                                  */
/******************************************************************/
void setup() {
  b1 = 5;
  Wire.begin(0xA); // Indirizzo a cui connettersi (nell'EV3 il valore va raddoppiato)
  //Wire.setClock(400000); // Valore di default
  Wire.onReceive(Receive); // Impostazione della routine di risposta per l'evento di ricezione caratteri dall'IIC
  Wire.onRequest(Request);
  Serial.begin(115200);
}
void loop() {
  //Serial.write('A');
  distance[0] = sonarFront.ping_cm();
  Serial.println(distance[0]);
  //Serial.write('B');
  distance[1] = 'a';
  //Serial.write('C');
  distance[2] = 'a';
  //Serial.write('D');
  distance[3] = 'a';
}

void requestDistance() {
}
void Request() {
  for (int i = 0; i < sizeof(distance); i++) {
    Wire.write(distance[i]);
  }
}

// Routine di risposta per l'evento di ricezione caratteri dall'IIC
void Receive(int Bytes) {
  if (Wire.read() == b1) {
    //bel reset
  }
}
