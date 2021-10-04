#awk -f Ejericio2partea.awk badLoginArenal.txt secure secure-20210418 secure-20210426 secure-20210502 secure-20210510
#Pasos 
# 1. Guardar las fechas en un arreglo de fechas
# 2. Hacer el método que compara fechas 
# 3. Sumar solo si 2 es falso 


BEGIN{
	FS= " ";
	print "IP" "\t" "CantidadAtaques";
}

function compararFechas(fecha1, fecha2){

	#print "Fecha1: " fecha1 "Fecha2: "fecha2;
	split(fecha1, a, "---");
	horaAtaqueAComprobar = substr(fecha2,1,12);
	#print "Hora modificada del secure:" horaAtaqueAComprobar;
	introducir = 0;
	for (key in a){
		#print "Valor del arreglo a: "a[key];
		# Primero la comprobación por mes 
		mesArreglo = substr(a[key],1,3);
		mesAtaqueSecure = substr(horaAtaqueAComprobar, 1,3);
		#print "MEses:" mesArreglo, mesAtaqueSecure;

		if (mesArreglo == mesAtaqueSecure){
			#print "Mismo mes"
			DiaArreglo = substr(a[key],4,4);
			DiaAtaqueSecure = substr(horaAtaqueAComprobar,4,4);
			#print "Dias: " DiaArreglo, DiaAtaqueSecure;
			# Comprobamos por día del mes
			if(DiaArreglo == DiaAtaqueSecure){
				#print "Mismo dia";
				# Comprobamos por hora con la diferencia de un minuto
				horaArreglo = substr(a[key],7);
				horaAtaqueSecure = substr(horaAtaqueAComprobar,7);
				#print "HoraArreglos " horaArreglo;
				#print "HoraAtaqueSecure " horaAtaqueSecure;
				
				if (horaArreglo == horaAtaqueSecure){
					# Tenemos un ataque que ya habiamos visto
					#print"Es el mismo atacque!";
					introducir = 1;
				}
			}
		}	
	}
	if (introducir == 0){
		# Recorrio todo el arreglo de los ataques de esta IP y no encontro uno con su misma fecha entones es un ataque nuevo
		# Debemos de cocatenar la mica al final del la posición de la hila
		#print "Valor a modificar:"
		#print fecha1;
		fecha1 = fecha1 "---" horaAtaqueAComprobar;
		#print "Valor nuevo:";
		#print fecha1;
	}
	return fecha1;
}
{
	if ($2 == "ssh:notty"){
		#Archivo del arenal primero se lee este archivo
		#Crear un arreglo para meter las IPS y aumentar la cantidad de veces reportadas
		arregloIPS[$10] = $10;

		if (!(arregloArenal[$10] > 0)){
			arregloTiempoArenal[$10] = "0";
			cantidadAtaquesIP[$10]= 0;
		}

		fecha = $4 " "$5 " "$8;
		#print fecha;

		if(arregloTiempoArenal[$10] == "0"){
			#Primera vez que vamos a meter una fecha entonces borramos el 0 y ponemos la fecha 
			arregloTiempoArenal[$10] = fecha;
			cantidadAtaquesIP[$10] = cantidadAtaquesIP[$10] +1;

		}else{
			#Quiere decir que ya han habido otros ataques de la misma IP y que ocupamos concatenar la nueva fecha
			arregloTiempoArenal[$10] = arregloTiempoArenal[$10]"---"fecha;
			cantidadAtaquesIP[$10] = cantidadAtaquesIP[$10] +1;
		}
		

		arregloArenal[$10] = arregloArenal[$10] + 1; Original
		arregloSecure[$10] = 0;
	}else{
		#Archivos de secure
		if ($6 == "Failed"){
			# Se encontro un intento de intrusión

			for (i = 0;i < 20; i++){
				if($i == "from"){
					# parte de la ubicacion de IP's
					IP = i+1;
					direccion = $IP;
					arregloIPS[$IP] = $IP;

					
					if (!(arregloSecure[direccion] > 0) && !(arregloArenal[direccion] >0)){
						# Primera vez que se observa esta IP en los archivos
						#print "hola";
						arregloArenal[direccion] = 0;
						arregloTiempoArenal[direccion] =  "0";
					}

					fechaNueva = $1" "$2" "$3;
					horaAtaqueNuevo = substr(fechaNueva,1,12);
					#print "Hora del nuevo Ataque:" horaAtaqueNuevo;

					if(arregloTiempoArenal[direccion] == "0"){
						#Primera vez que encontramos esta IP
						#print " primera vez";
						arregloTiempoArenal[direccion] = horaAtaqueNuevo;

					}else{
						#Quiere decir que ya han habido otros ataques de la misma IP y que ocupamos concatenar la nueva fecha
						arregloTiempoArenal[direccion] = arregloTiempoArenal[direccion]"---"horaAtaqueNuevo;
					}
		
					arregloSecure[$IP] = arregloSecure[$IP]+1;

				}
			}
			# Primero encontrar la fecha de este ataque
			fechaSecure = $1" "$2" "$3;
			#print "Direccion a la que se le calcula: " arregloIPS[direccion];
			#print "FechaSecure: " fechaSecure;

			fechaModificada = compararFechas(arregloTiempoArenal[direccion],fechaSecure);
			arregloTiempoArenal[direccion] = fechaModificada;
			#print "La fecha del arreglo quedo como: ";
			#print arregloTiempoArenal[direccion];
			#print "--------------------------";

		}
	}

}

END{

	#Calcular el total de ataques para cada IP
	for(key in arregloIPS){
		split(arregloTiempoArenal[key], a, "---"); # Crea un vector "a" dividiendo el string de adentro
		cantidadAtaques = length(a);
		arregloCantidadAtaquesFinal[key] = cantidadAtaques;
	}

	for (key in arregloIPS){
		print arregloIPS[key] "\t" arregloCantidadAtaquesFinal[key];
	}


	for(key in arregloTiempoArenal){
		#print "Hilera del arreglo del tiempo para la IP: "arregloIPS[key] " es: " arregloTiempoArenal[key];
	}
	print "----------------------------------";

	#print length(arregloIPS)
}