/* (c) Larry Herman, 2023.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

/* DO NOT MODIFY THIS FILE OR YOUR CODE WILL NOT COMPILE ON THE SUBMIT
 * SERVER. */

#include "queue-prio-list-datastructure.h"

short init_queue_list(Queue_prio_list *const queue_prio_list);
short add_queue_prio(Queue_prio_list *const queue_prio_list,
                     const char new_queue_name[]);
short num_queues(const Queue_prio_list *const queue_prio_list);
Queue_prio *get_queue(const Queue_prio_list *const queue_prio_list,
                      const char queue_name[]);
short remove_queue(Queue_prio_list *const queue_prio_list,
                   const char queue_to_remove[]);
unsigned short clear_queue_prio_list(Queue_prio_list *const queue_prio_list);
