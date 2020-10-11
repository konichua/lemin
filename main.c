//
// Created by Professional on 20.09.2020.
//
#include "lemin.h"

int exit_func(t_lemin **lemin)
{
	return 0;
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
