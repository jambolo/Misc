#include "Misc/Assert.h"
#include "Misc/Etc.h"
#include "Misc/Random.h"
#include "Misc/exceptions.h"
#include <cassert>
#include <memory>

class ConstructorFailedExceptionTester
{
public:
    ConstructorFailedExceptionTester(bool fail)
    {
        if (fail)
        {
            throw ConstructorFailedException();
        }
    }
};

int main(int argc, char ** argv)
{
    // Test random number generator

    Random rng(0);
    RandomFloat frng(0);
    unsigned int i = rng();
//    float f        = frng();

    // Test asserts

    assert_limits(0, i, 0xffffffffffffffff);
    assert_memset_valid(&i, 0);

    // Test elementsof

    int elementsofTester[314] = { 0 };

    assert(elementsof(elementsofTester) == 314);

    // Test exceptions

    ConstructorFailedExceptionTester cfet(true);
    
    return 0;
}
