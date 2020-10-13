//
// Created by Professional on 23.09.2020.
//
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
