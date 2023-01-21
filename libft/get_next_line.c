/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:37:33 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/21 13:28:43 by tfujiwar         ###   ########.fr       */
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
	*(new_line_pos) = '\0';
	*line_p = ft_strdup(save_plus_buff);
	free(save_plus_buff);
}

static bool	handle_eof_or_error(char **save_p, char **buff_p, \
								char **line_p, ssize_t code)
{
	free(*buff_p);
	if (code == 0)
	{
		if (!*save_p || !**save_p)
		{
			free(*save_p);
			return (false);
		}
		else
		{
			*line_p = *save_p;
			*save_p = NULL;
			return (true);
		}
	}
	else
	{
		free(*save_p);
		return (false);
	}
}

bool	get_next_line(int fd, char **line)
{
	char		*buff;
	static char	*save;
	ssize_t		code;

	*line = NULL;
	buff = NULL;
	split_next_line(&save, &buff, line);
	if (*line)
		return (true);
	buff = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (false);
	while (*line == NULL)
	{
		code = read(fd, buff, BUFFER_SIZE);
		if (code == 0 || code == -1)
			return (handle_eof_or_error(&save, &buff, line, code));
		buff[code] = '\0';
		split_next_line(&save, &buff, line);
	}
	free(buff);
	return (true);
}
