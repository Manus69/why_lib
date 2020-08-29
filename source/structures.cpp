
#include "why_stack.h"

namespace why
{
    void Stack::increase_capacity(unsigned int increment)
    {
        unsigned int new_capacity;

        new_capacity = (this->capacity + increment) * sizeof(void *);
        this->array = (void **)reallocate_memory(this->array, 
                        this->current_index * sizeof(void *), new_capacity);
        this->capacity = new_capacity;
    }

    Stack::Stack(unsigned int capacity)
    {
        this->capacity = capacity;
        this->current_index = 0;
        this->acquired_resources = false;
        this->array = (void **)std::malloc(sizeof(void *) * capacity);
    }

    void Stack::destroy(void (*free_function)(void *))
    {
        unsigned int n;

        if (free_function)
        {
            n = 0;
            while (n < this->current_index)
            {
                free_function(this->array[n]);
                n ++;
            }
        }
        free(this->array);
    }

    void Stack::push(void *stuff, unsigned int size, void *(*copy_function)(const void *, unsigned int))
    {
        if (!this->get_remaining_capacity())
            this->increase_capacity(this->capacity);
        if (!copy_function)
            this->array[this->current_index] = stuff;
        else
        {
            this->array[this->current_index] = copy_function(stuff, size);
            this->acquired_resources = true;
        }
        this->current_index ++;
    }

    void *Stack::pop(void)
    {
        void *item;

        if (!this->current_index)
            return NULL;
        item = this->array[this->current_index];
        this->current_index --;

        return item;
    }

    void print_thing(void *thing, char type, char space = ' ');

    void Stack::display(const char type) const
    {
        unsigned int n;

        n = 0;
        while (n < this->current_index)
        {
            print_thing(this->array[n], type);
            n ++;
        }
    }
}