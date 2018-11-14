counter=0
for file in $(ls tests/code-cases/*.txt); do
	shortfile="$(basename $file)" 
	echo $shortfile
	./etapa6 < tests/code-cases/$shortfile > tests/code-cases/temp$shortfile
	diff tests/code-cases/temp$shortfile tests/code-cases/results/$shortfile
	rm -f tests/code-cases/temp$shortfile
	counter=$((counter+1))
done
