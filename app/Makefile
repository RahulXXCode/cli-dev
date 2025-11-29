
output_dir = ../output/app

#executable: $(objects)
#	gcc $(objects) -o executable

test: $(output_dir)/main.o

$(output_dir)/main.o: include/app.h main.c
	mkdir -p $(output_dir)
	gcc -c main.c -o $(output_dir)/main.o

clean:
	rm -f $(output_dir)/main.o
