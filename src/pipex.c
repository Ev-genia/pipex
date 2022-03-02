/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:54:53 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/02 09:57:19 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n < 1)
		return (0);
	while (n > 1 && *s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
write(2, "malloc strjoin*\n", 16);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		dest[i] = s2[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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
write(2, "free strjoin*\n", 14);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
write(2, "free strjoin*\n", 14);			
		i++;
	}
	return (NULL);
}

void	ft_free(char **mas)
{
	int	i;

	i = 0;
	while (mas[i])
	{
		free(mas[i]);
write(2, "free*\n", 6);
		i++;
	}
	free(mas);
write(2, "free**\n", 7);
}

// char	*ft_get_path(char **env, char **cmd)
char	*ft_get_path(char *env, char **cmd)
{
	// int		num_str;
	char	*str;
	char	**tracks;

	str = NULL;

	// num_str = ft_get_number_str(env);
// 	if (num_str == -1)
// 	{
		
// 		write(2, "No command ", 11);
// 		perror(cmd[0]);
// write(2, "no nbr srt, free cmd\n", 21);
// 		ft_free(cmd);

// while (1) {}
// 		exit(1);
// 	}
	tracks = ft_split(env + 5, ':');
	if (ft_check_path(cmd[0], tracks) == NULL)
	{
		perror(cmd[0]);
write(2, "cmd_no path\n", 12);		
		ft_free(cmd);
write(2, "tracks_no path\n", 15);
		ft_free(tracks);

while (1) {}

		exit(127);
	}
	else
		str = ft_check_path(cmd[0], tracks);
	return (str);
}

void	ft_execve(char **env, char *cmd)
{
	char	*path;
	char	**command;
	int		num_str;
	
	num_str = ft_get_number_str(env);
	if (num_str == -1)
	{
		perror(cmd);
// while (1) {}
		exit(1);
	}
	command = ft_split(cmd, ' ');
	path = ft_get_path(env[num_str], command);
	// execve(path, command, env);
	if (execve(path, command, env) == -1)
	{
			ft_perror(command);
			perror(path);
			ft_perror(path);
			exit(1);
	}
}

void	ft_first_child(char **argv, int *fd_pipe, char **env)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0644);
	if (fd_in == -1)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		ft_perror(argv[1]);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd_pipe[1], STDOUT_FILENO) == -1)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		ft_perror("Can not create copy of descriptor1");
	}
	close(fd_pipe[0]);
	close(fd_in);
	close(fd_pipe[1]);
	ft_execve(env, argv[2]);
}

void	ft_second_child(int ac, char **argv, int *fd_pipe, char **env)
{
	int	fd_out;

	fd_out = open(argv[ac - 1], O_WRONLY + O_TRUNC + O_CREAT, 0644);
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
}

void	pipex(int argc, char **argv, char **env)
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
		ft_first_child(argv, fd_pipe, env);
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

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		write(2, "Too few or too many arguments\n", 30);
		return(1);
	}
	pipex(argc, argv, env);
	return (0);
}