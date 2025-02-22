#include "Animation.h"

#include "Timer/Timer.h"

namespace FlyEngine
{

	Animation::Animation()
	{
		currentTime = 0;
		currentFrame = 0;
		length = 1000;
	}

	Animation::~Animation(void) {}

	void Animation::Update() 
	{
		currentTime += Timer::DeltaTime();

		while (currentTime > length) 
		{
			currentTime -= length;
		}

		float frameLength = length / frames.size();
		currentFrame = static_cast<int>(currentTime / frameLength);
	}

	void Animation::AddFrame(float frameX, float frameY,
		float frameWidth, float frameHeigth,
		float textureWidth, float textureHeigth,
		float durationInSecs)
	{
		length = durationInSecs * 1000;

		Frame frame = Frame(
			{ frameX / textureWidth, frameY / textureHeigth },
			{ (frameX + frameWidth) / textureWidth, (frameY + frameHeigth) / textureHeigth }
		);

		/*
		frame.coords[0].x = (frameX / textureWidth);
		frame.coords[0].y = (frameY / textureHeigth);

		frame.coords[1].x = ((frameX + frameWidth) / textureWidth);
		frame.coords[1].y = (frameY / textureHeigth);

		frame.coords[2].x = (frameX / textureWidth);
		frame.coords[2].y = ((frameY + frameHeigth) / textureHeigth);

		frame.coords[3].x = ((frameX + frameWidth) / textureWidth);
		frame.coords[3].y = ((frameY + frameHeigth) / textureHeigth);
		*/

		frames.push_back(frame);
	}

	void Animation::AddFrame(float frameX, float frameY,
		float frameWidth, float frameHeigth,
		float textureWidth, float textureHeigth,
		float durationInSecs,
		int frameCount)
	{
		length = durationInSecs * 1000;

		float frameXIndex = 0;

		for (int i = 0; i < frameCount; i++) 
		{
			Frame frame = Frame(
				(frameX + frameXIndex) / textureWidth,
				frameY / textureHeigth,
				((frameX + frameXIndex) + frameWidth) / textureWidth,
				(frameY + frameHeigth) / textureHeigth
			);

			/*
			frame.coords[0].x = ((frameX + frameXIndex) / textureWidth);
			frame.coords[0].y = (frameY / textureHeigth);

			frame.coords[1].x = (((frameX + frameXIndex) + frameWidth) / textureWidth);
			frame.coords[1].y = (frameY / textureHeigth);

			frame.coords[2].x = ((frameX + frameXIndex) / textureWidth);
			frame.coords[2].y = ((frameY + frameHeigth) / textureHeigth);

			frame.coords[3].x = (((frameX + frameXIndex) + frameWidth) / textureWidth);
			frame.coords[3].y = ((frameY + frameHeigth) / textureHeigth);
			*/

			frames.push_back(frame);
			frameXIndex += frameWidth;
		}
	}

	int Animation::CurrentFrame()
	{
		return currentFrame;
	}

	std::vector<Frame>& Animation::GetFrames() 
	{
		return frames;
	}


}