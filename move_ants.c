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

void	fix_arr_way(t_lemin **lemin, int way, int n)
{
	int i;
	int end;
	int k;
	int j;

	j = n;
	k = 0;
	end = find_index((*lemin)->names, (*lemin)->end);

	while (j != end)
	{
		i = 0;
		while (i < (*lemin)->n)
		{
			if ((*lemin)->ways[i][j] == 1)
			{
				j = i;
				(*lemin)->paths_arr[way][k] = j;
				k++;
				break;
			}
			i++;
		}
	}
}

void 	memalloc_arr_paths(t_lemin **lemin)
{
	int i;

	(*lemin)->paths_arr = (int **)malloc(sizeof(int *) * (*lemin)->paths_amount);
	(*lemin)->ants_arr = (int **)malloc(sizeof(int *) * (*lemin)->paths_amount);
	i = 0;
	while (i < (*lemin)->paths_amount)
	{
		(*lemin)->paths_arr[i] = (int *)malloc(sizeof(int) * (*lemin)->paths[i]);
		(*lemin)->ants_arr[i] = (int *)malloc(sizeof(int) * (*lemin)->paths[i]);
		i++;
	}
}

void	fill_arr_ants(t_lemin **lemin)
{
	int i;
	int j;

	i = 0;
	while (i < (*lemin)->paths_amount)
	{
		j = 0;
		while (j < (*lemin)->paths[i])
		{
			(*lemin)->ants_arr[i][j] = 0;
			j++;
		}
		i++;
	}
}

void 	make_arr_paths2(t_lemin **lemin, int cur_way)
{
	int j;
	int n;

	j = 0; // отвечает за вторую координату в paths_arr
	int start = find_index((*lemin)->names, (*lemin)->start);
	n = -1;
	int count = 0;
	// ищем конкретный путь
	while (count <= find_unsorted_way(lemin, cur_way) && n < (*lemin)->n)
	{
		n++;
		if ((*lemin)->ways[n][start] == 1)
			count++;
	}
	if (n == -1)
		n = 0;

	while (j < (*lemin)->paths[cur_way])
	{
		while (n < (*lemin)->n)
		{
			if ((*lemin)->ways[n][start] == 1)
			{
				(*lemin)->paths_arr[cur_way][j] = n;
				start = n;
				break;
			}
			n++;
		}
		n = 0;
		j++;
	}
}

void	make_arr_paths(t_lemin **lemin)
{
	int i;

	i = 0;
	memalloc_arr_paths(lemin);
	fill_arr_ants(lemin);
	while (i < (*lemin)->paths_amount)
	{
		make_arr_paths2(lemin, i);
		i++;
	}
}

void 	make_paths(t_lemin **lemin)
{
	(*lemin)->paths_amount = count_paths2(lemin);
	(*lemin)->paths = (int *)malloc(sizeof(int) * (*lemin)->paths_amount);
    (*lemin)->unsorted_paths = (int *)malloc(sizeof(int) * (*lemin)->paths_amount);
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
	make_arr_paths(lemin);
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
}

void	move_new_ant(t_lemin **lemin, int num_way, int ant)
{
	(*lemin)->ants_arr[num_way][0] = ant;
	write_ant(ant, (*lemin)->names[(*lemin)->paths_arr[num_way][0]]);
}

int 	move_exst_ants(t_lemin **lemin, int end_ant) // возвращает 0 когда муравьи закончились
{
	int i;
	int j;
	int flag;

	i = 0;
	flag = 0;
	while (i < (*lemin)->paths_amount)
	{
		j = (*lemin)->paths[i] - 1;
		while (j > -1)
		{
			if ((*lemin)->ants_arr[i][j] != 0)
			{
				if (j + 1 < (*lemin)->paths[i])
				{
					(*lemin)->ants_arr[i][j + 1] = (*lemin)->ants_arr[i][j];
					write_ant((*lemin)->ants_arr[i][j + 1], (*lemin)->names[(*lemin)->paths_arr[i][j + 1]]);
				}
				(*lemin)->ants_arr[i][j] = 0;
				flag = 1;
			}
			j--;
		}
		i++;
	}
	if (flag == 0)
		return 0;
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
//	output_sorted_paths(lemin);
//	output_paths(lemin);
//	output_path_arr(lemin);
//	output_ants_arr(lemin);
//	output_ways(lemin);
//	exit(/0);
//
//	ft_printf("amount of paths: %d\n", (*lemin)->paths_amount);
//	ft_printf("amount of ants: %d\n", (*lemin)->ants);
//	output_paths(lemin);
//    output_sorted_paths(lemin);


    // this loop will continue untill all new ants
    // move
    while ((*lemin)->ants > 0)//(i < (*lemin)->paths_amount && (*lemin)->ants > 0)
    {
        move_exst_ants(lemin, (*lemin)->init_ants);
        i = 0;

        // решаем пускать муравья по данному пути или нет
        while (i < (*lemin)->paths_amount && (*lemin)->ants > 0 && is_ant_moving(lemin, i))  // YES
        {
//        	ft_printf("next move new ant, i = %d\n", i);
            move_new_ant(lemin, i, ant); // пустить НОВОГО муравья по конкретному пути
            (*lemin)->ants--;
            ant++;
            i++;
        }
        ft_printf("\n");
    }

//    output_ants_arr(lemin);
	while (move_exst_ants(lemin, (*lemin)->init_ants))
    {
//	    ft_printf("ENDING PART");
		ft_printf("\n");
	}

}
