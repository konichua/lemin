//
// Created by Professional on 20.09.2020.
//

#ifndef MY_PRINF_LEMIN_H
#define MY_PRINF_LEMIN_H
#include "libft/libft.h"
#include "includes/ft_printf.h"

typedef struct 			s_lemin
{
	int init_ants; // количество муравьев (2)
	int ants; // количество муравьев
	char *start; // название стартовой вершины
	char *end; // название конечной вершины
	int is_start; // нужно для коммента ##start
	int is_end;
	char **names; // названия вершин. по names можно однозначно присвоить индекс названию вершины
	int **adj_matrix; // матрица смежностей. индексы [i][j] соответствуют индексам из names
	int n; // размерность матрицы
	int *marked_graph; // метки вершин по алгоритму дейкстры. индекс элемента соответствует индексу вершины, значение элемента - значению метки
	int **ways; // найденные пути
	int **copy_matrix; // точная копия adj_matrix ИСПОЛЬЗОВАТЬ ЕГО
	int **matr_ants; // где двигаются муравьи
	int *paths; // одномерный массив длин путей
	int *unsorted_paths; // одномерный unsorted массив длин путей
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
void 	output_marked_graph(int *graph, int n);
void 	delete_way(t_lemin **lemin);
int		bellman_ford(t_lemin **lemin, int current, int i);
void	fix_found_way(t_lemin **lemin, int current, int i);
void 	copy_matrix(t_lemin **lemin);
void	make_matr_ants(t_lemin **lemin);
void 	move_ants(t_lemin **lemin);
void	move_new_ant(t_lemin **lemin, int num_way, int ant);
void 	output_paths(t_lemin **lemin);
void	free_struct(t_lemin **lemin);
void 	output_sorted_paths(t_lemin **lemin);
int     find_min(t_lemin **lemin);
int     find_max(t_lemin **lemin);
void    save_map(char *line, int flag);


#endif
