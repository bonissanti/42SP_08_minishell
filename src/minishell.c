/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allesson <allesson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:38:13 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/01 15:14:33 by allesson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **envp)
	{
	(void)argc;
	(void)argv;
	t_list *tests = NULL;
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
	// ft_lstadd_back(&tests, ft_lstnew("echo 1 hello world")); 			// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 2 \"hello world\"")); 		// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 3 'hello world'"));			// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 4 hello'world'")); 			// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 5 hello\"\"world")); 			// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 6 - \"\" \"  \" hello")); 	// comeu a letra 'o'
	// ft_lstadd_back(&tests, ft_lstnew("echo 7 ''")); 						// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 8 \"$PWD\"")); 				// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 9 '$PWD'")); 					// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 10 \"aspas ->'\"")); 			//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 11 \"aspas -> ' \"")); 		//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 12 'aspas ->\"'")); 			//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 13 'aspas -> \" '")); 		//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 14 \"> >> < * ? [ ] | ; [ ] || && ( ) & # $ \\ <<\"")); //ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 15 '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \\ <<'")); //ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 16 \"exit_code ->$? user ->$USER home -> $HOME\"")); //ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 17 'exit_code ->$? user ->$USER home -> $HOME'")); //ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 18 \"$\"")); 					//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 19 '$'")); 					//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 20 $"));						//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 21 $?")); 					//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 22 $?HELLO")); 				//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo 23 $?HE$?LLO$?")); 			//ok
	// ft_lstadd_back(&tests, ft_lstnew("echo \"hi\" | cat | cat | cat | cat | cat | cat | cat")); //ok
	// ft_lstadd_back(&tests, ft_lstnew("pwd")); 							//ok
	// ft_lstadd_back(&tests, ft_lstnew("pwd oi")); 						//ok
	// ft_lstadd_back(&tests, ft_lstnew("export hello"));
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO=123"));
	// ft_lstadd_back(&tests, ft_lstnew("export A-")); 
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO=123 A"));
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO=\"123 A-\""));
	// ft_lstadd_back(&tests, ft_lstnew("export hello world"));
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO-=123 A"));
	// ft_lstadd_back(&tests, ft_lstnew("export ="));
	// ft_lstadd_back(&tests, ft_lstnew("export = \'"));
	// ft_lstadd_back(&tests, ft_lstnew("export 123"));
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO+=123"));
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO-=123"));
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO-=\'123\'"));
	// ft_lstadd_back(&tests, ft_lstnew("export HELLO+=\"123\""));



	// ft_lstadd_back(&tests, ft_lstnew("unset")); 										// ok
	// ft_lstadd_back(&tests, ft_lstnew("unset HELLO")); 								// ok
	// ft_lstadd_back(&tests, ft_lstnew("unset HELLO1 HELLO2")); 						// ok
	// ft_lstadd_back(&tests, ft_lstnew("unset HOME")); 								// ok
	// ft_lstadd_back(&tests, ft_lstnew("unset PATH")); 								// ok
	// ft_lstadd_back(&tests, ft_lstnew("unset SHELL")); 								// ok
	// ft_lstadd_back(&tests, ft_lstnew("cd $PATH"));									// ok
	// ft_lstadd_back(&tests, ft_lstnew("cd $PATH oi")); 								// ok
	// ft_lstadd_back(&tests, ft_lstnew("cd 123123")); 									// ok
	// ft_lstadd_back(&tests, ft_lstnew("exit 123")); 									// ok
	// ft_lstadd_back(&tests, ft_lstnew("exit 298")); 									// ok
	// ft_lstadd_back(&tests, ft_lstnew("exit +100")); 									// ok
	// ft_lstadd_back(&tests, ft_lstnew("exit \"+100\"")); 								// ok
	// ft_lstadd_back(&tests, ft_lstnew("exit -100")); 									// ok
	// ft_lstadd_back(&tests, ft_lstnew("exit \"-100\"")); 								// ok
	// ft_lstadd_back(&tests, ft_lstnew("exit -\"100\"")); 								// ok
	// ft_lstadd_back(&tests, ft_lstnew("exit hello")); 								// ok
	// ft_lstadd_back(&tests, ft_lstnew("exit 42 world")); 								// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile"));  								// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | wc")); 							// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | sort | wc")); 					// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile > outfile")); 					// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | wc > outfile")); 				// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | sort | wc > outfile")); 		// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF")); 								// ok
	// ft_lstadd_back(&tests, ft_lstnew("<< EOF")); 									// leaks
	// ft_lstadd_back(&tests, ft_lstnew("<<"));											// ok
	// ft_lstadd_back(&tests, ft_lstnew("<"));											// ok
	// ft_lstadd_back(&tests, ft_lstnew(">"));											// ok
	// ft_lstadd_back(&tests, ft_lstnew(">>"));											// ok
	// ft_lstadd_back(&tests, ft_lstnew("<< EOF cat"));									// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > 1 > 2 > 3 > 4")); 				// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo << EOF > 1 > 2 > 3 > 4"));				// leaks
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > 1 > 2 > 3 > 4 | wc")); 			// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > 1 < 1 > 2"));        				// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > 1 < 1 | wc"));					// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF < 1 > 1 | wc")); 					// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF < 1 > 2"));
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF < 1")); // leaks quando o arquivo não existe
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > otario"));						// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > outfile.txt | wc"));				// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF > outfile.txt | ls | wc")); 		// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF < infile | wc"));					// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo << EOF < not_found.txt | wc"));			// leaks
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF < infile | sort | wc"));			// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF << EOF << EOF"));					// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF | wc"));							// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF | sort | wc"));						// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat << EOF < infile > otario.txt")); 			// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo << EOF > lazarento")); 					// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile"));								// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat \"<\" infile")); 							// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat \'<\' infile")); 							// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat \"<\"" infile \"|\" wc")); 				// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | wc"));							// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile | sort | wc"));					// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < not_found.txt | wc"));					// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat not_found.txt | wc"));						// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi < not_found.txt | wc"));				// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile > otario.txt"));					// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat < infile >> otario.txt"));					// ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | sort | wc > outfile.txt"));				// ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | sort >> outfile.txt"));					// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat > outfile.txt | wc"));						// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat | ls"));									// ok	
	// ft_lstadd_back(&tests, ft_lstnew("cat | cat | ls"));								// ok
	// ft_lstadd_back(&tests, ft_lstnew("cat | cat | cat | cat | cat | ls"));			// ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | wc > 1 < 1 > 2"));						// ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | wc > 1 < 1 > 2 < 2 > 3 < 3 > 4")); 		// ok
	// ft_lstadd_back(&tests, ft_lstnew("ls | wc > 1 > 2 > 3 > 4")); 					// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi > 1 > 2 > 3 > 4"));					// leaks
	// ft_lstadd_back(&tests, ft_lstnew("echo oi > 1 < 1 > 2")); 						// leaks
	// ft_lstadd_back(&tests, ft_lstnew("echo oi | wc < not_found > 1"));				// leaks
	// ft_lstadd_back(&tests, ft_lstnew("echo oi | wc > 1 < 1 > 2 < not_found.txt > 3")); 	// leaks
	// ft_lstadd_back(&tests, ft_lstnew("echo oi | wc > 1 < > 2"));						// leaks
	// ft_lstadd_back(&tests, ft_lstnew("ls | wc > 1 < > 2"));							// leaks
	// ft_lstadd_back(&tests, ft_lstnew("<")); 											// ok
	// ft_lstadd_back(&tests, ft_lstnew("\"<\""));										// ok
	// ft_lstadd_back(&tests, ft_lstnew("\'<\'"));										// ok
	// ft_lstadd_back(&tests, ft_lstnew("<<")); 										// ok
	// ft_lstadd_back(&tests, ft_lstnew("\"<<\"")); 									// ok
	// ft_lstadd_back(&tests, ft_lstnew("\'<<\'"));										// ok
	// ft_lstadd_back(&tests, ft_lstnew(">")); 											// ok
	// ft_lstadd_back(&tests, ft_lstnew("\">\"")); 										// ok
	// ft_lstadd_back(&tests, ft_lstnew("\'>\'"));										// ok
	// ft_lstadd_back(&tests, ft_lstnew("|"));											// ok
	// ft_lstadd_back(&tests, ft_lstnew("\"|\""));										// ok
	// ft_lstadd_back(&tests, ft_lstnew("\'|\'"));										// ok
	// ft_lstadd_back(&tests, ft_lstnew("< \"Makefile\"")); 							// leak
	// ft_lstadd_back(&tests, ft_lstnew("| \"Makefile\""));		
	// ft_lstadd_back(&tests, ft_lstnew("< 'Makefile')); 								// leaks
	// ft_lstadd_back(&tests, ft_lstnew("ls | wc cat << EOF"));							// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo oi cat << EOF")); 						// leaks
	// ft_lstadd_back(&tests, ft_lstnew("echo oi | wc")); 								// leaks
	// ft_lstadd_back(&tests, ft_lstnew("ls | sort | wc"));								// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo fucker | wc")); 							// leaks
	// ft_lstadd_back(&tests, ft_lstnew("ls | ls | sort | wc"));						// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo fucker | sort | wc")); 					// leaks
	// ft_lstadd_back(&tests, ft_lstnew("export otario"));		
	// ft_lstadd_back(&tests, ft_lstnew("export otario=\'"));
	// ft_lstadd_back(&tests, ft_lstnew("export otario=\""));
	// ft_lstadd_back(&tests, ft_lstnew("export otario=\"fucker"));
	// ft_lstadd_back(&tests, ft_lstnew("export otario=\'fucker"));
	// ft_lstadd_back(&tests, ft_lstnew("export otario="));
	// ft_lstadd_back(&tests, ft_lstnew("export otario=fucker"));
	// ft_lstadd_back(&tests, ft_lstnew("echo $otario"));
	// ft_lstadd_back(&tests, ft_lstnew("export otario=fucker"));
	// ft_lstadd_back(&tests, ft_lstnew("\"echo | ola\""));								// Não funciona
	// ft_lstadd_back(&tests, ft_lstnew("\'echo | ola\'"));								// Não funciona
	// ft_lstadd_back(&tests, ft_lstnew("\"ls | wc\""));								// Não funciona
	// ft_lstadd_back(&tests, ft_lstnew("\'ls | wc\'"));								// Não funciona
	// ft_lstadd_back(&tests, ft_lstnew("echo export fucker=$USER"));					// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo export fucker=\"$USER\""));				// ok
	// ft_lstadd_back(&tests, ft_lstnew("echo export fucker=\'$USER\'"));				// ok


























 	init_hash(envp);
	prompt(g_global.hash, tests);
	return (g_global.exit_status);
}

// echo Lorem Ipsum is simply dummy text of the printing and typesetting industry. $PATH Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book

