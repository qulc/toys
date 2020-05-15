#include <stdio.h>
#include <stdlib.h>


struct Dict
{
    char *key;
    char *value;
    struct Dict *next;
};


struct Dict *create(char *key, char *value)
{
    struct Dict *dict = malloc(sizeof(struct Dict));
    dict->key = key;
    dict->value = value;
    return dict;
}


char *get(struct Dict *dict, char *key)
{
    while(dict != NULL)
    {
        if (dict->key == key)
        {
             return dict->value;
        }
        dict = dict->next;
    }
    return "";
}

void update(struct Dict **dict, char *key, char *value)
{
    struct Dict *new_dict = malloc(sizeof(struct Dict));
    new_dict->key = key;
    new_dict->value = value;

    new_dict->next = *dict;

    *dict = new_dict;
}


void delete(struct Dict **_dict, char *key)
{
    struct Dict *dict = *_dict;

    if (dict->key == key)
    {
        *_dict = dict->next;
        return;
    }

    struct Dict *prev;
    while (dict != NULL)
    {
        if (dict->key == key)
        {
            prev->next = dict->next;
            break;
        }
        prev = dict;
        dict = dict->next;
    }
}


void print(struct Dict *dict)
{
    while(dict != NULL) 
    {
        printf("key: %s, value: %s \n", dict->key, dict->value);
        dict = dict->next;
    }
}


int main()
{
    struct Dict *dict = create("foo0", "bar0");

    update(&dict, "foo1", "bar1");
    update(&dict, "foo2", "bar2");
    update(&dict, "foo3", "bar3");
    print(dict);

    printf("foo1: %s\n", get(dict, "foo1"));
    printf("foo2: %s\n", get(dict, "foo2"));

    delete(&dict, "foo0");
    delete(&dict, "foo3");
    print(dict);

    return 0;
}

