/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkivilah <nkivilah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:15:54 by akilk             #+#    #+#             */
/*   Updated: 2022/02/15 11:49:38 by nkivilah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Function try_put tries to apply current tetromino to map
 * at given coordinates x and y. If that is possible function returns 0,
 * if not it clears the map to previous state and returns -1.
 */

static int	try_put(t_map *map, t_map *tetromino, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < tetromino->size)
	{
		j = 0;
		while (j < tetromino->size)
		{
			if (get(tetromino, j, i) != '.')
			{
				if ((x + j < map->size) && (y + i < map->size)
					&& get(map, x + j, y + i) == '.')
					put(map, x + j, y + i, get(tetromino, j, i));
				else
				{
					clear(map, tetromino, x, y);
					return (-1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

/*
* To optimize time of calculation, function change_position compares
* current tetromino with others from the list. If there are the same
* shape i.e. same ID tetrominoes in the list, function assign their
* starting position to the latest. Start position is the map coordinate,
* from which tetromino tries to fit into the map.
* This way, tetrominoes with the same shape will not start from
* the top left corner of the map.
*/

static void	change_position(int pos, t_list **tetro_list)
{
	t_map	*next;
	t_map	*this;
	t_list	*tetromino;

	tetromino = *tetro_list;
	this = (t_map *)tetromino->content;
	while (tetromino->next)
	{
		next = (t_map *)tetromino->next->content;
		if (this->id == next->id)
			next->start = pos + 1;
		tetromino = tetromino->next;
	}
}

/*
 * Function solve receive map with the size created in try_map()
 * and the list of tetrominoes one by one. It goes through the list
 * recursively and tries to put current tetromino to given map at current
 * coordinates with the try_put() functions. 2D coordinates x,y are
 * changed to pos i.e. position to use one integer instead of two.
 * If current tetromino is succesfully placed, function solve takes the
 * tetromino in recursive call. If not, we delete last placed tetromino
 * and try another position.
*/

static int	solve(t_map *map, t_list *tetro_list)
{
	t_map	*tetromino;
	int		pos;
	int		size;

	size = map->size;
	if (tetro_list == NULL)
		return (0);
	else
	{
		tetromino = (t_map *)tetro_list->content;
		pos = tetromino->start;
		while (pos < size * size)
		{
			if (try_put(map, tetromino, pos % size, pos / size) == 0)
			{
				change_position(pos, &tetro_list);
				if (solve(map, tetro_list->next) == 0)
					return (0);
				else
					clear(map, tetromino, pos % size, pos / size);
			}
			pos++;
		}
	}
	return (-1);
}

/*
 * Function calculate_min_size receives the list of tetrominoes, counts them
 * and calculates a minimun map size using formula:
 * size * size >= number_of_pieces * 4
*/

static int	calculate_min_size(t_list **tetro_list)
{
	t_list	*tetromino;
	int		count;
	int		i;

	count = 0;
	tetromino = *tetro_list;
	while (tetromino)
	{
		count++;
		tetromino = tetromino->next;
	}
	i = 2;
	while (i * i < count * 4)
		i++;
	return (i);
}

/*
 * Function try_map creates a map with a size, that depends on number
 * tetrominoes. If function solve doesn't fit all pieces at given map
 * the size is increased by one.
 * The map is printed then.
*/

void	try_map(t_list *tetro_list)
{
	t_map	*map;
	int		size;

	size = calculate_min_size(&tetro_list);
	map = create(size);
	while (solve(map, tetro_list) != 0)
	{
		free(map);
		size++;
		map = create(size);
	}
	print(map);
	free(map);
}
