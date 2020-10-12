//
// Created by Professional on 12.10.2020.
//
#include "lemin.h"

void 	free_names(t_lemin **lemin)
{
	int i;

	i = 0;
	while (i < (*lemin)->n)
	{
		free((*lemin)->names[i]);
		i++;
	}
}

void 	free_two_ast(int ***item, t_lemin **lemin)
{
	int i;

	i = 0;
	while (i < (*lemin)->n)
	{
		free((*item)[i]);
		i++;
	}
}

void	free_struct(t_lemin **lemin)
{
	free((*lemin)->start);
	free((*lemin)->end);
	free((*lemin)->marked_graph);
	free((*lemin)->paths);
	free_names(lemin);
//	free_two_ast(&(*lemin)->adj_matrix, lemin);
// ...
	free((*lemin));
}
