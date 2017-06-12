CC = g++
CFLAGS = -std=c++11 -I$(IDIR) -lpthread -lX11
EXECUTABLE = ../image
ODIR = obj
SDIR = ../src
IDIR =../include
_DEPS = ImageProc.h Image.h CImg_wrapper.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ = main.o ImageProc.o Image.o CImg_wrapper.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
.PHONY:	clean
clean :
	rm -f $(ODIR)/*.o $(EXECUTABLE)
