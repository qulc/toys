#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

void *busy(void *str)
{
	puts(str);
}

int main()
{
	pthread_t id;
	pthread_create(&id, NULL, busy, "Hello World!");

	void *result;
	pthread_join(id, &result);
}
