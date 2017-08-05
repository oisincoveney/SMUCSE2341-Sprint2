#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "output.h"

int runCatchTests(int argc, char* const argv[])
{
    return Catch::Session().run(argc, argv);
    return 0;
}

int main(int argc, char* argv[])
{
    if(argc == 6)
    {
        Output o(argv[1], argv[2], argv[3], argv[4]);
        o.print(argv[5]);
        return 0;
    }
    else
    return runCatchTests(argc, argv);

}
