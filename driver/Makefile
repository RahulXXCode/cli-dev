drv_output_dir = ../output/driver
cli_output_dir = ../output/driver/cli

CC = gcc
CFLAGS = -Wall -O0

GCC = $(CC) $(CFLAGS)

objects = $(drv_output_dir)/driver.o $(cli_output_dir)/cli.o

test: $(objects)
	echo "building driver layer"

deb: CFLAGS += -g

deb:
	$(objects)
	echo "building driver layer"

$(drv_output_dir)/driver.o: driver.c include/driver.h
	mkdir -p $(drv_output_dir)
	$(GCC) -c driver.c -o $(drv_output_dir)/driver.o

$(cli_output_dir)/cli.o: cli/cli.c cli/cli.h
	mkdir -p $(cli_output_dir)
	$(GCC) -c cli/cli.c -o $(cli_output_dir)/cli.o

clean:
	echo "Cleaning driver layer"
	rm -rf $(drv_output_dir)/*
