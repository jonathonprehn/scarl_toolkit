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

#include "scarltypes.h"


/* Is the right hand side a descendent of the left hand side? */
int is_descendant_of(struct scarl_class_type *lhs, struct scarl_class_type *rhs) {
	return 0;
}

/* Is the right hand side a direct descendent (immediate child) of the left hand side? */
int is_direct_descendant_of(struct scarl_class_type *lhs, struct scarl_class_type *rhs) {
	return 0;
}

/* Is the right hand side an ancestor of the left hand side? */
int is_ancestor_of(struct scarl_class_type *lhs, struct scarl_class_type *rhs) {
	return 0;
}