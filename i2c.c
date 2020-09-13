#pragma config(Sensor, S1, TIR, sensorI2CCustom)
#define ARDUINO_ADDRESS 	0x14
#define ARDUINO_PORT 			S1
#define BUFFER_LENGTH			32
//buffer di 8 perchè 4 byte sono i sensori di distanza, 2 byte i pitch e roll del gyro e 2 byte i finecorsa
// Siccome l'I2C viaggia a 10KHz per trasmettere un byte serve circa 1ms.
// Quindi il time outi mi deve consentire almeno la trasmissione del pacchetto
// di dimensioni massime

#define TIME_OUT	BUFFER_LENGTH + 20

ubyte BufferTx[BUFFER_LENGTH + 3];
ubyte BufferRx[BUFFER_LENGTH];

/******************************************************************************/
/* Il pacchetto di trasmissione è così composto:                              */
/*                                                                            */
/* Byte       Descrizione                                                     */
/*    0       Numero di byte del pacchetto ovvero lunghezza del buffer da tra-*/
/*            smettere più due byte perb l'intestazione (il byte di indirizzo  */
/*            non va contato)                                                 */
/*    1       Indirizzo dell'Arduino nel bus I2C (moltiplicato per 2 rispetto */
/*            a quanto visibile da Arduino)                                   */
/*    2       Somma di controllo. La somma di tutti i byte è nulla            */
/* da 3 a N   Buffer da trasmettere (composto da N-3 byte)                    */
/******************************************************************************/
/******************************************************************************/
/* Il pacchetto di ricezione è così composto:                                 */
/*                                                                            */
/* Byte       Descrizione                                                     */
/* da 0 a N-2 Buffer di ricezione (composto da N-2 byte)                      */
/*   N-1      Numero di byte del pacchetto ovvero lunghezza del buffer da ri- */
/*            cezione più due byte in coda (la lunghezza e la somma di con-   */
/*            trollo)                                                         */
/*    N       Somma di controllo. La somma di tutti i byte è nulla            */
/******************************************************************************/
byte b1;

task main() {
	b1=0xF;
	BufferTx[0] = 5+2; //lunghezza byte + 2
	BufferTx[1] = ARDUINO_ADDRESS; //Indirizzo arduino
	BufferTx[2] = 0; // cksum
	BufferTx[3] = b1;
	BufferTx[4] = b1;
	while(1){
		sendI2CMsg(ARDUINO_PORT, &BufferTx[0], 10);
		for (int bCounter = 0; (bCounter < TIME_OUT) && (nI2CStatus[ARDUINO_PORT] != 0); bCounter++) wait1Msec(1);
		memset((byte *)BufferRx, 0xFF, sizeof(BufferRx)); //punta un po' di memoria per il buffer di ritorno
		readI2CReply(ARDUINO_PORT, &BufferRx[0], 4);
		if(BufferRx[0]!=255) displayCenteredBigTextLine(2, "%d", (BufferRx[0]));
		if(BufferRx[1]!=255) displayCenteredBigTextLine(5, "%d", BufferRx[1]);
		if(BufferRx[2]!=255) displayCenteredBigTextLine(8, "%d", BufferRx[2]);
		if(BufferRx[3]!=255) displayCenteredBigTextLine(11, "%d", BufferRx[3]);
	}
}
