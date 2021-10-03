BEGIN{
	FS = ":";
	total = 0;
}
{
	if (/\*/){ # Revisión de las hileras con un *
		i = 1;
		while(i <= NF){ # Recorremos las palabras de la hilera actual
			#print $i;
			if( ($i ~ /[0-9]$/) && !($i ~ /\*/) && (($i ~ /^[+-]/) || ($i ~ /^[0-9]/))  ){ # Revision de la palabra
				total = total + $i;
				#print $i;
			}
			i= i+1;
		}
	}
}
END{
	print "Total: " total;
}