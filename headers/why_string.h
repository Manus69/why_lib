#ifndef WHY_STRING_H
#define WHY_STRING_H

#include "why_memory.h"
#ifdef __unix
#include <unistd.h>
#endif

#define DIGITS "0123456789abcdef"

namespace why
{
    class String
    {
        private:
            unsigned int length;
            unsigned int buffer_size;
            char *buffer;
            
            void reallocate_buffer(unsigned int increment);
            void write_to_buffer(const char *string, unsigned int index, unsigned int number_of_bytes);

        public:
            String(const char *string = "");
            String(char *string, unsigned int length);
            String(unsigned int buffer_size);
            String(const String &string);
            inline ~String(void) {free(buffer);};

            String operator= (const String &string);
            String inline append(const String &string) {return append(string.buffer, string.length);}
            String inline append(const char c) {return append(&c, 1);}
            String append(const char *string, unsigned int length = 0);
            String reverse(void);
            String get_substring(unsigned int index, unsigned int length);
            void inject_substring(const String &substring, unsigned int index, unsigned int length);

            inline char& operator[] (unsigned int index) {return buffer[index];}
            inline unsigned int get_length(void) const {return length;}
            inline unsigned int get_buffer_size(void) const {return buffer_size;}
            inline unsigned int get_remainig_capacity(void) const {return buffer_size - length - 1;}
            inline char *get_buffer(void) const {return buffer;}

            void print(char space = '\n') const; //this is a problem
            friend String concatenate(const String &lhs, const String &rhs, char joint);

    };

    String concatenate(const String &lhs, const String &rhs, char joint = 0);
    unsigned int get_cstring_length(const char *string);
}

#endif