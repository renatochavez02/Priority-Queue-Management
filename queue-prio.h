/* (c) Larry Herman, 2023.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

/* DO NOT MODIFY THIS FILE OR YOUR CODE WILL NOT COMPILE ON THE SUBMIT
 * SERVER. */

#include "queue-prio-datastructure.h"

/* this macro ONLY works right in the scope where an array is DECLARED */
#define ARRSIZE(ARR) ((int) (sizeof(ARR) / sizeof((ARR)[0])))

unsigned short init_queue(Queue_prio *const queue_prio);
unsigned short en_queue(Queue_prio *const queue_prio,
                        const char new_element[], unsigned int priority);
short has_no_elements(const Queue_prio *const queue_prio);
short size(const Queue_prio *const queue_prio);
char *peek(const Queue_prio *const queue_prio);
char *de_queue(Queue_prio *const queue_prio);
char **all_element_names(const Queue_prio *const queue_prio);
unsigned short free_name_list(char *name_list[]);
unsigned short clear_queue_prio(Queue_prio *const queue_prio);
int get_priority(const Queue_prio *const queue_prio, const char element[]);
unsigned int remove_elements_between(Queue_prio *const queue_prio,
                                     unsigned int low, unsigned int high);
unsigned int change_priority(Queue_prio *const queue_prio,
                             const char element[], unsigned int new_priority);
