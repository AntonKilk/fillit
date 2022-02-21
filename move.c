/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:19:33 by akilk             #+#    #+#             */
/*   Updated: 2022/02/11 15:19:44 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * The purpose of these functions is moving tetromino
 * to the upper left corner of 4x4 square.
*/

static int	can_move_up(char *tetromino)
{
	while (*tetromino != '\n')
	{
		if (*tetromino == '#')
			break ;
		tetromino++;
	}
	if (*tetromino == '#')
		return (0);
	return (1);
}

static void	move_up(char *tetromino)
{
	int		i;
	char	*empty_line;

	i = 5;
	while (i < 20)
	{
		tetromino[i - 5] = tetromino[i];
		i++;
	}
	empty_line = "....\n";
	ft_strcpy(&tetromino[i - 5], empty_line);
}

static int	can_move_left(char *tetromino)
{
	if (tetromino[0] == '.' && tetromino[5] == '.'
		&& tetromino[10] == '.' && tetromino[15] == '.')
		return (1);
	else
		return (0);
}

static void	move_left(char *tetromino)
{
	int	i;
	int	k;

	i = 0;
	while (i < 20)
	{
		k = i % 5;
		if (k == 3)
			tetromino[i] = '.';
		else if (k == 4)
			tetromino[i] = tetromino[i];
		else
			tetromino[i] = tetromino[i + 1];
		i++;
	}
}

void	move_top_left(char *tetromino)
{
	while (can_move_up(tetromino))
		move_up(tetromino);
	while (can_move_left(tetromino))
		move_left(tetromino);
}
