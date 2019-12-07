# Release targets
TARGET_RELEASE ?= bin/acpu-sim
TARGET_DEBUG ?= bin/acpu-sim-debug
TARGET_TEST ?= bin/test

# Directory controls
OBJ_DIR ?= build
SRC_DIR ?= src
RESOURCE_DIR ?= data

# Compiler configuration
GCC := gcc
FLAGS_BASE ?=
FLAGS_DEBUG ?= $(FLAGS_BASE) -g
FLAGS_RELEASE ?= $(FLAGS_BASE) -O3
INC_FLAGS ?= -Iinclude -Isrc
LD_FLAGS ?=

# Enumerate sources
SRCS_NOMAIN := $(shell find $(SRC_DIR) -mindepth 2 -name *.c)
SRCS_TEST := $(SRCS_NOMAIN) src/test.c
SRCS_SIM := $(SRCS_NOMAIN) src/sim.c
OBJS_RELEASE := $(SRCS_SIM:%=$(OBJ_DIR)/release/%.o)
OBJS_DEBUG := $(SRCS_SIM:%=$(OBJ_DIR)/debug/%.o)
OBJS_TEST := $(SRCS_TEST:%=$(OBJ_DIR)/test/%.o)
DEPS := $(OBJS_DEBUG:.o=.d) $(OBJS_RELEASE:.o=.d) $(OBJS_TEST:.o=.d)

# Release object compilation
$(OBJ_DIR)/release/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	$(GCC) $(FLAGS_RELEASE) $(INC_FLAGS) -c $< -o $@

# Debug object compilation
$(OBJ_DIR)/debug/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	$(GCC) $(FLAGS_DEBUG) $(INC_FLAGS) -c $< -o $@

# Test object compilation
$(OBJ_DIR)/test/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	$(GCC) $(FLAGS_DEBUG) $(INC_FLAGS) -c $< -o $@

# Release target
release: copy_resources $(OBJS_RELEASE)
	@$(MKDIR_P) $(dir $(TARGET_RELEASE))
	$(GCC) $(OBJS_RELEASE) -o $(TARGET_RELEASE) $(LD_FLAGS)

# Release target
debug: copy_resources $(OBJS_DEBUG)
	@$(MKDIR_P) $(dir $(TARGET_DEBUG))
	$(GCC) $(OBJS_DEBUG) -o $(TARGET_DEBUG) $(LD_FLAGS)

# Test target
test: copy_resources $(OBJS_TEST)
	@$(MKDIR_P) $(dir $(TARGET_TEST))
	$(GCC) $(OBJS_TEST) -o $(TARGET_TEST) $(LD_FLAGS)

# Collect all resource files in the bin directory
copy_resources:
	@$(MKDIR_P) $(dir $(TARGET_RELEASE))
	cp -r $(RESOURCE_DIR) $(dir $(TARGET_RELEASE))

# Build everything
all: release debug test

# Clean, be careful with this
.PHONY: clean
clean:
	@$(RM) -rv $(OBJ_DIR)

# Include dependencies
-include $(DEPS)

# Make directory
MKDIR_P ?= mkdir -p
