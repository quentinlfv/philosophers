#include "philo.h"

int init_thread(t_indiv *p, size_t nu)
{
    size_t  i;

    i = 0;
    while (i < nu)
    {
        if (pthread_create(&p[i].philo, NULL, &routine, &p[i]) != 0)
        {
            perror("Failed to create thread");
            return (0);
        }
        i++;
    }
    // i = 0;
    // while (i < nu)
    // {
        // if (pthread_join(p[i].philo, NULL) != 0)
        // {
            // perror("Failed to join\n");
            // return (0);
        // }
        // printf("join OK\n");
        // i++;
    // }
    return (1);
}

int join_thread(t_indiv *p, size_t nu)
{
    size_t  i;

    i = 0;
    while (i < nu)
    {
        if (pthread_join(p[i].philo, NULL) != 0)
        {
            perror("Failed to join\n");
            return (0);
        }
        printf("join OK\n");
        i++;
    }
    return (1);
}
