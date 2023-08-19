#include <stdio.h>
#include <wchar.h>

#include "../inc/ui_ux.h"
#include "../inc/macros.h"
#include "../libs/linked_list/linked_list.h"
 
/*used for initiating program threads*/
int main(){
  _list* test = NewList();
  for (int x = 0; x < 100; x++){
    int* newInt = (int*)malloc(sizeof(int));
    *newInt = x;
    AppendToList(test, (void*)newInt);
  }
  //PrintList(test, "i");
  DeleteListIndex(test, test->length-1);
  PrintList(test, "i");
  printf("%d", test->length);
  ClearList(test);
  printf("%d", test->length);
  PrintList(test, "i");
  LOOP(10, 20);
  return 0;
}
