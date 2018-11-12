rm -f tests/tempresults.txt
for file in $(ls tests/cases/); do
	echo "\nFile:" $file
	./etapa5 < tests/cases/$file
	echo $? >> tests/tempresults.txt
done
