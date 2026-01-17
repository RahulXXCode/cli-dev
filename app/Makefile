
output_dir = ../output/app

#executable: $(objects)
#	gcc $(objects) -o executable

test: $(output_dir)/app.o

$(output_dir)/app.o: $(output_dir)/main.o $(output_dir)/logger.o

$(output_dir)/main.o: include/app.h main.c
	mkdir -p $(output_dir)
	gcc -c main.c -o $(output_dir)/main.o

$(output_dir)/logger.o: include/app.h logger.c
	mkdir -p $(output_dir)
	gcc -c logger.c -o $(output_dir)/logger.o

clean:
	rm -f $(output_dir)/app.o
	rm -f $(output_dir)/main.o
	rm -f $(output_dir)/logger.o
