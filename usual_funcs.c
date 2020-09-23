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
