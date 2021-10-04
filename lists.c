#include "lists.h"

void add_item(struct matrix **ptr, long double *data, size_t row, size_t col, char *op)
{
        struct matrix *item;

        item = malloc(sizeof(*item));

	    if (item == NULL)
        	return;
		else
			item->data = malloc(sizeof(long double) * row * col);

        item->next = *ptr;

		memcpy(item->data, data, sizeof(long double) * row * col);

		item->row = row;
		item->col = col;
		item->op = *op;
		*ptr = item;
}

/* Function to reverse the linked list */
void reverse(struct matrix** head_ref)
{
    struct matrix* prev = NULL;
    struct matrix* current = *head_ref;
    struct matrix* next = NULL;

    while (current != NULL)
	{
        /* Store next */
        next = current->next;
 
        /* Reverse current node's pointer */
        current->next = prev;
 
        /* Move pointers one position ahead */
        prev = current;
        current = next;
    }

    *head_ref = prev;
}

void delNextMatrix (struct matrix *head)
{
	struct matrix *tmp = head->next;
	head->op = head->next->op;
	head->next = head->next->next;
	free(tmp->data);
	free(tmp);
}

struct matrix *delMatrix (struct matrix *head)
{
	if (head == NULL)
        return NULL;
 
    // Move the head pointer to the next node
    struct matrix *tmp = head;
    head = head->next;
 
    free(tmp->data);
	free(tmp);
 
    return head;
}

struct matrix make_struct(size_t rows, size_t cols)
{
    struct matrix C;
    C.data = malloc(sizeof(long double) * rows * cols);
 
    C.row = rows;
    C.col = cols;
    
    return C;
}

void free_all(struct matrix *head)
{
	struct matrix *tmp;

    while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp->data);
       free(tmp);
    }
}

int stop(struct matrix *head, const char *error)
{
	free_all(head);
	fprintf(stderr, "Matrixlab error: %s\n", error);
	return -2;
}
