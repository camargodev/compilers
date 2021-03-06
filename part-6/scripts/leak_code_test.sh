for file in $(ls tests/code-cases/*.txt); do
	valgrind --log-file="tmplk.txt" --leak-check=full --show-leak-kinds=all ./etapa6 "none" < $file
	if grep -q "no leaks are possible" tmplk.txt; then
		if grep -q "0 errors" tmplk.txt; then
			echo $file "= SUCCESS"
		else
			echo $file "= has ERRORS"
		fi
	else
		echo $file "= has LEAKS"
	fi
done
rm -f tmplk.txt
