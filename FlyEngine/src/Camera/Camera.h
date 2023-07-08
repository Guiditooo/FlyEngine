#ifndef CAMERA_H
#define CAMERA_H

#include <Exports/Exports.h>
#include <Entity/Entity.h>

class /*FLY_API*/ Camera : public Entity
{
private:
	bool orthographic;

public:
	Camera();
	~Camera();

	void SwitchMode();

};


#endif // !CAMERA_H
