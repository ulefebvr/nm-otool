# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/26 18:52:01 by ulefebvr          #+#    #+#              #
#    Updated: 2016/12/26 18:52:05 by ulefebvr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET_EXEC1 ?= nm
TARGET_EXEC2 ?= otool

BUILD_DIR ?= ./build
SRC_DIRS1 ?= ./srcs/
SRC_DIRS2 ?= ./srcs/
# INC_DIR ?= ./includes


SRCS1 := $(shell find $(SRC_DIRS1) -name '*.cpp' -or -name '*.c' -or -name '*.s' | grep -v "/otool/")
SRCS2 := $(shell find $(SRC_DIRS2) -name '*.cpp' -or -name '*.c' -or -name '*.s' | grep -v "/nm/")
OBJS1 := $(SRCS1:%=$(BUILD_DIR)/%.o)
OBJS2 := $(SRCS2:%=$(BUILD_DIR)/%.o)
OBJS := $(OBJS1) $(OBJS2)
DEPS := $(OBJS:.o=.d)

# INC_DIRS := $(shell find $(INC_DIR) -type d)
INC_FLAGS := $(addprefix -I, ./includes ./includes/macosxheader ./lib/libft/includes ./lib/option/includes)

# CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -Wall -Werror -Wextra
CFLAGS ?= $(INC_FLAGS) -MMD -MP -Wall -Werror -Wextra

# Extra flags to give to compilers when they are supposed to invoke the linker, ‘ld’, such as -L.
# Libraries (-lfoo) should be added to the LDLIBS variable instead.
LDFLAGS ?= -L lib/libft -lft -L lib/option -loption

DEPENDENCE_RELINK = ./lib ./lib/libft.a ./lib/liboption.a

all: $(TARGET_EXEC1) $(TARGET_EXEC2) $(OBJS) $(DEPENDENCE_RELINK)

# $(TARGET_EXEC): $(OBJS)
# 	ar rc $(TARGET_EXEC) $(OBJS)
# 	ranlib $(TARGET_EXEC)

$(TARGET_EXEC2): $(OBJS2) $(DEPENDENCE_RELINK)
	$(CC) -o $@ $(OBJS2) $(LDFLAGS)

$(TARGET_EXEC1): $(OBJS1) $(DEPENDENCE_RELINK)
	$(CC) -o $@ $(OBJS1) $(LDFLAGS)

$(DEPENDENCE_RELINK):
	make -C lib/libft
	make -C lib/option

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean fclean re norme

clean:
	$(RM) -r $(BUILD_DIR)
	make clean -C lib/libft
	make clean -C lib/option

fclean: clean
	$(RM) $(TARGET_EXEC1) $(TARGET_EXEC2)
	make fclean -C lib/libft
	make fclean -C lib/option

re: fclean
	make

norme:
	norminette $(SRC_DIRS) $(INC_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
