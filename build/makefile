CC = g++
CFLAGS = -std=c++11 -I$(IDIR) -lpthread -lX11
EXECUTABLE = ../image
ODIR = obj
SDIR = ../src
IDIR =../include
_DEPS = Image.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ = main.o Image.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
.PHONY:	clean
clean :
	rm -f $(ODIR)/*.o $(EXECUTABLE)
