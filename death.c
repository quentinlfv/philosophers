#include "philo.h"

size_t    reset_death_timer(t_indiv p)
{
   struct   timeval action;
   size_t   time;

    gettimeofday(&action, NULL);
    time = (action.tv_sec * 1000 + action.tv_usec / 1000) - (p.ptr->start.tv_sec * 1000 + p.ptr->start.tv_usec / 1000);
    pthread_mutex_lock(&p.m_death_timer);
    p.death_timer = time + p.ptr->time_to_die;
    pthread_mutex_unlock(&p.m_death_timer);
    return (p.death_timer);
}

int check_death(t_indiv *p, size_t nu)
{
    struct  timeval action;
    size_t  i;
    size_t  time;

    while (1)
    {
        i = 0;
        while (i < nu)
        {
            gettimeofday(&action, NULL);
            time = (action.tv_sec * 1000 + action.tv_usec / 1000) - (p[i].ptr->start.tv_sec * 1000 + p[i].ptr->start.tv_usec / 1000);
            pthread_mutex_lock(&p[i].m_death_timer);
            if (p[i].death_timer < time)
            {
               
                printf("id : %d time | death timer  : %ld | %ld\n", p[i].id, time, p[i].death_timer);
                action_msg(p[i], "died");
                pthread_mutex_lock(&p[i].ptr->m_life);
                p[i].ptr->life = 0;
                pthread_mutex_unlock(&p[i].ptr->m_life);
                pthread_mutex_unlock(&p[i].m_death_timer);
                return (0);
            }
            else
                pthread_mutex_unlock(&p[i].m_death_timer);
            i++;
        }
    }
    return (1);
}
