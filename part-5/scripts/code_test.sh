for file in $(ls tests/code-cases/*.txt); do
	shortfile="$(basename $file)" 
	./etapa5 < tests/code-cases/$shortfile > tests/code-cases/temp$shortfile
	diff tests/code-cases/temp$shortfile tests/code-cases/results/$shortfile
	rm -f tests/code-cases/temp$shortfile
done
