CDEBUGFLAGS = -g -DGC_DEBUG
COPTFLAGS = -O2
CWARNFLAGS =  -Wall -Wno-switch
LIBS = -lgc -lcord
CFLAGS = $(CDEBUGFLAGS) $(COPTFLAGS) $(CWARNFLAGS)
CXXFLAGS = $(CDEBUGFLAGS) $(COPTFLAGS) $(CWARNFLAGS)

PERL = perl

OLDTMPSRCS= y.tab.c y.tab.h lex.yy.c \
	ym.tab.h ym.tab.c lex.mm.c lex.mm.h
TMPSRCS = mdl_builtins.cpp mdl_builtin_types.cpp mdl_built_in_types.h mdl_builtins.h
OLDCXXSRCS = zero.cpp

CXXSRCS = macros.cpp mdli.cpp mdl_builtins.cpp mdl_builtin_types.cpp mdl_read.cpp mdl_output.cpp mdl_binary_io.cpp mdl_decl.cpp mdl_assoc.cpp
OLDCSRCS = y.tab.c lex.yy.c \
           ym.tab.c lex.mm.c

CSRCS = 

OBJS = $(CXXSRCS:.cpp=.o) $(CSRCS:.c=.o)

mdli: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

#zero: $(OBJS)
#	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

mdl_builtins.o: mdl_builtins.h

mdl_builtins.cpp: macros.cpp
	$(PERL) find_builtins.pl $(@:.cpp=.h) < $< > $@	

mdl_builtin_types.o: mdl_builtin_types.h
mdl_builtin_types.h: mdl_builtin_types.cpp ;
mdl_builtins.h: mdl_builtins.cpp ;

mdl_builtin_types.cpp: macros.hpp mdl_builtins.h
	$(PERL) make_types.pl $(@:.cpp=.h) < $< > $@	

zero.o lex.yy.o: y.tab.h

macros.o: mdl_builtin_types.h mdl_builtins.h mdl_internal_defs.h
mdl_output.o: mdl_builtin_types.h mdl_builtins.h mdl_internal_defs.h
mdl_read.o: mdl_builtin_types.h mdl_builtins.h mdl_internal_defs.h
mdl_binary_io.o: mdl_builtin_types.h mdl_builtins.h mdl_internal_defs.h

clean: 
	rm -f *.o *~

extraclean: clean
	rm -f $(TMPSRCS) $(OLDTMPSRCS)
