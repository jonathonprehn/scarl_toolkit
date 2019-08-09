/*
This file is part of the SCARL toolkit.

SCARL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SCARL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SCARL.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef __SCARL_LINKED_LIST_H__
#define __SCARL_LINKED_LIST_H__

#include <stdlib.h>

struct link_list;

/*
	Can iterate through these lists by just 
	jumping to subsequent link_list->next nodes
*/
struct link_list {
	void *value;
	struct link_list *next;
};

struct link_list *create_empty_link_list();
struct link_list *create_link_list_with(void *first_item);
// this function takes a comparator function pointer that returns 0 if the two are equal
void *find_in_list(struct link_list *lst, void *val, int (*comparator_func)(void*, void*));
void add_to_list(struct link_list **lst, void *val); //pointer to pointer because it modifies list
void remove_from_list(struct link_list **lst, void *val, int (*comparator_func)(void*, void*)); //pointer to pointer because it modifies list
void delete_link_list_node(struct link_list *n);
int list_size(struct link_list *lst);

#endif //__SCARL_LINKED_LIST_H__