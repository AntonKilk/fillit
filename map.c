/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:39:09 by akilk             #+#    #+#             */
/*   Updated: 2022/02/11 10:29:47 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* Get coordinate */
char	get(t_map *map, int x, int y)
{
	int	size;

	size = map->size;
	return (map->data[x + y * size]);
}

/* Replace symbol at coordinates x, y with value */
void	put(t_map *map, int x, int y, char value)
{
	int	size;

	size = map->size;
	map->data[x + y * size] = value;
}

/* Clear last tetromino from map */
void	clear(t_map *map, t_map *tetromino, int x, int y)
{
	int		i;
	int		j;
	char	t;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			t = get(tetromino, j, i);
			if (t != '.' && t == get(map, j + x, i + y))
				put(map, j + x, i + y, '.');
			j++;
		}
		i++;
	}
}

/* Create a new map. Size is the length of 1 row/column */
t_map	*create(int size)
{
	t_map	*new_map;

	new_map = ft_memalloc(sizeof(t_map) + (size * size) + 1);
	if (!new_map)
	{
		ft_putstr_fd("Error creating a new map.", 2);
		exit(0);
	}
	new_map->size = size;
	ft_memset(new_map->data, '.', size * size);
	return (new_map);
}

/* Print a map */
void	print(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->size)
	{
		j = 0;
		while (j < map->size)
		{
			ft_putchar(get(map, j, i));
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
