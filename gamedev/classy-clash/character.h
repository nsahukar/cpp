#ifndef CHARACTER_H
#define CHARACTER_H

#include "base_character.h"
#include "raylib.h"

class Character : public BaseCharacter {
	public:
		Character(Texture2D idleTexture, Texture2D runTexture, int frames, int windowWidth, int windowHeight);
	protected:
		virtual void move() override;
};

#endif
