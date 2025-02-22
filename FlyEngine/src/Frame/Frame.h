#ifndef FRAME_H
#define FRAME_H

namespace FlyEngine
{

	struct FrameCoords
	{
		float x = 0;
		float y = 0;
	};

	class Frame
	{
	public:
		Frame();
		Frame(FrameCoords start, FrameCoords end);
		Frame(float x0, float y0, float x1, float y1);
		~Frame();
		FrameCoords coords[4];
	};

}

#endif
