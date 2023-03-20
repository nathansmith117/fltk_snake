FLCON = fltk-config
COMPILER = $(shell $(FLCON) --cxx)
CFLAGS = $(shell $(FLCON) --use-images --cxxflags)
LDFLAGS = $(shell $(FLCON) --use-images --ldstaticflags) \
	  -static-libstdc++ -static-libgcc

TARGET = ../fltk_snake
DEH = program_data.h
OBJS = main.o app_window.o snake_map.o top_menu.o snake_utils.o

%.o: %.cpp
	@echo compiling $<
	@$(COMPILER) $(CFLAGS) -c -o $@ $<
$(TARGET): $(OBJS)
	@echo making exe
	@$(COMPILER) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
debug:
	$(COMPILER) $(CFLAGS) -c *.cpp -g
	$(COMPILER) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS) -g

# Objects.
main.o: *.cpp *.h
app_window.o: app_window.cpp app_window.h snake_map.cpp snake_map.h $(DEH)
snake_map.o: snake_map.cpp snake_map.h snake_utils.cpp snake_utils.h $(DEH)
top_menu.o: top_menu.cpp top_menu.h snake_map.cpp snake_map.h $(DEH)
snake_utils.o: snake_utils.cpp snake_utils.h $(DEH)

clean:
	rm *.o
	rm $(TARGET)
