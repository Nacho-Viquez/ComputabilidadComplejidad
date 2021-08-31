#include <stdio.h>



int main(int argc, char const *argv[])
{
	//prueba();
	char caracter;

inicio: //Estado  inicial
	scanf("%c",&caracter);
	if (caracter == '1'){
		//Nos movemos al estado B
		goto estadoB;
	}else if (caracter == '0'){
		//Nos movemos al estado A
		goto estadoA;
	}else if (caracter == ' '){
		//Hilera nula
		goto MensajeFinal;
	}else if (caracter == '\n'){
		goto MensajeFinal;
	}

estadoA:
	printf("Hola estoy en A\n");
	scanf("%c",&caracter);
	if (caracter == '1'){
		//Nos movemos al estado F
		goto estadoF;
	}else if (caracter == '0'){
		//Nos movemos al estado C
		goto estadoC;
	}else if (caracter == '\n'){
		goto MensajeRechazo;
	}

estadoB:
	printf("Hola estoy en B\n");
	scanf("%c",&caracter);
	if (caracter == '1'){
		//Nos movemos al estado D
		goto estadoD;
	}else if (caracter == '0'){
		//Nos movemos al estado F
		goto estadoF;
	}else if (caracter == '\n'){
		goto MensajeRechazo;
	}

estadoF:
	printf("Hola estoy en F\n");
	scanf("%c",&caracter);
	if (caracter == '1'){
		//Nos movemos al estado I
		goto estadoI;
	}else if (caracter == '0'){
		//Nos movemos al estado G
		goto estadoG;
	}else if (caracter == '\n'){
		goto MensajeRechazo;
	}

estadoC:
	printf("Hola estoy en C\n");
	scanf("%c",&caracter);
	if (caracter == '1'){
		//Nos movemos al estado G
		goto estadoG;
	}else if (caracter == '0'){
		//Nos movemos al estado A
		goto estadoA;
	}else if (caracter == '\n'){
		goto MensajeRechazo;
	}

estadoD:
	printf("Hola estoy en D\n");
	scanf("%c",&caracter);
	if (caracter == '1'){
		//Nos movemos al estado E
		goto estadoE;
	}else if (caracter == '0'){
		//Nos movemos al estado I
		goto estadoI;
	}else if (caracter == '\n'){
		goto MensajeRechazo;
	}

estadoI:
	printf("Hola estoy en I\n");
	scanf("%c",&caracter);
	if (caracter == '1'){
		//Nos movemos al estado J
		goto estadoJ;
	}else if (caracter == '0'){
		//Nos movemos al estado K
		goto estadoK;
	}else if (caracter == '\n'){
		goto MensajeRechazo;
	}

estadoG:
	printf("Hola estoy en G\n");
	scanf("%c",&caracter);
	if (caracter == '1'){
		//Nos movemos al estado K
		goto estadoK;
	}else if (caracter == '0'){
		//Nos movemos al estado F
		goto estadoF;
	}else if (caracter == '\n'){
		goto MensajeRechazo;
	}

estadoE:
	printf("Hola estoy en E\n");
	scanf("%c",&caracter);
	if (caracter == '1'){
		//Nos movemos al estado B
		goto estadoB;
	}else if (caracter == '0'){
		//Nos movemos al estado J
		goto estadoJ;
	}else if (caracter == '\n'){
		goto MensajeRechazo;
	}

estadoJ:
	printf("Hola estoy en J\n");
	scanf("%c",&caracter);
	if (caracter == '1'){
		//Nos movemos al estado F
		goto estadoF;
	}else if (caracter == '0'){
		//Nos movemos al estado de finalizacion
		goto estadoH;
	}else if (caracter == '\n'){
		goto MensajeRechazo;
	}

estadoK:
	printf("Hola estoy en K\n");
	scanf("%c",&caracter);
	if (caracter == '1'){
		//Nos movemos al estado de finalizacion
		goto estadoH;
	}else if (caracter == '0'){
		//Nos movemos al estado I
		goto estadoI;
	}else if (caracter == '\n'){
		goto MensajeRechazo;
	}

estadoH: 
	printf("Hola estoy en H\n");
	scanf("%c",&caracter);
	if (caracter == '1'){
		//Nos movemos al estado G
		goto estadoG;
	}else if (caracter == '0'){
		//Nos movemos al estado J
		goto estadoJ;
	}else if (caracter == '\n'){
		goto MensajeFinal;
	}
MensajeFinal:
	printf("Se acepto la hilera introducida.\n");
	return 0;

MensajeRechazo:
	printf("La hilera no es parte del lenguaje.\n" );
	return 0;

}