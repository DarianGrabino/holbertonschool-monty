#include "monty.h"


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }


FILE *file = fopen(argv[1], "r");
if (file == NULL)
{
    fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
    exit(EXIT_FAILURE);
}

char *buffer = NULL, *code = NULL;
size_t buffsize = 0;

unsigned int line_number = 0;

while (getline(&buffer, &buffsize, file) != -1)
{
    line_number++;
    code = strtok(buffer, " \t\n");
    fprintf(stdout, "%s\n", code);
   
}


fprintf(stdout, "%u\n", line_number);

free(buffer);
fclose(file);
return (0);
}
