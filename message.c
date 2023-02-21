#include "philo.h"

void    msg(t_indiv p)
{
    struct timeval action;

    gettimeofday(&action, NULL);
    printf("%ld    Hello im a philosopher number and my id is %d\n", ((action.tv_sec * 1000 + action.tv_usec / 1000) -
    (p.ptr->start.tv_sec * 1000 + p.ptr->start.tv_usec / 1000)), p.id);
}

void    action_msg(t_indiv p, char *message)
{
    size_t  time;

        pthread_mutex_lock(&p.ptr->m_life);
        if (p.ptr->life != 0)
        {
            pthread_mutex_unlock(&p.ptr->m_life);
            time = get_time(p.ptr);
            pthread_mutex_lock(&p.ptr->msg);
            printf("%ld    %d %s\n", time, p.id, message);
            pthread_mutex_unlock(&p.ptr->msg);
            }
        else
        pthread_mutex_unlock(&p.ptr->m_life);
}
