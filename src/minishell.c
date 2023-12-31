/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:38:13 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/07 17:28:39 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **envp)
	{
	(void)argc;
	(void)argv;
	t_list *tests = NULL;
	// ---- leaks da substr presentes em todos os comandos ----
	// ft_lstadd_back(&tests, ft_lstnew("export"));
	// ft_lstadd_back(&tests, ft_lstnew("export="));
	// ft_lstadd_back(&tests, ft_lstnew("export test"));
	// ft_lstadd_back(&tests, ft_lstnew("export test="));
	// ft_lstadd_back(&tests, ft_lstnew("export test=\'"));
	// ft_lstadd_back(&tests, ft_lstnew("export test=\""));
	// ft_lstadd_back(&tests, ft_lstnew("export test=123")); leak
	// ft_lstadd_back(&tests, ft_lstnew("export test=\"456\"")); leak
	// ft_lstadd_back(&tests, ft_lstnew("export test+="));
	// ft_lstadd_back(&tests, ft_lstnew("export test-=123"));
	// ft_lstadd_back(&tests, ft_lstnew("echo hello world")); 						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo \"hello world\"")); 					//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 'hello world'"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo hello'world'")); 						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo hello\"\"world")); 						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo - \"\" \"  \" hello")); 				//comeu a letra 'o'
	// ft_lstadd_back(&tests, ft_lstnew("echo ''")); 									//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo \"$PWD\"")); 							//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo '$PWD'")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo \"aspas ->'\"")); 						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo \"aspas -> ' \"")); 					//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 'aspas ->\"'")); 						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 'aspas -> \" '")); 					//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo $/")); 					//comeu a ultima aspas
	// ft_lstadd_back(&tests, ft_lstnew("echo \"'\"$USER\"'\"")); 					//comeu a ultima aspas
	// ft_lstadd_back(&tests, ft_lstnew("echo '\"'$USER'\"'"));						//comeu a ultima aspas
	// ft_lstadd_back(&tests, ft_lstnew("\"echo | ola\""));						//comeu a ultima aspas
	// ft_lstadd_back(&tests, ft_lstnew("echo \"exit_code ->$? user ->$USER home -> $HOME\"")); //ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 'exit_code ->$? user ->$USER home -> $HOME'")); //ok
	// ft_lstadd_back(&tests, ft_lstnew("echo \"$\"")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo '$'")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo $"));									//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo $?")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo $?HELLO")); 							//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo $?HE$?LLO$?")); 						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo \"hi\" | cat | cat | cat | cat | cat | cat | cat")); //ok
	// ft_lstadd_back(&tests, ft_lstnew("echo $USER"));
	// ft_lstadd_back(&tests, ft_lstnew("echo \"'\">USER\"'\""));
	// ft_lstadd_back(&tests, ft_lstnew("echo test \"'\">USER1\"'\""));
	// ft_lstadd_back(&tests, ft_lstnew("echo test \"'\">USER2\"'\" test"));
	// ft_lstadd_back(&tests, ft_lstnew("echo test \"'\">USER3\"'\" \"test\""));
	// ft_lstadd_back(&tests, ft_lstnew("pwd")); 										//ok
	// ft_lstadd_back(&tests, ft_lstnew("pwd oi")); 									//ok
	// ft_lstadd_back(&tests, ft_lstnew("export hello"));								//ok
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO=123"));							//ok
	// ft_lstadd_back(&tests, ft_lstnew("export A-")); 									//ok
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO=123 A"));							//ok
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO=\"123 A-\""));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("export hello world"));							//ok
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO-=123 A"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("export ="));									//ok
	// ft_lstadd_back(&tests, ft_lstnew("export = \'"));								//ok
	// ft_lstadd_back(&tests, ft_lstnew("export 123"));									//ok
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO+=123"));							//ok
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO-=123"));							//ok
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO-=\'123\'"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO+=\"123\""));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("unset")); 										//ok
	// ft_lstadd_back(&tests, ft_lstnew("unset HELLO")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("unset HELLO1 HELLO2")); 						//ok
	// ft_lstadd_back(&tests, ft_lstnew("unset HOME")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("unset PATH")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("unset SHELL")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("cd $PATH"));									//ok
	// ft_lstadd_back(&tests, ft_lstnew("cd $PATH oi")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("cd 123123")); 									//ok
	// ft_lstadd_back(&tests, ft_lstnew("exit 123")); 									//ok
	// ft_lstadd_back(&tests, ft_lstnew("exit 298")); 									//ok
	// ft_lstadd_back(&tests, ft_lstnew("exit +100")); 									//ok
	// ft_lstadd_back(&tests, ft_lstnew("exit \"+100\"")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("exit -100")); 									//ok
	// ft_lstadd_back(&tests, ft_lstnew("exit \"-100\"")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("exit -\"100\"")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("exit hello")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("exit 42 world")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile"));  								//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | wc")); 							//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | sort | wc")); 					//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile > outfile")); 					//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | wc > outfile")); 				//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | sort | wc > outfile")); 		//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("<< EOF")); 									//ok
	// ft_lstadd_back(&tests, ft_lstnew("<<"));											//ok
	// ft_lstadd_back(&tests, ft_lstnew("<"));											//ok
	// ft_lstadd_back(&tests, ft_lstnew(">"));											//ok
	// ft_lstadd_back(&tests, ft_lstnew(">>"));											//ok
	// ft_lstadd_back(&tests, ft_lstnew("<< EOF cat"));									//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > 1 > 2 > 3 > 4")); 				//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo << EOF > 1 > 2 > 3 > 4"));				//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > 1 > 2 > 3 > 4 | wc")); 			//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > 1 < 1 > 2"));        				//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > 1 < 1 | wc"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF < 1 > 1 | wc")); 					//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF < 1 > 2"));							//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF < 1")); 							//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > otario"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > outfile.txt | wc"));				//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > outfile.txt | ls | wc")); 		//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF < infile | wc"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo << EOF < not_found.txt | wc"));			//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF < infile | sort | wc"));			//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF << EOF << EOF"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF | wc"));							//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF | sort | wc"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF < infile > otario.txt")); 			//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo << EOF > lazarento")); 					//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile"));								//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat \"<\" infile")); 							//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat \'<\' infile")); 							//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat \"<\"" infile \"|\" wc")); 				//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | wc"));							//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | sort | wc"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < not_found.txt | wc"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat not_found.txt | wc"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi < not_found.txt | wc"));				//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile > otario.txt"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile >> otario.txt"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | sort | wc > outfile.txt"));				//ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | sort >> outfile.txt"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat > outfile.txt | wc"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat | ls"));									//ok	
	// ft_lstadd_back(&tests, ft_lstnew("cat | cat | ls"));								//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat | cat | cat | cat | cat | ls"));			//ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | wc > 1 < 1 > 2"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | wc > 1 < 1 > 2 < 2 > 3 < 3 > 4")); 		//ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | wc > 1 > 2 > 3 > 4")); 					//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi > 1 > 2 > 3 > 4"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi > 1 < 1 > 2")); 						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi | wc < not_found > 1"));				//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi | wc > 1 < 1 > 2 < not_found.txt > 3"));	//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi | wc > 1 < > 2"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | wc > 1 < > 2"));							//ok
	// ft_lstadd_back(&tests, ft_lstnew("<")); 											//ok
	// ft_lstadd_back(&tests, ft_lstnew("\"<\""));										//ok
	// ft_lstadd_back(&tests, ft_lstnew("\'<\'"));										//ok
	// ft_lstadd_back(&tests, ft_lstnew("<<")); 										//ok
	// ft_lstadd_back(&tests, ft_lstnew("\"<<\"")); 									//ok
	// ft_lstadd_back(&tests, ft_lstnew("\'<<\'"));										//ok
	// ft_lstadd_back(&tests, ft_lstnew(">")); 											//ok
	// ft_lstadd_back(&tests, ft_lstnew("\">\"")); 										//ok
	// ft_lstadd_back(&tests, ft_lstnew("\'>\'"));										//ok
	// ft_lstadd_back(&tests, ft_lstnew("|"));											//ok
	// ft_lstadd_back(&tests, ft_lstnew("\"|\""));										//ok
	// ft_lstadd_back(&tests, ft_lstnew("\'|\'"));										//ok
	// ft_lstadd_back(&tests, ft_lstnew("< \"Makefile\"")); 							//ok
	// ft_lstadd_back(&tests, ft_lstnew("| \"Makefile\""));								//ok
	// ft_lstadd_back(&tests, ft_lstnew("< 'Makefile')); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | wc cat << EOF"));							//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi cat << EOF")); 						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi | wc")); 								//ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | sort | wc"));								//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo fucker | wc")); 							//ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | ls | sort | wc"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo fucker | sort | wc")); 					//ok
	// ft_lstadd_back(&tests, ft_lstnew("export otario"));								//ok
	// ft_lstadd_back(&tests, ft_lstnew("export otario=\'"));							//ok
	// ft_lstadd_back(&tests, ft_lstnew("export otario=\""));							//ok
	// ft_lstadd_back(&tests, ft_lstnew("export otario=\"fucker"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("export otario=\'fucker"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("export otario="));								//ok
	// ft_lstadd_back(&tests, ft_lstnew("export otario"));								//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo $otario"));								//ok
	// ft_lstadd_back(&tests, ft_lstnew("export otario=fucker"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo $otario"));								//ok
	// ft_lstadd_back(&tests, ft_lstnew("\"echo | ola\""));								//Não funciona
	// ft_lstadd_back(&tests, ft_lstnew("\"echo | ola\" | echo fucker"));				//funciona parcialmente
	// ft_lstadd_back(&tests, ft_lstnew("\'echo | ola\'"));								//Não funciona
	// ft_lstadd_back(&tests, ft_lstnew("\"ls | wc\""));								//Não funciona
	// ft_lstadd_back(&tests, ft_lstnew("\'ls | wc\'"));								//Não funciona
	// ft_lstadd_back(&tests, ft_lstnew("echo export fucker=$USER"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo export fucker=\"$USER\""));				//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo export fucker=\'$USER\'"));				//ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | wc cat << eof | sort | wc"));				//ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | wc cat << eof | wc"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi | echo ola > file_without_permission | echo fucker"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi | echo ola > file_without_permission"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < file_without_permission"));					//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < file_without_permission | sort | wc"));		//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < file_without_permission | wc"));				//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << eof > file_without_permission"));			//ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << eof > file_without_permission"));			//ok


































 	init_hash(envp);
	prompt(g_global.hash, tests);
	return (g_global.exit_status);
}

// echo Lorem Ipsum is simply dummy text of the printing and typesetting industry. $PATH Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book

