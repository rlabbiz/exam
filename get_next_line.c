#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 4

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i] && str[i] != '\0')
        i++;
    return (i);
}

char *ft_substr(char *str, int start, int len)
{
    int i = 0;
    char *res = malloc(sizeof(char ) * len + 1);
    while (i < len)
    {
        res[i] = str[start];
        start++;
        i++;
    }
    res[i] = '\0';
    return (res);
}

char *ft_strjoin(char *s1, char *s2)
{
    char *str;

    if (!s1)
    {
        s1 = malloc(1);
        s1[0] = '\0';
    }
    str = malloc(sizeof(char ) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
    int i = 0;
    int j = 0;
    while (s1[i] != '\0')
    {
        str[i] = s1[i];
        i++;
    }
    free(s1);
    while(s2[j] != '\0')
    {
        str[i] = s2[j];
        i++;
        j++;
    }
    str[i] = '\0';
    return (str);
}

int ft_strchr(char *str)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

char *ft_get_buff(int fd, char *str)
{
    char *buff = malloc(sizeof(char ) * BUFFER_SIZE + 1);
    int i = 1;
    
    while (i)
    {
        if (i == -1)
        {
            free(buff);
            break ;
        }
        i = read(fd, buff, BUFFER_SIZE);
        str = ft_strjoin(str, buff);
        if (ft_strchr(buff))
            break ;
    }
    free(buff);
    return (str);
}

char *ft_get_line(char *str)
{
    int i = 0;
    char *line;

    while (str[i] && str[i] != '\n')
        i++;
    line = ft_substr(str, 0, i + 1);
    return (line);
}

char *ft_get_sub(char *str)
{
    int i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    char *sub = ft_substr(str, i + 1, ft_strlen(str) - i);
    free(str);
    return (sub);
}

char *get_next_line(int fd)
{
    static char *sub;
    char *line;

    if (fd < 0)
        return (NULL);

    sub = ft_get_buff(fd, sub);
    line = ft_get_line(sub);
    sub = ft_get_sub(sub);
    return (line);
}

int main()
{
    int fd = open("text.txt", O_RDONLY);

    // static char *str;
    // str[0] = '\0';

    // char *buff = ft_get_buff(fd, str);
    char *line = get_next_line(fd);
    char *line2 = get_next_line(fd);
    // char *sub = ft_get_sub(buff);
    printf("%s\n", line);
    printf("%s\n", line2);
    free(line);
    free(line2);
    // free(buff);
    // free(str);
}