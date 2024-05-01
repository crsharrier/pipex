/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:47:21 by crsharrier        #+#    #+#             */
/*   Updated: 2024/04/23 22:28:09 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Pass msg to perror and exit program.
*/
void    error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

/*
A wrapper around execve. Take `environ` as a variable and determine 
whether the program name found at arg[0] can be found on PATH. Call
execve if found.
*/
int ft_exec(char **args, char **env)
{
    int     i;
    int     access_status;
    char    *joined_path;
    char    **paths;

    i = 0;
    while (ft_strncmp(ft_substr(env[i], 0, 5), "PATH=", 5) != 0)
        i++;
    paths = ft_split(ft_split(env[i], '=')[1], ':');
    while (*paths)
    {
        joined_path = ft_strjoin(ft_strjoin(*paths, "/"), args[0]);
        access_status = access(joined_path, X_OK);
        if (access_status == 0)
            break ;
        paths++;
    }
    if (access_status < 0)
        error("Executable name not found in PATH");
    return (execve(joined_path, args, env));
}