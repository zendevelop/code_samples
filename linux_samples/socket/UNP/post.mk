mod_c99_objs		:= $(mod_c99_srcs:%.c=%.o)
mod_cpp_objs		:= $(mod_cpp_srcs:%.cpp=%.o)

mod_c99_flags		+= $(addprefix -I, $(mod_c99_incs))
mod_cpp_flags		+= $(addprefix -I, $(mod_cpp_incs))

mod_out_lib_name	:= $(project_root)/$(OUT_LIB_DIR)/lib$(mod_lib_name).a
mod_out_c99_objs	:= $(addprefix $(project_root)/$(OUT_OBJ_DIR)/$(mod_lib_name)/, $(mod_c99_objs))
mod_out_cpp_objs	:= $(addprefix $(project_root)/$(OUT_OBJ_DIR)/$(mod_lib_name)/, $(mod_cpp_objs))

mod_out_dir_names	:= $(dir $(mod_out_lib_name))
mod_out_dir_names	+= $(dir $(mod_out_c99_objs))
mod_out_dir_names	+= $(dir $(mod_out_cpp_objs))
mod_out_dir_names	:= $(shell echo $(mod_out_dir_names) | sed 's/ /\n/g' | sort -u)

$(mod_out_lib_name) :  $(mod_out_dir_names) $(mod_out_c99_objs) $(mod_out_cpp_objs)
	@rm -f $@
	$(TOOL_CHAIN_AR) $(tool_chain_ar_flags) -o $@ $(mod_out_c99_objs)

$(mod_out_dir_names) :
	mkdir -p $@

$(mod_out_c99_objs) : $(project_root)/$(OUT_OBJ_DIR)/$(mod_lib_name)/%.o : %.c
	$(TOOL_CHAIN_C99) $(mod_c99_flags) -o $@ $^

$(mod_out_cpp_objs) : $(project_root)/$(OUT_OBJ_DIR)/$(mod_lib_name)/%.o : %.cpp
	$(TOOL_CHAIN_CPP) $(mod_cpp_flags) -o $@ $^

clean:
	rm -rf (mod_out_c99_objs)
	rm -rf (mod_out_cpp_objs)
	rm -rf (mod_out_lib_name)
	rm -rf (mod_out_dir_names)
