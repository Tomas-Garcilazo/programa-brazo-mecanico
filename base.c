/// pins motor Y
const int pinENA = 6;
const int pinIN1 = 7;
const int pinIN2 = 8;

const int pinMotor_Y[3] = { pinENA, pinIN1, pinIN2 };

/// pins motor X
const int pinENB = 11;
const int pinIN3 = 9;
const int pinIN4 = 10;

const int pinMotor_X[3] = { pinENB, pinIN3, pinIN4 };

/// constantes
const int TIEMPO_ESPERA = 2000;   //espera entre fases
const int VELOCIDAD = 200;      //velocidad de giro 80% (200/255)

void moveForward(const int pinMotor[3]);
void moveBackward(const int pinMotor[3]);
void marcar_hoja()

void setup(){
	/// setup pins Y
	pinMode(pinENA, OUTPUT);
	pinMode(pinIN1, OUTPUT);
	pinMode(pinIN2, OUTPUT);

	/// setup pins X
	pinMode(pinENB, OUTPUT);
	pinMode(pinIN3, OUTPUT);
	pinMode(pinIN4, OUTPUT);

	marcar_hoja();
}

void loop(){
	/*
	/// move motor Y
	moveForward(pinMotor_Y);
	delay(TIEMPO_ESPERA);
	moveBackward(pinMotor_Y);
	delay(TIEMPO_ESPERA);

	/// move motor X
	moveForward(pinMotor_X);
	delay(TIEMPO_ESPERA);
	*/
}

void moveForward(const int pinMotor[3]){
   digitalWrite(pinMotor[1], HIGH);
   digitalWrite(pinMotor[2], LOW);

   analogWrite(pinMotor[0], VELOCIDAD);
}

void moveBackward(const int pinMotor[3]){
   digitalWrite(pinMotor[1], LOW);
   digitalWrite(pinMotor[2], HIGH);

   analogWrite(pinMotor[0], VELOCIDAD);
}

void marcar_hoja(){
	int x=0, y=0;
	int x_destino, y_destino;
	
	for (int i = 0; i < TAM; i++){

		x_destino = vec[i][0];
		y_destino = vec[i][1];

		if (x < x_destino){
			// va hasta al punto X
			for (x; x < x_destino; x++)
				{ moveForward(pinMotor_X); }

			delay(TIEMPO_ESPERA);
		}
		if (y < y_destino){
			// va hasta al punto Y
			for (y; y < y_destino; y++)
				{ moveForward(pinMotor_Y); }

			delay(TIEMPO_ESPERA);
			
			// vuelve a 0
			for (y; y > 0; y--)
				{ moveBackward(pinMotor_Y); }

			delay(TIEMPO_ESPERA);
		}
	}
}