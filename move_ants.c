//
// Created by Professional on 07.10.2020.
//
#include "lemin.h"

int		count_paths2(t_lemin **lemin)
{
	int j;
	int start;
	int counter;

	start = find_index((*lemin)->names, (*lemin)->start);
	j = 0;
	counter = 0;
	while (j < (*lemin)->n)
	{
		if ((*lemin)->ways[j][start] == 1)
			counter++;
		j++;
	}
	return counter;
}

int		len_way(t_lemin **lemin, int j)
{
	int i;
	int end;
	int counter;

	counter = 1;
	end = find_index((*lemin)->names, (*lemin)->end);
	while (j != end)
	{
		counter++;
		i = 0;
		while (i < (*lemin)->n)
		{
			if ((*lemin)->ways[i][j] == 1)
			{
				j = i;
				break;
			}
			i++;
		}
	}
	return counter;
}

void 	sort_paths(t_lemin **lemin)
{
	int i;
	int flag;
	int c;
	int j;

	flag = 1;
	while (flag)
	{
		flag = 0;
		i = 0;
		j = 1;
		while (i < (*lemin)->paths_amount && j < (*lemin)->paths_amount)
		{
			if ((*lemin)->paths[i] > (*lemin)->paths[j])
			{
				flag = 1;
				c = (*lemin)->paths[j];
				(*lemin)->paths[j] = (*lemin)->paths[i];
				(*lemin)->paths[i] = c;
			}
			i++;
			j++;
		}
	}
}

void 	make_paths(t_lemin **lemin)
{
	(*lemin)->paths_amount = count_paths2(lemin);
	(*lemin)->paths = (int *)malloc(sizeof(int) * (*lemin)->paths_amount);
	int start = find_index((*lemin)->names, (*lemin)->start);
	int path_ind;

	path_ind = 0;
	int j = 0;
	// записываем длины путей в массив
	if ((*lemin)->paths_amount > 0)
	{
		while (j < (*lemin)->n)
		{
			if ((*lemin)->ways[j][start] == 1)
			{
				(*lemin)->paths[path_ind] = len_way(lemin, j);
				path_ind++;
			}
			j++;
		}
	}
	sort_paths(lemin);
}

void 	output_paths(t_lemin **lemin)
{
	int i;

	i = 0;
	ft_printf("paths:\n");
	while (i < (*lemin)->paths_amount)
	{
		ft_printf("%d ", (*lemin)->paths[i]);
		i++;
	}
	ft_printf("\n");
}

int		is_ant_moving(t_lemin **lemin, int num_way)
{
	int j;
	int total;

	j = 0;
	total = 0;
	while (j < num_way)
	{
		total += (*lemin)->paths[num_way] - (*lemin)->paths[j];
		j++;
	}
	if ((*lemin)->ants > total)
		return 1;
	return 0;
}

void 	write_ant(int ant, char *room)
{
	ft_printf("L");
	ft_printf("%d", ant);
	ft_printf("-");
	ft_printf("%s", room);
	ft_printf(" ");
//	ft_printf("L%d-%s ", ant, room);
//	ft_printf("?");
}

void	move_new_ant(t_lemin **lemin, int num_way, int ant)
{
	int way;
	int j;

	way = -1;
	j = 0;
	while (way != num_way && j < (*lemin)->n)
	{
//		ft_printf("What");
		if ((*lemin)->ways[j][find_index((*lemin)->names, (*lemin)->start)] == 1)
			way++;
		j++;
//		ft_printf("IsThis");
	}
//	ft_printf("lol");
	j--;
	(*lemin)->matr_ants[j][find_index((*lemin)->names, (*lemin)->start)] = ant;
//	ft_printf("kek");
	write_ant(ant, (*lemin)->names[j]);
//	ft_printf("cheburek");
}

int		find_running_ant(int ant, t_lemin **lemin)
{
	int i;
	int j;

	i = 0;
	while (i < (*lemin)->n)
	{
		j = 0;
		while (j < (*lemin)->n)
		{
			if ((*lemin)->matr_ants[i][j] == ant)
				return 1;
			j++;
		}
		i++;
	}
	return 0;
}

void 	go_ant(int ant, t_lemin **lemin)
{
	int i;
	int j;
	int ind;

	i = 0;
	ind = -1;
	while (i < (*lemin)->n)
	{
		j = 0;
		while (j < (*lemin)->n)
		{
			if ((*lemin)->matr_ants[i][j] == ant) // стираем муравья отсюда
			{
				(*lemin)->matr_ants[i][j] = 0;
				ind = i;
			}
			j++;
		}
		i++;
	}
	j = 0;
	if (find_index((*lemin)->names, (*lemin)->end) != ind) // муравей не на финише,
		// если был на финише - его просто стерли (или переписали)
	{
		while (j < (*lemin)->n)
		{
			if ((*lemin)->ways[j][ind] == 1)
			{
				(*lemin)->matr_ants[j][ind] = ant;
				write_ant(ant, (*lemin)->names[j]);
				break;
			}
			j++;
		}
	}
}

void	move_exst_ants(t_lemin **lemin)
{
	int i;

	i = 1;
	while (i <= (*lemin)->init_ants)
	{
		if (find_running_ant(i, lemin)) // если мы нашли конкретного бегущего муравья
			go_ant(i, lemin);
		i++;
	}
}

int 	is_ant_on_map(t_lemin **lemin)
{
	int i;
	int j;

	i = 0;
	while (i < (*lemin)->n)
	{
		j = 0;
		while (j < (*lemin)->n)
		{
			if ((*lemin)->matr_ants[i][j] != 0)
				return 1;
			j++;
		}
		i++;
	}
	return 0;
}

void 	move_ants(t_lemin **lemin)
{
	int i; // отвечает за текущий номер пути
	int ant; // муравей для output'a

	ant = 1;
	// выделяем память под пути и записываем длину каждого пути + сортируем
	make_paths(lemin);
	ft_printf("amount of paths: %d\n", (*lemin)->paths_amount);
	ft_printf("amount of ants: %d\n", (*lemin)->ants);
	output_paths(lemin);
	// в каждой итерации решаем пускать муравья по данному пути или нет
	while ((*lemin)->ants > 0)
	{
//		ft_printf("loh");
		i = 0;
//		while (i < (*lemin)->paths_amount && (*lemin)->ants > 0)
//		{
//			ft_printf("got");
			move_exst_ants(lemin);
			while (is_ant_moving(lemin, i))  // YES
			{
//				ft_printf("YES");

//				ft_printf("SEGA?");
				move_new_ant(lemin, i, ant); // пустить НОВОГО муравья по конкретному пути
//				ft_printf("HERE?");
				(*lemin)->ants--;
				ant++;
				i++;
			}
			ft_printf("\n");

//		}
	}
	while (is_ant_on_map(lemin)) // пока муравьи есть на карте
	{
		move_exst_ants(lemin);
		ft_printf("\n");
	}
}
