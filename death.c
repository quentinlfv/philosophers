#include "philo.h"

size_t    reset_death_timer(t_indiv p)
{
   size_t   time;

    pthread_mutex_lock(&p.ptr->m_start);
    time = get_time(p.ptr);
    pthread_mutex_unlock(&p.ptr->m_start);
    // pthread_mutex_lock(&p.m_death_timer);
    p.death_timer = time + p.ptr->time_to_die;
    // pthread_mutex_unlock(&p.m_death_timer);
    return (p.death_timer);
}

int check_death(t_indiv p, size_t nu)
{
    // size_t  i;
    size_t  time;

    // while (1)
    // {
        // i = 0;
        // while (i < nu)
        // {
            pthread_mutex_lock(&p.ptr->m_start);
            time = get_time(p.ptr);
            pthread_mutex_unlock(&p.ptr->m_start);
            pthread_mutex_lock(&.m_death_timer);
            if (p.death_timer < time)
            {
               
                // printf("id : %d time | death timer  : %ld | %ld\n", p[i].id, time, p[i].death_timer);
                action_msg(p[i], "died");
                pthread_mutex_lock(&p.ptr->m_life);
                // p[i].ptr->life = 0;
                pthread_mutex_unlock(&p.ptr->m_life);
                pthread_mutex_unlock(&p.m_death_timer);
                return (0);
            }
            else
                pthread_mutex_unlock(&p.m_death_timer);
            usleep(50);
            // i++;
        // }
    // }
    return (1);
}
