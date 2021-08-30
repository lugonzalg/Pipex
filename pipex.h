/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugonzal <lugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:54:00 by lugonzal          #+#    #+#             */
/*Updated: 2021/08/16 21:54:22 by lugonzal               ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>

typedef struct s_data {
	char	**stored;
	char	**cmd;
	char	*path;
	int		**fd;
	int		signal :1;
	int		n;
	pid_t	*pid;
}	t_data;

void	set_cmd(char *argv, t_data *data);
void	check_cmd(t_data *data, int argc, char **argv);
void	ft_rare_case(int *i, char *str, char *c);
void	error_signal_0(int signal, t_data **data);
void	error_signal_1(int signal, t_data **data);
void	init_data(t_data *data, char **envp, int argc);
char	**ft_split_4(const char *s, char c);
void	free_data(t_data *data);

#endif 
