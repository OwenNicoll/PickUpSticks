#include "Animation.h"

void Animation::Update()
{
	// Process Animation

	//sf::Time timePassedThisFrame = animationClock.getElapsedTime();
	//if (timePassedThisFrame >= timePerFrame)
	//{
	//	animationClock.restart();

	//	// Go to the next frame of the animation
	//	++currentFrame;
	//	if (currentFrame >= currentClip->textures.size())
	//	{
	//		currentFrame = 0;
	//	}
	//	animatedSprite->setTexture((*currentClip)[currentFrame]);

	//}
}

Animation::Animation(sf::Sprite* newAnimatedSprite, std::string newBaseFilePath, float framesPerSecond, std::string newFilePath, std::string newFileType)
	: animatedSprite(newAnimatedSprite)
	,baseFilePath (newBaseFilePath)
	,fileType (newFileType)
	,currentClip (nullptr)
	,animations()
	,currentFrame(0)
	,timePerFrame(sf::seconds(1/framesPerSecond))
	
{
}

void Animation::AddClip(std::string clipName, int numFrames, bool shouldLoop)
{
	Clip newClip;

	for (int i = 0; i < numFrames; ++i)
	{
		newClip.textures.push_back(sf::Texture());
		newClip.textures[i].loadFromFile(baseFilePath + "_" + clipName + "_" + std::to_string((int)(i + 1)) + fileType);
	}

	newClip.loop = shouldLoop;

	// Add the clip to our map
	animations[clipName] = newClip;
}

void Animation::Play()
{
	
}

void Animation::Play(std::string clipToPlay)
{
	currentClip = &animations[clipToPlay];
	isPlaying = true;
}

void Animation::Stop()
{
	isPlaying = false;
	currentFrame = 0;
}

void Animation::Pause()
{
	isPlaying = false;
}
