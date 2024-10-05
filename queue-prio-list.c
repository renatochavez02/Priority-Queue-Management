
/* The following functions operate upon a list of priority queues. A singly
   linked list is also used. The priority queues are the nodes for this list,
   but this time there is no priority.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue-prio.h"
#include "queue-prio-list.h"

/* This function initializes the elements in the priority queue list that
   the parameter points to. Then, it returns 1.*/
short init_queue_list(Queue_prio_list *const queue_prio_list) {
  short is_valid = 1;
  /* Return 0 if the parameter is null.*/
  if (queue_prio_list == NULL)
    is_valid = 0;
  else 
    queue_prio_list->head_q = NULL;

  return is_valid;
}

/* This function adds a new priority queue with the name of its second 
   parameter to the list that its first parameter points to.*/
short add_queue_prio(Queue_prio_list *const queue_prio_list,
		     const char new_queue_name[]) {
  short is_valid = 1;
  Q_Node *curr = NULL, *new_queue_node = NULL;
  Queue_prio *new_queue_prio = NULL;
  char *name_ptr = NULL;

  /* Check that none of the parameters are null, return 0 if they are.*/
  if (queue_prio_list == NULL || new_queue_name == NULL)
    is_valid = 0;
  else {
    /* set the curr pointer to the beggining of the list to traverse.*/
    curr = queue_prio_list->head_q;
    
    if (curr != NULL) {
      /* traverse through the list to get the last position where the new 
	 priority queue will be addded to.*/
      while (curr->next_q != NULL && is_valid) {
	/* Return 0 if there is any priority queue with that name alredy.*/
	if (strcmp(curr->name, new_queue_name) == 0)
	  is_valid = 0;
	curr = curr->next_q;
      }
    }
    /* If no conditions are violated, allocate memory for the priority queue
       to be added, as well as for the name of this queue.*/
    if (is_valid) {
      new_queue_node = malloc(sizeof(*new_queue_node));
      name_ptr = malloc(strlen(new_queue_name) + 1);
      new_queue_prio = malloc(sizeof(*new_queue_prio));
      new_queue_prio->head = NULL;
      /* deep copy the name into the dynamically allocated array.*/
      strcpy(name_ptr, new_queue_name);
      
      new_queue_node->name = name_ptr;
      new_queue_node->queue = new_queue_prio;
      new_queue_node->next_q = NULL;

      /* Adjust the pointers of the head to the new element, if the priority
	 queue to be addded is the first element, or adjust the last priority
	 queue to point to the new one that is added.*/
      if (curr == NULL)
	queue_prio_list->head_q = new_queue_node;
      else
	curr->next_q = new_queue_node;
    }
  }

  return is_valid;

}

/* This function returns the number of priority queues that are being stored 
   in the list.*/
short num_queues(const Queue_prio_list *const queue_prio_list) {
  int num_queues = 0;
  Q_Node *curr = NULL;

  /* If the parameter is null, return -1.*/
  if (queue_prio_list == NULL)
    num_queues = -1;
  else {
    curr = queue_prio_list->head_q;
    /* Traverse the list while counting the queues that are stored.*/
    while (curr != NULL) {
      num_queues++;
      curr = curr->next_q;
    }
  }

  return num_queues;
}

/* This function returns a pointer to the priority queue that has the same 
   name that its second parameter. The priority queue list to look at is 
   passed in the first parameter as pointer to it.*/
Queue_prio *get_queue(const Queue_prio_list *const queue_prio_list,
		      const char queue_name[]) {
  Queue_prio *q;
  Q_Node *curr = NULL;
  short q_found = 0;
  /* Return null if any parameter is null.*/
  if (queue_prio_list == NULL || queue_name == NULL)
    q = NULL;
  else {
    /* Check that the list is not empty*/
    if (queue_prio_list->head_q != NULL) {
      curr = queue_prio_list->head_q;
      /* Traverse the list, looking for the queue with the same name as the 
	 second parameter.*/
      while (curr != NULL && !q_found) {
	/* Compare the names in the list with the name passed in the second 
	   parameter. */
	if (strcmp(curr->name, queue_name) == 0) {
	  q = curr->queue;
	  q_found = 1; /* Stop traversing once the name is found.*/
	}
	curr = curr->next_q;
      }
      /* If the queue that we are looking for is not in the list, return null.*/
      if (!q_found)
	q = NULL;
    }
    else
      q = NULL;
  }

  return q;
}

/* This function removes a priority queue with the name of the second parameter
   from the priority queue list that its first parameter points to and returns
   1. If the first parameter is null, return -1. If no queue with the name 
   passed as the second parameter is found in the priority queue list, 
   return 0. */
short remove_queue(Queue_prio_list *const queue_prio_list,
		   const char queue_to_remove[]) {
  short removed = 1, found = 0;
  Queue_prio *q = NULL;
  /* variable track will help us free memory from a queue.*/
  Q_Node *curr = NULL, *track = NULL, *prev = NULL;
  /* Check that none of the parameters are null, return -1 if so.*/
  if (queue_prio_list == NULL || queue_to_remove == NULL)
    removed = -1;
  else {
    /* Check that the list is not empty. */
    if (queue_prio_list->head_q != NULL) {
      curr = queue_prio_list->head_q;
      /* Traverse the list until the element we are looking for is found.*/
      while (curr != NULL && !found) {
	if (strcmp(curr->name, queue_to_remove) == 0) {
	  q = curr->queue;
	  found = 1;
	  track = curr;
	}
	else 
	  prev = curr;
	curr = curr->next_q;
      }
      /* If the element is not found in the list, return 0.*/
      if (!found)
	removed = 0;
    }
    else
      q = NULL;

    /* Once we find the element, start freeing its contents*/
    if (found && removed) {
      /* Free the name, then call the function that frees the entire priority
	 queue.*/
      free(track->name);
      clear_queue_prio(q);

      if (prev == NULL)
	queue_prio_list->head_q = curr;
      else
	prev->next_q = curr;
      /* Free the rest of its contents and the queue itself.*/
      free(track->queue);
      free(track);
    }
  }

  return removed;
}

/* This functions frees the memory of all of the contents that its parameter
   points to, then it returns 1.*/
unsigned short clear_queue_prio_list(Queue_prio_list *const queue_prio_list) {
  unsigned short is_valid = 1;
  /* Track variable will help us free elements as we move in the list.*/
  Q_Node *curr = NULL, *track = NULL;
  Queue_prio * q = NULL;
  /* If the parameter is null, return 0.*/
  if (queue_prio_list == NULL)
    is_valid = 0;
  else {
    /* Check that the queue is not empty*/
    if (queue_prio_list->head_q != NULL) {
      curr = queue_prio_list->head_q;
      /* Start traversing the queue and removing its contents.*/
      while (curr != NULL) {
	track = curr;
	/* q variable points to the priority queue itself, so we can call 
	   the function we wrote that clears a single priority queue.*/
	q = curr->queue;
	curr = curr->next_q;
	/* Free the elements of the priority queue.*/
	free(track->name);
	clear_queue_prio(q);
	free(track->queue);
	free(track);
      }
    }
  }
  
  return is_valid;
}

