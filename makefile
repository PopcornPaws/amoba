###################### MAKEFILE for C practice codes #####################
# Includes all necessary .h and .c files from a separate 'src' directory #
# Output file is generated inside a separate 'build' directory			 #
# 'run' option is added to run the compiled output file instantaneously	 #
##########################################################################

# Define project name (file to compile)
PROJECT = main
# Define 'header', 'object', and 'build' directories
SRCDIR = src
OBJDIR = obj
OUTDIR = build
# Dependencies (header and c files)
HDEPS := $(shell find $(SRCDIR) -name '*.h')
$(info $$HDEPS is [${HDEPS}])
CDEPS := $(notdir $(shell find $(SRCDIR) -name '*.c'))
$(info $$CDEPS is [${CDEPS}])
# Object files
OBJS = $(subst .c,.o,$(CDEPS))
OBJFILES = $(addprefix $(OBJDIR)/,$(OBJS))
$(info $$OBJFILES is [${OBJFILES}])
# Define compiler
CC = gcc
# Define compilation flags (e.g. where g++ should look for header files)
CFLAGS = -I $(SRCDIR) -lncurses

# Run the output in terminal
run : $(OUTDIR)/$(PROJECT)
	$^

# Generate executable from object files
$(info ${OBJDIR}/${OBJFILES})

$(OUTDIR)/$(PROJECT) : $(OBJFILES) $(OBJDIR)/$(PROJECT).o | $(OUTDIR)
	$(CC) -o $@ $^ $(CFLAGS)

# Generate object files 
$(OBJDIR)/%.o : $(SRCDIR)/%.c $(HDEPS) | $(OBJDIR) # substitute src to obj
	$(CC) -o $@ -c $< $(CFLAGS) 

# Generate main.o separately
$(OBJDIR)/$(PROJECT).o : $(PROJECT).c $(HDEPS) | $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS)

# MAKE directories
$(OBJDIR) :
	mkdir -p $(OBJDIR)
$(OUTDIR) :
	mkdir -p $(OUTDIR)

# PHONY clean rule
.PHONY : clean

clean : 
	rm -rf $(OUTDIR)
	rm -rf $(OBJDIR)
