CC = g++
CFLAGS = -std=c++11 -I$(IDIR) -lpthread -lX11
EXECUTABLE = ../image
ODIR = obj
SDIR = ../src
IDIR =../include
#_DEPS = ImageProc.h Image.h CImg_wrapper.h Image_types.h CImg.h Image_math.h Image_math_types.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
DEPS = $(IDIR)/*.h
_OBJ = main.o ImageProc.o Image.o CImg_wrapper.o Image_math.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
.PHONY:	clean
clean :
	rm -f $(ODIR)/*.o $(EXECUTABLE)
