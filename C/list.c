#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *next;
};

struct Node *create(int value)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->value = value;
    node->next = NULL;
}

struct Node *end(struct Node *node)
{
    if (node->next == NULL)
    {
        return node;
    }
    return end(node->next);
}

void append(struct Node *head, int value)
{
    struct Node *new_node = create(value);
    end(head)->next = new_node;
}

void print(struct Node *head)
{
    struct Node *node = head;

    while (node)
    {
        printf("%d ", node->value);
        node = node->next;
    }
    puts("\n");
}

int length(struct Node *head)
{
    int count = 0;
    for (struct Node *node = head; node != NULL; node = node->next)
    {
        count++;
    }
    return count;
}

struct Node *get(struct Node *head, int index)
{
    struct Node *node = head;
    for (int i = 0; i < index - 1; i++)
    {
        node = node->next;
    }
    return node;
}

void insert(struct Node *head, int index, int value)
{
    struct Node *node = get(head, index);
    struct Node *new_node = create(value);

    new_node->next = node->next;
    node->next = new_node;
}

void del(struct Node **head, int value)
{
    struct Node *first = *head;

    if (first->value == value)
    {
        *head = first->next;
        free(first);
        return;
    }

    for (struct Node *node = first; node != NULL; node = node->next)
    {
        if (node->next->value == value)
        {
            free(node->next);
            node->next = node->next->next;
            break;
        }
    }
}

int main()
{
    struct Node *head = create(0);

    for (int i = 1; i < 9; i++)
    {
        append(head, i);
    }

    insert(head, 3, 12);
    insert(head, 4, 13);
    print(head);

    del(&head, 0);
    del(&head, 12);
    del(&head, 8);
    print(head);

    return 0;
}