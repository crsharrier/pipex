/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:58:58 by crsharrier        #+#    #+#             */
/*   Updated: 2024/05/02 21:12:20 by crsharrier       ###   ########.fr       */
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

void    child_process(char *cmd1, t_pipex px, int mode)
{
    char    **args;

    if (mode == CMD1)
    {
        dup2(px.fd[1], STDOUT_FILENO);
        dup2(px.fd_infile, STDIN_FILENO);
    }
    else
    {
        dup2(px.fd[0], STDIN_FILENO);
        dup2(px.fd_outfile, STDOUT_FILENO);
    }
    close(px.fd[0]);
    close(px.fd[1]);
    close(px.fd_infile);
    close(px.fd_outfile);
    args = ft_split(cmd1, ' ');
    if (ft_exec(args, environ) < 0)
        error("Error ft_exec");
}

/*
Take argc and argv.
Ensure 
*/
// t_pipex    validate_input(int argc, char *argv[])
// {
//     t_pipex px;
//     int     i;

//     if (argc < 5)
//         error("Invalid number of arguments");
//     px.fd_infile = open(argv[1], O_RDONLY | O_CREAT, 00777);
//     px.fd_outfile = open(argv[argc - 1], O_WRONLY | O_CREAT, 00777);
//     i = 2;
//     while (i < argc - 1)
//     {

//         i++;
//     }
        
// }

// infile "ls -l" "wc -l" outfile
int main(int argc, char *argv[])
{
    t_pipex px;

    px.fd_infile = open(argv[1], O_RDONLY | O_CREAT, 00777);
    px.fd_outfile = open(argv[4], O_WRONLY | O_CREAT, 00777);
    if (argc != 5)
        error("Invalid number of arguments");

    if (pipe(px.fd) < 0)
        error("Error opening pipe");
    
    if ((px.pid1 = fork()) < 0)
        error("Error forking process 1");
    if (px.pid1 == 0)
        child_process(argv[2], px, CMD1);
    
    px.pid2 = fork();
    if (px.pid2 < 0)
        error("Error forking process 2");
    if (px.pid2 == 0)
        child_process(argv[3], px, CMD2);

    close(px.fd[0]);
    close(px.fd[1]);
    close(px.fd_infile);
    close(px.fd_outfile);
    waitpid(px.pid1, NULL, 0);
    waitpid(px.pid2, NULL, 0);
    return (0);
}