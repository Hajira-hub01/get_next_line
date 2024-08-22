/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:28:03 by hajmoham          #+#    #+#             */
/*   Updated: 2024/08/22 11:20:02 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_fd(int fd, char *str)
{
	char	*temp_str;
	int		size;

	temp_str = malloc(BUFFER_SIZE + 1);
	if (!temp_str)
		return (NULL);
	size = 1;
	while (!ft_strchr(str, '\n') && (size != 0))
	{
		size = read(fd, temp_str, BUFFER_SIZE);
		if (size < 0)
		{
			free(str);
			free(temp_str);
			return (NULL);
		}
		temp_str[size] = '\0';
		str = ft_strjoin(str, temp_str);
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
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
	{
		return (NULL);
	}
	str = read_fd(fd, str);
	if (!str)
	{
		return (NULL);
	}
	line = existing_line(str);
	str = next_line(str);
	return (line);
}
// int main(void)
// {
//     int fd;
//     char *line;

//     // Open a file in read-only mode
//     fd = open("example.txt", O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Failed to open file");
//         return (1);
//     }

//     // Read and print each line from the file
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }

//     // Close the file descriptor
//     close(fd);
//     return (0);
// }

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("example.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free (line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

// int main(void)
// {
// 	int fd = open("example.txt", O_RDONLY);
// 	char *line;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if ((!line))
// 			break ;
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }