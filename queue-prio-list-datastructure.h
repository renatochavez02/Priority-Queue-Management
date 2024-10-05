/* Name: Renato Chavez Lovon
   TerpConnect login ID: rchl07
   University ID Number: 120401329
   Discussion Section Number: 0302

   I pledge on my honor that I have not given or received any unauthorized 
   assistance on this examination (or assignment). */

/* The following structures handle a list of priority queues. 
   The linked data structure is again a singly linked list, this time the nodes
   will represent priority queues. The struct Queue_prio_list contains a head 
   pointing to the first priority queue in the list. Each node contains a name,
   a pointer to the priority queue struct itself, and a pointer to the next
   element.*/

#if !defined(QUEUE_PRIO_LIST_DATASTRUCTURE_H)
#define QUEUE_PRIO_LIST_DATASTRUCTURE_H

typedef struct q_node {
  char *name;
  Queue_prio *queue;
  struct q_node *next_q;
} Q_Node;

typedef struct queue_prio_list {
  Q_Node *head_q;
} Queue_prio_list;

#endif
