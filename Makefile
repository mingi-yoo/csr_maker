CXX = g++ 
#CXXFLAGS = -g -std=c++11 -Wall -Wextra -Wno-sign-compare -O3
CXXFLAGS = -g -fopenmp -std=c++11 -Wall -Wno-sign-compare -O3

SRCDIR = src
OBJDIR = obj
BINDIR = bin

INCS := $(wildcard $(SRCDIR)/*.h)
SRCS := $(wildcard $(SRCDIR)/*.cc)
OBJS := $(SRCS:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

all:  bin/csr



bin/csr: $(OBJS)
	mkdir -p bin
	@echo "OBJ: "$(OBJS)
	$(CXX) $^ -o $@ $(CXXFLAGS)
			    @echo "Compiled "$<" successfully!"


.PHONY:	test clean

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	    mkdir -p obj 
	    @echo $(CXX)  -c $< -o $@ $(CXXFLAGS) 
	    $(CXX)  -c $< -o $@ $(CXXFLAGS)
			@echo "Compiled "$<" successfully!"

clean:
	rm -f $(OBJS) $(OBJS:%.o=%.d) 
	rm -rf bin/*
