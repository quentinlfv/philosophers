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
    struct timeval action;

        pthread_mutex_lock(&p.ptr->m_life);
        if (p.ptr->life != 0)
        {
            pthread_mutex_unlock(&p.ptr->m_life);
            gettimeofday(&action, NULL);
            pthread_mutex_lock(&p.ptr->msg);
            printf("%ld    %d %s\n", ((action.tv_sec * 1000 + action.tv_usec / 1000) -
            (p.ptr->start.tv_sec * 1000 + p.ptr->start.tv_usec / 1000)), p.id, message);
            pthread_mutex_unlock(&p.ptr->msg);
        }
        else
        pthread_mutex_unlock(&p.ptr->m_life);
}
