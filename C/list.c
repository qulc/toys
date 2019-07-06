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

    for (struct Node *node = first; node->next != NULL; node = node->next)
    {
        if (node->next->value == value)
        {
            free(node->next);
            node->next = node->next->next;
            break;
        }
    }
}

void swap(struct Node *one, struct Node *two)
{
    struct Node temp = *one;
    *one = *two;
    *two = temp;

    two->next = one->next;
    one->next = two;
}

void sort(struct Node *head)
{
    int len = length(head);
    for (int i = 0; i < len; i++)
    {
        for (struct Node *node = head; node->next != NULL; node = node->next)
        {
            if (node->value < node->next->value)
            {
                swap(node, node->next);
            }
        }
    }
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

int main()
{
    struct Node *head = create(0);

    for (int i = 1; i < 9; i++)
    {
        append(head, i);
    }
    print(head);

    insert(head, 0, 9);
    insert(head, 9, 9);
    print(head);

    sort(head);
    print(head);

    del(&head, 0);
    del(&head, 5);
    del(&head, 9);

    del(&head, 10); // non existent value
    print(head);

    return 0;
}