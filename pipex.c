/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 19:02:41 by lugonzal          #+#    #+#             */
/*Updated: 2021/08/11 19:23:22 by lugonzal               ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "Libft/include/libft.h"
#include <fcntl.h>
#include "pipex.h"

static void	set_cmd(char *argv, t_data *data)
{
	int	i;

	if (!argv)
		exit(0);
	data->cmd = ft_split_4(argv, ' ');
	i = -1;
	while (data->stored[++i])
	{
		data->path = ft_strjoin (data->stored[i], data->cmd[0]);
		data->signal = access(data->path, X_OK);
		if (data->signal < 0)
			free(data->path);
		else
			break ;
	}
	error_signal_0(data->signal);
}

static void	multi_pipe(t_data *data, char **argv, int n)
{
	int	i;

	i = -1;
	set_cmd(argv[n + 2], data);
	while (++i < data->n + 1)
	{
		if (i != n)
			close(data->fd[i][0]);
		if (i != n + 1)
			close(data->fd[i][1]);
	}
	dup2(data->fd[n][0], 0);
	close(data->fd[n][0]);
	dup2(data->fd[n + 1][1], 1);
	close(data->fd[n + 1][1]);
	execve(data->path, data->cmd, NULL);
}

void	init_fd(t_data *data, int argc, char **argv)
{
	close(data->fd[0][0]);
	data->fd[0][0] = open(argv[1], O_RDONLY);
	error_signal_1(data->fd[0][0]);
	close(data->fd[data->n][1]);
	data->fd[data->n][1]
		= open(argv[argc - 1], O_WRONLY | O_CREAT, 0777);
}

void	init_data(t_data *data, char **envp, int argc)
{
	char	*tmp;
	int		i;

	while (ft_strncmp(*envp, "PATH=", 5))
		envp++;
	tmp = ft_strtrim(*envp, "PATH=");
	data->stored = ft_split(tmp, ':');
	free(tmp);
	i = -1;
	while (data->stored[++i])
	{
		tmp = ft_strjoin(data->stored[i], "/");
		free(data->stored[i]);
		data->stored[i] = tmp;
	}
	data->n = argc - 3;
	data->pid = (int *)malloc(sizeof(int) * data->n);
	data->fd = (int **)malloc(sizeof(int *) * (data->n + 1));
	data->fd[data->n] = NULL;
	i = -1;
	while (++i < data->n + 1)
	{
		data->fd[i] = (int *)malloc(sizeof(int) * 2);
		error_signal_1(pipe(data->fd[i]));
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;

	if (argc < 5)
		exit (0);
	else
	{	
		init_data(&data, envp, argc);
		init_fd(&data, argc, argv);
		i = -1;
		while (++i < data.n)
		{
			data.pid[i] = fork();
			if (data.pid[i] == 0)
				multi_pipe(&data, argv, i);
		}
	}
	i = -1;
	free_data(&data);
}
