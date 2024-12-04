SRCS = test.cpp main.cpp LinkedList.cpp OrderOstream.cpp HashTable.cpp OrderSystem.cpp interactive-main.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)
SUBMISSION = SmartPtr-impl.h BST-impl.h Order.h
OBJ_DEBUG_PREFIX = leak

CPPFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -g
# CPPFLAGS_DEBUG = -std=c++11 -fsanitize=address,undefined,leak -Wall -Wextra -Wpedantic -g
CPPFLAGS_DEBUG = -std=c++11 -fsanitize=address,undefined -Wall -Wextra -Wpedantic -g
OBJS_DEBUG = $(addprefix $(OBJ_DEBUG_PREFIX)_,$(OBJS))
DEPS_DEBUG = $(OBJS_DEBUG:.o=.d)

ifeq (Windows_NT, $(OS))
RM_CMD := /C del
PA3=pa3.exe
PA3_LEAK=pa3_leak.exe
else
RM_CMD := rm -vf
PA3=pa3
PA3_LEAK=pa3_leak
endif

all: $(PA3)
debug: $(PA3_LEAK)

$(PA3): $(OBJS)
	g++ -o $@ $(CPPFLAGS) $^

$(PA3_LEAK): $(OBJS_DEBUG)
	g++ -o $@ $(CPPFLAGS_DEBUG) $^

clean:
	$(RM_CMD) $(OBJS) $(OBJS_DEBUG) $(PA3) $(PA3_LEAK)

# To include the .d dependency files
-include $(DEPS) $(DEPS_DEBUG)

%.o: %.cpp
	g++ $(CPPFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DEBUG_PREFIX)_%.o: %.cpp
	g++ $(CPPFLAGS_DEBUG) -MMD -MP -c $< -o $@
