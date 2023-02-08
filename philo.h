#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_indiv
{
    size_t die_in;
}t_indiv;

typedef struct s_philo
{
    t_indiv *my_philo;
    size_t nu_philo;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    struct timeval start;
    struct timeval action;
    pthread_t *philo;
    pthread_t watch;
    pthread_mutex_t *mutex;
}t_philo;

/* main.c */
int     check_args(int argc);
void    *routine(void *arg);
void    *watch(void *arg);
int     create_watch(t_philo p);
t_philo    init_var(t_philo p, char **argv);
int     init_philo(t_philo p);
int     init_die_in(t_philo p);

/* mutex.c */
int    init_mutex(t_philo p);
void    destroy_mutex(t_philo p);


/* functions.c */
size_t	ft_atoi(const char *nptr);

#endif