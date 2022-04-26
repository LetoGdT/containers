NAME		:=	ft std
SRCS		:=	main.cpp

HDRS		:=	AVL_tree.hpp\
				is_integral.hpp\
				iterator.hpp\
				lexicographical_compare.hpp\
				map.hpp\
				map_iterator.hpp\
				pair.hpp\
				reverse_iterator.hpp\
				stack.hpp\
				vector.hpp\
				vector_iterator.hpp

OBJS		:=	$(SRCS:%.cpp=%.o)

CXX			:=	c++
CFLAGS		:=	-Wall -Wextra -Werror -std=c++98
RM			:=	rm -f

all:			ft std test

test:
				@./ft > tmp_ft
				@./std > tmp_std
				@diff tmp_ft tmp_std
				@rm tmp_ft tmp_std
				time ./ft > /dev/null
				time ./std > /dev/null

ft:				$(SRCS) $(HDRS)
				$(CXX) $(CFLAGS) $< -o ft

std:			$(SRCS) $(HDRS)
				$(CXX) $(CFLAGS) -D STD $< -o std

clean:
				@echo "Deleting object files"
				@$(RM) $(OBJS)

fclean:			clean
				@$(RM) $(NAME)

re: 			fclean all

.PHONY:			all clean fclean re libs
