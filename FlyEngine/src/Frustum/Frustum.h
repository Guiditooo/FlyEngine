#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Plane/Plane.h"

namespace FlyEngine
{
    class Transform;

    namespace FlyFrustrum
    {
        struct FLY_API Frustum
        {
            Plane topFace;
            Plane bottomFace;
            Plane rightFace;
            Plane leftFace;
            Plane farFace;
            Plane nearFace;
        
            Frustum createFrustumFromCamera(Transform camT, float aspect, float fovY, float zNear, float zFar);
        };
    }
}

#endif // !FRUSTUM_H
