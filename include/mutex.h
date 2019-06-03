/*-------------------------------------------------------------------*/
#ifndef _MUTEX_H_
#define _MUTEX_H_
/*-------------------------------------------------------------------*/
#include <semaphore.h>
/*-------------------------------------------------------------------*/
/* for semaphore operations */
#define LOCK_OBJ(x)            sem_wait(&(x.mutex))
#define RELEASE_OBJ(x)         sem_post(&(x.mutex))
#define LOCK_PTR(x)            sem_wait(&(x->mutex))
#define RELEASE_PTR(x)         sem_post(&(x->mutex))
/*-------------------------------------------------------------------*/
#endif /* _MUTEX_H_ */
/*-------------------------------------------------------------------*/
