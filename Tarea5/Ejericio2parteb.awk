#awk -f Ejericio2partea.awk badLoginArenal.txt secure secure-20210418 secure-20210426 secure-20210502 secure-20210510
#Pasos 
# 1. Guardar las fechas en un arreglo de fechas
# 2. Hacer el método que compara fechas 
# 3. Sumar solo si 2 es falso 


BEGIN{
	FS= " ";
	print "IP" "\t" "ArenalBadLogin" "\t" "secure(s)" "\t" "Ambos";
}

function compararFechas(fecha1, fecha2, archivo){
	#print "Parámetros: " fecha1 "\t"fecha2
	#Ejemplo de parámetros: Parámetros: Thu May 6 01:12 01:12	Wed May 5 18:48 18:48

	#Primero hay que hacer algo con los días 


	#Si los días estan bien revisamos las horas 
	if (archivo == 1){
		# son los del arenal
		horaAtaqueAnterior = substr(fecha1,17); 
		horaNuevoAtaque = substr(fecha2,17);
		print (horaNuevoAtaque - horaAtaqueAnterior)*1;
	}
}
{
	if ($2 == "ssh:notty"){
		#Archivo del arenal primero se lee este archivo
		#Crear un arreglo para meter las IPS y aumentar la cantidad de veces reportadas
		arregloIPS[$10] = $10;

		if (!(arregloArenal[$10] > 0)){ # si el valor es menor a 0 entonces es el primer ataque para esta IP 
			fecha = $3" "$4 " "$5 " "$6 " "$8;
			#print fecha
			arregloTiempo[$10] = fecha
			arregloArenal[$10] = arregloArenal[$10] + 1;
		}else {
			# ya han habido otros ataques debemos de comparar la fecha vieja y la de la nueva linea
			# como en el archivo del arenal vienen ordenadas no hemos de preocuparnos mucho por esto
			fechaNuevoAtaque = $3" "$4 " "$5 " "$6 " "$8;
			compararFechas(arregloTiempo[$10], fechaNuevoAtaque,1);
			arregloArenal[$10] = arregloArenal[$10] + 1;
		}

		#arregloArenal[$10] = arregloArenal[$10] + 1; Original
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
		}
	}

}

END{

	for(key in arregloIPS){
		if ( (arregloArenal[key] != 0) && (arregloSecure[key]!= 0) ){
			# Esta en ambos 
			arregloAmbos[key] = "*";
		}	
		print arregloIPS[key] "\t" arregloArenal[key] "\t" arregloSecure[key]"\t" arregloAmbos[key] "\t" arregloTiempo[key]
	}

	print length(arregloIPS)
}