# José Ignacio Viquez Rojas b78451
# Correr con: sed -f Viquez_Ignacio_docbook.sed datebook2.txt
#1
/\(<article>\|<\/article>\)/d 
#2
s/<title>/Title: /
s/<\/title>//
#3
/\(<para>\|<\/para>\)/{
	s/\(<para>\|<\/para>\)//
	/^$/d
}
#4
s/\(<emphasis>\|<\/emphasis>\)/*/ 
#5
s/web/Web/

#8 
/<listing>/,/<\/listing>/ {
	s/\&lt;/\</g
	s/\&gt;/\>/g
	s/\&amp;/\&/g
}

#6
s/<listing>/---begin listing/
#7
s/<\/listing>/---end listing/
