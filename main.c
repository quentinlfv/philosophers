#include "philo.h"

int check_args(int argc)
{
    if (argc > 5)
    {
        perror("too much args");
        return (0);
    }
    printf("number of args : OK\n");
    return (1);
}

void *routine(void *arg)
{
    t_philo p;

    p = *(t_philo *)arg;
    gettimeofday(&p.action, NULL);
    printf("%ld    Hello im a philosopher number\n", ((p.action.tv_sec * 1000 + p.action.tv_usec) -
    (p.start.tv_sec * 1000 + p.start.tv_usec)));
    return (NULL);
}

void *watch(void *arg)
{
    struct timeval cmp;
    size_t time;
    size_t i;
    t_philo p;

    p = *(t_philo *)arg;
    while (1)
    {
        i = 0;
        while (i < p.nu_philo)
        {
            printf("yo");
            gettimeofday(&cmp, NULL);
            time = cmp.tv_usec; 
            if (time >= p.my_philo[i].die_in)
            {
                printf("%ld died\n", i);
                // free
                exit(1);
            }
            i++;
        }
    }
    // gettimeofday(&p.action, NULL);
    // printf(" %ld    Hello im a philosopher number\n", ((p.action.tv_sec * 1000 + p.action.tv_usec) -
    // (p.start.tv_sec * 1000 + p.start.tv_usec)));
    return (NULL);
}

t_philo    init_var(t_philo p, char **argv)
{
    p.nu_philo = ft_atoi(argv[1]);
    p.time_to_die = ft_atoi(argv[2]);
    p.time_to_eat = ft_atoi(argv[3]);
    p.time_to_sleep = ft_atoi(argv[4]);
    return (p);
}

int init_die_in(t_philo p)
{
    size_t i;

    p.my_philo = malloc(sizeof(t_indiv) * p.nu_philo);
    printf("start in ms : %ld\n", p.start.tv_usec);
    if(!p.my_philo)
    {
        perror("failed to malloc\n");
        return (0);
    }
    i = 0;
    while (i < p.nu_philo)
    {
        p.my_philo[i].die_in =  p.start.tv_usec + p.time_to_die * 1000;
        printf("die in for philo nu %ld : %ld\n", i, p.my_philo[i].die_in);
        i++;
    }
    return (1);
}

int    init_philo(t_philo p)
{
    size_t i;

    p.philo = malloc(sizeof(pthread_t) * p.nu_philo);
    if (!p.philo)
    {
        perror("Failed to malloc\n");
        return (0);
    }
    i = 0;
    while (i < p.nu_philo)
    {
        if (pthread_create(&p.philo[i], NULL, &routine, &p) != 0)
        {
            perror("Failed to create thread\n");
            return (0);
        }
        i++;
    }
    i = 0;
    while (i < p.nu_philo)
    {
          if (pthread_join(p.philo[i], NULL) != 0)
          {
            perror("Failed to join");
            return (0);
          }
        i++;
    }
    return (1);
}

int create_watch(t_philo p)
{
    if (pthread_create(&p.watch, NULL, &watch, &p) != 0)
    {
        perror("Failed to create thread\n");
        return (0);
    }
    if (pthread_join(p.watch, NULL) != 0)
    {
        perror("Failed to join\n");
        return (0);
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_philo p;

    gettimeofday(&p.start, NULL);
    if (!check_args(argc))
        return (2);
    p = init_var(p, argv);
    p.philo = NULL;
    if (!init_philo(p))
        return (2);
    if (!init_die_in(p))
        return (2);
    if (!create_watch(p))
        return (2);
    // if (!init_mutex(p))
    //     return (2);
    // destroy_mutex(p);
    return (0);
}
