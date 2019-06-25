#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    int ages[] = {20, 30, 40, 50};
    char *names[] = {"lichun", "qulc", "smith", "alex"};

    int length = sizeof(ages) / sizeof(int);

    for (int i = 0; i < length; i++)
    {
        printf("%s: %d; ", names[i], ages[i]);
    }
    puts("\n");

    int *cur_ages = ages;
    char **cur_names = names;

    for (int i = 0; i < length; i++)
    {
        printf("%s: %d; ", cur_names[i], cur_ages[i]);
    }
    puts("\n");

    for (int i = 0; i < length; i++)
    {
        printf("%s: %d; ", *(cur_names++), *(cur_ages++));
    }
    puts("\n");

    for (cur_ages = ages, cur_names = names;
         (cur_ages - ages) < length;
         cur_ages++, cur_names++)
    {
        printf("%s: %d; ", *cur_names, *cur_ages);
    }
    puts("\n");

    cur_ages = ages;
    cur_ages += 2;

    assert(*cur_ages == 40);

    cur_names = names;
    cur_names++;

    assert(*cur_names == "qulc");
    assert(*(*cur_names) == 'q');
    assert(*cur_names[0] == 'q');

    return 0;
}
