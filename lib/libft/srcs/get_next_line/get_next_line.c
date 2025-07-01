/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:34:02 by armarboe          #+#    #+#             */
/*   Updated: 2025/04/12 23:32:01 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_file(int fd, char *buf)
{
	int	res;

	if (fd < 0)
		return (-1);
	res = read(fd, buf, BUFFER_SIZE);
	if (res == -1)
		return (-1);
	else
		buf[res] = '\0';
	return (res);
}

char	*final_line(char *s)
{
	char	*line;
	int		i;

	i = 0;
	if (!*s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	line = ft_substr_gnl(s, 0, i + (s[i] == '\n'));
	return (line);
}

char	*adjust_buffer(char *s)
{
	char	*buf;
	int		i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!*s)
		return (free(s), NULL);
	buf = ft_substr_gnl(s, i + (s[i] == '\n'), -1);
	free(s);
	return (buf);
}

char	*check_buffer(int fd, char *temp)
{
	int		res;
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	res = 1;
	while (!ft_strchr_gnl(temp, '\n') && res != 0)
	{
		res = read_file(fd, buf);
		if (res == -1)
		{
			(free(temp), free(buf));
			return (NULL);
		}
		if (!temp)
			temp = ft_strdup_gnl(buf);
		else
			temp = ft_strjoin_gnl(temp, buf);
	}
	free(buf);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*line;

	if (fd == -1 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = check_buffer(fd, buf);
	if (!buf)
		return (NULL);
	line = final_line(buf);
	buf = adjust_buffer(buf);
	if (buf && *buf == '\0')
	{
		free(buf);
		buf = NULL;
	}
	return (line);
}

// #include <stdbool.h>

// int main()
// {
// 	int fd = open("test.fdf", O_RDONLY);
// 	char *line;
// 	while (true)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		printf("%s", line);
// 		free(line);
// 	}
//     close(fd);
//     return (0);
// }
