#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_philo
{
    size_t nu_philo;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    struct timeval start;
    // struct timeval action;
    // pthread_t watch;
    // pthread_mutex_t *mutex;
}t_philo;

typedef struct s_indiv
{
    int         id;
    size_t      death_timer;
    pthread_t   philo;
    // struct timeval get_time;
    t_philo *ptr;
}t_indiv;

/* main.c */
int         check_args(int argc);
void        *routine(void *arg);
void        *watch(void *arg);
int         create_watch(t_philo p);
t_philo     init_var(t_philo p, char **argv);
t_indiv     *init_philo(t_indiv *p, t_philo *data);
void        init_death_timer(t_indiv *p);
int init_thread(t_indiv *p, size_t nu);

/* mutex.c */
int     init_mutex(t_philo p);
void    destroy_mutex(t_philo p);

/* functions.c */
size_t	ft_atoi(const char *nptr);

#endif