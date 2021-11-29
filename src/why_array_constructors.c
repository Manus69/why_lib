#include "why_lib.h"
#include "why_array.h"
#include "why_math_complex.h"
#include "why_math_rational.h"

void* _get_array(int_signed size, int_signed item_size)
{
    return allocate(size * item_size);
}

void* array_pointer_at(const Array* array, int_signed n)
{
    return ((void **)array->data)[n];
}

void array_pointer_set(Array* array, const void* item, int_signed n)
{
    ((void **)array->data)[n] = (void *)item;
}

void array_pointer_swap(Array* array, int_signed n, int_signed m)
{
    MEM_SWAP(array->data, n, m, void *);
}

void* array_value_at(const Array* array, int_signed n)
{
    return MEM_GET(array->data, n, array->item_size);
}

void array_value_set(Array* array, const void* value, int_signed n)
{
    MEM_SET(array->data, n, value, void *);
}

void array_value_swap(Array* array, int_signed n, int_signed m)
{
    MEM_SWAP(array->data, n, m, void *);   
}

void* array_byte_at(const Array* array, int_signed n)
{
    return (void *)&((byte *)array->data)[n];
}

void array_byte_set(Array* array, const void* value, int_signed n)
{
    MEM_SET(array->data, n, value, byte);
}

void array_byte_swap(Array* array, int_signed m, int_signed n)
{
    MEM_SWAP(array->data, m, n, byte);
}

void* array_int_at(const Array* array, int_signed n)
{
    return (void *)&((int_signed *)array->data)[n];
}

void array_int_set(Array* array, const void* value, int_signed n)
{
    MEM_SET(array->data, n, value, int_signed);
}

void array_int_swap(Array* array, int_signed m, int_signed n)
{
    MEM_SWAP(array->data, m, n, int_signed);
}

void array_real_set(Array* array, const void* value, int_signed n)
{
    MEM_SET(array->data, n, value, real);
}

void array_real_swap(Array* array, int_signed m, int_signed n)
{
    MEM_SWAP(array->data, m, n, real);
}

void array_complex_set(Array* array, const void* value, int_signed n)
{
    MEM_SET(array->data, n, value, Complex);
}

void array_complex_swap(Array* array, int_signed m, int_signed n)
{
    MEM_SWAP(array->data, m, n, Complex);
    // SWAP(((Complex *)array->data)[m], ((Complex *)array->data)[n], Complex);
}

void* array_rational_at(const Array* array, int_signed n)
{
    return (void *)&((Rational *)array->data)[n];
}

void array_rational_set(Array* array, const void* value, int_signed n)
{
    MEM_SET(array->data, n, value, Rational);
}

void array_rational_swap(Array* array, int_signed m, int_signed n)
{
    MEM_SWAP(array->data, m, n, Rational);
}

static Array* _create(void* (*at)(), void (*set)(), void (*swap)(), void* (*copy)(),
                        void (*destroy)(), int_signed capacity, int_signed item_size)
{
    Array* array;

    array = allocate(sizeof(Array));

    capacity = capacity == 0 ? A_CAPACITY_DEFAULT : capacity;
    capacity = capacity < A_CAPACITY_MIN ? A_CAPACITY_MIN : capacity;

    array->data = _get_array(capacity, item_size);
    array->at = at;
    array->set = set;
    array->swap = swap;
    array->copy = copy;
    array->destroy = destroy;
    array->compare = NULL;

    array->item_size = item_size;
    array->capacity = capacity;
    array->left_index = capacity / 2;
    array->right_index = array->left_index + 1;

    return array;
}

Array* array_create_with_capacity(void* (copy)(), void (*destroy)(), int_signed capacity)
{
    return _create(array_pointer_at, array_pointer_set, array_pointer_swap,
                    copy, destroy, capacity, sizeof(void *));
}

Array* array_create(void* (*copy)(), void (*destroy)())
{
    return array_create_with_capacity(copy, destroy, A_CAPACITY_DEFAULT);
}

Array* array_createVAL(int_signed capacity, int_signed item_size)
{
    return _create(array_value_at, array_value_set, array_value_swap, 
                    copy_shallow, destroy_shallow, capacity, item_size);
}

Array* array_createINT(int_signed capacity)
{
    return _create(array_value_at, array_int_set, array_int_swap, 
                    copy_shallow, destroy_shallow, capacity, sizeof(int_signed));
}

Array* array_createBYTE(int_signed capacity)
{
    return _create(array_value_at, array_byte_set, array_byte_swap, 
                    copy_shallow, destroy_shallow, capacity, sizeof(byte));
}

Array* array_createREAL(int_signed capacity)
{
    return _create(array_value_at, array_real_set, array_real_swap, 
                    copy_shallow, destroy_shallow, capacity, sizeof(real));
}

Array* array_createCPLX(int_signed capacity)
{
    return _create(array_value_at, array_complex_set, array_complex_swap, 
                    copy_shallow, destroy_shallow, capacity, sizeof(Complex));
}

Array* array_createRAT(int_signed capacity)
{
    return _create(array_value_at, array_rational_set, array_rational_swap, 
                    copy_shallow, destroy_shallow, capacity, sizeof(Rational));
}

static void _destroy_items(Array* array)
{
    if (!array)
        return ;
    
    array_map(array, array->destroy);
}

void array_destroy(Array* array)
{
    if (!array)
        return ;
    
    if (array->destroy != destroy_shallow)
        _destroy_items(array);
    
    free(array->data);
    free(array);
}

void array_destroy_no_content(Array* array)
{
    if (!array)
        return ;
    
    free(array->data);
    free(array);
}