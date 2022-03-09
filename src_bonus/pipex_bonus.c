/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:54:53 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/09 10:06:29 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_open_outfile(int ac, char **av)
{
	int	fd;

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		fd = open(av[ac - 1], O_WRONLY + O_APPEND + O_CREAT, 0644);
	else
		fd = open(av[ac - 1], O_WRONLY + O_TRUNC + O_CREAT, 0644);
	return(fd);
}

void	ft_first_child(int i, int ac, char **argv, int *fd_pipe, char **env)
{
	int	fd_in;

	close(fd_pipe[0]);
	if (i == ac - 2)
		exit(1);
	if (i == 2)
	{
		fd_in = open(argv[1], O_RDONLY, 0644);
		if (fd_in == -1)
		{
			close(fd_pipe[1]);
			ft_perror(argv[1]);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			close(fd_pipe[1]);
			ft_perror("Can not create copy of descriptor1");
		}
	}
	dup2(fd_pipe[1], 1);
	close(fd_pipe[1]);
	ft_execve(env, argv[i]);
}

void	ft_parent_proc(int i, int ac, char **argv, int *fd_pipe, char **env, int pid)
{
	int	fd_out;

	close(fd_pipe[1]);
	if (i == ac - 2)
	{
		waitpid(pid, NULL, 0);
		fd_out = ft_open_outfile(ac, argv);
		if (fd_out == -1)
		{
			close(fd_pipe[0]);
			ft_perror(argv[ac - 1]);
		}
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			close(fd_pipe[0]);
			ft_perror("Can not create copy of descriptor2");
		}
		close(fd_out);
		close(fd_pipe[0]);
		ft_execve(env, argv[ac - 2]);
	}
	dup2(fd_pipe[0] ,0);
	close(fd_pipe[0]);
}

void	pipex(int argc, char **argv, char **env, int num)
{
	pid_t	pid1;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		ft_perror("Pipe failed");
	pid1 = fork();
	if (pid1 == -1)
		ft_perror("Pipe failed");
	if (pid1 == 0)
		ft_first_child(num, argc, argv, fd_pipe, env);
	else
		ft_parent_proc(num, argc, argv, fd_pipe, env, pid1);
}

int	main(int argc, char **argv, char **env)
{
	int	i;

	if (argc >= 5)
	{
		if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			pipex_heredoc(argv);
			i = 3;
		}
		else
			i = 2;
		while (i < argc - 1)
		{
			pipex(argc, argv, env, i);
			i++;
		}
	}
	else
	{
		write(2, "Too few arguments\n", 18);
		return(1);
	}
// perror("the end");
	return (0);
}