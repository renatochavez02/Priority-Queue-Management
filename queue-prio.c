#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue-prio.h"

/* The following functions operate upon one priority queue. 
   The data structure that is used is a singly linked list, so that 
   we will have nodes that represent the elements in the priority queue, as 
   well as the head which is a pointer to the first element in the priority 
   queue. 
*/

/* This function initializes the priority queue that its parameter points to.*/
unsigned short init_queue(Queue_prio *const queue_prio) {
  unsigned short is_valid = 1;
  
  /* The function returns 0 if the parameter is null, and 1 otherwise.*/
  if (queue_prio == NULL)
    is_valid = 0;
  else
    queue_prio->head = NULL;
  
  return is_valid;
}

/* This function will add a new element to the priority queue that its first
   parameter points to. The element will represent a node, and it will have a
   name and a priority indicated by the second and third parameter. It will
   handle special cases such as adding an element to an empty list, adding 
   in-between two elements, adding it to the end of the list, or adding it 
   to the beggining of a non empty list. The location where the new node
   will be added to is determined by the priority parameter.*/
unsigned short en_queue(Queue_prio *const queue_prio,
			const char new_element[], unsigned int priority) {
  unsigned short is_valid = 1;
  /* These pointers to other nodes in the linked list will help keep track of
     the previous and current node.*/
  Node *curr = NULL, *prev = NULL, *new_item = NULL;
  /* This pointer to a char will point to a dynamically allocated string.*/
  char *name_ptr = NULL;

  /* Return 0 if any parameter is null.*/
  if (queue_prio == NULL || new_element == NULL)
    is_valid = 0;
  else /* set our curr pointer to point to the head of the list. */
    curr = queue_prio->head;

  /* Look at each node in the list until we find a priority that is greater 
     than the new node's priority because the list is in descending order.*/
  while (curr != NULL && priority <= curr->priority) {
    /* Adding an element with the same priority as another element in the list
       is not valid, so 0 would be returned.*/
    if (priority == curr->priority)
      is_valid = 0;
    prev = curr;
    curr = curr->next;  
  }

  /* After finding the location where the node is inserted, we will dynamically
     allocate enough memory for our new node. Then, dynamically allocate 
     enough memory for the string that represents the name (deep copy).*/
  if (is_valid) {
    new_item = malloc(sizeof(*new_item));
    name_ptr = malloc(strlen(new_element) + 1);

    strcpy(name_ptr, new_element);

    new_item->name = name_ptr;
    new_item->priority = priority;
    new_item->next = curr;

    /* Adjust the prev pointer to point to the new node if needed.*/
    if (prev == NULL)
      queue_prio->head = new_item;
    else
      prev->next = new_item;
  }

  return is_valid;
}

/* This function returns 1 if the parameter that is passed has no elements 
   stored in it. It returns 0 if there are elements stored, and it returns 
   -1 if the parameter is NULL. */
short has_no_elements(const Queue_prio *const queue_prio) {
  short no_elements = 0;

  if (queue_prio == NULL)
    no_elements = -1;
  else if (queue_prio->head == NULL)
    no_elements = 1;

  return no_elements;
    
}

/* This function returns the number of elements in the priority queue that 
   the parameter points to.*/
short size(const Queue_prio *const queue_prio) {
  short size = 0;
  Node *curr = NULL;
  /* return -1 if the parameter is null. */
  if (queue_prio == NULL)
    size = -1;
  else {
    curr = queue_prio->head;
    /* traverse through the elements of the queue while counting them.*/
    while (curr != NULL) {
      size++;
      curr = curr->next;
    }
  }

  return size;
}

/* This function returns a pointer to a dynamically allocated string of the
   element with highest priority in the priority queue that the parameter 
   points to.*/
char *peek(const Queue_prio *const queue_prio) {
  char *pk;

  /* Return null if the parameter is null or if the priority queue is empty.*/
  if (queue_prio == NULL || queue_prio->head == NULL) /* should I do 2 checks*/
    pk = NULL;
  else {
    /* Dynamically allocate memory for the string and copy the content to it.*/
    pk = malloc(strlen(queue_prio->head->name) + 1);
    strcpy(pk, queue_prio->head->name);
  }

  return pk;
}

/* This function removes the element with highest priority in the queue. 
   It returns a pointer to the name of the element that is being removed.*/
char *de_queue(Queue_prio *const queue_prio) {
  char *rm;
  Node *track = NULL;

  /* If the parameter is null or if the queue is empty, return null.*/
  if (queue_prio == NULL || queue_prio->head == NULL) 
    rm = NULL;
  else {
    /* save the location of the head node that is being removed.*/
    track = queue_prio->head;
    rm = queue_prio->head->name;
    /* set the head to point to the next element in the queue*/
    queue_prio->head = queue_prio->head->next;
    /* free the node that was removed.*/
    free(track);
  }

  return rm;
}

/* This function returns a pointer to a dynamically allocated array of 
   pointers to strings that are also dynamically allocated. The strings
   that the array elements point to represent the names of all the elements
   in the priority queue in decreasing priority. */
char **all_element_names(const Queue_prio *queue_prio) {
  char **ppc = NULL, **start = NULL;
  Node *curr = NULL;

  /* Check if there are elements in the array to start traversing*/
  if (queue_prio->head != NULL)
    curr = queue_prio->head;

  /* If the parameter is null, then return null*/
  if (queue_prio == NULL)
    ppc = NULL;
  else {
    /* allocate memory for the array of pointers to strings*/
    ppc = malloc((size(queue_prio) + 1) * sizeof(*ppc));
    start = ppc; /* save a pointer to the beggining of the array.*/
    while (curr != NULL) {
      /* Allocate memory for each string that the array elements are pointing 
	 to. Then copy the strings to them (deep copy).*/
      *ppc = malloc(strlen(curr->name) + 1);
      strcpy(*ppc, curr->name);
      ppc++;
      curr = curr->next;
    }
    
    *ppc = NULL;
  }
  /* return the saved location to the beggining of the array.*/
  return start;
}

/* This function frees a dynamically allocated array of pointers to 
   dynamically allocated strings, then return 1 after freeing the array 
   itself.*/
unsigned short free_name_list(char *name_list[]) {
  unsigned short is_valid = 1;
  /* curr variable will help us move from element to element within the array,
     and track will help us free the elements in the array.*/
  char **curr = NULL, **track = NULL; 
  int i = 0; /* This will be an index variable*/
  /* If the parameter is null, simply return 0.*/
  if (name_list == NULL)
    is_valid = 0;
  else {
    curr = name_list;
    /* go to each element of the array.*/
    while (*curr != NULL) {
      track = curr;
      /* free each element in the array.*/
      free(*track);
      i++;
      /* continue to the next element in the array.*/
      *curr = name_list[i];
    }
    /* Free the array itself, once we are done.*/
    free(name_list);
  }

  return is_valid;
}

/* This functions frees all memory used in a priority queue by going element
   by element and freeing each of its dynamically allocated contents.*/
unsigned short clear_queue_prio(Queue_prio *const queue_prio) {
  unsigned short is_valid = 1;
  /* track will help us again to be able to free memory.*/
  Node *curr = NULL, *track = NULL;
  /* If the parameter is null, simply return 0.*/
  if (queue_prio == NULL)
    is_valid = 0;
  else {
    /* Check that we are not in an empty priority queue. */
    if (queue_prio->head != NULL) {
      curr = queue_prio->head;
      /* traverse the queue while freeing all of its elements.*/
      while (curr != NULL) {
	track = curr;
	curr = curr->next;
	/* First, we free the name. Then, we free the element itself.*/
	free(track->name);
	free(track);
      }
    }
  }

  return is_valid;
}

/* This function returns the priority of the element that is indicated by
   the second parameter inside the priority queue that the first parameter 
   points to. If the element is present more than once, return the highest
   priority.*/
int get_priority(const Queue_prio *const queue_prio, const char element[]) {
  int prio = -1, found = 0;
  Node *curr = NULL;
  /* If either parameter is null, return -1.*/
  if (queue_prio == NULL || element == NULL)
    prio = -1;
  else {
    /* Check that the priority queue is not empty.*/
    if (queue_prio->head != NULL) {
      curr = queue_prio->head;
      /* Traverse the linked list until we find the element. The first time it
	 is found, will indicate the highest priority because the list is in
	 descending order (higher priority elements will be found first).*/
      while (curr != NULL && !found) {
	if (strcmp(curr->name, element) == 0) {
	  found = 1;
	  prio = curr->priority;
	}
	curr = curr->next;
      }
    }
  }

  return prio;
  
}

/* This function removes all elements between the bounds (inclusive )
   passed in by the second and third parameter within the priority queue 
   that its first parameter points to. When removing elements from the queue
   memory that was previously dynamically allocated will be freed. The 
   function returns the number of elements that were removed.*/
unsigned int remove_elements_between(Queue_prio * const queue_prio,
				     unsigned int low, unsigned int high) {
  /* Keep track of the elements that have been removed.*/
  unsigned int removed_elements = 0;
  /* curr and prev will help us keep track of where we are in the priority 
     queue. track will help us free memory and connect will help us link
     the queue with the next element that was removed if needed.*/
  Node *curr = NULL, *track = NULL, *connect = NULL, *prev = NULL;
  /* If the  first parameter is null, simply return 0.*/
  if (queue_prio == NULL)
    removed_elements = 0;
  else {
    /* Check that the priority queue is not empty.*/
    if (queue_prio->head != NULL) {
      curr = queue_prio->head;
      /* traverse the priority queue.*/
      while (curr != NULL) {
	track = curr;
	/* If an element's priority is between the bounds, free it and its 
	   contents. Do not forget to link the previous element to the list.*/
	if (track->priority >= low && track->priority <= high) {
	  /* free the name, then the element itself. Use connect to know what
	     the next element is.*/
	  free(track->name);
	  connect = track->next;
	  free(track);
	  /* Check if the element removed was the first one in the list. If 
	     needed, connect the head pointer to the new first element.*/
	  if (prev != NULL)
	    prev->next = connect;
	  else
	    queue_prio->head = connect;
	  /* increment the counter when an element is removed.*/
	  removed_elements++;
	  curr = connect;
	}
	else {
	  prev = curr;
	  curr = curr->next;
	}
      }
    }

  }
  
  return removed_elements;
  
}

/* This functions changes the priority with the one passed as the third 
   parameter of an element name as the second parameter, which is present in
   the priority queue that its first parameter points to. However, there are
   a few instances where it is not valid to change the priority of an element.
   These instances are explained below, and 0 is returned if invalid.*/
unsigned int change_priority(Queue_prio *const queue_prio,
			     const char element[], unsigned int new_priority) {
  unsigned int is_valid = 1, found = 0, times_in_queue = 0;
  Node *curr = NULL;
  /* Check that none of the first two parameters are null.*/
  if (queue_prio == NULL || element == NULL)
    is_valid = 0;
  else {
    /* Check that the priority queue is not empty.*/
    if (queue_prio->head != NULL) {
      curr = queue_prio->head;
      /* Traverse the queue, if an element with the same priority as the third
	 parameter is present, invalid. Also, if an element is found more
	 than once, it will be invalid.*/
      while (curr != NULL && is_valid && times_in_queue <= 1) {
	if (curr->priority == new_priority)
	  is_valid = 0;
	if (strcmp(curr->name, element) == 0) 
	  times_in_queue++;
	curr = curr->next;
      }   
      if (times_in_queue > 1)
	is_valid = 0;
    }
    /* If none conditions are violated (not invalid)*/
    if (is_valid) {
      curr = queue_prio->head;
      /* Traverse the queue and look for the element with name equal to 
	 the second parameter.*/
      while (curr != NULL && !found) {
	if(strcmp(curr->name, element) == 0)
	  found = 1; /* exit loop when element is found*/
	if (!found)
	  curr = curr->next;
      }
      /* Set the element's priority equal to the new priority passed as 
	 the third parameter.*/
      if (found)
	curr->priority = new_priority;
      else /* if the element is not present in the queue, return 0.*/
	is_valid = 0;
    }
  }

  return is_valid;
}
