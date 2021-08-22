/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 19:27:07 by lugonzal          #+#    #+#             */
/*Updated: 2021/08/17 19:28:22 by lugonzal               ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "Libft/include/libft.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_rare_case(int *i, char *str, char *c)
{
	if (str[*i] == 34 && str[*i - 1] != 39)
	{
		(*i)++;
		*c = 34;
	}
	else if (str[*i] == 39 && str[*i + 1] == '{')
	{
		*c = 39;
		(*i)++;
	}
	else if (str[*i] == 39 && str[*i + 1] == 34)
	{
		(*i)++;
		*c = 39;
	}
}

void	free_chain(void **chain)
{
	int	i;

	i = -1;
	while (chain[++i])
		free(chain[i]);
	free(chain);
}

void	error_signal_0(int signal, char **chain)
{
	if (signal < 0)
	{
		free_chain((void **)chain);
		exit (0);
	}
	else
		return ;
}

void	error_signal_1(int signal)
{
	if (signal < 0)
		exit (0);
	else
		return ;
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (data->stored[++i])
		free(data->stored[i]);
	free(data->stored);
	i = -1;
	while (++i < data->n + 1)
		free(data->fd[i]);
	free(data->fd);
	free(data->pid);
}
