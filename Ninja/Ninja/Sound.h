#pragma once

#include <irrlicht.h>
#include <irrKlang.h>

class Game;

/**
* Represents sound of any supported format. 
* Can be played or stopped independently of other sounds.
*/

class Sound
{
public:
	
	/**
	* Initializes sound using provided path to file.
	*/
	Sound(Game* game, const irr::io::path& filename, bool looped = false, bool stopped = true);
	~Sound(void);

	/**
	* Plays sound.
	* @param stoppable Should sound play uninterruptibly until end?
	*/
	void play(bool stoppable = true);
	void stop();

private:

	/**
	* @param _game Game instance.
	* @param _filename Path to sound file.
	* @param _looped Should sound be repeated?
	* @param _stopped If false sound will be played after creation.
	*/
	Game* _game;
	irr::io::path _filename;
	bool _looped;
	bool _stopped;
	irrklang::ISound* _sound;
};