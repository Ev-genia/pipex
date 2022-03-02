/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:52:24 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/02 16:32:02 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	ft_execve_h_d(env, argv[2]);
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
		ft_second_child(argc, argv, fd_pipe, env);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	if (waitpid(pid1, NULL, 0) == -1)
		ft_perror("Error of terminated 1 child process");
	if (waitpid(pid2, NULL, 0) == -1)
		ft_perror("Error of terminated 2 child process");
}
