/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:10:31 by akilk             #+#    #+#             */
/*   Updated: 2022/02/18 16:57:52 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Freeing list of tetrominoes to avoid leackage.
*/

static void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
	}
}

/*
 * Checks validity of tetromino and requirement for * input file.
 * Input file should have 1 to 26 tetrominoes,
 *  resulting in 20 - 544 bytes in total
 * Arguably there should not be '\n' (or other symbols)
 *  after the last tetromino.
*/

static int	check_size(char *file)
{
	int		fd;
	int		ret;
	char	buf[546];

	fd = open(file, O_RDONLY);
	ret = read(fd, buf, 546);
	close(fd);
	if (ret % 21 != 20)
		return (-1);
	if (ret < 19 || ret > 545)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	*tetro_list;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit source_file\n");
		return (1);
	}
	tetro_list = read_tetromino(argv[1]);
	if (tetro_list == NULL || check_size(argv[1]) == -1)
	{
		ft_putstr("error\n");
		return (-1);
	}
	try_map(tetro_list);
	free_list(tetro_list);
	return (0);
}
