#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{
  Heap *heap = malloc(sizeof(Heap)*1);
  heap->nodeCount = 0;
  heap->type = htype;
  heap->destroyData = destroyDataFP;
  heap->printNode = printNodeFP;
  heap->compare = compareFP;
  return heap;
}

Node *createHeapNode(void *data)
{
  Node *newNode = malloc(sizeof(Node)*1);

  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;

  return newNode;
}

void insertHeapNode(Heap *heap, void *data)
{
  Node *nodeToInsert = createHeapNode(data);
  Node *placeHolder=heap->heap;
  Node *parentHolder = NULL;
  heap->nodeCount = heap->nodeCount + 1;
  int counter = heap->nodeCount;
  int line = 0;
  int position = 1;

  if (counter == 1)
  {
    heap->heap= nodeToInsert;
    return;
  }
  while (counter>1)
  {
    position = position *2;
    line = line +1;
    counter = counter/2;
  }
  counter = position;
  position = position *0.5;
  while(line != 0)
  {
    if (heap->nodeCount>=(counter + position))
    {
      counter = counter + position;
      parentHolder=placeHolder;
      placeHolder=placeHolder->right;
    }
    else
    {
      parentHolder=placeHolder;
      placeHolder=placeHolder->left;
    }
    position = position *0.5;//changed from /0.5
    line = line - 1;
  }
  if(parentHolder->left==NULL)
  {
    parentHolder->left = nodeToInsert;
  }
  else
  {
    parentHolder->right = nodeToInsert;
  }
  nodeToInsert->parent=parentHolder;
  reheapify(heap,nodeToInsert);
  return;

}

void deleteMinOrMax(Heap * heap)
{
  if (heap->nodeCount==1)
  {
    heap->destroyData(heap->heap->data);
    free(heap->heap);
    heap->heap=NULL;
  }
  if (heap->nodeCount>1)
  {
    float counter = heap->nodeCount;
    int line = 0;
    int position = 1;
    Node *placeHolder;
    Node *parentHolder;
    while (counter>1)
    {
      position = position *2;
      line = line +1;
      counter = counter/2;
    }
    counter = position;
    position = position *0.5;
    while(line != 0)
    {
      if (heap->nodeCount>=(counter + position))
      {
        counter = counter + position;
        parentHolder=placeHolder;
        placeHolder=placeHolder->right;
      }
      else
      {
        parentHolder=placeHolder;
        placeHolder=placeHolder->left;
      }
      position = position /0.5;
      line = line - 1;
    }
    heap->heap=placeHolder;
    heap->destroyData(placeHolder->data);
    free(placeHolder);

    getMinOrMax(heap); // NEEDS TO BE ADDED STILL
  }
  heap->nodeCount= heap->nodeCount-1;
  return;

}
void *getMinOrMax(Heap *heap)
{
  Node *placeHolder;
  Node *parent = heap->heap;
  int left = 1;
  int right = 1;
  while(parent->left!=NULL && parent->right!=NULL)
  {
    if(heap->compare(parent->left->data,parent->right->data)>=0)
    {
      if(heap->compare(parent->data,parent->left->data)<0)
      {
        placeHolder=parent;
        parent=parent->left;
        placeHolder->left=parent;
      }
      else
      {
        return;
      }

    }
    else
    {
      if(heap->compare(parent->data,parent->right->data)<0)
      {
        placeHolder=parent;
        parent=parent->right;
        placeHolder->right=parent;
      }
      else
      {
        return;
      }
    }
  }
  return;
}

void changeHeapType(Heap * heap)
{

  return;
}

void reheapify(Heap * heap, Node * newNode)
{
  Node *parentNode = newNode->parent;
  Node *placeHolder = malloc(sizeof(Node)*1);
  Node *placeHolder2 = malloc(sizeof (Node)*1);
  placeHolder->data=newNode->data;
  placeHolder2->data=parentNode->data;
  while(parentNode!=NULL && heap->compare(placeHolder->data,placeHolder2->data)>0)  //or less than for a min heap
  {
    placeHolder->data= newNode->data;
    printf("%d",placeHolder->data);
    newNode->data= placeHolder2->data;
    parentNode->data = placeHolder->data;

    placeHolder2 = newNode->parent;
    printf("\n%d",parentNode->data);

  }
  return;
}

void deleteHeap(Heap *heap)
{
  while(heap->nodeCount>0)
  {
    deleteMinOrMax(heap);
  }
  free(heap);
  return;
}


