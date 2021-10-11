
#ifndef WHY_BUFFER_INTERFACE_H
#define WHY_BUFFER_INTERFACE_H

#include "why_string_interface.h"

typedef struct Buffer Buffer;

#ifdef __cplusplus
    extern "C" {
#endif

Buffer*     buffer_create();
void        buffer_destroy(Buffer* buffer);
int_signed  buffer_search(Buffer* buffer, char c);
int_signed  buffer_search_string(Buffer* buffer, const char* literal);
int_signed  buffer_write_into(Buffer* buffer, int_signed n_bytes, int f_descriptor);
int_signed  buffer_write_all_bytes_into(Buffer* buffer, int f_descriptor);
int_signed  buffer_count_unread_bytes(Buffer* buffer);
String*     buffer_read_from(Buffer* buffer, int_signed n_bytes);
String*     buffer_flush_all(Buffer* buffer);
String*     buffer_flush_sequence(Buffer* buffer, char terminator);

#ifdef __cplusplus
    }
#endif

#endif
