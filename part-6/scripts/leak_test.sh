for file in $(ls tests/cases/); do
	printf "\n"
	echo $file
	valgrind --log-file="tmplk.txt" --leak-check=full --show-leak-kinds=all ./etapa6 < tests/cases/$file
	if grep -q "no leaks are possible" tmplk.txt; then
		if grep -q "0 errors" tmplk.txt; then
			echo "    SUCCESS!"
		else
			echo "    Has ERRORS"
		fi
	else
		echo "    Has LEAKS"
	fi
done
rm -f tmplk.txt
