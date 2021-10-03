#awk -f Ejericio2partea.awk badLoginArenal.txt secure secure-20210418 secure-20210426 secure-20210502 secure-20210510
BEGIN{
	FS= " ";
	
	print "IP" "\t" "ArenalBadLogin" "\t" "secure(s)" "\t" "Ambos";
}
{
	if ($2 == "ssh:notty"){
		#Archivo del arenal primero se lee este archivo
		#Crear un arreglo para meter las IPS y aumentar la cantidad de veces reportadas
		arregloIPS[$10] = $10;
		arregloArenal[$10] = arregloArenal[$10] + 1;
		arregloSecure[$10] = 0;
	}else{
		#Archivos de secure
		if ($6 == "Failed"){
			# Se encontro un intento de intrusión

			for (i = 0;i < 20; i++){
				if($i == "from"){
					IP = i+1;
					direccion = $IP;
					arregloIPS[$IP] = $IP;
					arregloSecure[$IP] = arregloSecure[$IP]+1;
					if (!(arregloArenal[direccion] >0)){
						arregloArenal[direccion] = 0;
					}
				}
			}
			#Idea original de usar una expresion regular para indexar
			#arregloIPS[/[0-9]?[0-9]?[0-9]\.[0-9]?[0-9]?[0-9]\.[0-9]?[0-9]?[0-9]\.[0-9]?[0-9]?[0-9]/] = /[0-9]?[0-9]?[0-9]\.[0-9]?[0-9]?[0-9]\.[0-9]?[0-9]?[0-9]\.[0-9]?[0-9]?[0-9]/;
		}
	}

}

END{

	for(key in arregloIPS){
		if ( (arregloArenal[key] != 0) && (arregloSecure[key]!= 0) ){
			# Esta en ambos 
			arregloAmbos[key] = "*";
		}	
		print arregloIPS[key] "\t" arregloArenal[key] "\t" arregloSecure[key]"\t" arregloAmbos[key]
	}

	#print length(arregloIPS)
}