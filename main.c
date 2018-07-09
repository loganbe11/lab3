#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "main.h"
int main()
{

  int data1= 23;
  int data2= 13;
  int data3= 32;
  int data4 = 34;
  Heap *heap = createHeap(0,MAX_HEAP,&free,NULL,compareIntFunction);
  insertHeapNode(heap,(void*)data1);
  insertHeapNode(heap,(void*)data2);
  insertHeapNode(heap,(void*)data3);
  insertHeapNode(heap, (void*)data4);
  insertHeapNode(heap, (void*)data1);
  insertHeapNode(heap,(void*)data4);
  printf("\n%d",heap->heap->data);
  printf("\n%d",heap->heap->left->data);
  printf("\n%d",heap->heap->right->data);
  printf("\n%d",heap->heap->left->left->data);
  printf("\n%d",heap->heap->left->right->data);
  printf("\n%d",heap->heap->right->left->data);





  return 0;
}

int compareIntFunction(const void *first,const void *second)
{
  printf("\n Comparing %d and %d",first, second);
  if(first==second)
  {
    printf("\n 0:equal");
    return 0;
  }
  else if(first>second)
  {
    printf("\n 1:first greater");
    return 1;
  }
  printf("\n -1:second greater");
  return -1;
}

