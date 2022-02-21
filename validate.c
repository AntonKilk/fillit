/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:18:10 by akilk             #+#    #+#             */
/*   Updated: 2022/02/18 16:59:40 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Function checks adjascent blocks of tetromino (#).
 * Valid tetromino can have 6-8 adjacent blocks.
 * Function returns number of adjacent blocks.
 * If tetromino symbol = #.
 * - look for all # on the left except first
 * - look for all # on the right
 * - starting from second row (i > 4) look for all # up
 * - for all rows except last one (i < 14) look row down
*/

static int	calculate_adjascent_blocks(char *tetromino, int i)
{
	int	sides;

	sides = 0;
	if (tetromino[i] == '#')
	{
		if (tetromino[i - 1] == '#' && i != 0)
			sides++;
		if (tetromino[i + 1] == '#')
			sides++;
		if (i > 4)
		{
			if (tetromino[i - 5] == '#')
				sides++;
		}
		if (i < 14)
		{
			if (tetromino[i + 5] == '#')
				sides++;
		}
	}
	return (sides);
}

/*
 * Function checks validity of tetromino.
 * Returns -1 if tetromino is invalid.
 * Returns 0 if tetromino is valid.
 * If 5th symbol is not '\n'. Lines are invalid.
 * If there are other symbols beside '#' and '.' in tetromino,
 * it is invalid.
 * If there is over 4 '#' symbols, tetromino is invalid.
 * If there less than 6 or over 8 adjacent sides, tetromino is invalid.
*/

static int	check_tetromino(char *tetromino)
{
	int	i;
	int	len;
	int	count_hash;
	int	sides;

	len = ft_strlen(tetromino);
	i = 0;
	count_hash = 0;
	sides = 0;
	while (i < len)
	{
		if (i % 5 == 4 && tetromino[i] != '\n')
			return (-1);
		else if (i % 5 != 4 && tetromino[i] != '.' && tetromino[i] != '#')
			return (-1);
		sides += calculate_adjascent_blocks(tetromino, i);
		if (tetromino[i] == '#')
			count_hash++;
		i++;
	}
	if (count_hash != 4)
		return (-1);
	if (sides < 6 || sides > 8)
		return (-1);
	return (0);
}

/*
 * This condition brought separately just to save space in previous function.
*/

int	check_valid(char *tetromino)
{
	if (check_tetromino(tetromino) == -1)
		return (-1);
	return (0);
}

/*
 * Function replace # with letters in alphabetic order.
*/

void	replace_with_letters(char *tetromino)
{
	static int	i;

	while (*tetromino)
	{
		if (*tetromino == '#')
			*tetromino = 'A' + i;
		tetromino++;
	}
	i++;
}
