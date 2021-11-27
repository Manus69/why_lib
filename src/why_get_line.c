#include "why_lib.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define READ_SIZE               (1 << 11)
#define NUMBER_OF_DESCRIPTORS   (1 << 10)

static void _destroy_buffers(Buffer** buffers)
{
    int_signed n;

    n = 0;
    while (n < NUMBER_OF_DESCRIPTORS)
    {
        buffer_destroy(buffers[n]);
        n ++;
    }
}

static Buffer* _get_buffer(int_signed index)
{
    static Buffer* buffers[NUMBER_OF_DESCRIPTORS];

    if (index < 0)
    {
        _destroy_buffers(buffers);
        return NULL;
    }

    if (index >= NUMBER_OF_DESCRIPTORS)
        return NULL;

    if (buffers[index] == NULL)
        buffers[index] = buffer_create();

    return buffers[index];
}

String* get_line(int file_descriptor)
{
    String* line;
    Buffer* buffer;
    int     status;
    
    buffer =  _get_buffer(file_descriptor);
    if (!buffer)
        return NULL;
    
    while (TRUE)
    {
        line = buffer_flush_sequence(buffer, '\n');
        if (line)
            return line;
        
        status = buffer_write_into(buffer, READ_SIZE, file_descriptor);
        if (status <= 0)
            return buffer_flush_all(buffer);
    }
}

String* get_all_lines(int file_descriptor)
{
    Buffer* buffer;
    String* string;

    buffer = buffer_create();

    buffer_write_all_bytes_into(buffer, file_descriptor);
    string = buffer_read_from(buffer, buffer_count_unread_bytes(buffer));
    buffer_destroy(buffer);

    return string;
}

Array* get_all_linesA(int file_descriptor)
{
    String* line;
    Array*  lines;

    lines = array_create(copy_shallow, string_destroy);
    
    while ((line = get_line(file_descriptor)))
        array_push(lines, line);

    return lines;
}

Array* get_all_linesAFN(const char* file_name)
{
    int     fd;
    Array*  array;

    fd = open(file_name, O_RDONLY | O_EXCL);
    if (fd < 0)
        return NULL;

    array = get_all_linesA(fd);
    close(fd);

    return array;
}