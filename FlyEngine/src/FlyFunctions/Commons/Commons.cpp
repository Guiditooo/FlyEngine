#include "Commons.h"
#include <stdlib.h>

namespace FlyEngine
{

    namespace Utils
    {

        float Commons::RandomFloat(float initRange, float endRange)
        {
            float random = ((float)rand()) / (float)RAND_MAX;
            float diff = endRange - initRange;
            float r = random * diff;
            return initRange + r;
        }

    }

}