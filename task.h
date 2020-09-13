task update(){
	while(1){
		displayCenteredBigTextLine(4,"%s",mode);
		color0=getColorReflected(sensor0);
		getColorRGB(sensorDx, redValueDx, greenValueDx, blueValueDx); /*Acquisizione dei valori dei canali rgb nelle variabili*/
		getColorRGB(sensorSx, redValueSx, greenValueSx, blueValueSx);
		error=(int)(redValueDx-redValueSx*1.1); //calcolo l'errore e moltiplico il canale sx per un guadagno*/
		p_value = (int)(error * kP); //calcolo il parametro proporzionale del pid
		//i_value = 0;
		//d_value = (int)(error- error_prec) * kD;
		PID = p_value + i_value + d_value;
		if(redValueDx>redOnSilver && redValueSx>redOnSilver){ // se entrambi vedono l'argento
			mode=1; //modalità raccogli palline
		}
		//if(error<-5 || error>5) { //se l'errore è prossimo allo zero per un tempo
		//	clearTimer(T1);
		//}
		//if(time1[T1]>Max_Timing){ //se è passato un tempo maggiore di quello prefissato per cui il robot è rimasto con un errore costante allora
		//	//inizio procedura ricerca linea
		//	mode=2;
		//}
		error_prec=error;
	}
}
