#include <Wire.h>
#include <NewPing.h>

#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define BUFFER_LENGTH 8

#define TRIGGER_PIN_FRONT 2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_FRONT 3  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN_BACK 4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_BACK 5  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN_LEFT 6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_LEFT 7  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN_RIGHT 8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_RIGHT 9  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define LIMIT_DX 9
#define LIMIT_SX 10
#define BT_PIN 11

NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK, MAX_DISTANCE);
NewPing sonarLeft(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT, MAX_DISTANCE);
NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);

byte InBuffer[BUFFER_LENGTH], OutBuffer[BUFFER_LENGTH];
bool InError, OutError;
byte InLength, OutLength;
char b1;
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
  pinMode(LIMIT_DX, INPUT_PULLUP);
  pinMode(LIMIT_SX, INPUT_PULLUP);
  pinMode(BT_PIN, INPUT_PULLUP);
  Wire.begin(0xA); // Indirizzo a cui connettersi (nell'EV3 il valore va raddoppiato)
  //Wire.setClock(400000); // Valore di default
  Wire.onReceive(Receive); // Impostazione della routine di risposta per l'evento di ricezione caratteri dall'IIC
  Wire.onRequest(Request);
  Serial.begin(115200);
}
void loop() {
  /*Serial.write('A');
    OutBuffer[0] = Serial.read();
    Serial.println(OutBuffer[0]);
    Serial.write('B');
    OutBuffer[1] = Serial.read();
    Serial.println(OutBuffer[1]);
    Serial.write('C');
    OutBuffer[2] = Serial.read();
    Serial.println(OutBuffer[2]);
    Serial.write('D');
    OutBuffer[3] = Serial.read();
    Serial.println(OutBuffer[3]);*/
  OutBuffer[0] = !digitalRead(BT_PIN);
  OutBuffer[1] = !digitalRead(LIMIT_DX);
  OutBuffer[2] = !digitalRead(LIMIT_SX);
  OutBuffer[3] = sonarFront.ping_cm();
  OutBuffer[4] = sonarBack.ping_cm();
  OutBuffer[5] = sonarLeft.ping_cm();
  OutBuffer[6] = sonarRight.ping_cm();
}

void Request() {
  Wire.write(OutBuffer[0]);
  Wire.write(OutBuffer[1]);
  Wire.write(OutBuffer[2]);
  Wire.write(OutBuffer[3]);
  Wire.write(OutBuffer[4]);
  Wire.write(OutBuffer[5]);
  Wire.write(OutBuffer[6]);
  /*for (int i = 0; i < sizeof(OutBuffer); i++) {
    Wire.write(OutBuffer[i]);
    }*/
}

// Routine di risposta per l'evento di ricezione caratteri dall'IIC
void Receive(int Bytes) {
  if (Wire.read() == b1) {
    //bel reset
  }
}
