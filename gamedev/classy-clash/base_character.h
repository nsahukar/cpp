#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter {
	public:
		BaseCharacter();
		void setScale(float val);
		void setSpeed(float val);
		Vector2 getMovement();
		void tick(float dT, float updateTime);
		void undoMovement();
		Rectangle getCollisionRec();
		void unload();
	protected:
		Texture2D idle;
		Texture2D run;
		Texture2D texture;
		Rectangle source{};
		Rectangle destination{};
		Vector2 movement{};
		Vector2 lastMovement{};
		int frame{};
		int maxFrame{};
		float runningTime{};
		float scale{4.f};
		float speed{4.f};

		void setSource(int frames);
		virtual void setDestination(int windowWidth, int windowHeight);
		void setDirection(float leftRight);
		virtual void move();
		void animate(float dT, float updateTime);
		void draw();
};
#endif
