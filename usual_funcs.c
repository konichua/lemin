//
// Created by Professional on 23.09.2020.
//
#include "lemin.h"

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

int     find_max(t_lemin **lemin)
{
    int i;
    int j;
    int max;

    i = 0;
    max = 0;
    while (i < (*lemin)->n)
    {
        j = 0;
        while (j < (*lemin)->n)
        {
            if ((*lemin)->matr_ants[i][j] > max)
                max = (*lemin)->matr_ants[i][j];
            j++;
        }
        i++;
    }
    if (max == 0)
        return -1;
    return max;
}

int     find_min(t_lemin **lemin)
{
    int i;
    int j;
    int min;

    i = 0;
    min = 1000000;
    while (i < (*lemin)->n)
    {
        j = 0;
        while (j < (*lemin)->n)
        {
            if ((*lemin)->matr_ants[i][j] < min && (*lemin)->matr_ants[i][j] != 0)
                min = (*lemin)->matr_ants[i][j];
            j++;
        }
        i++;
    }
    if (min == 1000000)
        return -1;
    return min;
}
