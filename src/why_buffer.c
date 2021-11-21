#include "why_buffer.h"
#include "why_string_view.h"

#include <unistd.h>

static void _buffer_init(Buffer* buffer, char* bytes, int_signed size)
{
    buffer->bytes = bytes;
    buffer->read_pointer = bytes;
    buffer->write_pointer = bytes;
    buffer->search_pointer = bytes;
    buffer->size = size;
}

Buffer* buffer_create()
{
    Buffer* buffer;
    char*   bytes;

    buffer = allocate(sizeof(Buffer));    
    bytes = memory_zero(BUFFER_DEFAULT_SIZE);
    _buffer_init(buffer, bytes, BUFFER_DEFAULT_SIZE);

    return buffer;
}

void buffer_destroy(Buffer* buffer)
{
    if (!buffer)
        return ;

    free(buffer->bytes);
    free(buffer);
}

int_signed buffer_count_written_bytes(Buffer* buffer)
{
    return buffer->write_pointer - buffer->bytes;
}

int_signed buffer_get_remaining_capacity(Buffer* buffer)
{
    return buffer->size - buffer_count_written_bytes(buffer);
}

int_signed buffer_count_unread_bytes(Buffer* buffer)
{
    return buffer->write_pointer - buffer->read_pointer;
}

int_signed buffer_count_read_bytes(Buffer* buffer)
{
    return buffer->read_pointer - buffer->bytes;
}

int_signed buffer_count_unsearched_bytes(Buffer* buffer)
{
    return buffer->write_pointer - buffer->search_pointer;
}

static int_signed _reallocate_bytes(Buffer* buffer, int_signed extra_capacity)
{
    int_signed  new_size;
    int_signed  unread_bytes;
    int_signed  shift;
    char*       new_byte_array;

    new_size = MAX(buffer->size + extra_capacity, buffer->size * 2);
    new_byte_array = allocate(new_size);

    shift = buffer->search_pointer - buffer->read_pointer;
    unread_bytes = buffer_count_unread_bytes(buffer);
    memory_init(new_byte_array, buffer->read_pointer, unread_bytes);
    free(buffer->bytes);

    _buffer_init(buffer, new_byte_array, new_size);
    buffer->write_pointer = buffer->bytes + unread_bytes;
    buffer->search_pointer = buffer->bytes + shift;

    return SUCCESS;
}

int_signed buffer_write_into(Buffer* buffer, int_signed n_bytes, int f_descriptor)
{
    int_signed read_size;

    if (buffer_get_remaining_capacity(buffer) < n_bytes)
        _reallocate_bytes(buffer, n_bytes);

    read_size = read(f_descriptor, buffer->write_pointer, n_bytes);
    if (read_size <= 0)
        return read_size;

    buffer->write_pointer += read_size;

    return read_size;
}

int_signed buffer_write_all_bytes_into(Buffer* buffer, int f_descriptor)
{
    int_signed status;

    while (TRUE)
    {
        status = buffer_write_into(buffer, buffer->size, f_descriptor);
        if (status <= 0)
            break ;
    }
    
    return status;
}

String* buffer_read_from(Buffer* buffer, int_signed n_bytes)
{
    String*     string;
    int_signed  bytes_availible;

    bytes_availible = buffer_count_unread_bytes(buffer);
    if (!bytes_availible)
        return NULL;
        
    if (n_bytes > bytes_availible)
        n_bytes = bytes_availible;

    string = string_createFL(buffer->read_pointer, n_bytes);
    
    buffer->read_pointer += n_bytes;

    return string;
}

String* buffer_flush_all(Buffer* buffer)
{
    return buffer_read_from(buffer, buffer->size);
}

String* buffer_flush_sequence(Buffer* buffer, char terminator)
{
    int_signed  index;
    String*     string;

    index = buffer_search(buffer, terminator);
    if (index == NOT_FOUND)
        return NULL;
    
    string = buffer_read_from(buffer, index);
    buffer->read_pointer ++;

    return string;
}

static int_signed _process_index(Buffer* buffer, int_signed index)
{
    if (index == NOT_FOUND)
    {
        buffer->search_pointer = buffer->write_pointer;

        return NOT_FOUND;
    }
    else
    {
        buffer->search_pointer += index;
        index = buffer->search_pointer - buffer->read_pointer;
        buffer->search_pointer ++;

        return index;
    }
}

int_signed buffer_search(Buffer* buffer, char c)
{
    StringView  view;
    int_signed  length;
    int_signed  index;

    length = buffer_count_unsearched_bytes(buffer);
    if (length <= 0)
        return NOT_FOUND;
    
    string_view_initB(&view, buffer->search_pointer, length);
    index = string_view_index_of(&view, c);
    index = _process_index(buffer, index);

    return index;
}

int_signed buffer_search_string(Buffer* buffer, const char* literal)
{
    String*     string;
    int_signed  length;
    int_signed  index;

    length = buffer_count_unsearched_bytes(buffer);
    if (length <= 0)
        return NOT_FOUND;
    
    string = string_createFL(buffer->search_pointer, length);
    index = string_find_literal(string, literal);
    index = _process_index(buffer, index);
    string_destroy(string);

    return index;
}