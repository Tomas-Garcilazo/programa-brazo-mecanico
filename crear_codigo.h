void escribir_base(){
	FILE *base = fopen("base.c", "r");
	fseek(base, 0, 2);

	int tamanio_archivo = ftell(base)/sizeof(char);

	char *texto = new char[tamanio_archivo+1];

	fseek(base, 0, 0);
	fread(texto, tamanio_archivo, 1, base);
	fclose(base);
	texto[tamanio_archivo]='\0';
	cout << texto << endl;
}

void cargar_matriz(int mapa[49][65]){
	FILE *f_matriz = fopen("archivo_matriz.dat", "rb");
	fread(mapa, sizeof(int)*49*65, 1, f_matriz);
	fclose(f_matriz);
}

void escribir_instrucciones(){
	int mapa[49][65];
    cargar_matriz(mapa);
    /// escribir el codigo segun los valores de la matriz
    int tam = 0;
    cout << "const int vec[][2] = {";
	for (int x = 0; x < 65; x++){
		for (int y = 0; y < 49; y++){
			if(mapa[y][x] == 1){
				//cout << "\t//y: " << y << " x: " << x << endl;
				//cout << "{" << y << ", " << x << "}";
				cout << x << ", " << y << ", ";
				tam++;
			}
		}
	}
	cout << "};" << endl;
	cout << "const int TAM = " << tam <<";" << endl << endl << endl;
}
void escribir_codigo_final(){
	freopen("codigo_generado/codigo_generado.ino","w", stdout);
	escribir_instrucciones();
	escribir_base();
	fclose (stdout);
	freopen("CON","w",stdout);
}