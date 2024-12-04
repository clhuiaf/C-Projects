CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

ifneq ($(OS), Windows_NT)
ifeq ($(shell uname), Linux)
# Enable AddressSanitizer and UndefinedBehaviorSanitizer on Linux
CXXFLAGS += -fsanitize=address,undefined
endif
endif

SRCS = main.cpp transaction.cpp blockchain.cpp user.cpp bitcoin.cpp
SRCS_TEST = main_test.cpp transaction.cpp blockchain.cpp user.cpp bitcoin.cpp
OBJS = $(SRCS:.cpp=.o)
OBJS_TEST = $(SRCS_TEST:.cpp=.o)

ifneq ($(OS), Windows_NT)
# If the OS is not Windows, the executable file is named pa1
EXEC = pa1
EXEC_TEST = pa1_test
else
# If the OS is Windows, the executable file is named pa1.exe
EXEC = pa1.exe
EXEC_TEST = pa1_test.exe
endif

all: $(EXEC)

test: $(EXEC_TEST)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(EXEC_TEST): $(OBJS_TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

ifneq ($(OS), Windows_NT)
# If the OS is not Windows, use rm to remove files
clean:
	rm -f $(OBJS) $(EXEC) $(OBJS_TEST) $(EXEC_TEST)
else
# If the OS is Windows, use cmd del to remove files
clean:
	cmd "/C del $(OBJS) $(EXEC) $(OBJS_TEST) $(EXEC_TEST)"
endif