/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 11:49:08 by akilk             #+#    #+#             */
/*   Updated: 2022/02/18 15:58:09 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H

# define FILLIT_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

/*
 * Structure t_map is used for tetrominoes and map.
 * Size is a length of map side. So, total map area will be
 * size * size;
 * Tetromino size is always 4.
 * Start position is the map coordinate, where tetromino tries to fit
 * It is 0 by default, so top left corner, but for the same shape tetrominoes
 * it is adjusted so that lattest same shape tetrominoes avoid going through
 * same path. This is used for time optimization in case of large files.
 * ID of tetromino is used for shape. Same shape tetrominoes have same ID-s.
 * data[0] - used for keeping map or tetromino data.
 */

typedef struct s_map
{
	int		size;
	int		start;
	char	id;
	char	data[0];
}				t_map;

/* main.c */
int		main(int argc, char **argv);

/* parse.c */
t_list	*read_tetromino(char *tetromino_file);
void	replace_with_letters(char *tetromino);

/* validate.c */
int		check_valid(char *tetromino);
void	replace_with_letters(char *tetromino);

/* move.c */
void	move_top_left(char *tetromino);

/* map.c */
t_map	*create(int size);
void	print(t_map *map);
void	put(t_map *map, int x, int y, char value);
char	get(t_map *map, int x, int y);
void	clear(t_map *map, t_map *tetromino, int x, int y);

/* solve.c */
void	try_map(t_list *tetro_list);

#endif
