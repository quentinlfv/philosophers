#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_philo
{
    int     life;
    size_t  nu_philo;
    size_t  time_to_die;
    size_t  time_to_eat;
    size_t  time_to_sleep;
    struct  timeval start;
    pthread_mutex_t msg;
    // struct timeval action;
    // pthread_t watch;
    // pthread_mutex_t *mutex;
}t_philo;

typedef struct s_fork
{
    pthread_mutex_t    *right;
    pthread_mutex_t    *left;
}t_fork;

typedef struct s_indiv
{
    int         id;
    size_t      death_timer;
    pthread_t   philo;
    pthread_mutex_t my_fork;
    // struct timeval get_time;
    t_philo     *ptr;
    t_fork      fork;
}t_indiv;

/* main.c */
int         check_args(int argc);
void        *routine(void *arg);
void        *watch(void *arg);
void        msg(t_indiv p);
int         create_watch(t_philo p);
t_philo     init_var(t_philo p, char **argv);
t_indiv     *init_fork(t_indiv *p, size_t nu);
t_indiv     *init_philo(t_indiv *p, t_philo *data);
void        init_death_timer(t_indiv *p);
size_t      reset_death_timer(t_indiv p);
int         check_death(t_indiv *p, size_t nu);
int         init_thread(t_indiv *p, size_t nu);
int         join_thread(t_indiv *p, size_t nu);

/* mutex.c */
int         init_mutex(t_philo p);
void        destroy_mutex(t_philo p);

/* message. c */
void    action_msg(t_indiv p, char *message);
void        msg(t_indiv p);
void        fork_msg(t_indiv p);
void        eat_msg(t_indiv p);
void        sleep_msg(t_indiv p);
void        thinking_msg(t_indiv p);
void        died_msg(t_indiv p);

/* functions.c */
size_t	    ft_atoi(const char *nptr);

#endif