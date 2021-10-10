lib = libWHY.a
lib_header = why_lib.h
driver_name = test

cc = gcc
flags = -Wall -Wextra -g
release_flags = -Wall -Wextra -O3

source_folder = src/
obj_folder = obj/
include_folder = src/

headers = $(wildcard $(source_folder)*.h)
source = $(wildcard $(source_folder)*.c)
objects = $(subst $(source_folder),$(obj_folder),$(source:.c=.o))
driver = test.c

.PHONY: directory

# all: directory $(lib)
all: directory $(driver_name)

directory:
	@mkdir -p $(obj_folder)

release: flags = $(release_flags)
release: fclean all

test_release: flags = $(release_flags)
test_release: fclean all $(driver_name)
 
$(obj_folder)%.o : $(source_folder)%.c $(headers) $(lib_header)
	$(cc) $(flags) $< -I $(include_folder) -I. -c -o $@

$(driver_name): $(driver) $(lib)
	$(cc) $(flags) $< -I $(include_folder) -I. -c -o $(obj_folder)$(driver:.c=.o)
	# $(cc) $(flags) $(obj_folder)$(driver:.c=.o) -o $(driver_name) $(lib)
	$(cc) $(flags) $(objects) $(obj_folder)$(driver:.c=.o) -o $(driver_name)

$(lib): $(objects)
	ar rcs $(lib) $(objects)

clean:
	rm -f $(objects) $(driver:.c=.o)

fclean: clean
	rm -f $(driver:.c=.o) $(lib)

re: fclean all

