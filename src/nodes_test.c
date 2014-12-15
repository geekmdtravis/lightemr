// file: main.cp
// TODO: Work on case '1', looking up a patient from a database.

#include <string.h>
#include "interface.h"
#include "patient.h" 
#include "database.h"
#include "modstring.h"
#include "login.h"

#define MIN_NODE 1
#define MAX_NODE 50000

int main()
{
  PQ_node *p_head = PQ_node_alloc();
  PQ_node *p_selected, *p_tmp;
  int i;
  int selection = 2;
  
  for(i = MIN_NODE; i <= MAX_NODE - 1; i++) PQ_node_add(p_head);

  for(p_tmp = p_head; p_tmp->next; p_tmp = p_tmp->next) {
    if(p_tmp->count == selection) {
      p_selected = p_tmp;
    }
  }
  if(p_tmp->count == selection) p_selected = p_tmp;

  p_selected = PQ_list_node_extract(p_selected);
  PQ_list_purge(p_head);

  PQ_node_destroy(p_selected);
  
  exit(EXIT_SUCCESS);
}
