all:	disp

clean:
	rm disp

disp: disp.cc
	`root-config --cxx` `root-config --cflags --libs` -L. $^ -o disp
