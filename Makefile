exe_output_dir = output
app_output_dir = output/app
drv_output_dir = output/driver
cli_output_dir = output/driver/cli

objects = $(app_output_dir)/main.o $(drv_output_dir)/driver.o $(cli_output_dir)/cli.o

executable = demo_app

test:
	$(MAKE) -C app
	$(MAKE) -C driver
	gcc $(objects) -o $(exe_output_dir)/$(executable)

clean:
	$(MAKE) -C app clean
	$(MAKE) -C driver clean
	rm -f $(exe_output_dir)/$(executable)
