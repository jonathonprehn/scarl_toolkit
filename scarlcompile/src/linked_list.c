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

#include <stdio.h>

#include "linked_list.h"

struct link_list *create_empty_link_list() {
	struct link_list *empty_list = (struct link_list*)malloc(sizeof(struct link_list));
	empty_list->value = NULL;
	empty_list->next = NULL;
	return empty_list;
}

struct link_list *create_link_list_with(void *first_item) {
	if (first_item != NULL) {
		struct link_list *the_list = create_empty_link_list();
		the_list->value = first_item;
		return the_list;
	}
	else {
		return NULL; // cannot have the value be NULL for a link_list node
	}
}

void *find_in_list(struct link_list *lst, void *val, int (*comparator_func)(void*, void*)) {
	struct link_list *n = lst;
	while(n->value != NULL && comparator_func(lst->value, val) != 0) {
		n = n->next;
	}
	if (n->value != NULL) {
		return n->value;
	}
	else {
		return NULL; //redundant, but being explicit about not finding anything
	}
}

void add_to_list(struct link_list **lst, void *val) {
	if (val == NULL) {
		return; // no value-less lists
	}
	struct link_list *n = *lst;
	if (n == NULL) {
		*lst = create_link_list_with(val);
	}
	else {
		while(n->next != NULL) {
			n = n->next;
		}
		// add a new node to this list
		struct link_list *new_node = create_link_list_with(val);
		n->next = new_node;
	}
}

void remove_from_list(struct link_list **lst, void *val, int (*comparator_func)(void*, void*)) {
	if (val == NULL) {
		return; //doesn't make sense to try and remove NULL
	}
	struct link_list *n = *lst;
	struct link_list *prev = NULL;
	while(n != NULL && comparator_func(n->value, val) != 0) {
		prev = n;
		n = n->next;
	}
	if (n != NULL) {
		// remove this node from the linked list 
		if (prev == NULL) {
			// it was the first one
			*lst = n->next;
		}
		else {
			prev->next = n->next;
		}
		delete_link_list_node(n);
	}
	else {
		// this value was not in the list, do nothing
	}
}

void delete_link_list_node(struct link_list *n) {
	free(n->value);
	free(n);
}

int list_size(struct link_list *lst) {
	int size = 0;
	struct link_list *n = lst;
	while (n != NULL) {
		n = n->next;
		size++;
	}
	return size;
}
