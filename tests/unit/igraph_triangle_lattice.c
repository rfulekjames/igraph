/*
   IGraph library.
   Copyright (C) 2021  The igraph development team <igraph@igraph.org>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <igraph.h>
#include "test_utilities.h"

int main(void) {
    igraph_t graph;
    igraph_vector_int_t dimvector;

    /* triangular triangle lattice with a single vertex and no edges*/
    igraph_vector_int_init(&dimvector, 1);
    VECTOR(dimvector)[0] = 1;

    igraph_triangle_lattice(&graph, &dimvector, true, false);
    igraph_integer_t number_of_edges = igraph_vector_int_size(&graph.from);
    IGRAPH_ASSERT(number_of_edges == 0);

    igraph_destroy(&graph);

    /* triangular triangle lattice */
    igraph_vector_int_init(&dimvector, 1);
    VECTOR(dimvector)[0] = 5;

    igraph_triangle_lattice(&graph, &dimvector, true, false);
    number_of_edges = igraph_vector_int_size(&graph.from);
    IGRAPH_ASSERT(number_of_edges == 30);

    igraph_destroy(&graph);

    /* rectangular triangle lattice */
    igraph_vector_int_init(&dimvector, 2);
    VECTOR(dimvector)[0] = 4;
    VECTOR(dimvector)[1] = 5;

    igraph_triangle_lattice(&graph, &dimvector, true, true);
    number_of_edges = igraph_vector_int_size(&graph.from);
    IGRAPH_ASSERT(number_of_edges == 86);

    igraph_destroy(&graph);

    /* hexagonal triangle lattice */
    igraph_vector_int_init(&dimvector, 3);
    VECTOR(dimvector)[0] = 3;
    VECTOR(dimvector)[1] = 4;
    VECTOR(dimvector)[2] = 5;

    igraph_triangle_lattice(&graph, &dimvector, false, true);
    number_of_edges = igraph_vector_int_size(&graph.from);
    IGRAPH_ASSERT(number_of_edges == 87);

    igraph_vector_int_destroy(&dimvector);

    /*Erroneous calls*/
    igraph_set_error_handler(igraph_error_handler_ignore);
    IGRAPH_ASSERT(igraph_triangle_lattice(&graph, &dimvector, true, true) == IGRAPH_EINVAL);

    igraph_vector_int_init(&dimvector, 1);
    VECTOR(dimvector)[0] = -3;
    IGRAPH_ASSERT(igraph_triangle_lattice(&graph, &dimvector, true, true) == IGRAPH_EINVAL);

    igraph_destroy(&graph);
    igraph_vector_int_destroy(&dimvector);

    VERIFY_FINALLY_STACK();
    return 0;
}
