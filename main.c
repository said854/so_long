
#include "so_long.h"
#include <fcntl.h>    // For open
#include <unistd.h>   // For close, read
#include <stdio.h>    // For perror, printf
#include <stdlib.h>   // For malloc, free


int check_walls(char *str)
{
    int i;
    i = 0;
    while(str[i])
    {
        if (str[i] == '\n')
        {
            break;
        }
        if (str[i] != '1')
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int check_first_walls(char *str)
{
    int len;
    len = ft_strlen(str);
    if (str[0] != '1'  || str[len - 2] != '1')
    {
        return 0;
    }
    return 1;
}

void check_map_element(t_map map , char **str)
{
    int i;
    int j;
    i = 0;
    j = 0;
    while (str[j])
    {
        while (str[j][i])
        {
            if (str[j][i] == 'C')
                map.collection += 1;
            if (str[j][i] == 'E')
                map.door += 1;
            if (str[j][i] == 'P')
                map.player += 1;
           i++;
        }
        
        j++;
    }
    
}
int check_map(t_map map)
{
    if (map.collection != 1 || map.door != 1 || map.player != 1)
    {
        return 0;
    }
    return 1;
}


int main(int ac, char **av)
{
    int fd;
    char **ptr = NULL;
    char *line = NULL;
    int i = 0;
    int j = 0;
    t_map map;
    if (ac < 2) {
        perror("No file provided");
        return 1;
    }

    fd = open(av[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    ptr = malloc(sizeof(char *) * 1024); 
    if (!ptr) {
        perror("Memory allocation failed");
        close(fd);
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL) 
    {
        ptr[i++] = line; 
    }
    ptr[i] = NULL;

    close(fd);
    
    //check walls
    if (!check_walls(ptr[0]) || !check_walls(ptr[i - 1]))
    {
        perror("Error\n");
        exit(1);
    }
    while (j <= i - 1)
    {
        if (!check_first_walls(ptr[j]))
        {
            perror("Error\n");
            exit(1);  
        }
        j++;
    }
    map = (t_map){0, 0, 0};
    if (!check_map(map))
    {
        perror("Error\n");
        exit(1);  
    }

    return 0;
}


