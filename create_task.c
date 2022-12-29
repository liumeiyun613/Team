
#include <stdio.h>
#include <pthread.h>

int create_task(void* (*task)(void*), void* arg)
{
	int ret = 0;
	pthread_t id;

	ret = pthread_create(&id, NULL, (void*)task, arg);
	if (ret != 0)
	{
		printf("Create pthread error!/n");
		return -1;
	}

	return id;
}