CC := clang

CFLAGS := \
	-std=c99 \
	-fshort-enums \
	-ftrivial-auto-var-init=zero \
	-W \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Wconversion \
	-Wimplicit-fallthrough \
	-Wmissing-prototypes \
	-Wshadow \
	-Wstrict-prototypes \
	-Wno-unused-parameter

NAME := clox
HEADERS := $(wildcard *.h)
SOURCES := $(wildcard *.c)

BUILD_DIR := out
BUILD_DIR_DEBUG := $(BUILD_DIR)/debug
BUILD_DIR_RELEASE := $(BUILD_DIR)/release

DEBUG_OBJECTS += $(addprefix $(BUILD_DIR_DEBUG)/, $(SOURCES:.c=.o))
RELEASE_OBJECTS += $(addprefix $(BUILD_DIR_RELEASE)/, $(SOURCES:.c=.o))

all: debug tidy

debug: CFLAGS += -fsanitize=address,undefined -g3 -DDEBUG
debug: $(BUILD_DIR_DEBUG)/$(NAME)

release: CFLAGS += -O1 -flto -fwrapv
release: $(BUILD_DIR_RELEASE)/$(NAME)

$(BUILD_DIR_DEBUG)/$(NAME): $(DEBUG_OBJECTS) | $(BUILD_DIR_DEBUG)
	@ printf "LD $@\n"
	@ $(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR_RELEASE)/$(NAME): $(RELEASE_OBJECTS) | $(BUILD_DIR_RELEASE)
	@ printf "LD $@\n"
	@ $(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR_DEBUG)/%.o: %.c $(HEADERS) | $(BUILD_DIR_DEBUG)
	@ printf "CC $@\n"
	@ $(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR_RELEASE)/%.o: %.c $(HEADERS) | $(BUILD_DIR_RELEASE)
	@ printf "CC $@\n"
	@ $(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR_DEBUG):
	@ mkdir -p $@

$(BUILD_DIR_RELEASE):
	@ mkdir -p $@

tidy: $(HEADERS) $(SOURCES)
	@ clang-format -i $^

clean:
	@ rm -rf $(BUILD_DIR)

.PHONY: all debug release tidy clean
