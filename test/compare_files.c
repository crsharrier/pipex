/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:57:56 by crsharrier        #+#    #+#             */
/*   Updated: 2024/04/24 11:12:07 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "test/test.h"
#include "pipex.h"
#include "libft.h"

void    error(char *msg)
{
    perror(msg);
    exit(1);
}

void    ft_append(char **line, char *next_line)
{
    char    *new_str;

    new_str = ft_strjoin(*line, next_line);
    free(*line);
    free(next_line);
    *line = new_str;
}

bool    compare_files(int fd1, int fd2)
{
    char    **file1;
    char    **file2;
    char    *line;
    char    *next_line;
    int     i;

    line = get_next_line(fd1);
    while ((next_line = get_next_line(fd1)))
        ft_append(&line, next_line);
    file1 = ft_split(line, '\n');

    line = get_next_line(fd2);
    while ((next_line = get_next_line(fd2)))
        ft_append(&line, next_line);
    file2 = ft_split(line, '\n');

    i = 0;
    while (file1[i])
    {
        if (strcmp(file1[i], file2[i]) != 0)
        {
            printf(MAGENTA "from file 1: %s\nfrom file 2: %s\n" RESET, file1[i], file2[i]);
            return false;
        }
        i++;
    }
    if (file2[i] != NULL)
        return false;
    return true;
}

int main(int argc, char *argv[])
{
    int     fd1;
    int     fd2;

    if (argc != 4)
        error(
            RED "Incorrect number of arguments. Please provide: " \
            CYAN "test number, file1, file2\n" RESET
            );
    fd1 = open(argv[2], O_RDONLY);
    fd2 = open(argv[3], O_RDONLY);
    if (compare_files(fd1, fd2) != true)
        printf("%s: " RED "Files %s and %s do not match!\n" RESET, argv[1], argv[2], argv[3]);
    else
        printf("%s: " GREEN "Files %s and %s match!\n" RESET, argv[1], argv[2], argv[3]);
    return (0);
}