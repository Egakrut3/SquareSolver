CXX="g++"
SRC_DIR="./src"
INCLUDE_DIR="./include"

SRC="$SRC_DIR/Common.cpp $SRC_DIR/Option_manager.cpp $SRC_DIR/User_error_handler.cpp   \
$SRC_DIR/Calculation_constants.cpp $SRC_DIR/Coefficient_scaner.cpp $SRC_DIR/Solver.cpp \
$SRC_DIR/Solver_test.cpp $SRC_DIR/Roots_printer.cpp $SRC_DIR/Source.cpp"

TARGET="quadratic"

FLAGS="-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code \
-Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall   \
-g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security            \
-Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor              \
-Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing                       \
-Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE              \
-D__USE_MINGW_ANSI_STDIO"

echo "Compilation start"
$CXX $SRC -o $TARGET $FLAGS -I $INCLUDE_DIR
echo "Compilation end"

# echo "Program start"
# ./$TARGET.exe
# echo "Program end"
