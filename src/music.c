/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:18:50 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:26:49 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <unistd.h>

void	*run_music(void *arg)
{
	char	*av[3];

	av[0] = "afplay";
	av[1] = arg;
	av[2] = NULL;
	execve("/usr/bin/afplay", av, NULL);
	return (NULL);
}

void	play_music(char *path)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		run_music(path);
		custom_exit(0);
	}
}
