CC := g++
INCD := include 
SRCD := src
BLDD := build
BIND := bin

ALL_SRCF := $(shell find $(SRCD) -type f -name *.cpp)
ALL_OBJF := $(patsubst $(SRCD)/%,$(BLDD)/%,$(ALL_SRCF:.cpp=.o))
VCDF := packet_translator.vcd

INC := -I $(INCD) -I $(SYSTEMC_HOME)/include 
LINK := -L $(SYSTEMC_HOME)/lib-linux64 -Wl,-rpath=$(SYSTEMC_HOME)/lib-linux64
LIBS := -lsystemc -lm
DFLAGS := -g

EXEC := comm_interface 

.PHONY: clean all 

all: setup $(EXEC)

setup:
	mkdir -p bin build

$(EXEC): $(ALL_OBJF)
	$(CC) $(DFLAGS) $(INC) $(LINK) $^ -o $(BIND)/$@ $(LIBS)

$(BLDD)/%.o: $(SRCD)/%.cpp
	$(CC) $(DFLAGS) $(INC) $(LINK) -c -o $@ $< $(LIBS)

clean:
	rm -rf $(BLDD) $(BIND) $(VCDF)
