#include "./linked_list.h"

_list* NewList(){
  _list* newList = (_list*)malloc(sizeof(_list));
  newList->length = 0;         
  newList->first = NULL;
  newList->last = NULL;
  newList->current = NULL;
  return newList;
}

void* GetListIndexPointer(_list* thisList, long int index){
  thisList->current = thisList->first;
  if((index < 0)||(index >= thisList->length)) 
    return NULL;
  for(long int x = 0; x < index; x++)
    thisList->current = thisList->current->next;
  return thisList->current;
}

void* GetListIndexValuePointer(_list* thisList, long int index){
  _node* thisNode = GetListIndexPointer(thisList, index);
  return thisNode->value;
}

void DeleteNodePointer(_list* thisList, _node* thisNode){ 
  if((thisNode->next == NULL)&&(thisNode->previous == NULL))
    goto DELETE_SINGLE_NODE;
  if(thisNode->previous != NULL)
    thisNode->previous->next = thisNode->next;
  else thisList->first = thisList->first->next;
  if(thisNode->next != NULL)
    thisNode->next->previous = thisNode->previous;
  else thisList->last = thisList->last->previous;
  DELETE_SINGLE_NODE:
  free(thisNode->value);
  free(thisNode); 
}

void DeleteListIndex(_list* thisList, long int index){
  if(thisList->length < 1) return;
  _node* thisNode = GetListIndexPointer(thisList, index);
  if(thisNode == NULL) return;
  DeleteNodePointer(thisList, thisNode);
  thisList->length--;
  if(thisList->length == 0){
    thisList->first = NULL;
    thisList->last = NULL;
  }
}

void ClearList(_list* thisList){
  while(thisList->length != 0)
    DeleteListIndex(thisList, 0);
}

void AppendToList(_list* thisList, void* item){
  _node* newNode = (_node*)malloc(sizeof(_node));
  if(thisList->length){// list allready has itesm
    thisList->last->next = newNode;
    newNode->previous = thisList->last;
    thisList->last = newNode;
    newNode->next = NULL;
  }else{ // list is currently empty
    thisList->first = newNode;
    thisList->last = newNode;
    newNode->previous = NULL;
  }
  newNode->next = NULL;
  newNode->value = item; 
  thisList->length++;
}

void PrintList(_list* thisList, char* type){
  thisList->current = thisList->first;
  long int count = 0;
  if(thisList->first == NULL)
    printf("List is empty");
  while(thisList->current != NULL){
    printf("[%lu]: ", count);
    if(*type == *"i")
      printf("%d\n", *(int*)thisList->current->value);
    else if(*type == *"f")
      printf("%f\n", *(float*)thisList->current->value);
    else if(*type == *"c")
      printf("%c\n", *(char*)thisList->current->value);
    else printf("non-printable object\n");
    thisList->current = thisList->current->next;
    count++;
  }
}
