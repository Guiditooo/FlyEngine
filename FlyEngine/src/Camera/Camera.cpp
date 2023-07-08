#include "Camera.h"

Camera::Camera()
{
	orthographic = false;
}

Camera::~Camera()
{
}

void Camera::SwitchMode()
{
	orthographic = !orthographic;
}
