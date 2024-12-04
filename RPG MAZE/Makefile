CC = g++
CPPFLAGS = -std=c++11 -Wall -g
SRCS = main.cpp blockEntity.cpp movableEntity.cpp hollow.cpp
SRCS_TST = main_test.cpp blockEntity.cpp movableEntity.cpp hollow.cpp
OBJS = $(SRCS:.cpp=.o)
OBJS_TST = $(SRCS_TST:.cpp=.o)
DEPS = $(OBJS:.o=.d)
DEPS_TST = $(OBJS_TST:.o=.d)

ifneq ($(OS), Windows_NT)
RM = -rm
ifeq ($(shell uname), Linux)
# Enable AddressSanitizer and UndefinedBehaviorSanitizer on Linux
CPPFLAGS += -fsanitize=address,undefined
endif
else
RM = -del
endif

pa2: $(OBJS)
	$(CC) -o $@ $^ $(CPPFLAGS)

pa2_test: $(OBJS_TST)
	$(CC) -o $@ $^ $(CPPFLAGS)

# To include the .d dependency files
-include $(DEPS)

%.o: %.cpp
	$(CC) -MMD -MP -c -o $@ $< $(CPPFLAGS)

clean:
	$(RM) -f *.o *.d pa2 pa2_test pa2.exe pa2_test.exe