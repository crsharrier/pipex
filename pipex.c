/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <csharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:58:58 by crsharrier        #+#    #+#             */
/*   Updated: 2024/05/03 13:49:26 by csharrie         ###   ########.fr       */
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

void    child_process(char *cmd, t_pipex px)
{
    char    **args;

    dup2(px.new_in, STDIN_FILENO);
    dup2(px.new_out, STDOUT_FILENO);
    close(px.pipe[0]);
    close(px.pipe[1]);
    close(px.infile);
    close(px.outfile);
    args = ft_split(cmd, ' ');
    if (ft_exec(args, environ) < 0)
        error("Error ft_exec");
}

int main(int argc, char *argv[])
{
    t_pipex px;
    int     i;
    int     pid;

    px.infile = open(argv[1], O_RDONLY);
    px.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT, 00777);
    if (argc < 5)
        error("Invalid number of arguments");
    if (pipe(px.pipe) < 0)
        error("Error opening pipe");
    i = 2;
    while (i < argc - 1)
    {
        pid = fork();
        if (pid < 0)
            error("Error forking process");
        px.new_in = px.pipe[0];
        px.new_out = px.pipe[1];
        if (i == 2)
        {
            px.new_in = px.infile;
            px.new_out = px.pipe[1];
        }
        else if (i == argc - 2)
        {
            px.new_in = px.pipe[0];
            px.new_out = px.outfile;
        }
        if (pid == 0)
            child_process(argv[i], px);
        i++;
    }
    close(px.pipe[0]);
    close(px.pipe[1]);
    close(px.infile);
    close(px.outfile);
    wait(NULL);
    return (0);
}