BIN_DIR = ./bin
BIN_SUF = .o
make_bin_path = $(addprefix $(BIN_DIR), $(addsuffix $(BIN_SUF), $(1)))

SRC_DIR = ./src
SRC_SUF = .cpp
make_src_path = $(addprefix $(SRC_DIR), $(addsuffix $(SRC_SUF), $(1)))

H_DIR = ./include

CXX = g++
CXX_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline   \
-Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default  \
-Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy \
-Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op                      \
-Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith          \
-Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits           \
-Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE -D__USE_MINGW_ANSI_STDIO

TARGET = $(addprefix $(BIN_DIR), /square.exe)
OBJ = /Colored_printf /Common /Calculation_constants /Option_manager /User_error_handler \
	  /Coefficient_scaner /Solver /Solver_test /Roots_printer /Source

make_object = $(call make_bin_path, $(1)) : $(call make_src_path, $(1)); \
@$(CXX) $(CXX_FLAGS) -c $(call make_src_path, $(1)) -I $(H_DIR) -o $(call make_bin_path, $(1))

.PHONY : all prepare clean documentation

all : prepare $(call make_bin_path, $(OBJ))
	@$(CXX) $(CXX_FLAGS) $(call make_bin_path, $(OBJ)) -o $(TARGET)
	@echo Compilation end

prepare :
	@mkdir -p bin

#TODO - Don't works

$(call make_object, /Colored_printf)

$(call make_object, /Common)

$(call make_object, /Calculation_constants)

$(call make_object, /Option_manager)

$(call make_object, /User_error_handler)

$(call make_object, /Coefficient_scaner)

$(call make_object, /Solver)

$(call make_object, /Solver_test)

$(call make_object, /Roots_printer)

$(call make_object, /Source)

clean:
	@rm -rf bin
	@rm -rf html

documentation: Doxyfile
	@doxygen Doxyfile
