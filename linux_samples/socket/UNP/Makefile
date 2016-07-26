BIN_NAME	:= all 

include ./prev.mk

SAMPLE_MODS	:= sample

ALL_MODS	:= unpwrap
#ALL_MODS	+= socket	

ALL_LIBS	:= $(addsuffix .a, $(addprefix $(OUT_LIB_DIR)/lib, $(ALL_MODS)))
SAMPLE_LIBS := $(addsuffix .a, $(addprefix $(OUT_LIB_DIR)/lib, $(SAMPLE_MODS)))

BIN_INCS	:= unpwrap 
#BIN_INCS	+= routines/include

BIN_LDFLAGS	:= _out/lib
BIN_LDLIBS		:= $(SAMPLE_MODS)
BIN_LDLIBS		+= $(ALL_MODS)

.PHONY : $(BIN_NAME) clean info libs sam $(ALL_MODS)

# ---------------------------------------------------------------
# to generate binary, libraries.
# ---------------------------------------------------------------
$(BIN_NAME) : $(SAMPLE_LIBS) $(ALL_LIBS)
	mkdir -p $(OUT_BIN_DIR)
	$(TOOL_CHAIN_C99) -o $(OUT_BIN_DIR)/$@ $(addprefix -L, $(BIN_LDFLAGS)) $(addprefix -l, $(BIN_LDLIBS))
	cp $(OUT_BIN_DIR)/$@ $@

libs : $(ALL_LIBS)

$(ALL_LIBS) : $(OUT_LIB_DIR)/lib%.a :%
	make -C $^ project_root=$(shell echo $^ | sed 's#[a-z_1-8]*#\.\.#g')

sam : $(SAMPLE_LIBS)
	mkdir -p $(OUT_BIN_DIR)
	$(TOOL_CHAIN_C99) -o $(OUT_BIN_DIR)/$@ $(addprefix -L, $(BIN_LDFLAGS)) $(addprefix -l, $(BIN_LDLIBS))
	cp $(OUT_BIN_DIR)/$@ $@

$(SAMPLE_LIBS) : $(OUT_LIB_DIR)/lib%.a :%
	make -C $^ project_root=$(shell echo $^ | sed 's#[a-z_1-8]*#\.\.#g')

clean:
	rm -rf $(OUT_OBJ_DIR)
	rm -rf $(OUT_LIB_DIR)
	rm -rf $(OUT_BIN_DIR)
info:
	@echo
	@echo -e "================================================================"
	@echo -e "information of this build system."
	@echo -e "================================================================"

	@echo -e "TOOL_CHAIN_DIR    = $(TOOL_CHAIN_DIR)"
	@echo -e "TOOL_CHAIN_PREFIX = $(TOOL_CHAIN_PREFIX)"

	@echo -e "OUT_DEP_DIR       = $(OUT_DEP_DIR)"
	@echo -e "OUT_OBJ_DIR       = $(OUT_OBJ_DIR)"
	@echo -e "OUT_LIB_DIR       = $(OUT_LIB_DIR)"
	@echo -e "OUT_BIN_DIR       = $(OUT_BIN_DIR)"

	@echo -e "OOL_CHAIN_C99    = $(TOOL_CHAIN_C99)"
	@echo -e "TOOL_CHAIN_CPP    = $(TOOL_CHAIN_CPP)"
	
	@echo -e "TOOL_CHAIN_LD     = $(TOOL_CHAIN_LD)"
	@echo -e "TOOL_CHAIN_AR     = $(TOOL_CHAIN_AR)"	
	@echo
	@echo

