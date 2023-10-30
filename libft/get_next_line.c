/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalshebl <nalshebl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:48:06 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/16 22:43:37 by nalshebl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
checks if there is a new line in the stash. if there is, it sets the stash
as a duplicate of everything after the newline (if there is nothing after the
newline, set as null). it then null terminates right after the newline of
the previous stash and this is sent back.
*/
char	*check(char **new)
{
	char	*check;
	char	*temp;

	if (ft_strchr(*new, '\n') != 0)
	{
		check = ft_strchr(*new, '\n');
		temp = *new;
		if (*(check + 1) == 0)
			*new = NULL;
		else
			*new = ft_strdup(check + 1);
		*(check + 1) = 0;
		return (temp);
	}
	else
		return (NULL);
}

/*
function to read the whole line. it first checks if the existing
stash has a line to be returned. if yes, it is returned else it
continues in the loop. it reads up to "buffer" number of characters or
until it reaches a null terminator. it then null terminates the string
that was just read, assigns the address to a temporary variable,
concatenates the string just read with the existing stash and then
frees the previously read string. if there is no new line it exits
the loop, sets the stash to null and returns the previous value of the stash.
*/
char	*line(char **new, char *str, int fd)
{
	char	*temp;
	char	*new_line_check;
	int		chars_read;

	chars_read = 1;
	while (chars_read > 0)
	{
		new_line_check = check(new);
		if (new_line_check)
			return (new_line_check);
		chars_read = read(fd, str, BUFFER_SIZE);
		if (chars_read <= 0)
			break ;
		if (!*new)
			*new = ft_strdup("");
		str[chars_read] = '\0';
		temp = *new;
		*new = ft_strjoin(*new, str);
		free(temp);
	}
	temp = *new;
	*new = NULL;
	return (temp);
}

/*
first check if the file descriptor and buffer size is valid. If the buffer
size goes above max int, set it to max int and use that. allocate space for the
string to be read and then call the function that will return the line's value.
*/
char	*get_next_line(int fd)
{
	char		*str;
	static char	*new;
	char		*return_val;
	size_t		buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (size_t)BUFFER_SIZE;
	str = malloc(buffer + 1);
	if (!str)
		return (0);
	return_val = line(&new, str, fd);
	free(str);
	return (return_val);
}
