//
// Created by Professional on 23.09.2020.
//
#include "lemin.h"

void	set_start_end(t_lemin **lemin, char **arr)
{
	if ((*lemin)->is_start)
	{
		(*lemin)->start = ft_strdup(arr[0]);
		(*lemin)->is_start = 0;
	}
	else if ((*lemin)->is_end)
	{
		(*lemin)->end = ft_strdup(arr[0]);
		(*lemin)->is_end = 0;
	}
}

void	add_name(t_lemin **lemin, char *str)
{
	int len;
	char **new_arr;
	int i;

	i = 0;
	len = len_arr((*lemin)->names);
	new_arr = (char **)malloc(sizeof(char *) * (len + 2));
	if ((*lemin)->names != NULL)
	{
		// копируем предыдущий массив в новый
		while ((*lemin)->names[i])
		{
			new_arr[i] = ft_strdup((*lemin)->names[i]);
			i++;
		}
	}
	// и добавляем новую вершину
	new_arr[i] = ft_strdup(str);
	new_arr[++i] = NULL;
	(*lemin)->names = new_arr;
}

int find_index(char **names, char *str)
{
	int i;

	i = 0;
	while (names[i])
	{
		if (ft_strcmp(names[i], str) == 0)
			return i;
		i++;
	}
	return -1;
}

void 	allocate_memory_matrix(t_lemin **lemin)
{
	int i;

	i = 0;
	(*lemin)->n = len_arr((*lemin)->names); // размерность матрицы = количеству вершин
	(*lemin)->adj_matrix = (int **)malloc(sizeof(int *) * (*lemin)->n);
	(*lemin)->copy_matrix = (int **)malloc(sizeof(int *) * (*lemin)->n);
	while (i < (*lemin)->n)
	{
		(*lemin)->adj_matrix[i] = (int *)malloc(sizeof(int) * (*lemin)->n);
		(*lemin)->copy_matrix[i] = (int *)malloc(sizeof(int) * (*lemin)->n);
		i++;
	}
}

void 	set_comment(t_lemin **lemin, char **arr)
{
	if (ft_strcmp(arr[0], "##start") == 0)
		(*lemin)->is_start = 1;
	else if (ft_strcmp(arr[0], "##end") == 0)
		(*lemin)->is_end = 1;
}

int 	fix_links(t_lemin **lemin, char **links)
{
	int index1;
	int index2;

	index1 = find_index((*lemin)->names, links[0]); // находим индекс первой и второй комнаты
	index2 = find_index((*lemin)->names, links[1]);
	if (index1 == -1 || index2 == -1)
	{
		return -1;
	}
	(*lemin)->adj_matrix[index1][index2] = 1;
	(*lemin)->adj_matrix[index2][index1] = 1;
	return 0;
}

int		check_struct(t_lemin **lemin)
{
	if ((*lemin)->start == NULL || (*lemin)->end == NULL || (*lemin)->adj_matrix == NULL)
		return -1;
	if ((*lemin)->ants < 0 || (*lemin)->n < 0)
		return -1;
	return 0;
}

void	allocate_memory_marked_graph(t_lemin **lemin)
{
	(*lemin)->marked_graph = (int *)malloc(sizeof(int) * (*lemin)->n);
}

void 	del_loops(t_lemin **lemin)
{
	int i;

	i = 0;
	while (i < (*lemin)->n)
	{
		(*lemin)->adj_matrix[i][i] = 0;
		i++;
	}
}

void 	allocate_memory_ways(t_lemin **lemin)
{
	int i;

	i = 0;
	(*lemin)->ways = (int **)malloc(sizeof(int *) * (*lemin)->n);
	while (i < (*lemin)->n)
	{
		(*lemin)->ways[i] = (int *)malloc(sizeof(int) * (*lemin)->n);
		i++;
	}
}

void 	copy_matrix(t_lemin **lemin)
{
	int i;
	int j;

	i = 0;
	while (i < (*lemin)->n)
	{
		j = 0;
		while (j < (*lemin)->n)
		{
			(*lemin)->copy_matrix[i][j] = (*lemin)->adj_matrix[i][j];
			j++;
		}
		i++;
	}
}

int		parse_map(t_lemin **lemin)
{
	char *line; // for gnl
	char **arr; // для разбивания строки по пробелам
	char **links; // для разбивания строки по дефисам
	int i = 0;

	nullify_struct(lemin);
	while (get_next_line(0, &line) > 0)
	{
		arr = ft_strsplit(line, ' ');
		if (!arr)
			return -1;
		// это либо количество муравьев, либо коммент, либо связь м/у вершинами
		if (len_arr(arr) == 1)
		{
			// если первый символ - решетка, то это коммент. кроме старта и енда ничего не интересует
			if (arr[0][0] == '#')
				set_comment(lemin, arr);
			// в другом случае это связь с дефисом
			else if (len_arr(links = ft_strsplit(arr[0], '-')) == 2) // links[0], links[1]
			{
				if ((*lemin)->adj_matrix == NULL) // выделяем память, потому что комнаты закончились. дальше будут только связи. cюда зайдет только один раз
				{
					allocate_memory_matrix(lemin);
					nullify_matrix(lemin);
				}
				// записываем связи в adj_matrix
				if (fix_links(lemin, links))
					return -1;
//				ft_output_matrix(lemin);
			}
			// ну или это количество муравьев
			else if (ft_isdigit((int)arr[0][0]))
			{
				if ((*lemin)->ants == -1)
					(*lemin)->ants = ft_atoi(arr[0]);
				else
					return -1;
			}

		}
		else if (len_arr(arr) == 3)
		{
			if (!ft_isdigit((int)arr[1][0]) || !ft_isdigit((int)arr[2][0]))
				return -1;
			add_name(lemin, arr[0]);
			set_start_end(lemin, arr);
		}
		else
		{
			break;
			return -1;
		}
	}
	del_loops(lemin);
	allocate_memory_marked_graph(lemin);
	allocate_memory_ways(lemin);
	nullify_ways(lemin);
	copy_matrix(lemin);
	(*lemin)->init_ants = (*lemin)->ants;
	return check_struct(lemin);
}
