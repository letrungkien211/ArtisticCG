CC = g++ -g
RM = rm -rf

LIBS = -lglut -lGL -lGLU -lm -lpthread 

TARGET = GLTeapot
all: $(TARGET)

.cpp.o:
	$(CC) -c $< $(LIBS)

$(TARGET): %: %.o
	$(CC) -o $@ $^ $(LIBS)

clean:
	$(RM) *.o $(TARGET) *~ *#*