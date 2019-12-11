CXXFILES := main.c test.c

CC := gcc
LIBS :=
LDFLAGS := -L.
DEFINES :=
INCLUDE := -I ./
CFLAGS :=
CXXFLAGS :=
TARGET := simplefork

all:
	$(CC) $(CXXFILES) $(INCLUDE) $(LDFLAGS)  $(LIBS) $(CXXFLAGS) -o $(TARGET)
clean:
	rm -rf *.o
	rm -rf $(TARGET)



