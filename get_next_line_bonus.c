/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 08:48:31 by hajmoham          #+#    #+#             */
/*   Updated: 2024/08/23 10:56:23 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_fd(int fd, char *temp_str, char *str)
{
	int		size;
	char	*s;

	size = 1;
	while ((!ft_strchr(str, '\n')) && size > 0)
	{
		size = read(fd, temp_str, BUFFER_SIZE);
		if (size < 0)
		{
			free(str);
			free(temp_str);
			return (NULL);
		}
		if (size == 0)
		{
			free(temp_str);
			return (str);
		}
		temp_str[size] = '\0';
		s = str;
		str = ft_strjoin(str, temp_str);
		free(s);
	}
	free(temp_str);
	return (str);
}

char	*existing_line(char *str)
{
	char	*exist_line;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	exist_line = malloc(i + 1);
	if (!exist_line)
		return (NULL);
	exist_line[i] = '\0';
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		exist_line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		exist_line[i] = '\n';
	return (exist_line);
}

char	*next_line(char *str)
{
	size_t	i;
	char	*next_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	next_str = ft_strdup(str + i);
	if (!next_str)
		return (NULL);
	free(str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[1024];
	char		*temp_str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	temp_str = malloc(BUFFER_SIZE + 1);
	if (!temp_str)
		return (NULL);
	str[fd] = read_fd(fd, temp_str, str[fd]);
	if (!str[fd])
		return (NULL);
	line = existing_line(str[fd]);
	str[fd] = next_line(str[fd]);
	return (line);
}

// int main(void)
// {
// 	int fd1 = open("example1.txt", O_RDONLY);
// 	int fd2 = open("example2.txt", O_RDONLY);
// 	int fd3 = open("example3.txt", O_RDONLY);
// 	char *str1;
// 	char *str2;
// 	char *str3;
	
//  	while (1)
// 	{
// 			str1 = get_next_line(fd1);
// 			str2 = get_next_line(fd2);
// 			str3 = get_next_line(fd3);
// 		if (str1)
// 		{
// 			printf("%s", str1);
// 			free(str1);
// 		}
// 		if (str2)
// 		{
// 			printf("%s", str2);
// 			free(str2);
// 		}
// 		if (str3)
// 		{
// 			printf("%s", str3);
// 			free(str3);
// 		}
// 		if (!str1 && !str2 && !str3)
//             break;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// }
