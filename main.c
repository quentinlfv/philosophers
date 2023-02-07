#include "philo.h"

int main(void)
{
    struct timeval start, action;

    gettimeofday(&start, NULL);
    for (int i = 0; i < 6; i++)
    {
        gettimeofday(&action, NULL);
        printf("Timer since program launched %ld  in milli seconds\n",
    ((action.tv_sec * 1000 + action.tv_usec) -
    (start.tv_sec * 1000 + start.tv_usec)));
    sleep(1);
    }
    return (0);
}