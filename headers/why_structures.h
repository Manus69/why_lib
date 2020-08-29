#ifndef WHY_STRUCTURES_H
#define WHY_STRUCTURES_H

#include "why_memory.h"
#include <iostream>

namespace why
{
    template <class type>
    class Stack
    {
        unsigned int capacity;
        unsigned int current_index;
        type *array;

        unsigned int inline get_remaining_capacity(void) const {return capacity - current_index;}
        void increase_capacity(void)
        {
            array = (type *)reallocate_memory(array,
                            current_index * sizeof(type), capacity * 2 * sizeof(type));
            capacity += capacity;
        }
        
        public:
            
            Stack(unsigned int capacity)
            {
                this->capacity = capacity;
                this->current_index = 0;
                this->array = (type *)std::malloc(sizeof(type) * capacity);
            }

            void push(type item)
            {
                if (!get_remaining_capacity())
                    increase_capacity();
                array[current_index] = item;
                current_index ++;
            }

            type pop(void)
            {
                return array[current_index --];
            }

            void display(void)
            {
                unsigned int n;

                n = 0;
                while (n < current_index)
                {
                    std::cout << array[n];
                    std::cout << ' ';
                    n ++;
                }
            }
    };
}

#endif