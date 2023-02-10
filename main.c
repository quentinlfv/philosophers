#include "philo.h"

int check_args(int argc)
{
    if (argc > 5)
    {
        perror("too much args pipis");
        return (0);
    }
    printf("number of args : OK\n");
    return (1);
}

void *routine(void *arg)
{
    t_indiv p;

    p = *(t_indiv *)arg;
    msg(p);
    usleep(p.ptr->time_to_eat * 1000);
    usleep(p.ptr->time_to_sleep * 1000);
    /* thinking */
    return (NULL);
}


void    msg(t_indiv p)
{
    struct timeval action;

    gettimeofday(&action, NULL);
    printf("%ld    Hello im a philosopher number and my id is %d\n", ((action.tv_sec * 1000 + action.tv_usec) -
    (p.ptr->start.tv_sec * 1000 + p.ptr->start.tv_usec)), p.id);
}

// void    reset_dead_timer(t_philo p, int id)
// {
//     size_t  time;

//     gettimeofday(&p.my_philo[id].get_time, NULL);
//     p.my_philo[id] = ((p.my_philo[id].get_time.tv_sec * 1000 + p.my_philo[id].get_time.tv_usec) -
//                     (p.start.tv_sec * 1000 + p.start.tv_usec));
    

// }

// void *watch(void *arg)
// {
//     struct timeval cmp;
//     size_t time;
//     size_t i;
//     t_philo p;

//     p = *(t_philo *)arg;
//     printf("die in watch : %ld\n", p.my_philo[0].dead_timer);
//     while (1)
//     {
//         i = 0;
//         while (i < p.nu_philo)
//         {
//             gettimeofday(&cmp, NULL);
//             time = ((cmp.tv_sec * 1000 + cmp.tv_usec) -
//                     (p.start.tv_sec * 1000 + p.start.tv_usec));
//             printf("timer : %ld\n", time); 
//             if (time >= p.my_philo[i].dead_timer)
//             {
//                 printf("%ld died\n", i);
//                 // free
//                return (NULL);
//                 // exit(1);
//             }
//             usleep(50);
//             i++;
//         }
//     }
//     return (NULL);
// }

t_philo    init_var(t_philo data, char **argv)
{
    data.nu_philo = ft_atoi(argv[1]);
    data.time_to_die = ft_atoi(argv[2]);
    data.time_to_eat = ft_atoi(argv[3]);
    data.time_to_sleep = ft_atoi(argv[4]);
    return (data);
}

void    init_death_timer(t_indiv *p)
{
    size_t  i;
    size_t  nu;

    i = 0;
    nu = p[i].ptr->nu_philo;
    while (i < nu)
    {
        p[i].death_timer = p[i].ptr->time_to_die;
        i++;
    }
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
        p[i].id = i;
        p[i].ptr = data;
        i++;
    }
    printf("nu phil : %ld\n", p[0].ptr->nu_philo);
    return (p);
}


/* ---------------------------------------------------------------------*/
/*  INIT PHILO THREAD */
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

/* --------------------------------------------------------------------*/


// int create_watch(t_philo p)
// {
//     if (pthread_create(&p.watch, NULL, &watch, &p) != 0)
//     {
//         perror("Failed to create thread\n");
//         return (0);
//     }
//     if (pthread_join(p.watch, NULL) != 0)
//     {
//         perror("Failed to join\n");
//         return (0);
//     }
//     return (1);
// }

int main(int argc, char **argv)
{
    t_indiv *p; 
    t_philo data;

    if (!check_args(argc))
        return (2);
    gettimeofday(&data.start, NULL);
    data = init_var(data, argv);
    p = NULL;
    p = init_philo(p, &data);
    if (p == NULL)
        return (2);
    init_death_timer(p);
    printf("death_timer : %ld\n", p[0].death_timer);
    if(!init_thread(p, p[0].ptr->nu_philo))
        return (2);
    // if (!create_watch(p))
    //     return (2);
    // if (!init_mutex(p))
    //     return (2);
    // destroy_mutex(p);
    return (0);
}
