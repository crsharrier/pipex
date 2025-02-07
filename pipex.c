/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:58:58 by crsharrier        #+#    #+#             */
/*   Updated: 2024/04/24 09:21:12 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ALLOWED FUNCTIONS:
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/
/*
ALSO RESEARCH:
select, poll
*/

#include "libft.h"
#include "pipex.h"

extern char **environ;

void    child_process(char *cmd1, t_PipexFD pfd, int mode)
{
    char    **args;

    if (mode == CMD1)
    {
        dup2(pfd.fd[1], STDOUT_FILENO);
        dup2(pfd.fd_infile, STDIN_FILENO);
    }
    else
    {
        dup2(pfd.fd[0], STDIN_FILENO);
        dup2(pfd.fd_outfile, STDOUT_FILENO);
    }
    close(pfd.fd[0]);
    close(pfd.fd[1]);
    close(pfd.fd_infile);
    close(pfd.fd_outfile);
    args = ft_split(cmd1, ' ');
    if (ft_exec(args, environ) < 0)
        error("Error ft_exec");
}

// infile "ls -l" "wc -l" outfile
int main(int argc, char *argv[])
{
    t_PipexFD pfd;

    pfd.fd_infile = open(argv[1], O_RDONLY | O_CREAT, 00777);
    pfd.fd_outfile = open(argv[4], O_WRONLY | O_CREAT, 00777);
    if (argc != 5)
        error("Invalid number of arguments");
    if (pipe(pfd.fd) < 0)
        error("Error opening pipe");
    if ((pfd.pid1 = fork()) < 0)
        error("Error forking process 1");
    if (pfd.pid1 == 0)
        child_process(argv[2], pfd, CMD1);
    pfd.pid2 = fork();
    if (pfd.pid2 < 0)
        error("Error forking process 2");
    if (pfd.pid2 == 0)
        child_process(argv[3], pfd, CMD2);
    close(pfd.fd[0]);
    close(pfd.fd[1]);
    close(pfd.fd_infile);
    close(pfd.fd_outfile);
    waitpid(pfd.pid1, NULL, 0);
    waitpid(pfd.pid2, NULL, 0);
    return (0);
}