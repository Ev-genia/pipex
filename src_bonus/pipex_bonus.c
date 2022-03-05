/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:54:53 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/05 16:20:34 by mlarra           ###   ########.fr       */
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
			// close(fd_pipe[0]);
			close(fd_pipe[1]);
			ft_perror(argv[1]);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			// close(fd_pipe[0]);
			close(fd_pipe[1]);
			ft_perror("Can not create copy of descriptor1");
		}
	}
	// close(fd_pipe[0]);
	dup2(fd_pipe[1], 1);
	close(fd_pipe[1]);
	ft_execve(env, argv[i]);
}

void	ft_second_child(int i, int ac, char **argv, int *fd_pipe, char **env)
{
	int	fd_out;

	close(fd_pipe[1]);
	if (i == ac - 2)
	{

		fd_out = open(argv[ac - 1], O_WRONLY + O_TRUNC + O_CREAT, 0644);
		if (fd_out == -1)
		{
			close(fd_pipe[0]);
			// close(fd_pipe[1]);
			ft_perror(argv[ac - 1]);
		}
		if (dup2(fd_out, STDOUT_FILENO) == -1 || dup2(fd_pipe[0], STDIN_FILENO) == -1)
		{
			close(fd_pipe[0]);
			// close(fd_pipe[1]);
			ft_perror("Can not create copy of descriptor2");
		}
		// close(fd_pipe[1]);
		close(fd_out);
		close(fd_pipe[0]);
		ft_execve(env, argv[ac - 2]);
	}
	close(fd_pipe[0]);
	// exit(0);
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
			// close(fd_pipe[1]);
			ft_perror(argv[ac - 1]);
		}
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			close(fd_pipe[0]);
			// close(fd_pipe[1]);
			ft_perror("Can not create copy of descriptor2");
		}
		// close(fd_pipe[1]);
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
	// pid_t	pid2;
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
	// pid2 = fork();
	// if (pid2 == -1)
	// 	ft_perror("Pipe failed");
	// if (pid2 == 0)
	// 	ft_second_child(num, argc, argv, fd_pipe, env);
	// close(fd_pipe[0]);
	// close(fd_pipe[1]);
	// if (waitpid(pid1, NULL, 0) == -1)
	// 	ft_perror("Error of terminated 1 child process");
	// if (waitpid(pid2, NULL, 0) == -1)
	// 	ft_perror("Error of terminated 2 child process");
}

// void	pipex_infile_pipe(int i, int argc, char **argv, char **env)
// {
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int		fd_pipe[2];

// 	if (pipe(fd_pipe) == -1)
// 		ft_perror("Pipe failed");
// 	pid1 = fork();
// 	if (pid1 == -1)
// 		ft_perror("Pipe failed");
// 	if (pid1 == 0)
// 		ft_first_child(i, argv, fd_pipe, env);
// 	pid2 = fork();
// 	if (pid2 == -1)
// 		ft_perror("Pipe failed");
// 	if (pid2 == 0)
// 		ft_second_child(argc, argv, fd_pipe, env);
// 	close(fd_pipe[0]);
// 	close(fd_pipe[1]);
// 	if (waitpid(pid1, NULL, 0) == -1)
// 		ft_perror("Error of terminated 1 child process");
// 	if (waitpid(pid2, NULL, 0) == -1)
// 		ft_perror("Error of terminated 2 child process");
// }

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
	
	// if (argc < 5)
	// {
	// 	write(2, "Too few arguments\n", 18);
	// 	return(1);
	// }
	// else
	// {
	// 	if (env == 0)
	// 		ft_perror("env error");
	// 	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	// 	{
	// 		pipex_here_doc(argc, argv, env);
	// 		i = 2;
	// 	}
	// 	else
	// 		i = 1;
	// 	while (argc > 5)
	// 	{
	// 		pipex(argc, argv, env);
	// 		argc--;
	// 	}
	// 	pipex(argc, argv, env);
	// }
perror("the end");
	return (0);
}