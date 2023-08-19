#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
  void* value;
  struct _node* next;
  struct _node* previous;
}_node;

typedef struct _list{
  _node* first;
  _node* last;
  _node* current;
  int length;
}_list;

void AppendToList(_list*, void*);
void* GetListIndexPointer(_list*, long int);
void* GetListIndexValuePointer(_list*, long int);
void PrintList(_list*, char*);
void DeleteNodePointer(_list*, _node*);
void DeleteListIndex(_list*, long int);
void ClearList(_list*);
_list* NewList();
