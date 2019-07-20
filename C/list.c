#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *next;
};

struct List
{
    size_t size;
    struct Node *head;
    struct Node *end;
};

struct List *new_list()
{
    struct List *list = (struct List *)malloc(sizeof(struct List));
    list->size = 0;
    list->head = NULL;
    list->end = NULL;

    return list;
}

struct Node *create(int value)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->value = value;
    node->next = NULL;

    return node;
}

void append(struct List *list, int value)
{
    struct Node *node = create(value);
    if (list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        list->end->next = node;
    }
    list->end = node;
    list->size++;
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

void insert(struct List *list, int index, int value)
{
    struct Node **head = &(list->head);
    struct Node *new_node = create(value);

    if (index == 0)
    {
        new_node->next = *head;
        *head = new_node;
    }
    else
    {
        struct Node *node = get(*head, index);
        new_node->next = node->next;
        node->next = new_node;
    }

    list->size++;
}

void del(struct List *list, int value)
{
    struct Node **head = &(list->head);
    struct Node *first = *head;

    if (first->value == value)
    {
        *head = first->next;
        free(first);
        list->size--;
        return;
    }

    for (struct Node *node = first; node->next != NULL; node = node->next)
    {
        if (node->next->value == value)
        {
            free(node->next);
            node->next = node->next->next;
            list->size--;
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

void sort(struct List *list)
{
    for (int i = 0; i < list->size; i++)
    {
        for (struct Node *node = list->head; node->next != NULL; node = node->next)
        {
            if (node->value < node->next->value)
                swap(node, node->next);
        }
    }
}

void print(struct List *list)
{
    struct Node *node = list->head;
    while (node)
    {
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\tlength: %ld\n", list->size);
}

int main()
{
    struct List *list = new_list();

    for (int i = 0; i < 9; i++)
    {
        append(list, i);
    }
    print(list);

    insert(list, 0, 9);
    insert(list, 9, 9);
    print(list);

    sort(list);
    print(list);

    del(list, 0);
    del(list, 5);
    del(list, 9);
    del(list, 10); // non existent value
    print(list);

    return 0;
}