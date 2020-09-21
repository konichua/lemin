//
// Created by Professional on 20.09.2020.
//

#ifndef MY_PRINF_LEMIN_H
#define MY_PRINF_LEMIN_H

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

#endif
