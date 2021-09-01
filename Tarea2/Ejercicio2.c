#include <stdio.h>
int main(int argc, char const *argv[])
{
	char caracter;
	printf("Ingrese la hilera que desea evaluar, finalice la hilera con un enter(cambio de linea): \n");
residuo0: //residuo  inicial
	scanf("%c",&caracter);
	if (caracter == '0'){
		//Loop en residuo0
		goto residuo0;
	}else if (caracter == '1'){
		//Nos movemos al residuo1
		goto residuo1;
	}else if (caracter == '2'){
		//Nos movemos al residuo2
		goto residuo2;
	}else if (caracter == ' '){
		//Hilera nula
		goto MensajeFinal;
	}else if (caracter == '\n'){
		//Fin de la hilera o hilera nula con cambio de linea
		goto MensajeFinal;
	}

residuo1:
	scanf("%c",&caracter);
	if (caracter == '0'){
		//Nos movemos al residuo3
		goto residuo3;
	}else if (caracter == '1'){
		//Nos movemos al residuo0
		goto residuo0;
	}else if (caracter == '2'){
		//Loop en residuo1
		goto residuo1;
	}else if (caracter == '\n'){
		//Hilera no aceptada
		goto MensajeRechazo;
	}

residuo2:
	scanf("%c",&caracter);
	if (caracter == '0'){
		//Loop residuo2
		goto residuo2;
	}else if (caracter == '1'){
		//Nos movemos al residuo3
		goto residuo3;
	}else if (caracter == '2'){
		//Nos movemos al residuo0
		goto residuo0;
	}else if (caracter == '\n'){
		//Hilera no aceptada
		goto MensajeRechazo;
	}

residuo3: 
	scanf("%c",&caracter);
	if (caracter == '0'){
		//Nos movemos al residuo1
		goto residuo1;
	}else if (caracter == '1'){
		//Nos movemos al residuo2
		goto residuo2;
	}else if (caracter == '2'){
		//Loop residuo3
		goto residuo3;
	}else if (caracter == '\n'){
		//Hilera no aceptada
		goto MensajeRechazo;
	}
	

MensajeFinal:
	printf("Se acepto la hilera introducida.\n");
	return 0;

MensajeRechazo:
	printf("La hilera no es parte del lenguaje.\n" );
	return 0;
}