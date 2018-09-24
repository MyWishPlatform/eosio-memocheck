NAME=memocheck

all:
	rm -rf $(NAME)/$(NAME).w*
	eosiocpp -o $(NAME)/$(NAME).wast $(NAME).cpp
