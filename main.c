#include "philo.h"

int check_args(int argc)
{
    if (argc > 5)
    {
        perror("too much args pipis");
        return (0);
    }
    // printf("number of args : OK\n");
    return (1);
}

/* 
    a faire :
    - separer en deux groupes : paire / impair
    - regler actualisation death timer 
    - faire un my_usleep
*/

void *routine(void *arg)
{
    t_indiv p;

    p = *(t_indiv *)arg;
    if (p.id % 2 == 0)
        usleep(100);
    while (1)
    {
        pthread_mutex_lock(&p.ptr->m_life);
        if (p.ptr->life == 0)
        {
            pthread_mutex_unlock(&p.ptr->m_life);
            break;
        }
        else 
        {
            // printf("life = %d\n", p.ptr->life);
            pthread_mutex_unlock(&p.ptr->m_life);
            pthread_mutex_lock(p.fork.right);
            action_msg(p, "has taken a fork");
            pthread_mutex_lock(&p.ptr->m_life);
            if (p.ptr->life == 0)
            {
                pthread_mutex_unlock(p.fork.right);
                pthread_mutex_unlock(&p.ptr->m_life);
                break;
            }
            pthread_mutex_unlock(&p.ptr->m_life);
            pthread_mutex_lock(p.fork.left);
            action_msg(p, "has taken a fork");
            action_msg(p, "is eating");
            pthread_mutex_lock(&p.m_death_timer);
            p.death_timer = reset_death_timer(p);
            pthread_mutex_unlock(&p.m_death_timer);
            usleep(p.ptr->time_to_eat * 1000);
            printf("%d death timer is : %ld\n", p.id , p.death_timer);
            pthread_mutex_unlock(p.fork.right);
            pthread_mutex_unlock(p.fork.left);
            action_msg(p, "is sleeping");
            usleep(p.ptr->time_to_sleep * 1000);
            action_msg(p, "is thinking");
        }   
    }
    return (NULL);
}

size_t    get_time(t_philo *data)
{
    struct timeval action;
    size_t time;

    gettimeofday(&action, NULL);
    // pthread_mutex_lock(&data->m_start);
    time = ((action.tv_sec * 1000 + action.tv_usec/1000) -
    (data->start.tv_sec * 1000 + data->start.tv_usec / 1000));
    // pthread_mutex_unlock(&data->m_start);

    return (time);
}

int main(int argc, char **argv)
{
    t_indiv *p; 
    t_philo data;
    // size_t i = 0;

    if (!check_args(argc))
        return (2);
    data = init_var(data, argv);
    p = NULL;
    p = init_philo(p, &data);
    p = init_fork(p, data.nu_philo);
    if (p == NULL)
        return (2);
    init_death_timer(p);
    gettimeofday(&data.start, NULL);
    if(!init_thread(p, p[0].ptr->nu_philo))
        return (2);
    while (check_death(p,  p[0].ptr->nu_philo) == 1);
    p[0].ptr->life = 0;
    // check_death(p, p[0].ptr->nu_philo);
    if(!join_thread(p, p[0].ptr->nu_philo))
        return (2);
    destroy_mutex(p, p[0].ptr->nu_philo);
    return (0);
}