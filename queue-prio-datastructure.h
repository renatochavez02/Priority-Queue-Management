
/* The following structures will handle a single priority queue. The 
   linked data structure is a singly linked list. A Queue_prio struct contains
   the a head that points to the start of the list. Each node has a name, 
   a priority, and a pointer to the next element in the list.*/

#if !defined(QUEUE_PRIO_DATASTRUCTURE_H)
#define QUEUE_PRIO_DATASTRUCTURE_H

typedef struct node {
 char *name;
 int priority;
 struct node *next;
} Node;

typedef struct queue_prio {
  Node *head; 
} Queue_prio;

#endif
