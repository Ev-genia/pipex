/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:54:53 by mlarra            #+#    #+#             */
/*   Updated: 2022/02/18 13:25:23 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h>

int	main(int argc, char **argv)//, char **env)
{
	pid_t	pid;
	int		mypipe[2];

// while (*env)
// {
// 	printf("%s\n", *env);
// 	(*env)++;
// }

// printf("Directory = %s\n", getenv("bash"));

(void)argv;

	if (argc != 5)
	{
		write(2, "Too few or many arguments\n", 26);
		return (0);
	}
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