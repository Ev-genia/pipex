/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:16:18 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/02 12:42:44 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(1);
}

void	ft_write(char *s)
{
	int	i;

	write(2, "command not found: ", 19);
	i = -1;
	while (s[++i])
		write(2, &s[i], 1);
	write(2, "\n", 1);
}

void	ft_free(char **mas)
{
	int	i;

	i = -1;
	while (mas[++i])
		free(mas[i]);
	free(mas);
}
