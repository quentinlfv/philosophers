#include "philo.h"

void    msg(t_indiv p)
{
    struct timeval action;

    gettimeofday(&action, NULL);
    printf("%ld    Hello im a philosopher number and my id is %d\n", ((action.tv_sec * 1000 + action.tv_usec) -
    (p.ptr->start.tv_sec * 1000 + p.ptr->start.tv_usec)), p.id);
}

void    fork_msg(t_indiv p)
{
    struct timeval action;

    gettimeofday(&action, NULL);
    pthread_mutex_lock(&p.ptr->msg);
    printf("%ld    %d has taken a fork\n", ((action.tv_sec * 1000 + action.tv_usec) -
    (p.ptr->start.tv_sec * 1000 + p.ptr->start.tv_usec)), p.id);
    pthread_mutex_unlock(&p.ptr->msg);
}

void    action_msg(t_indiv p, char *message)
{
    struct timeval action;

    gettimeofday(&action, NULL);
    pthread_mutex_lock(&p.ptr->msg);
    printf("%ld    %d %s\n", ((action.tv_sec * 1000 + action.tv_usec) -
    (p.ptr->start.tv_sec * 1000 + p.ptr->start.tv_usec)), p.id, message);
    pthread_mutex_unlock(&p.ptr->msg);
}

void    eat_msg(t_indiv p)
{
    struct timeval action;

    gettimeofday(&action, NULL);
    pthread_mutex_lock(&p.ptr->msg);
    printf("%ld    %d is eating\n", ((action.tv_sec * 1000 + action.tv_usec) -
    (p.ptr->start.tv_sec * 1000 + p.ptr->start.tv_usec)), p.id);
    pthread_mutex_unlock(&p.ptr->msg);
}

void    sleep_msg(t_indiv p)
{
    struct timeval action;

    gettimeofday(&action, NULL);
    pthread_mutex_lock(&p.ptr->msg);
    printf("%ld    %d is sleeping\n", ((action.tv_sec * 1000 + action.tv_usec) -
    (p.ptr->start.tv_sec * 1000 + p.ptr->start.tv_usec)), p.id);
    pthread_mutex_unlock(&p.ptr->msg);
}

void    thinking_msg(t_indiv p)
{
    struct timeval action;

    gettimeofday(&action, NULL);
    pthread_mutex_lock(&p.ptr->msg);
    printf("%ld    %d is thinking\n", ((action.tv_sec * 1000 + action.tv_usec) -
    (p.ptr->start.tv_sec * 1000 + p.ptr->start.tv_usec)), p.id);
    pthread_mutex_unlock(&p.ptr->msg);
}

void    died_msg(t_indiv p)
{
    struct timeval action;

    gettimeofday(&action, NULL);
    pthread_mutex_lock(&p.ptr->msg);
    printf("%ld    %d died\n", ((action.tv_sec * 1000 + action.tv_usec) -
    (p.ptr->start.tv_sec * 1000 + p.ptr->start.tv_usec)), p.id);
    pthread_mutex_unlock(&p.ptr->msg);
}
