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
	echo $/ >> bash_result
	echo "'"$USER"'" >> bash_result
	echo '"'$USER'"' >> bash_result
	"echo | ola" >> bash_result
	echo "exit_code ->$? user ->$USER home -> $HOME" >> bash_result
	echo 'exit_code ->$? user ->$USER home -> $HOME' >> bash_result
	echo "$" >> bash_result
	echo '$' >> bash_result
	echo $ >> bash_result
	echo $? >> bash_result
	echo $?HELLO >> bash_result
	echo $?HE$?LLO$? >> bash_result
	echo "hi" | cat | cat | cat | cat | cat | cat | cat >> bash_result
	echo $USER >> bash_result
	echo "'">USER"'" >> bash_result
	echo test "'">USER1"'" >> bash_result
	echo test "'">USER2"'" test >> bash_result
	echo test "'">USER3"'" "test" >> bash_result