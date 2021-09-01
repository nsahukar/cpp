#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter {
	public:
		BaseCharacter(Texture2D idleTexture, Texture2D runTexture, int frames, Vector2 position);
		BaseCharacter(Texture2D idleTexture, Texture2D runTexture, int frames, int windowWidth, int windowHeight);
		void setScale(float val);
		void setSpeed(float val);
		Vector2 getPos();
		Vector2 getScreenPos();
		virtual void tick(float dT, float updateTime);
		void undoMovement();
		Rectangle getCollisionRec();
		void setAlive(bool val);
		bool isAlive();
		virtual void unload();
	protected:
		Texture2D idle;
		Texture2D run;
		Texture2D texture;
		Vector2 position{};
		Rectangle source{};
		Rectangle destination{};
		Vector2 velocity{};
		Vector2 lastPosition{};
		int frame{};
		int maxFrame{};
		float runningTime{};
		float scale{4.f};
		float speed{4.f};

		virtual Vector2 calcPosition(int windowWidth, int windowHeight);
		virtual void setPos(Vector2 pos);
		virtual void setScreenPos(Vector2 pos);
		void setSource();
		void setDestination();
		virtual void setDirection(float leftRight);
		virtual void move();
		virtual void animate(float dT, float updateTime);
		virtual void draw();
	private:
		float leftRight{1.f};
		bool alive{true};
};

#endif
