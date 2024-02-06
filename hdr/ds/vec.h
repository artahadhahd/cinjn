#ifndef HDR_DS_VEC_H
#define HDR_DS_VEC_H

#define _CREATE_VECTOR_STRUCTS(dimensions, T)\
struct vec##dimensions##T {T indices[dimensions];};

#define _CREATE_CONSTRUCTOR_V(dimension, T)\
struct vec##dimensions##T vec##dimensions##T_new()

#define CREATE_VECTOR(dimensions, T)\
    _CREATE_VECTOR_STRUCTS(dimension, T)\
    _CREATE_CONSTRUCTOR_V(dimension, T)

#endif