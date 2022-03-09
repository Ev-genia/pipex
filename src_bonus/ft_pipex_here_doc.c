/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:52:24 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/09 12:56:17 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(1);
}

void	ft_init_struct(int argc, char **argv, char **env, t_pipe *str_pipex)
{
	str_pipex->ac = argc;
	str_pipex->av = argv;
	str_pipex->env = env;
}

void	ft_child_h_d(char **argv, int *fd_pipe)
{
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		ft_perror("Error of create copy of descriptor");
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	ft_execve_h_d(argv[2], fd_pipe);
}

void	pipex_heredoc(char **argv)
{
	pid_t	pid1;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		ft_perror("Pipe error");
	pid1 = fork();
	if (pid1 == -1)
		ft_perror("Pipe error");
	if (pid1 == 0)
		ft_child_h_d(argv, fd_pipe);
	else
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], 0);
		close(fd_pipe[0]);
		if (waitpid(pid1, NULL, 0) == -1)
			ft_perror("Error of terminated 1 child process");
	}
}
