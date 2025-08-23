//Solves square equation of form ax2 + bx + c = 0
//is_nil - checks whether real number equal 0 or not (taking into account the inaccuracy)
//

#include "Flag_manager.h"
#include "Input.h"
#include "Solve.h"
#include "Output.h"

int main(int const argc, char *argv[])
{
    set_config(argc, argv);
    make_output(solve(get_input()));

    return 0;
}
