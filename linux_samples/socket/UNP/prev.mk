PLATFORM := linux

OUT_DEP_DIR			:= _out/dep
OUT_OBJ_DIR			:= _out/obj
OUT_LIB_DIR			:= _out/lib
OUT_BIN_DIR			:= _out/bin

TOOL_CHAIN_DIR		:=
TOOL_CHAIN_PREFIX	:=

TOOL_CHAIN_C99		:=$(TOOL_CHAIN_DIR)$(TOOL_CHAIN_PREFIX)gcc
TOOL_CHAIN_CPP		:=$(TOOL_CHAIN_DIR)$(TOOL_CHAIN_PREFIX)g++
TOOL_CHAIN_LD		:=$(TOOL_CHAIN_DIR)$(TOOL_CHAIN_PREFIX)g++
TOOL_CHAIN_AR 		:=$(TOOL_CHAIN_DIR)$(TOOL_CHAIN_PREFIX)ar

# define golbal cpp flags, c99 flags, ar flags
tool_chain_c99_flags	:= -c -g -O2 -Wall -Wmissing-declarations
tool_chain_cpp_flags	:= $(TOOL_CHAIN_C99_FLAGS)
tool_chain_ld_flags		:= --shared
tool_chain_ar_flags		:= -rs