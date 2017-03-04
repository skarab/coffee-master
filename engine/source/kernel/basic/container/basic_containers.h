//------------------------------------------------------------------------------------------------//
//
// Note that all these containers are serializable and changes safe.
// Here is the containers usage:
//
//  coffee::basic::Array       used for scalars/structs array
//  coffee::basic::Vector      used for objects array
//  coffee::basic::Prow        used for pointers array, can own the ptr (auto. del.)
//  coffee::basic::Rope        block managed, used for big scalar/pointer/structs array
//  coffee::basic::List        double linked list, allowing fast insertion
//
//------------------------------------------------------------------------------------------------//
#ifndef _COFFEE_BASIC_CONTAINERS_H_
#define _COFFEE_BASIC_CONTAINERS_H_

#include "kernel/basic/container/basic_container.h"
#include "kernel/basic/container/array/basic_array.h"
#include "kernel/basic/container/vector/basic_vector.h"
#include "kernel/basic/container/prow/basic_prow.h"
#include "kernel/basic/container/rope/basic_rope.h"
#include "kernel/basic/container/list/basic_list.h"

#endif
