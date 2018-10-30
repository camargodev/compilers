rm -f tests/tempresults.txt
for file in $(ls tests/cases/); do
	./etapa5 < tests/cases/$file
	echo $? >> tests/tempresults.txt
done
