NAME :=  ircserv
CC := g++
CFLAGS :=  #-Wall -Wextra -Werror -std=c++98

SRCS_DIR := ./src
OBJS_DIR := ./objs

HEADERS := ./include
FILES := main.cpp \
			Serveur.cpp \
			Client.cpp \
			Channel.cpp \
			Utils.cpp \
			cmdError.cpp \
			cmdInvite.cpp \
    		cmdJoin.cpp \
    		cmdKick.cpp \
    		cmdMode.cpp \
    		cmdNick.cpp \
    		cmdNotice.cpp \
    		cmdPart.cpp \
			cmdPass.cpp \
    		cmdPing.cpp \
    		cmdPrivmsg.cpp \
    		cmdQuit.cpp \
    		cmdTopic.cpp \
    		cmdUser.cpp


SRCS := $(addprefix $(SRCS_DIR)/, $(FILES))
OBJS := $(addprefix $(OBJS_DIR)/, $(FILES:.cpp=.o))
DEPS := $(OBJS:.o=.d)


# COLOR #
GREEN	:= \033[38;5;76m
RED		:= \033[38;5;160m
BRIGHT_RED := \033[38;5;196m
YELLOW	:= \033[38;5;226m
ORANGE	:= \033[38;5;202m
PURPLE	:= \033[38;5;213m
LBLUE	:= \033[38;5;51m
BLUE	:= \033[38;5;117m
INDI	:= \033[38;5;99m
RESET	:= \033[00m
BROWN   := \033[38;5;130m
PINK    := \033[38;5;218m
GOLD := \033[38;5;220m
DARK_BLUE := \033[38;5;26m
MINT_GREEN := \033[38;5;38m

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I$(HEADERS) -o $(NAME) $(OBJS)
	@printf "$(RESET)\n\n\n"
	@printf "⠀⠀$(PURPLE)⢀⠂⠘⠀⠱⠈⡝⣏⠐⠀⠑⠒⠤⣼⢶⠁⣠⠀⠠$(INDI)⠀⠀⠀⠀⢸⠍⣎⢙⣿⣿⢿⡁⠤⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣄⡀⠀$(RED)⠀⠀⠀⠀⠀⠀⠄⣡⠀⠈⠒⠄⢄⠀⠀⠀$(INDI)⠐⣫⡇⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠶⣷⣴⣥⣐⠘⢟⡟⡧⢛⣤⣳⣿⣿⠿⠟⠉⠀⠀⣰⡛⠄$(BLUE)⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⡇⠒⡤$(RESET)\n"
	@printf "⠀$(PURPLE)⠀⡠⠒⠂⠡⠐⠁⡠⠠⢈⠍⠁⠀⠘⢟⢾⣿⣿⡀⠁$(INDI)⠀⠀⠀⠀⠘⢦⠰⣍⡻⣿⢀⢺⠁⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⢹⣿⣿⣿⣆⡀$(RED)⠀⠀⠀⠀⢠⢚⡤⡸⢊⣀⢨⣌⠀⠀⠀$(INDI)⢚⡿⠀⡰⠀⡀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠉⠛⠊⢀⠔⠿⠿⠋⠉⠀⠀⠀⠀⠀⣸⣿⣯$(BLUE)⠀⢀⡠⠶⣀⠀⠀⠀⠘⣿⡅⠈⠌⠋$(RESET)\n"
	@printf "⠀$(PURPLE)⠈⡄⠀⠀⠆⠈⢐⠡⠀⠀⠀⢀⣐⡁⠐⠉⡛⡛⠹⠈⢄⠀$(INDI)⠀⠀⠀⢿⡂⢿⣿⣮⠸⡇⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣛⠛⠿⣿⣶⡶⢬⣉⣿⣿⣿⡥$(RED)⠀⠀⠀⠀⠢⠋⡠⢴⣋⢆⠁⠈⠁⡀$(INDI)⢰⣿⠁⢠⠁⢸⡗⠀⠁⢢⡄⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡽⣿⣿$(BLUE)⢲⠟⠨⠽⣛⣤⠀⠈⠀⣥⣰⡆⣄⣂$(RESET)\n"
	@printf "⠀$(PURPLE)⠀⠀⠀⠁⠂⠀⠀⢃⣠⣾⣿⣿⣿⣿⡀⠀⠁⠈⠀⢀⠨⡀$(INDI)⠀⢀⡳⠵⣥⡘⢿⣯⠳⡀⣀⠀⠀⢠⣿⣿⣿⠡⣶⠂⢉⡐⡠⠄⡙⣿⣼⡿⠿⠿⣟⢾$(RED)⠀⠀⠀⠀⠈⢠⡍⣤⢭⣤⣬⢀⠀⠀$(INDI)⠢⠈⠀⠎⠀⣈⠁⠀⠀⠛⠃⠀⠈$(GOLD)⣠⡄⡄⢠⣐⢠⣴⣷⣾⣄⢆⡠$(INDI)⠀⠄⢀⠀⠀⢀⠎⡽⣿⣿⠇$(BLUE)⠶⣤⣾⣿⣿⡆⢀⠀⣿⣿⣿⣷⡇$(RESET)\n"
	@printf "⠀⠀⠀⠀$(PURPLE)⢰⣶⣶⣶⣿⣿⣿⣿⡿⠿⠿⢷⣤⣄⠀⢀⠠⠚⢱$(INDI)⣶⢮⣥⢄⣬⠝⢷⣝⠃⢂⠌⠻⣄⣾⣿⣿⣿⣧⣬⣤⣤⣜⣹⣾⣿⣿⠉⠀⠀⠐⢢⡝⡐⠀⢀$(RED)⠀⡡⡀⢃⣶⣶⣶⣯⡜⠁⠀$(INDI)⡟⠀⠘⠀⡀⣈⠀⠀⢰⡇$(GOLD)⠠⣀⣀⢟⠵⣚⣭⣴⣿⣿⣶⣶⣆⡤⢆⣉⢁⠐⠪⢐$(INDI)⠻⣆⠹⠝$(BLUE)⡁⠠⠈⠁⠀⣹⡿⠁⢸⣦⠘⢟⢣⠤⠈$(RESET)\n"
	@printf "⠀$(PURPLE)⠀⠌⡧⢘⣿⣿⣿⣿⣿⣿⢿⣾⣿⣿⣿⢿⣿⡆$(INDI)⣮⣀⠈⢐⡪⢦⡄⠈⠗⢠⣷⣍⠂⡿⠰⠂⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⢠⡀⠈⠽⡀⠀⣠⡴⠃$(RED)⠀⢑⡄⣒⠐⠒⠂⠭⢑⠀$(INDI)⣴⠇⠀⣶⠀⠀⠩⠒$(GOLD)⣰⣵⣿⣿⣯⡝⡵⢟⣻⣿⣿⣿⣿⣿⣿⣟⡻⢿⣾⣽⣖⡥⣺⢿⣮⣕⡆$(BLUE)⣷⠀⠀⢀⠺⠟⠀⣠⠼⣫⣴⠆⠀⠂⠄$(RESET)\n"
	@printf "⠀⠀$(PURPLE)⠼⡓⡀⣌⠛⢿⣿⣿⣧⢊⡾⣟⠩⣢⣿⣿⡿$(INDI)⢘⣟⠃⠨⠀⠋⢥⡜⠿⠿⣿⡟⠂⠑⢄⣀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⡿⠃⣿⣿⣟⠃⡜⠉⢔⣡⣶⡿$(RED)⠐⠡⢣⠒⠜⠦⠀$(INDI)⢸⡏⠀⠀⣋⡀⠀$(GOLD)⢖⢿⣿⣿⡿⠳⠶⢠⣾⢿⣿⣿⣿⣿⣿⣿⣿⣿⢿⡻⣾⣽⡻⣿⣶⣥⡚⣙⠢$(BLUE)⠿⠇⣀⣀⡈⠰⠂⠲⣿⣿⡿⠁⠀⠀⠀$(RESET)\n"
	@printf "⠀⠀$(PURPLE)⠠⢡⠱⣄⠛⢗⢹⣿⣷⣷⣾⣿⡏⠻⣿⣿⣿$(INDI)⠂⠩⡔⣠⡦⢚⣵⣶⣽⡆⣹⡟⠀⠀⠀⠧⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣋⠤⣜⢿⣻⡞⠀⢀⣼⣿⣿⡟⠁⠀⠀⡀$(RED)⠀⠀$(INDI)⣀⣤⣾⠀⠀⠀⠹⢃$(GOLD)⢆⣵⡿⣫⣶⣾⣭⢋⢉⣾⣿⣿⣿⣿⣿⣛⠿⣿⣿⣿⣶⣼⡛⢿⣷⣭⡻⢯⡒⢝⠿⠆$(BLUE)⠀⠀⢁⡄⠀⢰⣝⡛⠀⠀⠀⠀⠀$(RESET)\n"
	@printf "⠀⠀$(PURPLE)⢐⡠⢿⣿⡆⠘⢻⣿⣿⣿⣿⣿⣿⣀⣽⣿⣿⣇$(INDI)⢀⠄⢿⡡⢾⣿⣝⣿⡇⣤⠠⠁⠀⠀⠇⠀⢸⣿⣿⣿⣿⣿⣿⡿⠿⠿⣭⡐⠻⣜⣯⡟⠀⣠⠟⣽⢫⢃⣠⣤⣶⠟$(INDI)⠀⠀⠠⠿⣿⡃$(GOLD)⠀⠀⠀⠰⢋⣾⡷⢢⡿⣿⣿⡿⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⡛⣿⣽⢿⣷⣤⡠⣍⡛⠚⠥⠈⠈⠢⠀$(BLUE)⠿⣀⠆⣪⡶⠁⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(PURPLE)⠰⡜⣄⠢⢍⠀⣼⣿⡿⣿⣿⣿⣿⢟⣽⣝⠻⣃$(INDI)⣀⡙⠶⣝⣂⠉⠛⢿⣧⢿⡀⠀⠀⠀⠀⡄⠀⠙⠿⣿⣿⣿⣿⣷⡲⡰⢤⡬⣗⣿⠊⠀⡰⢥⠛$(BRIGHT_RED)⣈⢤⣭⣅⡲⢔⠄⡀$(INDI)⠀⠀⠀⠀⠉⠲⣦$(GOLD)⣔⣜⣾⣻⣱⡿⣹⣿⣿⡷⣸⣿⣿⣿⠿⣿⣿⣝⡻⣮⣻⣿⣿⣮⡛⠿⣿⣝⢿⣦⡙⢦⢈⠛⢧⣢$(BLUE)⡹⡏⠀⢰⡿⠁⠀⠀⠀⠀⠀⠀$(RESET)\n"
	@printf "⠀⠀⠀$(PURPLE)⢡⠂⡍⢢⣦⢩⡑⢐⠛⠫⠽⣢⣯⣝⢟⣡$(INDI)⣤⣬⣭⣿⣿⣮⣗⡠⣂⠹⣞⣿⡈⠄⠀⢰⣧⣃⠐⣀⠈⠻⣿⣿⣿⣷⣙⣧⢻⠝⠀⠀⢌⠑⡂$(BRIGHT_RED)⣨⣙⡛⡔⠢⡙⡌⠇⠁⡤$(GOLD)⠀⠀⠀⠀⠀⢨⢎⣞⡏⣿⣸⣡⡿⡟⣿⣧⣙⣿⣿⠿⣿⣮⡛⣿⣿⣮⡻⣷⣽⡙⠿⣧⡈⠙⢧⠈⠛⢦⠻⣕⢤⡁⠹$(BLUE)⡜⡄⠘$(RESET)⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(PURPLE)⡀⠡⠈⢄⢫⡿⠋⣠⣾⣿⣿⣶⡿⣹⠋$(INDI)⠀⡝⠿⣿⣿⡿⣿⣿⣿⣿⣾⣶⣜⣿⣧⠁⠀⠀⠉⠻⠄⠲⢢⠄⠈⠙⠟⣶⡹⠎⠁⠀⠀⠈⠀⣴⡇$(BRIGHT_RED)⣟⢭⠁⢨⣵⣶⣶⣾⣇⠀⠀⠐⢢⠈⡗$(GOLD)⠎⣼⢻⢹⣟⣿⢿⣷⡇⡟⢿⣧⢘⣿⣎⢮⡻⣿⣶⣍⢻⣿⣶⡙⢷⣄⠈⠛⢆⠀⠑⢤⣀⠑⠙⢮⣻⣄⢻⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(PURPLE)⠴⣣⣼⠀⣦⢎⡊⠀⣼⣿⡿⠫⠞⠁$(INDI)⢀⠍⢘⣛⣂⣉⠹⠒⠦⠋⠝⠻⢿⣍⠘⢿⡆⠀⣀⠀⢄⠀⠀⠀⠙⣦⠀⡀⠀⠀⣠⠀⠀⠀⠀⢘⣻⣿⡄$(BRIGHT_RED)⡁⠀⣦⠿⠿⠷⣉⠁⠈⢄⠀⣼⢠⢃⣾$(GOLD)⠇⡟⣺⡧⣟⢹⡇⡇⣿⣤⢻⡆⠻⣿⣄⡙⢬⠻⢿⢧⡘⢿⣌⠪⣧⡀⢀⠀⠡⠑⢦⡘⣦⡈⠀⡳⢻⢘$(DARK_BLUE)⠄⢀⢀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(PURPLE)⠠⠛⢃⡋⢗⢃⣵⠾⡿⡫⢄⡃$(INDI)⠀⠀⠈⠀⠀⠙⠟⢿⣿⣿⣿⡿⢶⣦⠄⠩⠂⠈⢿⡰⠀⠀⠈⢳⡠⠀⢡⣿⡝⡶⠀⡞⡄⣀⠀⠀⠀⠎⢙⣭⡟$(BRIGHT_RED)⠀⠀⢿⣷⣶⣾⡿⠄⠉⠸⡄⣾⢺$(GREEN)⢄⠵⡄$(GOLD)⡇⢟⣅⣿⠸⠁⡇⢿⡌⢏⢿⡀⠉⠻⣿⡄⠑⡀⠁⠙⣄⠻⣆⠀⢻⡄⠂⠄⠀⠄⠻⣌⠏$(DARK_BLUE)⣦⣼⣧⣈⣿⣾⣥⣢⡤⣄⡀⠀⠀⠀$(RESET)\n"
	@printf "⠀⠀⠀$(PURPLE)⣦⣅⠢⠍⠉⠉⠈⢊⣙⡀⠂$(INDI)⠀⠀⠀⠀⠀⠰⠦⠥⡽⠋⠁⢐⠠⠂⡀⠁⠀⠁⠎⢣⠐⠎⡂⡀⠑⢄⣻⣛⠋⠑⣪⡗⠃⠀⠀⠀⠀⠐⠿⠟$(BRIGHT_RED)⠀⠹⣶⡀⠛⠿⣟⡀⢀⢟⣬⠀⡿$(GREEN)⡑⠁⠀⠃$(GOLD)⠀⠞⠋⠀⢀⡇⠱⠘⣧⠘⠌⢳⡀⠀⠈⠻⡄⣌⠠⠀⠀⠂⠙⡆⡄⠻⡄⢃⡆⡨$(DARK_BLUE)⠠⢭⣭⣾⣿⣿⠿⣿⣻⣿⣿⢷⣽⠃⠀⡄⢆$(RESET)\n"
	@printf "⠀$(PURPLE)⣠⡾⡿⠂⡰⠀$(RESET)⣤⣧⣄$(PURPLE)⠒⠀⠀⠥⠀$(MINT_GREEN)⠀⠒⢒⠀⠀⢤⡄⠐⠀⠀⡀⠀⠻⢿⣿⣷⣶$(INDI)⡱⢠⠠⣤⠔⢤⠚⢂⢢⡄⢀⡘⠃⠀⠀⠀⠀⠀⠀⠀$(BRIGHT_RED)⢠⣿⣄⠀⠀⠙⠀⠀⠈⠁⠈⡏⠇$(GREEN)⠈⠔⠀⠀⠀⠀⠀⠀⠀⠀$(GOLD)⣼⠝⡠⠃⠈⠆⠈⠀⠡⠀⠌⢦⣀⠙⢠⠀⡀⣶⣄⡐⠸⡀⢻⡀$(DARK_BLUE)⡜⠌⡳⣓⠽⡿⠛⠡⠒⠙⠿⢿⣿⣓⢁⣠⠺⣿⡆$(RESET)\n"
	@printf "⠀⣩⣵⣃⠀⠁⡴⣿⣟⣯$(PURPLE)⠰⡦⠐⠐⠶⠂$(MINT_GREEN)⢀⣨⣤⣶⠞⠁⠐⢶⢶⠇⡀⠀⠈⢙⠿⢫$(INDI)⢃⣾⡦⡉⠀⣈⠦⢊⠺⡷⠺⠁⠀⡐⠂⠀⠀⠀⠀$(BRIGHT_RED)⢠⣾⣿⣿⣦⣀⢀⡀⠀⠀⢀⠠⢱⠀⠀⠀⠀⠀$(GREEN)⡀$(GOLD)⠀⠀⠀⠀⠀⢉⣴⠃⢀⠀⠀⠀⠀⠠⣄⠐⢮⠛⢠⣌⠀⢣⡿⣽⣧⠀⢣⠘⣇⢡$(DARK_BLUE)⠐⢳⣽⡔⠡⢀⣠⣆⠀⠐⠚⢯⢛⣬⡯⠴⣿⡓$(RESET)\n"
	@printf "⠀⢉⣉⠛⠿⡆⣯⣉⡭⠍⢂⡔⠂⠀⠀⠁$(MINT_GREEN)⠻⣿⣿⠁⠀⢀⠘⡠⢜⣀⡾⠀⠀⠀⠀$(ORANGE)⢃⢸⡏⢩⣕⠊⠀⠉⠂⠀⠠⢂⡀⠀⠡⣓⡀⠀⠀$(BRIGHT_RED)⢀⣿⣿⣿⣟⢹⣿⠿⣪⣿⣿⣈⠤⠈⠁$(GREEN)⣤⣶⡿⠉⠩⣥⠀⠀⠀⠀$(GOLD)⠉⣠⢆⠀⡣⠍⠱⠷⣒⣬⡺⣬⣿⣥⣶⣶⣶⣿⣿⣿⠀⠈⠀$(DARK_BLUE)⠨⠈⠑⠒⠙⢏⠀⢹⣿⣿⣶⣒⠩⠑⢽⢩⠉⠀⠘⠃$(RESET)\n"
	@printf "⠀⠈⠛⠿⣦⢀⠐⠆⡠⢀⡒⠀$(YELLOW)⢲⡿⡿⣝⣕⣌⡳⠀$(MINT_GREEN)⠀⢠⠀⢛⡓⣉⡕⠐⡀$(ORANGE)⣴⣦⡌⢸⡱⠋⠈⠀⠀⠀⠀⠀⠀⢀⠃⠠⡒⠋⠀⠀⠀$(BRIGHT_RED)⣸⣿⣫⣶⡾$(PURPLE)⣦⡀⢰⡙⣣⠞⣫⠴⡲⠦$(GREEN)⠢⢹⣶⣧⣠⣿⡃⠀⠀$(GOLD)⡀⢼⡚⢇⡂⠉⣷⢿⣿⣿⡿⠁⢹⣿⣿⣿⣿⡿⠛⠉⠁⠀⠀$(DARK_BLUE)⠉⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣽⣿⢆⢐⠄⡛⣁⢦⠀⠀$(RESET)\n"
	@printf "⠀⠀⠀⢀⣐⠮⠥⠄⣀⡠$(YELLOW)⡀⢶⡿⡇⠹⠜⠎⢫⡄⠁$(MINT_GREEN)⠀⡄⢩⣐⡉⠌⡈⠴$(ORANGE)⠀⠉⠉⠀⠘⣠⡄⠀⢀⠀⠀⠀⠀⠀⢸⡇⢀⡠⠄⠀⠀⠀$(BRIGHT_RED)⣿⠃$(PURPLE)⠈⠻⡧⠹⢯⠳⣣⠉⠊⡔⠣⠄⠙⢻⣦$(GREEN)⠛⠙⢿⡿⠀⠀$(GOLD)⠈⠣⢀⠑⠆⠙⠤⠀⠙⣿⣻⡵⣖⠤⢿⣿⣿⣿⡇⠀⠀⠀$(DARK_BLUE)⠁⠀⠀⢠⡀⠀⠀⠀⠀⠀⠀$(GOLD)⢀⣶⣦⣰⡀⠀⠀⠀$(DARK_BLUE)⠋⠈⠀⠀$(RESET)\n"
	@printf "⠀⠀⣰⣭⣛⡛⣛⣫⠍$(YELLOW)⠀⠧⠀⠘⠈⣀⡄⠀⠀⠀⠀$(MINT_GREEN)⠐⠃⠈⠻⠏⠀⠀⣱$(ORANGE)⠀⠀⠀⠀⢀⠑⠠⣦⣨⣬⠀⠀⠀⠀⣼⣇⡉⡸⠁⠀⠀⠀$(BRIGHT_RED)⢹⠀⡀$(PURPLE)⠔⢊⠵⠉⠂⠀⠠⢶⣶⠶⣦⣄⠀⠺$(GREEN)⢕⣰⠂⠚⡟⢧⣉⠐⡒⢄$(GOLD)⠠⠁⣀⠁⠀⠀⠁⠛⢼⣫⣭⣿⣿⢟⣾⡦⠀⠀$(DARK_BLUE)⢐⠎⢗⠈⢰⠀⠀⠀⠀⠀⠀$(GOLD)⠈⣿⣿⣷⢵⣕⣔⣀⡀⠀⣠⡇\n"
	@printf "⠀⠀$(RESET)⢹⣛⣙⠁$(YELLOW)⠨⠡⠄⠀⠀⠀⠀⣌⣿⣷⣾⠟⣱⡇$(MINT_GREEN)⠀⠀⠀⠀⠀⠀⡰⠁$(ORANGE)⠀⠀⠀⠀⠈⠳⠦⠙⠿⠮⠉⠀⠀⠀⣉⠅⠀⠁⠀⠀⠀⠀$(BRIGHT_RED)⠘$(PURPLE)⠄⠘⠀⢃⠒⡡⠄⢤⠩⢍⠈⠓⢡⠈⠓⡀⠀$(GREEN)⢹⡀⠈⢀⠃⢚⡓⠦⠈⢂⠦⣐⠦⣄⠤⢀⠀⠀⠀$(GOLD)⠋⠉⢠⡾⠃⣠⡧⠀$(DARK_BLUE)⢼⠎⠈⢿⣆⠀⠀⠀⠀⠀⠀$(GOLD)⣠⠿⠻⠟⣸⡞⣿⣿⣿⣿⣷⣽\n"
	@printf "⠀⠀$(YELLOW)⢷⡍⠿⣀⠀⣀⡠⠂⣀⠀⠀⠙⠛⠿⢫⠦⠉⣀⠀⠀⠐⡀⡄$(ORANGE)⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣬⡆⡿⠀⠁⠀⠀⠀$(PURPLE)⢠⣋⠡⡌⠥⢉⠄⡐⣂⠒⠢⠄⣈⠥⢘⡂⠁⠀⠑⡀$(GREEN)⡇⢨⡄⢀⠘⠣⠙⠐⠀⢂⠆⠙⠖⠀⢠⠀⠔⠑$(GOLD)⣢⠤⠛⣈⣥⠾⠿⠁⠀⠀⠀⠀⠀$(DARK_BLUE)⠈⠉⠀⠀⠀⠀$(GOLD)⢠⠖⢶⣚⠗⣩⢾⠿⠿⢍⣝⣳⣭\n"
	@printf "⠀⠀$(YELLOW)⠈⠉⠈⣼⡶⢛⡑⠄⢀⢖⣦⣦⠲⠈⣠⡆⠂⠹⠛⠽⢿⣿⡿⢍⣴⣆$(ORANGE)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠄⠜⠐⢠⠀$(PURPLE)⢀⠔⢛⣫⣷⡟⡰⢂⠌⢀⡑⢦⣙⡰⣦⡐⡙⢶⡈⡀$(GREEN)⠀⠠⣣⡴⣮⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(GREEN)⠈⡀⠀$(GOLD)⢀⣠⣡⣄⠶⠘⢋⣼⡄⠀⠀⠀⠀⠀⠀⠀⠀⢠⠆⠀⢀⣫⣻⠛⠁⠌⣋⣤⢷⣾⣻⢿⡿⣟\n"
	@printf "⠀⠀$(YELLOW)⠠⣌⡄⣿⣅⠘⠀⠀⣌⣿⣿⣿⠁⢀⠗⣀⢯⢻⡇$(PINK)⢀⣿⡎⢙⣆⡉⠿⠆⣠⣀⠀$(ORANGE)⠀⠀⠀⠀⠀⠀⢀⣿⠀⠀⢠⠃⠀$(PURPLE)⢀⠴⢋⣽⠿⡼⢳⠃⢀⣤⡸⢢⡝⣿⣮⡻⢮⠲⡙⣄$(GREEN)⢢⢠⣅⠛⣫⡾⣷⠀⠀⠀⠀⠀⠀⢀⠐⡐⠲⡅$(GOLD)⡤⠟⠋⣉⢠⡔⢞⣾⡇⠀$(DARK_BLUE)⣀⠐⠒⣒⣀⠀⠀$(GOLD)⠀⡞⡀⠀⠀⠘⠁⣀⠶⠩⠛⠯⣿⡼⣏⡿⣵⢫\n"
	@printf "⠀⠀$(YELLOW)⠐⠀⠀⣿⣿⠀⣰⣦⢸⡏⡆⡿⠀⢰⣏⣏$(PINK)⡈⠘⢃⣰⣜⢷⣌⢿⣿$(BLUE)⡘⣷⣦⡉⠃⠉⠑⡀$(ORANGE)⢀⠒⠀⡀⠀⠀⠈⠂$(PURPLE)⠀⠀⠈⢠⠙⠁⠘⠁⢀⠀⢾⣿⣧⠁⠻⠑⡉⢓⠀⠀⠂⠴$(GREEN)⡈⢖⣤⠦⣄⣘⣩$(GOLD)⠴⣾⣶⡆$(GREEN)⠀⠀⣀⡤⢠⠈⡃⠕$(GOLD)⢞⠛⠋⡀⣴⡿⢊⡀$(DARK_BLUE)⠰⡭⣤⣜⡛⠯⣷⢦⣄$(GOLD)⠸⠈⠀⡀⠀⠀⠙⢾⡀⠀⠈⠀⠈⠉⠓⢭⣥\n"
	@printf "⠀⠀$(YELLOW)⣱⡀⢸⣿⣿⡎⣿⠇⢸⢱⠇⠀⠀⣾⢸⢹⣇$(PINK)⠛⢈⢳⣿⣮⢿⣷⣿⣷⢠$(BLUE)⡛⢿⣶⣄⡀⠀⠀⠀⠁⣠⣤⣶⣶⣾⣷⣶⣄$(PURPLE)⠂⠀⠄⠀⠀⢈⢘⡊⣿⣿⠀⡄⢡⠀⠀⠡⢀⠈⠄⠸$(GOLD)⣜⣷⣾⣿⣿⣿⣿⡶⢩⠆$(GREEN)⣀⣤⣶⣦⣕⠂⡈⠆$(GOLD)⢸⣿⡌⠁⢀⢠⡩⠗⡀$(DARK_BLUE)⠙⠚⠶⢹⠳⠖⠋⠓⢠⣤⣖⢍⣢⢀⠠⡶⢊⣀⠀⠀⠀⠀$(GOLD)⠤⠘⠛\n"
	@printf "⠀⠀$(YELLOW)⠘⠀⡘⣿⠸⠃⠁⠀⠘⢬⠈⠀⢐⢯⠬⡜⠃$(PINK)⠉⡄⡧⢻⢿⣧⢹⣿⢿⠏⢿⡀$(BLUE)⠈⠋⠀⠀⠀⣀⣿⣿⣿⣿⣿⣿⣿⣟⢿⣷⡄$(PURPLE)⠀⠀⠀⡿⠐⠁⢾⡿⣘⠁⣰⡆⢰⠀⠀⠂⢉⢎$(GOLD)⣾⣿⣿⠿⠿⠟⢋⡁$(GREEN)⢳⣿⣿⢙⣏⢿⡿⠀⠀⠀$(GOLD)⡾⠉⠀⠰⢊⠁⠀⠀⠘⢤⡀⢀⡀$(DARK_BLUE)⠐⠃⠀⠻⣱⣌⠛⢷⣮⡠⠉⡠$(GOLD)⡽⣿⣿⣿⡿⠿⠿⠓⠒\n"
	@printf "⠀⠀$(YELLOW)⠀⠀⠀⠘⠀⠀⠀⠀⠰⠎⠃⠀⠮⢍⣊$(PINK)⠀⡆⡀⠁⢉⣀⠸⢻⠅⢿⠘⠀⠘⡇$(BLUE)⠀⠀⠀⠀⠀⢼⣿⢟⡡⣦⣤⠤⠐⣈⢻⡏⠐$(PURPLE)⠀⠀⢸⣿⣷⡚⢘⣿⣯⡴⡖⠂⢀⠀⠀⡀⡦$(GOLD)⣿⢟⡵⠚⢉$(GREEN)⣤⣷⡿⣣⡐⡠⠹⣾⣿⣦⡀⠀⠀$(GOLD)⣌⡵⣶⢫⠁⢇⡂⠀⣠⣄⡄⠒⢉⠀⠀⠀⠀⠀$(DARK_BLUE)⡀⢀⣀⣂⣐⣾⣦⡃$(GOLD)⢷⠉⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(GREEN)⠠⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(PINK)⢠⢆⢇⠉⠄⠚⢷⡀⠈⠄⠈⠀⢠⡄⠀$(BLUE)⠀⠀⠀⠀⠀⢨⣿⣿⣯⣱⠊⣟⣥⣧⣾⢛⢷⣄⠀$(PURPLE)⠀⠹⣿⡷⢾⣿⢿⣿⣷⣤⠾⢀⣀⣐$(GOLD)⠉⠡⢁$(GREEN)⣤⣾⣿⢟⣯⣿⡿⠛⠀⠥⠙⠫⢱⡒⠒$(GOLD)⠈⢻⠟⣰⠃⠀⣊⡠⠜⠛⢣⣄⠴⠾⠓$(DARK_BLUE)⠤⢔⡬⣲⢭⣛⡼⡣⠟⠳⢻⠃$(GOLD)⢸⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(GREEN)⠀⠀⠐⡂⠄⣀⢆⣭⣿⣤⣤⠃⠆⠀$(PINK)⠠⣾⣿⣆⡄⢀⡶⠁⠀⡀⠀⠀⠆⠉⠐$(BLUE)⠀⠀⡠⠄⡀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣏⠼⠢⠻⣧⡁$(PURPLE)⠀⠈⢻⡕⣽⢯⠿⣉⢁⣽⣿⠿⠋$(GREEN)⣠⣷⣿⣿⢟⣵⠿⢋⠡⢀⢐⣠⡆⠀⠀⠀⠃⠁⠂⢀$(GOLD)⠘⠃⠒⠈⢩⠀$(DARK_BLUE)⣚⡍⢛⣭⢡⢪⢋⡟⠙⠒⠃⠛⠈⠁⢀⡤⠄⠒⠀$(GOLD)⢸⠁⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(GREEN)⠀⢠⡾⢋⠾⢡⠀⡿⡟⠺⢶⣅⠐⠄$(PINK)⠑⢻⡿⠚⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀$(BLUE)⠀⠀⢴⡀⠈⠲⣙⠻⢿⣿⣿⣿⣿⣿⣿⢦⣴⡤⠀$(PURPLE)⠀⠀⠀⠀⠈⣿⠠⠒⢢⡴⢶⠞$(GREEN)⢄⡖⣿⣿⢟⢱⡟⢁⠒⠌⣀⡾⠛⠿⡦⢄⠀⠀⠩⠦⢤⠉$(GOLD)⠠⡀⠀⠀⢸⠄$(DARK_BLUE)⠡⠠⠏⠹⠂⠀⠈⣀⠤⠠⠤⠀⠀⠀⠀⠃⠀⠀⠀$(GOLD)⢸⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀⠀$(GREEN)⠃⠁⠈⠘⠀⠀⠁⠁⠀⠀⠈⠁⠁⠀$(PINK)⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(BLUE)⠀⠀⠈⠀⠀⠀⠀⠀⠀⠉⠛⠙⠋⠉⠐⠉⠁⠀$(PURPLE)⠀⠀⠀⠀⠀⠂⠘⠀⠐⠈⠉⠃⠀$(GREEN)⠚⠉⠛⠁⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(DARK_BLUE)⠚⠁⠀⠁⠀⠀⠀⠀⠀⠀$(GOLD)⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀$(RESET)\n"


-include $(DEPS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(OBJS_DIR)
	@printf "$(LBLUE)[Compilation]$(RESET) In progress... $(GREEN)$<" && \
	$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@ && \
	printf "\r$(LBLUE)[Compilation]$(RESET) Completed   ... $(GREEN)$<" && \
	printf " $(LBLUE)[$(RESET)$(CC)$(LBLUE)/]$(RESET)\n"


clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
