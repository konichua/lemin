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
//		ft_printf(" %d ", counter);
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
	i = 0;
	while (i < (*lemin)->paths_amount)
    {
        (*lemin)->unsorted_paths[i] = (*lemin)->paths[i];
        i++;
    }

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
//    ft_printf("1");
	(*lemin)->paths = (int *)malloc(sizeof(int) * (*lemin)->paths_amount);
    (*lemin)->unsorted_paths = (int *)malloc(sizeof(int) * (*lemin)->paths_amount);
	int start = find_index((*lemin)->names, (*lemin)->start);
	int path_ind;
//    ft_printf("2");


    path_ind = 0;
	int j = 0;
	// записываем длины путей в массив
	if ((*lemin)->paths_amount > 0)
	{
		while (j < (*lemin)->n)
		{
//            ft_printf("3");
            if ((*lemin)->ways[j][start] == 1)
			{
				(*lemin)->paths[path_ind] = len_way(lemin, j);
				path_ind++;
			}
			j++;
		}
	}
//	ft_printf("make pafs");
	sort_paths(lemin);
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
//    ;
	ft_printf("L");
	ft_printf("%d", ant);
	ft_printf("-");
	ft_printf("%s", room);
	ft_printf(" ");
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

void 	go_ant2(int ant, int ind, t_lemin **lemin)
{
	int j;

	j = 0;
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

int 	go_ant(int ant, t_lemin **lemin, int end_ant)
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
	if (ind > -1 && find_index((*lemin)->names, (*lemin)->end) != ind) // муравей не на финише,
		// если был на финише - его просто стерли (или переписали)
	{
		go_ant2(ant, ind, lemin);
	}
	else if (ant == end_ant) // если он на финише и это последний муравей
	    return 1;
	return 0;
}

int 	move_exst_ants(t_lemin **lemin, int end_ant)
{
    int start;
    int end;

    if ((start = find_min(lemin)) == -1)
        return 0;
    end = find_max(lemin);
	while (start <= end)
	{
        if (go_ant(start, lemin, end_ant))
            return 0;
        start++;
	}
	return 1;
}

int     find_unsorted_way(t_lemin **lemin, int way)
{
//    (*lemin)->paths[way] // chosen way
    int duplicate;
    int i;
    int check_dup;

    duplicate = 0;
    i = 0;
    check_dup = 0;
    while (i < way)
    {
        if ((*lemin)->paths[i] == (*lemin)->paths[way])
            duplicate++;
        i++;
    }
    i = 0;
    while ((*lemin)->paths[way] != (*lemin)->unsorted_paths[i] || duplicate != check_dup)
    {
        if ((*lemin)->paths[way] == (*lemin)->unsorted_paths[i])
            check_dup++;
        i++;
    }
    return (i);
}

void 	move_ants(t_lemin **lemin)
{
	int i; // отвечает за текущий номер пути
	int ant; // муравей для output'a

	ant = 1;

	// выделяем память под пути и записываем длину каждого пути + сортируем
	make_paths(lemin);


	// DEBUG !!!!!!!!!!
	ft_printf("amount of paths: %d\n", (*lemin)->paths_amount);
	ft_printf("amount of ants: %d\n", (*lemin)->ants);
	output_paths(lemin);
    output_sorted_paths(lemin);


    // this loop will continue untill all new ants move
    while ((*lemin)->ants > 0)//(i < (*lemin)->paths_amount && (*lemin)->ants > 0)
    {
        move_exst_ants(lemin, (*lemin)->init_ants);
        i = 0;

        // решаем пускать муравья по данному пути или нет
        while (i < (*lemin)->paths_amount && (*lemin)->ants > 0 && is_ant_moving(lemin, i))  // YES
        {
            move_new_ant(lemin, find_unsorted_way(lemin, i), ant); // пустить НОВОГО муравья по конкретному пути
            (*lemin)->ants--;
            ant++;
            i++;
        }
        ft_printf("\n");
    }



//	while (is_ant_on_map(lemin)) // пока муравьи есть на карте
//	{
	while (move_exst_ants(lemin, (*lemin)->init_ants))
    {
//	    ft_printf("ENDING PART");
		ft_printf("\n");
	}

}
