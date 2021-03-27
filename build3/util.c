#include "util.h"

#include <string.h>

char *get_input()
{
    char *line = NULL;
    size_t len = 0;
    getline(&line, &len, stdin);
    len = strlen(line);
    if (len > 0)
    {
        line[len - 1] = '\0';
    }
    return line;
}

char *get_file_input(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    getline(&line, &len, fp);
    len = strlen(line);
    if (len > 0)
    {
        line[len - 1] = '\0';
    }
    return line;
}