void muovi(int dx, int sx, int time=0){
	if(time!=0){
		setMotorSpeed(motorDx, dx);
		setMotorSpeed(motorSx, sx);
		delay(time);
	} else {
		setMotorSpeed(motorDx, dx);
		setMotorSpeed(motorSx, sx);
	}
}
void muori(){
	muovi(0,0);
	while(1);
}
bool controlloVerde(long red, long green, long blue){
	if(green>25 && green<45 && blue>8 && blue<20 && red>3 && red<12) return true;
	else return false;
}
bool controlloVerdeDx(){
	return controlloVerde(redValueDx, greenValueDx, blueValueDx);
}
bool controlloAlzato(long red, long green, long blue){
	if(green<6 && green<6 && blue<6 ) return true;
	else return false;
}
bool controlloAlzatoDx(){
	return controlloVerde(redValueDx, greenValueDx, blueValueDx);
}
bool controlloAlzatoSx(){
	return controlloAlzato(redValueSx, greenValueSx, blueValueSx);
}
bool controlloAlzatoCC(){
	return controlloAlzato(redValueCC, greenValueCC, blueValueCC);
}
bool controlloVerdeSx(){
	return controlloVerde(redValueSx, greenValueSx, blueValueSx);
}

bool controlloNero(long red, long green, long blue){
	if(red<6 && green<6 && blue<6) return true;
	else return false;
}
bool controlloNero0(long red, long green, long blue){
	if(red<6 && green<6 && blue<10) return true;
	else return false;
}
bool controlloNeroDx(){
	return controlloNero(redValueDx, greenValueDx, blueValueDx);
}
bool controlloNeroCC(){
	return controlloNero0(redValueCC,greenValueCC,blueValueCC);
}
bool controlloNeroSx(){
	return controlloNero(redValueSx, greenValueSx, blueValueSx);
}
bool grigino(long red, long green, long blue){
	if(red<10 && green<10 && blue<10) return true;
	else return false;
}
bool griginoDx(){
	return grigino(redValueDx, greenValueDx, blueValueDx);
}
bool griginoSx(){
	return grigino(redValueSx, greenValueSx, blueValueSx);
}
bool controlloBianco(long red, long green, long blue){
	if(red>30 && green>30 && blue>30) return true;
	else return false;
}
bool controlloBiancoDx(){
	return controlloBianco(redValueDx, greenValueDx, blueValueDx);
}
bool controlloBiancoSx(){
	return controlloBianco(redValueSx, greenValueSx, blueValueSx);
}
void verdeDx(){
	repeatUntil(controlloBianco(redValueDx, greenValueDx, blueValueDx)) {
		muovi(30,30);
	}
	muovi(-30,30);
	delay(600);
	while(color0>REFLECTED_BLACK){
		muovi(-30,30);
	}
}
void verdeSx(){
	repeatUntil(controlloBianco(redValueSx, greenValueSx, blueValueSx)) {
		muovi(30,30);
	}
	muovi(30,-30);
	delay(600);
	while(color0>REFLECTED_BLACK){
		muovi(30,-30);
	}
}
void doppioVerde(){
	muovi(-30,-30);
	delay(200);
	while(!grigino(redValueDx, greenValueDx, blueValueDx)){
	clearTimer(T1);
	muovi(-30,30);
	}
	muovi(-30,-30);
	delay(500);
}
void evitaOstacolo(){
	muovi(-50,-50);
	delay(400);
	muovi(-50,50);
	delay(1150);
	muovi(60,20);
	delay(2000);
	muovi(50,-50);
	delay(300);
	muovi(50,50);
	delay(350);
	while(!grigino(redValueDx, greenValueDx, blueValueDx)){
	if(!grigino(redValueSx, greenValueSx, blueValueSx)){ //se prende il nero con il sensore di sx ha sbagliato e deve raddrizzarsi
		//procedura per raddrizzarsi
	} else {
		muovi(60,15);
	}
	}
	mode=0;
}
