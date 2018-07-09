
#ifndef _HEAP_defs_
#define _HEAP_defs_

#define MIN_HEAP 0
#define MAX_HEAP 1
#define HEAP_TYPE unsigned char


typedef struct Node
{
   void * data;
   struct Node * left;
   struct Node * right;
   struct Node * parent;
}Node;

typedef struct Heap
{
    Node *heap; /// contains all of the heap nodes
    HEAP_TYPE type; ///< flag for choosing between min and max heap
    int nodeCount; //optional element useful for finding where to insert the next value
    void (*destroyData)(void *data); ///< function pointer to a function to delete a single piece of data from the heap
    void (*printNode)(void *toBePrinted); ///< function pointer to a function that prints out a data element of the heap
    int (*compare)(const void *first, const void *second); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
}Heap;

void reheapify(Heap * heap, Node * newNode);


#endif
