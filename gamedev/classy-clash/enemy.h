#include "character.h"
#include "raylib.h"

class Enemy : public BaseCharacter {
	public:
		Enemy(Texture2D idleTexture, Texture2D runTexture, int frames, Vector2 pos);
		void setTarget(Character* character);
	protected:
		virtual void move() override;
	private:
		Character* target;
};
