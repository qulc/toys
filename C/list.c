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

void push(struct Node *head, int value)
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

int main()
{
    struct Node *head = create(0);

    for (int i = 1; i < 9; i++)
    {
        push(head, i);
    }

    print(head);
    printf("length: %d \n", length(head));

    return 0;
}