#awk -f EstadisticasCondados.awk  censo2000.txt
BEGIN{
	FS= "\t";
	nombreMayorDensidadPoblacional = "hola";
	valorMayorPoblacion = 0;

	nombreMenorDensidadPoblacional = "hola";
	valorMenorPoblacion = 10;

	nombreMayorCantidadAgua = "hola";
	valorMayorAgua = 0;

	nombreMenorCantidadAgua = "hola";
	valorMenorAgua= 1;
	#print "Nombre Condado" "\t" "Densidad Poblacional" "\t" "Porcentaje de agua"
	printf "Nombre Condado\tDensidad Poblacional\tPorcentaje Agua\n"
}
{
if (NR!=1){
	#print $1 "\t" ($2 / $4) "\t" ($3*100) / ($3+$4);

	printf"%s\t%s\t%s\n", $1, ($2 / $4), $3 / ($3+$4);

	if(valorMayorPoblacion < ($2 / $4)){
		valorMayorPoblacion = ($2 / $4)
		nombreMayorDensidadPoblacional = $1
	}
	if (valorMenorPoblacion > ($2 / $4)){
		valorMenorPoblacion = ($2 / $4)
		nombreMenorDensidadPoblacional = $1
	}
	if (valorMayorAgua < (($3) / ($3+$4)) ){
		valorMayorAgua = (($3) / ($3+$4))
		nombreMayorCantidadAgua = $1
	}
	if (valorMenorAgua > (($3) / ($3+$4))){
		valorMenorAgua = (($3) / ($3+$4));
		nombreMenorCantidadAgua = $1
	}
}


}

END{
	print "\nMayor densidad de poblacion "nombreMayorDensidadPoblacional " " valorMayorPoblacion;
	print "Menor densidad de poblacion "nombreMenorDensidadPoblacional " " valorMenorPoblacion;
	print "Mayor porcentaje de agua "nombreMayorCantidadAgua " " valorMayorAgua;
	print "Menor porcentaje de agua "nombreMenorCantidadAgua " " valorMenorAgua;

}