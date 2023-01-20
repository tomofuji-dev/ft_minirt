/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:37:33 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/20 10:07:34 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static void	split_next_line(char **save_p, char **buff_p, char **line_p)
{
	char	*save_plus_buff;
	char	*new_line_pos;

	save_plus_buff = ft_strjoin(*save_p, *buff_p);
	new_line_pos = ft_strchr(save_plus_buff, '\n');
	if (!new_line_pos)
	{
		free(*save_p);
		*save_p = save_plus_buff;
		return ;
	}
	free(*save_p);
	*save_p = ft_strdup(new_line_pos + 1);
	*(new_line_pos + 1) = '\0';
	*line_p = ft_strdup(save_plus_buff);
	free(save_plus_buff);
}

static char	*handle_eof_or_error(char **save_p, char **buff_p, \
								char **line_p, ssize_t code)
{
	free(*buff_p);
	if (code == 0)
	{
		if (!*save_p || !**save_p)
		{
			free(*save_p);
			return (NULL);
		}
		else
		{
			*line_p = *save_p;
			*save_p = NULL;
			return (*line_p);
		}
	}
	else
	{
		free(*save_p);
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*save;
	char		*line;
	ssize_t		code;

	line = NULL;
	buff = NULL;
	split_next_line(&save, &buff, &line);
	if (line)
		return (line);
	buff = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (NULL);
	while (line == NULL)
	{
		code = read(fd, buff, BUFFER_SIZE);
		if (code == 0 || code == -1)
			return (handle_eof_or_error(&save, &buff, &line, code));
		buff[code] = '\0';
		split_next_line(&save, &buff, &line);
	}
	free(buff);
	return (line);
}

// split_next_line(save, buff, line)
// {
// 	if '\n' not in save + buff
// 		save = save + buff;
// 		return ;
// 	line = (save + buff)[:'\n'];
// 	save = (save + buff)['\n':]; // if len(buff['\n':]) == 0, save = NULL
// }

// //cat "file"と等価
// #include <fcntl.h>
// #include <stdio.h>
// int	main(int argc, char *argv[])
// {
// 	int		fd;
// 	char	*line;

// 	if (argc != 2)
// 		return (0);
// 	fd = open(argv[1], O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 		printf("%s", line);
// 	return (0);
// }

// // cat "file"と等価
// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("./tester/files/43_no_nl", O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 		printf("%s", line);
// 	return (0);
// }