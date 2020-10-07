//
// Created by Professional on 07.10.2020.
//
#include "lemin.h"

/*
int 	check_way(int **ways, t_lemin **lemin)
{
	int j;
	int start;

	j = 0;
	start = find_index((*lemin)->names, (*lemin)->start);
	while (j < (*lemin)->n)
	{
		if (ways[j][start] == 1)
			return 1;
		j++;
	}
	return 0;
}

int		count_paths(int **ways, t_lemin **lemin)
{
	int i;
	int j;
	int counter;
	int end;

	counter = 0;
	end = find_index((*lemin)->names, (*lemin)->end);

	while (check_way(ways, lemin))
	{
		counter++;
		i = find_index((*lemin)->names, (*lemin)->start);
		while (i != end)
		{
			j = 0;
			while (j < (*lemin)->n)
			{
				if (ways[j][i] == 1)
				{
					ways[j][i] = 0;
					break;
				}
				j++;
			}
			i = j;
		}
	}
	return counter;
}
*/

int		count_paths2(t_lemin **lemin)
{
	int j;
	int start;
	int counter;

	start = find_index((*lemin)->names, (*lemin)->start);
	j = 0;
	counter = 0;
	while (j < (*lemin)->n)
	{
		if ((*lemin)->ways[j][start] == 1)
			counter++;
		j++;
	}
	return counter;
}

int		len_way(t_lemin **lemin, int j)
{
	int i;
	int end;
	int counter;

	counter = 1;
	end = find_index((*lemin)->names, (*lemin)->end);
	while (j != end)
	{
		counter++;
		i = 0;
		while (i < (*lemin)->n)
		{
			if ((*lemin)->ways[i][j] == 1)
			{
				j = i;
				break;
			}
			i++;
		}
	}
	return counter;
}

void 	sort_paths(t_lemin **lemin)
{
	int i;
	int flag;
	int c;
	int j;

	flag = 1;
	while (flag)
	{
		flag = 0;
		i = 0;
		j = 1;
		while (i < (*lemin)->paths_amount && j < (*lemin)->paths_amount)
		{
			if ((*lemin)->paths[i] > (*lemin)->paths[j])
			{
				flag = 1;
				c = (*lemin)->paths[j];
				(*lemin)->paths[j] = (*lemin)->paths[i];
				(*lemin)->paths[i] = c;
			}
			i++;
			j++;
		}
	}
}

void 	make_paths(t_lemin **lemin)
{
	(*lemin)->paths_amount = count_paths2(lemin);
	(*lemin)->paths = (int *)malloc(sizeof(int) * (*lemin)->paths_amount);
	int start = find_index((*lemin)->names, (*lemin)->start);
	int path_ind;

	path_ind = 0;
	int j = 0;
	// записываем длины путей в массив
	if ((*lemin)->paths_amount > 0)
	{
		while (j < (*lemin)->n)
		{
			if ((*lemin)->ways[j][start] == 1)
			{
				(*lemin)->paths[path_ind] = len_way(lemin, j);
				path_ind++;
			}
			j++;
		}
	}
	sort_paths(lemin);
}

void 	output_paths(t_lemin **lemin)
{
	int i;

	i = 0;
	ft_printf("paths:\n");
	while (i < (*lemin)->paths_amount)
	{
		ft_printf("%d ", (*lemin)->paths[i]);
		i++;
	}
	ft_printf("\n");
}

void 	move_ants(t_lemin **lemin)
{
	// выделяем память под пути и записываем длину каждого пути + сортируем
	make_paths(lemin);

	ft_printf("amount of paths: %d\n", (*lemin)->paths_amount);
	ft_printf("amount of ants: %d\n", (*lemin)->ants);
	output_paths(lemin);
}
