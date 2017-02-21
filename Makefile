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

TARGET_EXEC ?= nm

BUILD_DIR ?= ./build
SRC_DIRS ?= ./srcs
# INC_DIR ?= 


SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# INC_DIRS := $(shell find $(INC_DIR) -type d)
INC_FLAGS := $(addprefix -I, ./includes ./includes/sys/ ./lib/libft/includes \
./lib/option/includes)

# CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -Wall -Werror -Wextra
CFLAGS ?= $(INC_FLAGS) -MMD -MP -Wall -Werror -Wextra

# Extra flags to give to compilers when they are supposed to invoke the linker, ‘ld’, such as -L.
# Libraries (-lfoo) should be added to the LDLIBS variable instead.
LDFLAGS ?= -L lib/libft -lft -L lib/option -loption

all: $(TARGET_EXEC) $(OBJS)

# $(TARGET_EXEC): $(OBJS)
# 	ar rc $(TARGET_EXEC) $(OBJS)
# 	ranlib $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

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

fclean: clean
	$(RM) $(TARGET_EXEC)

re: fclean
	make

norme:
	norminette $(SRC_DIRS) $(INC_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
