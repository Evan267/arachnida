/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:18:24 by eberger           #+#    #+#             */
/*   Updated: 2023/06/08 23:04:25 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spider.h"

pid_t	getAllContent(char *path, int *pipes)
{

	pid_t	pid;
	int	status;
	char	*args[3];

	args[0] = ft_strdup("curl");
	args[1] = path;
	arg[2] = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		if(dup2(pipe[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(pipe[1]);
		close(pipe[0]);
		if (execve("/usr/bin/curl", args, NULL) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	free(args[0]);
	free(args[1]);
	return (pid);
}

int	wait_all_get(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITEDSTATUS(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	saveAllContent(char *path, int *pipes)
{
	pid_t	pid;
	int	status;

	pid = getAllContent(path, pipes);
	close(pipes[1]);
	return (wait_all_get(pid));
}

void	*setPipe(int **pipes)
{
	if (pipe(*pipes) == -1)
	{
		perror("pipe");
		exit(127);
	}
}

int	str_isNum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*error_args(void)
{
	ft_putendl_fd("Error arguments", 2);
	return (NULL);
}

char	*setParams(char **path, int *len, char **argv, int argc)
{
	int	i;
	char	*ret;

	i = 1;
	ret = ft_strdup("./data/");
	*len = -2;
	if (!ft_strncmp(argv[i], "-r", ft_strlen(argv[i])))
	{
		argc--;
		i++;
		*len = -1;
		if (!ft_strncmp(argv[i], "-l", ft_strlen(argv[i])))
		{
			argc--;
			i++;
			*len = 5;
			if (str_isNum(argv[i])
			{
				len = ft_atoi(argv[i]);
				argc--;
				i++;
			}
		}
	}
	if (!ft_strncmp(argv[i], "-p", ft_strlen(argv[i])))
	{
		argc--;
		i++;
		*len = 5;
		if (argv[i])
		{
			free(ret);
			ret = ft_strdup(argv[i]);
			argc--;
			i++;
		}
	}
	if (argc != 2)
		return (error_args());
	*path = ft_strdup(argv[i]);
	return (ret);
}

int	downloadImages(int *pipes, char *path_download, int len)
{
	if (mkdir(path_download, 0777) == -1)
		return (error_args(), 1);
	//TOBEDONE
}

int	close_clean(int *pipes, char *path_download, char *path)
{
	if (pipes && !access(pipes[1], F_OK) && !access(pipes[0], F_OK))
	{
		close(pipes[0]);
		close(pipes[1]);
	}
	if (path_download)
		free(path_download);
	if (path)
		free(path);
	return (1);
}

int main(int argc, char *argv[])
{
	char	*path;
	char	*path_download;
	int	len;
	int	pipes[2];
	
	setPipe(&pipes);
	path_download = setParams(&path, &len, argv, argc);
	if (!path_download)
		return (close_clean(pipes, NULL, path));
	if (saveAllContent(path, pipes))
		return (1);
	if (downloadImages(pipes, path_download, len);
	return (0);
}
