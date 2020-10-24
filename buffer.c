//
// Created by Mandi Burnette on 10/23/20.
//

#include "lemin.h"

void     save_map(char *line, int flag)
{
    int j;
    static int i = 0;
    static char buf[1000000];

    j = 0;
    if (flag)
    {
        write(1, buf, i);
        write(1, "\n", 1);
//        exit(0);
    }
    while (line[j])
    {
        buf[i] = line[j];
        j++;
        i++;
    }
    buf[i] = '\n';
    i++;
}

//int main()
//{
//    save_map("12345", 0);
//    save_map("67890", 0);
//    save_map("", 1);
//    return 0;
//}
