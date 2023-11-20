// void    expand_wildcard_and_store(char *pattern)
// {
// 	DIR *ptr_dir;
// 	struct dirent *entry;
// 	struct stat statbuf;

// 	char *dir;
// 	char *new_path;
// 	char *slash;
// 	t_files **head;

// 	dir = ".";
// 	head = NULL;
// 	new_path = ft_strjoin(dir, "/");
// 	slash = ft_strrchr(pattern, '/');
// 	if (slash)
// 	{
// 		dir = ft_strndup(pattern, slash - pattern);
// 		new_path = slash + 1;
// 	}

// 	ptr_dir = opendir(dir);
// 	if (ptr_dir == NULL)
// 	{
// 		ft_fprintf(2, "minishell: %s: No such file or directory\n", pattern);
// 		return ;
// 	}
// 	while ((entry = readdir(ptr_dir)))
// 	{
// 		if (stat(entry->d_name, &statbuf) == 0 && S_ISREG(statbuf.st_mode))
// 		{
// 			if (wildcard_match(entry->d_name, new_path))
// 			{
// 				add_file(head, entry->d_name);
// 				printf("%s\n", entry->d_name);
// 			}
// 		}
// 		else
// 			ft_printf("minishell: %s: No such file or directory\n", entry->d_name);

// 	}
// 	closedir(ptr_dir);
// }