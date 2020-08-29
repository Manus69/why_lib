#ifndef WHY_STACK_H
#define WHY_STACK_H

#include "why_memory.h"

namespace why
{
    class Stack
    {
        unsigned int current_index;
        unsigned int capacity;
        void **array;
        bool acquired_resources;

        void increase_capacity(unsigned int increment);
        // void free_objects(void (*free_function)(void *));

        public:
            Stack(unsigned int capacity);
            // ~Stack(void);
            void destroy(void (*free_function)(void *) = NULL);
            void push(void *stuff, unsigned int size = 0,
                        void *(*copy_function)(const void *, unsigned int) = NULL);
            void *pop(void);

            void display(const char type) const;
            void display(void (*print_item)(void *)) const;

            inline unsigned int get_remaining_capacity(void) const {return capacity - current_index;}
    };
}

#endif