#include "philo.h"

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

size_t    reset_death_timer(t_indiv p)
{
   struct   timeval action;
   size_t   time;

    gettimeofday(&action, NULL);
    time = (action.tv_sec * 1000 + action.tv_usec) - (p.ptr->start.tv_sec * 1000 + p.ptr->start.tv_usec);
    p.death_timer = time + p.ptr->time_to_die;
    return (p.death_timer);
}

int check_death(t_indiv *p, size_t nu)
{
    struct timeval action;
    size_t  i;
    size_t  time;

    while (1)
    {
        i = 0;
        while (i < nu)
        {
            gettimeofday(&action, NULL);
            time = (action.tv_sec * 1000 + action.tv_usec) - (p[i].ptr->start.tv_sec * 1000 + p[i].ptr->start.tv_usec);
            if (p[i].death_timer < time)
            {
                printf("time | death timer  : %ld | %ld\n", time, p[i].death_timer);
                died_msg(p[i]);
                p[i].ptr->life = 0;
                return (0);
            }
            i++;
        }
    }
    return (0);
}
