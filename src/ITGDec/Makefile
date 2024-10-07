CFLAGS = $(subst -O2,-O0,$(CXXFLAGS))
OBJS = ITGDecod.o ../common/ITG.o ../common/json_output.o

all: ITGDec$(SUFFIX)

ITGDec$(SUFFIX): $(OBJS)
ifeq ($(BUILD_ENV),WIN32_MINGW)
	@ echo [ LD ]  $@ ^<- $(OBJS)
else
	@ printf "[ LD ]\t$@ <- $(OBJS)\n"
endif
	@ $(CXX) $(CFLAGS) $(OBJS) -lm -lz -o $@ $(LDFLAGS)
	@ $(CP) $@ $(BIN)

ITGDecod.o: ITGDecod.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

../common/json_output.o: ../common/json_output.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
ifeq ($(BUILD_ENV),WIN32_MINGW)
	@- $(RM) *.o ITGDec$(SUFFIX) $(BIN)\ITGDec$(SUFFIX)
else
	@ $(RM) *.o ITGDec$(SUFFIX) $(BIN)/ITGDec$(SUFFIX)
endif

#---------------
include ../common.mk
#---------------
