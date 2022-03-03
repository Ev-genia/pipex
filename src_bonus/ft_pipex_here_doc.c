/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:52:24 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/03 12:35:54 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_second_child_h_d(int ac, char **argv, int *fd_pipe, char **env)
{
	int	fd_out;

	fd_out = open(argv[ac - 1], O_WRONLY + O_APPEND + O_CREAT, 0644);
	if (fd_out == -1)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		ft_perror(argv[ac - 1]);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1 || dup2(fd_pipe[0], STDIN_FILENO) == -1)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		ft_perror("Can not create copy of descriptor2");
	}
	close(fd_pipe[1]);
	close(fd_out);
	close(fd_pipe[0]);
	ft_execve(env, argv[ac - 2]);
perror("ft_second_child_h_d");
}

void	ft_first_child_h_d(char **argv, int *fd_pipe, char **env)
{
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		ft_perror("Can not create copy of descriptor1");
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	ft_execve_h_d(env, argv[2], argv[3], fd_pipe[1]);
perror("ft_first_child_h_d");
}

void	pipex_here_doc(int argc, char **argv, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		ft_perror("Pipe failed");
	pid1 = fork();
	if (pid1 == -1)
		ft_perror("Pipe failed");
	if (pid1 == 0)
		ft_first_child_h_d(argv, fd_pipe, env);
	pid2 = fork();
	if (pid2 == -1)
		ft_perror("Pipe failed");
	if (pid2 == 0)
		ft_second_child_h_d(argc, argv, fd_pipe, env);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	if (waitpid(pid1, NULL, 0) == -1)
		ft_perror("Error of terminated 1 child process");
	if (waitpid(pid2, NULL, 0) == -1)
		ft_perror("Error of terminated 2 child process");
}
