#include "base_character.h"

class Enemy : public BaseCharacter {
	public:
		Enemy(Texture2D idleTexture, Texture2D runTexture, int frames, int windowWidth, int windowHeight);
	protected:
		virtual void setDestination(int windowWidth, int windowHeight) override;
		virtual void move() override;
};
