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
	int *marked_graph; // метки вершин по алгоритму дейкстры. индекс элемента соответствует индексу вершины, значение элемента - значению метки
	int **ways; // найденные пути
	int **copy_matrix; // точная копия adj_matrix
	int **matr_ants; // где двигаются муравьи
	int *paths; // одномерный массив длин путей
	int paths_amount; // количество путей
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
void 	algorithm(t_lemin **lemin);
void 	bhandari(t_lemin **lemin);
void	allocate_memory_marked_graph(t_lemin **lemin);
void 	mark_vertices_with_infinity(t_lemin **lemin);
void ft_output_names(t_lemin **lemin);
void ft_output_matrix(t_lemin **lemin);
void 	del_loops(t_lemin **lemin);
void	nullify_ways(t_lemin **lemin);
void output_ways(t_lemin **lemin);
void 	delete_way(t_lemin **lemin);
int		bellman_ford(t_lemin **lemin, int current, int i);
void	fix_found_way(t_lemin **lemin, int current, int i);
void 	copy_matrix(t_lemin **lemin);
void	make_matr_ants(t_lemin **lemin);
void 	move_ants(t_lemin **lemin);

#endif
