/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:54:53 by mlarra            #+#    #+#             */
/*   Updated: 2022/02/21 15:34:28 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(1);
}

int	main(int argc, char **argv)//, char **env)
{
	pid_t	pid;
	int		mypipe[2];

(void)argv;

	if (argc != 5)
		ft_perror("Too few or many arguments");
	if (pipe(mypipe))
	{
		write(2, "Pipe failed.\n", 13);
	}
	pid = fork();
	if (pid == (pid_t) 0)
	{
		//read from pipe, gnl?
		return (0);
	}

	return (0);
}