# General Setup
NAME = RPN
TEST_NAME = test_rpn
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

# Files
FILES = main RPN
TEST_FILES = test_rpn RPN
HEADERS = RPN.hpp
SRCS = $(FILES:=.cpp)
TEST_SRCS = $(TEST_FILES:=.cpp)
OBJDIR = .objs
OBJS = $(addprefix $(OBJDIR)/, $(FILES:=.o))
TEST_OBJS = $(addprefix $(OBJDIR)/, $(TEST_FILES:=.o))

# Colors
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
ORANGE		=	\e[33;5;202m
RED			=	\e[31;5;196m
RESET		=	\e[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@printf "$(GREEN) $(NAME) $(RESET) has been created.\n"

$(OBJDIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -c $< -o $@
	@printf "$(YELLOW) Compiling: $(RESET) $< \n"

test: $(TEST_OBJS) $(HEADERS)
	@$(CC) $(FLAGS) $(TEST_OBJS) -o $(TEST_NAME)
	@printf "$(GREEN) $(TEST_NAME) $(RESET) has been created.\n"

clean:
	@$(RM) $(OBJDIR)
	@printf "$(ORANGE) Object files have been removed. \n"

fclean: clean
	@$(RM) $(NAME) $(TEST_NAME)
	@printf "$(RED) $(NAME) and $(TEST_NAME) have been removed. \n"

re: fclean all

cleanly: all clean

.PHONY: all test clean fclean re cleanly