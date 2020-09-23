//
// Created by Professional on 20.09.2020.
//

#ifndef MY_PRINF_LEMIN_H
#define MY_PRINF_LEMIN_H
#include "libft/libft.h"
#include "includes/ft_printf.h"

typedef struct 			s_lemin
{
	int ants;
	char *start;
	char *end;
	int is_start;
	int is_end;
	char **names; // названия вершин. по names можно однозначно присвоить индекс названию вершины
	int **adj_matrix; // матрица смежностей. индексы [i][j] соответствуют индексам из names
	int n; // размерность матрицы
}						t_lemin;

int 	len_arr(char **str);
void	add_name(t_lemin **lemin, char *str);
int 	find_index(char **names, char *str);
void	nullify_struct(t_lemin **lemin);
void	nullify_matrix(t_lemin **lemin);
int		parse_map(t_lemin **lemin);
void	set_start_end(t_lemin **lemin, char **arr);
void 	allocate_memory_matrix(t_lemin **lemin);
void 	set_comment(t_lemin **lemin, char **arr);
int 	fix_links(t_lemin **lemin, char **links);
int		check_struct(t_lemin **lemin);
int 	exit_func(t_lemin **lemin);


#endif
