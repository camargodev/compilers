rm -f tests/tempresults.txt
for file in $(ls tests/cases/); do
	#echo "\nFile:" $file
	./etapa6 "none" < tests/cases/$file
	echo $? >> tests/tempresults.txt
done
