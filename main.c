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
    // msg(p);
    while (p.ptr->life != 0)
    {
        printf("life = %d\n", p.ptr->life);
        if (pthread_mutex_lock(p.fork.right) == 0)
        {
            fork_msg(p);
            if (pthread_mutex_lock(p.fork.left) == 0)
            {
                action_msg(p, "has taken a fork");
                action_msg(p, "is eating");
                usleep(p.ptr->time_to_eat);
                p.death_timer = reset_death_timer(p);
                pthread_mutex_unlock(p.fork.right);
                pthread_mutex_unlock(p.fork.left);
                action_msg(p, "is sleeping");
                usleep((useconds_t)p.ptr->time_to_sleep);
                action_msg(p, "is sleeping");
            }
        }
    }
    return (NULL);
}

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
    p = init_fork(p, data.nu_philo);
    if (p == NULL)
        return (2);
    init_death_timer(p);
    printf("death_timer : %ld\n", p[0].death_timer);
    if(!init_thread(p, p[0].ptr->nu_philo))
        return (2);
    check_death(p, p[0].ptr->nu_philo);
    if(!join_thread(p, p[0].ptr->nu_philo))
        return (2);
    // if (!create_watch(p))
    //     return (2);
    // if (!init_mutex(p))
    //     return (2);
    // destroy_mutex(p);
    return (0);
}
