#include "Frame.h"

namespace FlyEngine
{

	Frame::Frame(void){}
	Frame::~Frame(void) {}

	Frame::Frame(FrameCoords start, FrameCoords end)
	{
		coords[0].x = start.x;
		coords[0].y = start.y;

		coords[1].x = end.x;
		coords[1].y = start.y;

		coords[2].x = start.x;
		coords[2].y = end.y;

		coords[3].x = end.x;
		coords[3].y = end.y;

	}

	Frame::Frame(float x0, float y0, float x1, float y1)
	{
		coords[0].x = x0;
		coords[0].y = y0;

		coords[1].x = x1;
		coords[1].y = y0;

		coords[2].x = x0;
		coords[2].y = y1;

		coords[3].x = x1;
		coords[3].y = y1;
	}

}