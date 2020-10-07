//
// Created by Professional on 20.09.2020.
//
#include "lemin.h"

int exit_func(t_lemin **lemin)
{
	return 0;
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

int main(int argc, char **argv)
{
	t_lemin *lemin;

	lemin = (t_lemin *)malloc(sizeof(t_lemin));
//	if (parse_map(&lemin))
//		return exit_func(&lemin);
	parse_map(&lemin);

	algorithm(&lemin);

//	ft_output_names(&lemin);
//	ft_output_matrix(&lemin);
	return 0;
}
