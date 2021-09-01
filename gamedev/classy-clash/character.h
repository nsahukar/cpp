#ifndef CHARACTER_H
#define CHARACTER_H

#include "base_character.h"
#include "raylib.h"

class Character : public BaseCharacter {
	public:
		Character(Texture2D idleTexture, Texture2D runTexture, int frames, Texture2D weaponTexture, int windowWidth, int windowHeight);
		virtual void unload() override;
		Rectangle getWeaponCollisionRec() const;
		float getHealth() const;
		void takeDamage(float damage);
	protected:
		virtual void setScreenPos(Vector2 pos) override;
		virtual void setDirection(float leftRight) override;
		virtual void move() override;
		virtual void draw() override;
	private:
		Texture2D weapon;
		Rectangle weaponSource{};
		Rectangle weaponDestination{};
		Rectangle weaponOffset{};
		Vector2 weaponOrigin{};
		Rectangle weaponCollisionRec{};
		float weaponRotation{};
		float health{100.f};

		void setWeaponScreenPos(Vector2 pos);
		void setWeaponSource();
		void setWeaponDestination();
		void setWeaponDirection(float leftRight);
		void moveWeapon();
		void drawWeapon();
		void setWeaponCollisionRec(float leftRight);
		void unloadWeapon();
};

#endif
