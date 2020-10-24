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

//    parse_map(&lemin);

//    ft_printf("log1");

	if (parse_map(&lemin) == 0)
	    save_map("", 1);
	else
    {
        ft_printf("Error");
//        	free_struct(&lemin);
    }
	algorithm(&lemin);
//    ft_printf("log2");

//	ft_output_names(&lemin);
//	ft_output_matrix(&lemin);
//	free_struct(&lemin);
	return 0;
}
