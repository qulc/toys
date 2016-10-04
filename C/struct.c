#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));
    assert(who != NULL);

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void Person_destroy(struct Person *who)
{
    assert(who != NULL);

    free(who->name);
    free(who);
}

void Person_print(struct Person *who)
{
    printf("Name: %s; Age: %d, Height: %d, Weight: %d\n", 
            who->name, who->age, who->height, who->weight);
}

int main()
{
    struct Person *joe = Person_create(
            "Joe Alex", 20, 64, 140);
    struct Person *frank = Person_create(
            "Frank Blank", 21, 72, 180);

    Person_print(joe);
    Person_print(frank);

    puts("\n");

    joe->age += 20;
    Person_print(joe);

    frank->age += 20;
    Person_print(frank);

    Person_destroy(joe);
    Person_destroy(frank);

    return 0;
}
