TARGET   = rpiLcd
CC       = g++
CFLAGS   = -Wall
LIBS     = -lbcm2835

OBJDIR = obj
BINDIR = bin

SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@

$(BINDIR)/$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

.PHONY : clean

clean:
	rm $(BINDIR)/$(TARGET) $(OBJS)
	@echo "Object files are $(TARGET) $(OBJS)"