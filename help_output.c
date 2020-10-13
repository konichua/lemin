//
// Created by Professional on 12.10.2020.
//

#include "lemin.h"

void 	output_paths(t_lemin **lemin)
{
	int i;

	i = 0;
	ft_printf("paths: ");
	while (i < (*lemin)->paths_amount)
	{
		ft_printf("%d ", (*lemin)->paths[i]);
		i++;
	}
	ft_printf("\n");
}

void 	output_sorted_paths(t_lemin **lemin)
{
    int i;

    i = 0;
    ft_printf("unsorted_paths:\n");
    while (i < (*lemin)->paths_amount)
    {
        ft_printf("%d ", (*lemin)->unsorted_paths[i]);
        i++;
    }
    ft_printf("\n");
}

void ft_output_names(t_lemin **lemin)
{
	ft_printf("vertices:\n");
	int i = 0;
	while ((*lemin)->names[i])
	{
		ft_printf("%d ", i);
		ft_printf("'%s'", (*lemin)->names[i]);
		ft_printf("\n");
		i++;
	}
}

void ft_output_matrix(t_lemin **lemin)
{
	int i = 0;
	int j = 0;
	ft_printf("matrix:\n");
	while (i < (*lemin)->n)
	{
		j = 0;
		while (j < (*lemin)->n)
		{
			ft_printf("%d ", (*lemin)->adj_matrix[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void output_ways(t_lemin **lemin)
{
	int i = 0;
	int j = 0;
	ft_printf("ways:\n");
	while (i < (*lemin)->n)
	{
		j = 0;
		while (j < (*lemin)->n)
		{
			ft_printf("%d ", (*lemin)->ways[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void 	output_marked_graph(int *graph, int n)
{
	int i = 0;
	ft_printf("marks: \n");
	while (i < n)
	{
		ft_printf("%d ", graph[i]);
		i++;
	}
	ft_printf("\n");
}
