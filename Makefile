NAME = philo
COMPIL = cc
FLAGS = -Wall -Werror -Wextra -fsanitize=thread
#-g3 
PINK = \033[1;35m
BLUE = \033[1;36m
NC = \033[0m

HEADER_F = headers/philo.h

MANDATORY_SRCS = philo.c \
				parsing.c \
				utils_parsing.c \
				utils.c \
				routine.c \
				monitor.c \
				thinking_utils.c \

# Magic with srcs and objs #

PMANDATORY = $(addprefix srcs/, $(MANDATORY_SRCS))
M_OBJS = $(PMANDATORY:srcs/%.c=objs/%.o)

all : $(NAME) 

objs/%.o: srcs/%.c $(HEADER_F)
	@mkdir -p objs/mandatory
	@$(COMPIL) $(FLAGS) -c $< -o $@

$(NAME) : $(M_OBJS) $(HEADER_F)
	@$(COMPIL) $(FLAGS) -o $@ $(M_OBJS)
	@echo  "$(BLUE)\n     PHILO COMPILED \n$(NC)"

clean :
	@rm -rf objs/*
	@echo  "$(PINK) \n  PHILO CLEANED  \n$(NC)"

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
