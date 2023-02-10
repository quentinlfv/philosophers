// #include "philo.h"

// int init_mutex(t_philo p)
// {
//     size_t i;

//     p.mutex = malloc(sizeof(pthread_mutex_t) * p.nu_philo);
//     if (!p.mutex)
//     {
//         perror("Failed to malloc mutex\n");
//         return (0);
//     }
//     i = 0;
//     while (i < p.nu_philo)
//     {
//         pthread_mutex_init(&p.mutex[i], NULL);
//         i++;
//     }
//     return (1);
// }

// void destroy_mutex(t_philo p)
// {
//     size_t i;

//     i = 0;
//     while (i < p.nu_philo)
//     {
//         pthread_mutex_destroy(&p.mutex[i]);
//         i++;
//     }
// }
