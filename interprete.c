#include "monty.h"

/**
 * _isdigit - checks if a string is a number
 * @c: character to check
 * Return: 1 if its a number, 0 otherwise
*/
int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/**
 * push - function to add a new element to the top of the stack
 * @stack: pointer to pointer to the first element on the stack
 * @line_number: number of the current line
 * Return: 0 if the element is successfully added to the stack
*/
int push(stack_t **stack, unsigned int line_number)
{
	char *numchar = NULL;
	int num = 0;
	stack_t *new_node = NULL;

	numchar = strtok(NULL, " \t\n");

	if (numchar == NULL)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; numchar[i] != '\0'; i++)
	{
		if (!_isdigit(numchar[i]) && numchar[i] != '-')
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
	}
	num = atoi(numchar);
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
	*stack = new_node;
	return (0);
}
/**
 * pall - print all elements in the stack
 * @stack: pointer to pointer to the first element on the stack
 * Return: 0 if the stack prints successfully, or if the stack is empty
*/
int pall(stack_t **stack)
{
	stack_t *current = *stack;

	if (current == NULL)
	{
		return (0);
	}

	while (current != NULL)
	{
		if (current->n)
			printf("%u\n", current->n);
		else
			printf("%u\n", 0);
		current = current->next;
	}
	return (0);
}
/**
 * main - program input
 * @argc: number of arguments passed on the command line
 * @argv: index of strings containing the arguments passed on the command line
 * Return: 0 if the program runs correctly
*/
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE); }
	stack_t *stack = NULL;
	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE); }
	char *buffer = NULL, *code = NULL;
	size_t buffsize = 0, size_t line_number = 0;

	while (getline(&buffer, &buffsize, file) != -1)
	{
		line_number++;
		code = strtok(buffer, " \t\n");
		if (code == NULL)
			continue;
		if (strcmp(code, "push") == 0)
			push(&stack, line_number);
		else if (strcmp(code, "pall") == 0)
			pall(&stack);
		else
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, code);
			exit(EXIT_FAILURE); } }
	fclose(file);
	while (stack != NULL)
	{
		stack_t *next_node = stack->next;

		free(stack);
		stack = next_node;
	}
	free(buffer);
	return (0);
}
