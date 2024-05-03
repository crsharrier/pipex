/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:20:24 by crsharrier        #+#    #+#             */
/*   Updated: 2024/05/02 21:22:30 by crsharrier       ###   ########.fr       */
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

# define CMD1 1
# define CMD2 2

typedef struct s_PipexFD
{
    int pid1;
    int pid2;
    int fd_infile;
    int fd_outfile;
    int fd[2];
}               t_pipex;

int     ft_exec(char **args, char **env);
void    error(char *msg);

#endif