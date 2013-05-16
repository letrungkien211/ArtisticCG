CC = g++ -g
RM = rm -rf

LIBS = -lglut -lGL -lGLU -lm -lpthread `pkg-config opencv --libs`
INCLUDES = `pkg-config opencv --cflags` -I/usr/include/eigen3/

TARGET = main
OBJ = particle.o
all: $(TARGET)

.cpp.o:
	$(CC) -c $< $(INCLUDES)
$(TARGET): %: %.o $(OBJ)
	$(CC) -o $@ $^ $(LIBS)
clean:
	$(RM) *.o $(TARGET) *~ *#*