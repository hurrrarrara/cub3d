CC = cc

NAME = libft.a

DEBUG  = 
CFLAGS = $(DEBUG) -Wall -Werror -Wextra


ODIR = ./obj
SDIR = ./src

BASICS_ODIR   = $(ODIR)/basics
GNL_ODIR      = $(ODIR)/gnl
FTPRINTF_ODIR = $(ODIR)/ftprintf
FTFPRINTF_ODIR = $(ODIR)/ftfprintf

BASICS_SDIR   = $(SDIR)/basics
GNL_SDIR      = $(SDIR)/gnl
FTPRINTF_SDIR = $(SDIR)/ftprintf
FTFPRINTF_SDIR = $(SDIR)/ftfprintf

BASICS_INCL   = $(BASICS_SDIR)/basics.h
GNL_INCL      = $(GNL_SDIR)/get_next_line.h
FTPRINTF_INCL = $(FTPRINTF_SDIR)/utils.h
FTFPRINTF_INCL = $(FTFPRINTF_SDIR)/futils.h

basics	:=	ft_atoi			ft_lstclear\
			ft_memset		ft_strlcpy\
			ft_bzero		ft_lstdelone\
			ft_putchar_fd	ft_strlen\
			ft_calloc		ft_lstiter\
			ft_putendl_fd	ft_strmapi\
			ft_isalnum		ft_lstlast\
			ft_putnbr_fd	ft_strncmp\
			ft_isalpha		ft_lstmap\
			ft_putstr_fd	ft_strnstr\
			ft_isascii		ft_lstnew\
			ft_split		ft_strrchr\
			ft_isdigit		ft_lstsize\
			ft_strchr		ft_strtrim\
			ft_isprint		ft_memchr\
			ft_strdup		ft_substr\
			ft_itoa			ft_memcmp\
			ft_striteri		ft_tolower\
			ft_lstadd_back	ft_strlcat\
			ft_memcpy		ft_strjoin\
			ft_toupper		ft_lstadd_front\
			ft_memmove		ft_strappend

gnl :=	get_next_line	get_next_line_utils

ftprintf := ft_printf	_putstr\
			_xtoa_base	_check_format\
			_utils		_writer\
			_xtoa_utils

ftfprintf := ft_fprintf	f_putstr\
			f_xtoa_base	f_utils	\
			f_writer	f_xtoa_utils

BASICS_OBJ = $(addprefix $(BASICS_ODIR), $(addprefix /, $(addsuffix .o, $(basics))))
GNL_OBJ = $(addprefix $(GNL_ODIR), $(addprefix /, $(addsuffix .o, $(gnl))))
FTPRINTF_OBJ = $(addprefix $(FTPRINTF_ODIR), $(addprefix /, $(addsuffix .o, $(ftprintf))))
FTFPRINTF_OBJ = $(addprefix $(FTFPRINTF_ODIR), $(addprefix /, $(addsuffix .o, $(ftfprintf))))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(BASICS_OBJ) $(GNL_OBJ) $(FTPRINTF_OBJ) $(FTFPRINTF_OBJ) Makefile
	ar -r $@ $(BASICS_OBJ) $(GNL_OBJ) $(FTPRINTF_OBJ) $(FTFPRINTF_OBJ)

$(BASICS_ODIR)/%.o : $(BASICS_SDIR)/%.c $(BASICS_INCL) Makefile
	@mkdir -p $(BASICS_ODIR)
	$(CC) $(CFLAGS) -I$(BASICS_SDIR) -o $@ -c $<

$(GNL_ODIR)/%.o : $(GNL_SDIR)/%.c $(GNL_INCL)  Makefile
	@mkdir -p $(GNL_ODIR)
	$(CC) $(CFLAGS) -I$(GNL_SDIR) -o $@ -c $<

$(FTPRINTF_ODIR)/%.o : $(FTPRINTF_SDIR)/%.c $(FTPRINTF_INCL) Makefile
	@mkdir -p $(FTPRINTF_ODIR)
	$(CC) $(CFLAGS) -I$(FTPRINTF_SDIR) -o $@ -c $<

$(FTFPRINTF_ODIR)/%.o : $(FTFPRINTF_SDIR)/%.c $(FTFPRINTF_INCL) Makefile
	@mkdir -p $(FTFPRINTF_ODIR)
	$(CC) $(CFLAGS) -I$(FTFPRINTF_SDIR) -o $@ -c $<

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -f $(NAME)

re: fclean all