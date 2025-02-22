#ifndef ANIMATION_H
#define ANIMATION_H

#include "Frame/Frame.h"
#include <vector>

namespace FlyEngine
{

	class Animation
	{
	public:
		Animation();
		~Animation();

		void Update();

		void AddFrame(float frameX, float frameY,
			float frameWidth, float frameHeigth,
			float textureWidth, float textureHeigth,
			float durationInSecs);

		void AddFrame(float frameX, float frameY,
			float frameWidth, float frameHeigth,
			float textureWidth, float textureHeigth,
			float durationInSecs,
			int frameCount);

		int CurrentFrame();

		std::vector<Frame>& GetFrames();

	private:
		int currentFrame;
		float currentTime;
		float length;
		std::vector<Frame> frames;
	};

}
#endif