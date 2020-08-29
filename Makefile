source_folder = ./source
object_folder = ./objects
header_folder = ./headers

source = $(wildcard $(source_folder)/*.cpp)
objects = $(subst .cpp,.o,$(subst $(source_folder),$(object_folder),$(source)))
headers = $(wildcard $(header_folder)/.h)
driver = main.cpp
driver_object = $(subst .cpp,.o,$(driver))
run_file = run
lib_name = libwhy.a

flags = -g -Wall -Wextra
compiler = g++

all: run

$(object_folder)/%.o : $(source_folder)/%.cpp $(headers)
	$(compiler) $(flags) -I$(header_folder) $< -c -o $@

run: $(objects) $(headers) $(driver)
	$(compiler) $(flags) $(objects) $(driver) -I$(header_folder) -o $(run_file)

clean:
	rm -f *.o
	rm -f $(objects)

re:
	rm -f $(run_file)
	make clean
	make all

test:
	echo $(objects)