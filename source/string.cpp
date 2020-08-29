#include "why_string.h"

namespace why
{
    void String::reallocate_buffer(unsigned int increment)
    {
        this->buffer = (char *)reallocate_memory(this->buffer,
                        this->buffer_size, this->buffer_size + increment);
        this->buffer_size += increment;
    }

    void String::write_to_buffer(const char *string, unsigned int index, unsigned int number_of_bytes)
    {
        char *location_pointer;

        location_pointer = this->buffer + index;
        reproduce_memory(location_pointer, string, number_of_bytes);
    }

    String::String(const char *string)
    {
        unsigned int length;
        unsigned int buffer_size;

        length = get_cstring_length(string);
        buffer_size = length + 1;
        this->buffer = (char *)copy_memory(string, buffer_size);
        this->length = length;
        this->buffer_size = buffer_size;
    }

    String::String(char *string, unsigned int length)
    {
        this->length = length;
        this->buffer_size = length + 1;
        this->buffer = string;
    }

    String::String(unsigned int buffer_size)
    {
        this->length = 0;
        this->buffer_size = buffer_size ? buffer_size : 1;
        this->buffer = (char *)get_n_zero_bytes(this->buffer_size);
    }

    String::String(const String &string) //this is bullshit
    {
        this->length = string.length;
        this->buffer_size = string.buffer_size;
        this->buffer = (char *)copy_memory(string.buffer, string.buffer_size);
    }

    String String::operator=(const String &string)
    {
        this->length = string.length;
        this->buffer_size = string.buffer_size;
        free(this->buffer);
        this->buffer = (char *)copy_memory(string.buffer, string.buffer_size);

        return string;
    }

    void String::print(char space) const
    {
        // std::printf("%s", this->buffer);
        write(STDOUT_FILENO, this->buffer, this->length);
        if (space)
            write(STDOUT_FILENO, &space, 1);
    }

    void String::inject_substring(const String &substring, unsigned int index, unsigned int length)
    {
        unsigned int number_of_bytes;
        unsigned int remaining_capacity;

        if (index > this->buffer_size - 1)
            return ;
        if (length > substring.length)
            length = substring.length;
        remaining_capacity = this->get_remainig_capacity();
        if (remaining_capacity >= length)
            number_of_bytes = length;
        else
            number_of_bytes = remaining_capacity;
        write_to_buffer(substring.buffer, index, number_of_bytes);
    }

    String String::get_substring(unsigned int index, unsigned int length)
    {
        char *source_pointer;
        char *substring;

        if (index >= this->buffer_size - 1)
            return String();
        if (index + length > this->length)
            length = this->length - index;
        source_pointer = this->buffer + index;
        substring = (char *)copy_memory(source_pointer, length + 1);
        substring[length] = 0;
        
        return String(substring, length);  
    }

    String String::append(const char *string, unsigned int length)
    {
        unsigned int capacity;

        if (!length)
            length = get_cstring_length(string);
        capacity = this->get_remainig_capacity();
        if (length > capacity)
        {
            if (length + this->length < this->buffer_size * 2)
                this->reallocate_buffer(this->buffer_size);
            else
                this->reallocate_buffer(length);
        }
        write_to_buffer(string, this->length, length);
        this->length += length;

        return *this;
    }

    String String::reverse(void)
    {
        unsigned int left_index;
        unsigned int right_index;

        if (this->length < 2)
            return *this;
        left_index = 0;
        right_index = this->length - 1;
        while (left_index < right_index)
        {
            swap(this->buffer[left_index], this->buffer[right_index]);
            left_index ++;
            right_index --;
        }

        return *this;
    }

    String concatenate(const String &lhs, const String &rhs, char joint)
    {
        unsigned int lhs_length;
        unsigned int rhs_length;
        unsigned int total_length;

        lhs_length = lhs.get_length();
        rhs_length = rhs.get_length();
        total_length = joint ? lhs_length + rhs_length + 1 : lhs_length + rhs_length;
        String result = String(total_length + 1);
        result.inject_substring(lhs, 0, lhs_length);
        if (joint)
        {
            result[lhs_length] = joint;
            result.inject_substring(rhs, lhs_length + 1, rhs_length);
        }
        else
            result.inject_substring(rhs, lhs_length, rhs_length);
        result.length = total_length;
        result[result.length] = 0;

        return result;
    }
    
}