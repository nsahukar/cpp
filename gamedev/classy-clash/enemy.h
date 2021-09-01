#include "character.h"
#include "raylib.h"

class Enemy : public BaseCharacter {
	public:
		Enemy(Texture2D idleTexture, Texture2D runTexture, int frames, Vector2 pos, float speed);
		virtual void tick(float dT, float updateTime) override;
		void setTarget(Character* character);
	protected:
		virtual void move() override;
	private:
		Character* target;
		float damagePerSec{10.f};
		float chaseRadius{32.f};
};
