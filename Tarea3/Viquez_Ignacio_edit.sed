Jose Ignacio
sed '1i\PERSONNEL FILE\' datebook.txt
sed '/500$/d' datebook.txt
sed 's/\([A-Z]\{1,\}[a-z]\{0,\}\) \([A-Z]\{1,\}[a-z]\{0,\}\)/\2 \1/' datebook.txt
sed '$a\THE END\' datebook.txt