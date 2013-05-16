CC = g++ -g
RM = rm -rf

LIBS = -lglut -lGL -lGLU -lm -lpthread `pkg-config opencv --libs`
INCLUDES = `pkg-config opencv --cflags`

TARGET = main
all: $(TARGET)

.cpp.o:
	$(CC) -c $< $(INCLUDES)
	
$(TARGET): %: %.o
	$(CC) -o $@ $^ $(LIBS)
	
clean:
	$(RM) *.o $(TARGET) *~ *#*
	
	
