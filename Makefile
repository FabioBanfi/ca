EXE 	= ca
CC 		= g++

IFLAGS 	= -Iinclude
CFLAGS 	= -Wall -Wextra -Wno-unused-parameter -std=c++11 -O3
DFLAGS  = -g -DDEBUG -O0
LFLAGS  = -lSDL2 -lboost_program_options

SRCDIR 	= src
TESTDIR = test
OBJDIR 	= obj
BINDIR 	= bin

SRCS 	= $(shell find $(SRCDIR) -name '*.cpp')
TESTS	= $(shell find $(TESTDIR) -name '*.cpp')
OBJS 	= $(subst $(SRCDIR)/,,$(SRCS:.cpp=.o)) $(subst $(TESTDIR)/,,$(TESTS:.cpp=.o))

MKDIR   = mkdir -p

all: directories $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJDIR)/*.o -o$(BINDIR)/$(EXE)

%.o: $(TESTDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o$(OBJDIR)/$@

%.o: $(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o$(OBJDIR)/$@

debug:
	@$(MAKE) CFLAGS="$(CFLAGS) $(DFLAGS)"

directories: ${BINDIR} ${OBJDIR}

${BINDIR}:
	${MKDIR} ${BINDIR}

${OBJDIR}:
	${MKDIR} ${OBJDIR}

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all debug directories clean