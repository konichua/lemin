//
// Created by Professional on 26.09.2020.
//
#include "lemin.h"
#include <stdio.h>

void 	mark_vertices_with_infinity(t_lemin **lemin)
{
	int i;

	i = 0;
	while(i < (*lemin)->n)
	{
		(*lemin)->marked_graph[i] = 2000000;
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

void 	delete_way(t_lemin **lemin)
{
	int i;
	int j;

	i = 0;
	while (i < (*lemin)->n)
	{
		j = 0;
		while (j < (*lemin)->n)
		{
			if ((*lemin)->ways[i][j] == 1)
				(*lemin)->adj_matrix[j][i] = 0; // [i][j]
			j++;
		}
		i++;
	}
}

void	fix_found_way(t_lemin **lemin, int current, int i) // идем финиш -> старт
{
	int current_mark = (*lemin)->marked_graph[find_index((*lemin)->names, (*lemin)->end)]; // нашли метку конечной вершины
	current = find_index((*lemin)->names, (*lemin)->end);
	int start = find_index((*lemin)->names, (*lemin)->start);
	while (current != start) // пока мы не достигнем стартовой вершины
	{
		i = 0;
		while (i < (*lemin)->n)
		{
			// если есть связь между вершинами и их метки отличаются на единицу, то это наш случай
			if ((*lemin)->copy_matrix[current][i] == 1 && current_mark - 1 == (*lemin)->marked_graph[i])
			{
				(*lemin)->ways[current][i] = 1;
				current = i;
				current_mark = (*lemin)->marked_graph[i];
				break;
			}
			i++;
		}
	}
}

int		bellman_ford(t_lemin **lemin, int current, int i)
{
	int stack[100000];
	int indx;
	int passed;
	int flag;

	passed = 0;
	indx = 1;
	mark_vertices_with_infinity(lemin);
	(*lemin)->marked_graph[current] = 0; // вес стартовой вершины - 0
	stack[0] = current; // первая пройденная вершина - стартовая. чтобы цикл работал нормально.
	flag = 1;
	int end = find_index((*lemin)->names, (*lemin)->end);

	// находим кратчайший путь
	while (passed < indx)
	{
		current = stack[passed];
		i = 0;
		while (i < (*lemin)->n)
		{
			if ((*lemin)->adj_matrix[current][i] == 1) // проверяем связь текущей вершины с ост. вершинами
			{
				// если у найденной вершины маркер больше, чем мы можем ей дать - обновляем
				if ((*lemin)->marked_graph[i] > (*lemin)->marked_graph[current] + 1)
				{
					(*lemin)->marked_graph[i] = (*lemin)->marked_graph[current] + 1;
					stack[indx] = i;
					indx++;
					if (end == i) // если дошли до конца
						flag = 0;
				}
			}
			i++;
		}
//		output_marked_graph((*lemin)->marked_graph, (*lemin)->n);
		passed++;
	}
	return flag;
}

void	remove_edjes(t_lemin **lemin) // мб можно сократить, ведь когда проходим матрицу, нам с большим i нужна уже большая j
{
	int i;
	int j;

	i = 0;
	while (i < (*lemin)->n)
	{
		j = 0;
		while (j < (*lemin)->n)
		{
			if ((*lemin)->ways[i][j] == (*lemin)->ways[j][i] == 1) // нашли ребра, которые обнуляют друг друга
			{
				(*lemin)->ways[i][j] = 0;
				(*lemin)->ways[j][i] = 0;
			}
			j++;
		}
		i++;
	}
}

void 	bhandari(t_lemin **lemin)
{
	int current;
	int i;

	current = find_index((*lemin)->names, (*lemin)->start); // находим индекс стартовой вершины
	// находим кратчайший путь
	while (bellman_ford(lemin, current, i) == 0) // значит нашли путь
	{
		ft_printf("way found:\n");
		// записываем найденный путь в way
		fix_found_way(lemin, current, i);
		output_ways(lemin);

		// стираем найденный путь из adj_matrix
		delete_way(lemin);
	}
	remove_edjes(lemin);
	ft_printf("ways after remove_edjes:\n");
	output_ways(lemin);
}

void 	algorithm(t_lemin **lemin)
{
	bhandari(lemin);
}
