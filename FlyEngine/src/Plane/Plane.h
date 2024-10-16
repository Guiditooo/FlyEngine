#ifndef PLANE_H
#define PLANE_H

#include "glm/glm.hpp"
#include "Exports/Exports.h"

namespace FlyEngine
{

class FLY_API Plane 
{
private:
    glm::vec3 normal; // Vector normal al Plane
    float distance;  // Distancia desde el origen
public:

    Plane();
    Plane(glm::vec3 normal, float distance);
    Plane(glm::vec3 normal, glm::vec3 point);
    Plane(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

    float GetDistanceToPoint(glm::vec3 point);
    bool IsPointInFront(glm::vec3 point);
};

#endif // !PLANE_H

}