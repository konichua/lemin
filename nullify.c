//
// Created by Professional on 23.09.2020.
//
#include "lemin.h"

void	nullify_matrix(t_lemin **lemin)
{
	int i;
	int j;

	i = 0;
	while (i < (*lemin)->n)
	{
		j = 0;
		while (j < (*lemin)->n)
		{
			(*lemin)->adj_matrix[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	nullify_struct(t_lemin **lemin)
{
	(*lemin)->is_start = 0;
	(*lemin)->is_end = 0;
	(*lemin)->names = NULL;
	(*lemin)->adj_matrix = NULL;
	(*lemin)->ants = -1;
	(*lemin)->start = NULL;
	(*lemin)->end = NULL;
	(*lemin)->n = -1;
}

void	nullify_ways(t_lemin **lemin)
{
	int i;
	int j;

	i = 0;
	while (i < (*lemin)->n)
	{
		j = 0;
		while (j < (*lemin)->n)
		{
			(*lemin)->ways[i][j] = 0;
			j++;
		}
		i++;
	}
}