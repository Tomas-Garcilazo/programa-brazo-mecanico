void escribir_base(){
	FILE *base = fopen("base.txt", "r");
	fseek(base, 0, 2);

	int tamanio_archivo = ftell(base)/sizeof(char)-13;

	char *texto = new char[tamanio_archivo];

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
	for (int y = 0; y < 49; y++){
		for (int x = 0; x < 65; x++){
				if(mapa[y][x] == 1){
				cout << "\t//y: " << y << " x: " << x << endl;
			}
		}
	}
    cout << "}";

}
void escribir_codigo_final(){
	freopen("codigo_generado/codigo_generado.ino","w", stdout);
	escribir_base();
	escribir_instrucciones();
	fclose (stdout);
	freopen("CON","w",stdout);
}