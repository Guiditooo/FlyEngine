#include "Commons.h"
#include <stdlib.h>

float FLY_ENGINE::Commons::RandomFloat(float initRange, float endRange)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = endRange - initRange;
    float r = random * diff;
    return initRange + r;
}
