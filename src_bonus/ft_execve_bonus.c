/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:14:49 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/05 16:59:33 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_check_path(char *command, char **tracks)
{
	int		i;
	char	*tmp;
	char	*path;

	if (command[0] == '/' || (command[0] == '.' && command[1] == '/') || command[0] == '~')
		return (command);
	i = 0;
	while (tracks[i])
	{
		path = ft_strjoin(tracks[i], "/");
		tmp = ft_strjoin(path, command);
		free(path);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

int	ft_get_number_str(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_get_path(char **env, char **cmd)
{
	int		num_str;
	char	*str;
	char	**tracks;

	str = NULL;

	num_str = ft_get_number_str(env);
	if (num_str == -1)
	{
		ft_write(cmd[0]);
		ft_free(cmd);
		exit(1);
	}
	tracks = ft_split(env[num_str] + 5, ':');
	str = ft_check_path(cmd[0], tracks);
	return (str);
}

void	ft_execve(char **env, char *cmd)
{
	char	*path;
	char	**command;
	
	command = ft_split(cmd, ' ');
	path = ft_get_path(env, command);
	if (!path)
	{
		ft_write(command[0]);
		ft_free(command);
		exit(1);
	}
	if (execve(path, command, env) == -1)
	{
		ft_perror(command[0]);
		perror(path);
		ft_perror(path);
		exit(1);
	}
}

void	ft_execve_h_d(char *stop, int *fds)
{
	//check on " "?
	char	*term_str;

// printf("exec fd_pipe[0]: %d, fd_pipe[1]: %d\n", fds[0], fds[1]);	
// perror("test1");	
	close(fds[0]);
	stop = ft_strjoin(stop, "\n");
	write(0, "pipex here_doc> ", 16);
	term_str = get_next_line(0);
	while (term_str != NULL && ft_strncmp(term_str, stop, ft_strlen(stop)) != 0)
	{
// perror("test4");
// printf("exec1 fd_pipe[0]: %d, fd_pipe[1]: %d\n", fds[0], fds[1]);
		ft_putstr(term_str, fds[1]);
		free(term_str);
// perror("test3");
		write(0, "pipex here_doc> ", 16);
		term_str = get_next_line(0);
	}
	if (term_str != NULL)
		free(term_str);
	free(stop);
	// if (execve(path, command, env) == -1)
	// {
	// 	ft_perror(command[0]);
	// 	perror(path);
	// 	ft_perror(path);
	// 	free(term_str);
	// 	exit(1);
	// }
// perror("test2");
	exit(0);
}
