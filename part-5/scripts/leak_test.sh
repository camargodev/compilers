rm -f tests/tempresults.txt
for file in $(ls tests/cases/); do
	echo $file
	valgrind --leak-check=full --show-leak-kinds=all ./etapa5 < tests/cases/$file
done
