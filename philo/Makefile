NAME := philo

CC := cc

#TODO: add back flags
#CFLAGS :=  -Wextra -Wall -Werror -I./includes -g
CFLAGS :=  -I./includes -g
LINKFLAGS := -pthread -fsanitize=address

SRCS := src/init.c src/main.c src/parsing.c src/utils.c src/start_eat.c
OBJDIR := obj
OBJS := $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

RM := rm -rf

all: $(NAME)

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LINKFLAGS)

-include $(OBJS:.o=.d)

clean:
	$(RM) $(OBJS) $(OBJS:.o=.d)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

