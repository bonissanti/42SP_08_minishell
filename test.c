	echo hello world >> bash_result
	echo "hello world" >> bash_result
	echo 'hello world' >> bash_result
	echo hello'world' >> bash_result
	echo hello""world >> bash_result
	echo - "" "  " hello >> bash_result
	echo '' >> bash_result
	echo "$PWD" >> bash_result
	echo '$PWD' >> bash_result
	echo "aspas ->'" >> bash_result
	echo "aspas -> ' " >> bash_result
	echo 'aspas ->"' >> bash_result
	echo 'aspas -> " ' >> bash_result
	echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<" >> bash_result
	echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<' >> bash_result
	echo "exit_code ->$? user ->$USER home -> $HOME" >> bash_result
	echo 'exit_code ->$? user ->$USER home -> $HOME' >> bash_result
	echo "$" >> bash_result
	echo '$' >> bash_result
	echo $ >> bash_result
	echo $? >> bash_result
	echo $?HELLO >> bash_result
	echo $?HE$?LLO$? >> bash_result