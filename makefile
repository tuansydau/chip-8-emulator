CFLAGS := $(shell sdl2-config --cflags)
LIBS := $(shell sdl2-config --libs)

sdl_test: main.cpp
	g++ main.cpp -o sdl_test $(CFLAGS) $(LIBS)
