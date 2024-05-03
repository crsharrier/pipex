/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <csharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:20:24 by crsharrier        #+#    #+#             */
/*   Updated: 2024/05/03 13:17:27 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_pipex
{
    int new_in;
    int new_out;

    int infile;
    int outfile;
    int pipe[2];

    int pid1;
    int pid2;
    int fd_infile;
    int fd_outfile;
    int fd[2];
}               t_pipex;

int     ft_exec(char **args, char **env);
void    error(char *msg);

#endif