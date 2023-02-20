#include "philo.h"

t_philo    init_var(t_philo data, char **argv)
{
    data.life = 1;
    data.nu_philo = ft_atoi(argv[1]);
    data.time_to_die = ft_atoi(argv[2]);
    data.time_to_eat = ft_atoi(argv[3]);
    data.time_to_sleep = ft_atoi(argv[4]);
    pthread_mutex_init(&data.msg, NULL);
    return (data);
}

t_indiv    *init_philo(t_indiv *p, t_philo *data)
{
    size_t i;

    p = malloc(sizeof(t_indiv) * data->nu_philo);
    if (!p)
    {
        perror("Failed to malloc\n");
        return (NULL);
    }
    i = 0;
    while (i < data->nu_philo)
    {
        p[i].id = i + 1;
        p[i].ptr = data;
        pthread_mutex_init(&p[i].my_fork, NULL);
        i++;
    }
    printf("nu phil : %ld\n", p[0].ptr->nu_philo);
    return (p);
}

t_indiv *init_fork(t_indiv *p, size_t nu)
{
    size_t  i;

    i = 0;
    while (i < nu)
    {
        p[i].fork.right = &p[i].my_fork;
        if (p[i].id == (int)nu)
            p[i].fork.left = &p[1].my_fork;
        else
            p[i].fork.left = &p[i + 1].my_fork;
        i++;
    }
    return (p);
}
