#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

void *busy(void *ptr)
{
	puts("Hello World");
	return NULL;
}


int main()
{
	pthread_t id;
	pthread_create(&id, NULL, busy, "Hi");

	void *result;
	pthread_join(id, &result);
}
