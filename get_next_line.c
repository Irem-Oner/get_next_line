/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioner <ioner@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:07:37 by ioner             #+#    #+#             */
/*   Updated: 2024/12/13 15:14:56 by ioner            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static int	ft_line(char *save)
{
	int	i;

	i = 0;
	if (!save)
		return (0);
	while (save[i])
	{
		if (save[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char	*ft_before_nl(char *save)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_line(save);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = save[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_after_nl(char *save)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_line(save);
	new = malloc(sizeof(char) * ((ft_strlen(save) - len) + 1));
	if (!new)
		return (NULL);
	while (save[len + i])
	{
		new[i] = save[len + i];
		i++;
	}
	new[i] = '\0';
	free(save);
	save = NULL;
	return (new);
}

static char	*ft_end(char **save)
{
	char	*end;

	end = NULL;
	if (*save)
	{
		end = ft_strdup(*save);
		free (*save);
		*save = NULL;
	}
	return (end);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*reading;
	char		*line;
	int			count;

	reading = (char *)malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || !reading)
		return (free(reading), free(save), save = NULL, NULL);
	count = 1;
	while (count > 0)
	{
		count = read(fd, reading, BUFFER_SIZE);
		if (((count == 0 && (!save || !*save)) || count == -1))
			return (free(reading), free(save), save = NULL, NULL);
		reading[count] = '\0';
		save = ft_strjoin(save, reading);
		if (ft_line(save))
		{
			line = ft_before_nl(save);
			if (!line)
				return (free(reading), free(save), save = NULL, NULL);
			return (save = ft_after_nl(save), free(reading), line);
		}
	}
	return (free(reading), ft_end(&save));
}
