#pragma once
#include<vector>
#include <SFML/Graphics.hpp>


class Animation
{
	struct Clip
	{
		std::vector<sf::Texture> textures;
		bool loop;
	};

public:

	void Update();

	Animation(sf::Sprite* newAnimatedSprite, std::string newBaseFilePath, float framesPerSecond, std::string newFilePath, std::string newFileType);

	void AddClip(std::string clipName, int numFrames, bool shouldLoop = false);

	void Play();
	void Play(std::string clipToPlay);
	void Stop();
	void Pause();

private:

	// Data
	sf::Sprite* animatedSprite;
	std::string fileType;
	std::string baseFilePath;
	std::string filePath;
	float framesPerSecond;
	Clip* currentClip;
	std::map<std::string, Clip> animations;
	int currentFrame;
	sf::Time timePerFrame;
	sf::Clock animationClock;
	bool isPlaying;


};

