#include "misc/Assert.h"
#include "misc/Etc.h"
#include "misc/Random.h"
#include "misc/exceptions.h"
#include <cassert>
#include <memory>

class ConstructorFailedExceptionTester
{
public:
    ConstructorFailedExceptionTester(bool fail)
    {
        if (fail) {
            throw ConstructorFailedException();
        }
    }
};

void main()
{
    // Test random number generator

    Random rng(0);
    RandomFloat frng(0);
    unsigned int i = rng();
    float f        = frng();

    // Test asserts

    assert_limits(0, i, 0xffffffffffffffff);
    assert_memset_valid(&i, 0);

    // Test elementsof

    int elementsofTester[314] = { 0 };

    assert(elementsof(elementsofTester) == 314);

    // Test exceptions

    ConstructorFailedExceptionTester cfet(true);
}
