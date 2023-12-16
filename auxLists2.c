#include "simple_shell.h"
/**
 * addRvarNode - This adds a variable at the end
 * of a r_var list
 *
 * @head: head of the linked list
 * @lvar: length of the variable
 * @vvalue: value of the variable
 * @lval: length of the value
 * Return: address of the head
 */
r_var *addRvarNode(r_var **head, int lvar, char *vvalue, int lval)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->lenVar = lvar;
	new->vvalue = vvalue;
	new->lenVal = lval;

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
 * freeRvarList
 * @head: head of the linked list
 * Return: no return
 */
void freeRvarList(r_var **head)
{
	r_var *temp;
	r_var *curr;

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
