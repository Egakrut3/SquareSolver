//Solves square equation of form ax2 + bx + c = 0
//is_nil - checks whether real number equal 0 or not (taking into account the inaccuracy)
//

#include "Common.h"
#include "Input.h"
#include "Solve.h"
#include "Output.h"

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        set_eps(strtold(argv[1], nullptr));
    }
    make_output(solve(get_input()));

    return 0;
}
