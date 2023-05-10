#include "monty.h"

int push(stack_t **stack, unsigned int line_number)
{
    char *numchar = NULL;
    int num = 0;
    stack_t *new_node = NULL; 

    numchar = strtok(NULL, " \t\n");
    if (numchar == NULL)
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
    }

    num = atoi(numchar);
    if (num == 0 && *numchar != '0')
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }
    
    new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->n = num;
    new_node->prev = NULL;
    new_node->next = *stack;
    if (*stack != NULL)
    {
        (*stack)->prev = new_node;
    }
    fprintf(stdout, "node: %d\n", new_node->n);
    *stack = new_node;
    return(0);
}

int pall(stack_t **stack)
{
    stack_t *current = *stack;
	while (current != NULL)
	{
		if (current->n)
			printf("%u\n", current->n);
		else
			printf("%u\n", 0);
		current = current->next;
	}
    return(0);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

stack_t *stack = NULL;
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
    if (strcmp(code, "push") == 0)
    {
        push(&stack, line_number);
    }
    /*fprintf(stdout, "%s\n", code);*/
}


fprintf(stdout, "%u\n", line_number);

free(buffer);
fclose(file);
return (0);
}