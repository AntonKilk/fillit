/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:28:00 by akilk             #+#    #+#             */
/*   Updated: 2022/02/18 15:54:03 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Function string2map receives a tetromino string from tetromino file
 * It creates a structure t_map to keep string data, adds size of 4.
*/

static t_map	*string2map(char *tetromino)
{
	int		x;
	int		y;
	t_map	*new_map;

	x = 0;
	y = 0;
	new_map = create(4);
	while (*tetromino)
	{
		if (*tetromino == '\n')
		{
			x = 0;
			y++;
			tetromino++;
		}
		put(new_map, x, y, *tetromino);
		tetromino++;
		x++;
	}
	return (new_map);
}

/*
 * This function is used to check if current tetromino shape
 * is the same as one of the previous from the list.
*/

static int	tetrominoes_are_equal(t_map *t1, t_map *t2)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < 16)
	{
		if (t1->data[i] != '.' && t2->data[i] != '.')
			count++;
		if (count == 4)
			return (1);
		i++;
	}
	return (0);
}

/*
 * This is where current tetromino is compared to each of the list.
 * Same ID character is applied for same shapes.
*/

static void	check_id(t_list **list)
{
	t_list	*current;
	t_map	*t1;
	t_map	*t2;

	current = *list;
	t1 = (t_map *)current->content;
	while (current->next)
	{
		t2 = (t_map *)current->next->content;
		if (tetrominoes_are_equal(t1, t2))
		{
			t1->id = t2->id;
			return ;
		}
		current = current->next;
	}
}

/*
 * This function adds tetrominoes in t_map format to the list.
 * ID and start position of 0 is applied.
 * t_list structure is used to keep tetrominoes in the list.
*/

static void	add2list(t_list **tetro_list, char	*tetromino)
{
	t_map		*mapped_t;
	t_list		*tetro;
	static char	id = 'A';

	mapped_t = string2map(tetromino);
	mapped_t->id = id;
	mapped_t->start = 0;
	id++;
	tetro = ft_lstnew(mapped_t, sizeof(t_map) + 16);
	ft_lstadd(tetro_list, tetro);
	check_id(tetro_list);
	free(mapped_t);
}

/*
 * Function reads the input file separating it on strings of 21 byte,
 * After validation of input strings, tetromino is moved to top left corner
 * of 4x4 field. '#' signs are replaced with letters in alphabetic order
 * and converted to 16 bytes data in t_map structure and added to the list.
 * As function ft_lstadd adds new elements in the beginning of the list,
 * function ft_lstrev is used to reverse the list.
*/

t_list	*read_tetromino(char *tetromino_file)
{
	int			fd;
	int			ret;
	char		tetromino[21];
	t_list		*tetro_list;

	fd = open(tetromino_file, O_RDONLY);
	tetro_list = NULL;
	while (1)
	{
		ret = read(fd, tetromino, 21);
		if (!ret)
			break ;
		tetromino[20] = '\0';
		if (check_valid(tetromino) != 0)
			return (NULL);
		move_top_left(tetromino);
		replace_with_letters(tetromino);
		add2list(&tetro_list, tetromino);
	}
	close(fd);
	ft_lstrev(&tetro_list);
	return (tetro_list);
}
