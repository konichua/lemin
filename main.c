//
// Created by Professional on 20.09.2020.
//
#include "libft/libft.h"
#include "includes/ft_printf.h"
#include "lemin.h"

int len_arr(char **str)
{
	int i;

	i = 0;
	if (str == NULL)
		return i;
	while (str[i])
		i++;
	return i;
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

void	parse_map(t_lemin **lemin) {
	char *line; // for gnl
	char **arr; // для разбивания строки по пробелам
	char **links; // для разбивания строки по дефисам
	int len;
	int i = 0;

	(*lemin)->is_start = 0;
	(*lemin)->is_end = 0;
	(*lemin)->names = NULL;
	(*lemin)->adj_matrix = NULL;
	while (get_next_line(0, &line) > 0)
	{
		arr = ft_strsplit(line, ' ');
		// это либо количество муравьев, либо коммент, либо связь м/у вершинами
		if (len_arr(arr) == 1)
		{
			// если первый символ - решетка, то это коммент. кроме старта и енда ничего не интересует
			if (arr[0][0] == '#')
			{
				if (ft_strcmp(arr[0], "##start") == 0)
					(*lemin)->is_start = 1;
				else if (ft_strcmp(arr[0], "##end") == 0)
					(*lemin)->is_end = 1;
			}
			// в другом случае это количество муравьев
			else if (ft_isdigit((int)arr[0][0]))
			{
				//ft_printf("its digit");
				(*lemin)->ants = ft_atoi(arr[0]);
			}
			// ну или это связь с дефисом
			else if (len_arr(links = ft_strsplit(arr[0], '-')) == 2) // links[0], links[1]
			{
				if ((*lemin)->adj_matrix == NULL) // выделяем память, потому что комнаты закончились. дальше будут только связи
				{
					len = len_arr((*lemin)->names); // размерность матрицы = количеству вершин
					(*lemin)->adj_matrix = (int **)malloc(sizeof(int *) * len);
					while (i < len)
					{
						(*lemin)->adj_matrix[i] = (int *)malloc(sizeof(int) * len);
						i++;
					}
				}
				// ================= ?????? ============
				// записываем связи в adj_matrix
			}
		}
		else if (len_arr(arr) == 3)
		{
			add_name(lemin, arr[0]);
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

		else
			ft_printf("Error", "\n");
	}
}

int main()
{
	t_lemin *lemin;

	lemin = (t_lemin *)malloc(sizeof(t_lemin));
	parse_map(&lemin);

	ft_printf("output:\n");
	int i = 0;
	while (lemin->names[i])
	{
		ft_printf(lemin->names[i]);
		i++;
	}
	return 0;
}