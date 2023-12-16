#include "simple_shell.h"

/**
 * addSepNodeEnd - function to add a separator found at the end
 * of a seppList.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
seppList *addSepNodeEnd(seppList **head, char sep)
{
	seppList *new, *temp;

	new = malloc(sizeof(seppList));
	if (new == NULL)
		return (NULL);

	new->septor = sep;
	new->nextNode = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->nextNode != NULL)
			temp = temp->nextNode;
		temp->nextNode = new;
	}

	return (*head);
}

/**
 * freeSepList - To free a seppList
 * @head: head of the linked list.
 * Return: no return.
 */
void freeSepList(seppList **head)
{
	seppList *temp;
	seppList *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->nextNode;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * addLineNodeEnd - To add a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
lineeList *addLineNodeEnd(lineeList **head, char *line)
{
	lineeList *new, *temp;

	new = malloc(sizeof(lineeList));
	if (new == NULL)
		return (NULL);

	new->cmline = line;
	new->nextNode = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->nextNode != NULL)
			temp = temp->nextNode;
		temp->nextNode = new;
	}

	return (*head);
}

/**
 * freeLineList - Function To free a lineeList
 * @head: head of the linked list.
 * Return: no return.
 */
void freeLineList(lineeList **head)
{
	lineeList *temp;
	lineeList *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->nextNode;
			free(temp);
		}
		*head = NULL;
	}
}
