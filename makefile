
############################################################
# All targets
############################################################

TARGETS := sort_array

############################################################
# Common build rules
############################################################
OBJDIR := ./obj
OUTPUTDIR := ./output
SOURCEDIR := ./source

COMPILEFLAGS := -g -Wall
#COMPILEFLAGS += -ffunction-sections
#LINKERFLAGS := -Wl,-Map=$(OUTPUTDIR)/out.map
#LINKERFLAGS += -Wl,--print-map>$(OUTPUTDIR)/outmap.txt
#LINKERFLAGS += -Wl,--cref
#LINKERFLAGS += -Wl,--gc-sections


$(TARGETS): | $(OUTPUTDIR)

$(OUTPUTDIR):
	mkdir $(OUTPUTDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OUTPUTDIR)
	rm -rf $(OBJDIR)

############################################################

SORT_ARRAY_DIR := ./source

SORT_ARRAY_OBJECTS := $(addprefix $(OBJDIR)/, \
             sort_array.o \
             sort_array_funcs.o \
             sort_array_algorithm.o \
	     )

SORT_ARRAY_HEADERS := $(SORT_ARRAY_DIR)/sort_array.h \
                    $(SORT_ARRAY_DIR)/sort_array_algorithm.h

############################################################

sort_array: $(SORT_ARRAY_OBJECTS)
	gcc $(LINKERFLAGS) $(SORT_ARRAY_OBJECTS) -o $(OUTPUTDIR)/$@

$(OBJDIR)/%.o : $(SORT_ARRAY_DIR)/%.c $(SORT_ARRAY_HEADERS) $(COMMON_HEADERS)
	gcc $(COMPILEFLAGS) -c $< -o $@

$(SORT_ARRAY_OBJECTS): | $(OBJDIR)

