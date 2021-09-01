#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter {
	public:
		BaseCharacter(Texture2D idleTexture, Texture2D runTexture, int frames, Vector2 position);
		BaseCharacter(Texture2D idleTexture, Texture2D runTexture, int frames, int windowWidth, int windowHeight);
		void setScale(float val);
		void setSpeed(float val);
		Vector2 getMovement();
		Vector2 getScreenPos();
		void tick(float dT, float updateTime);
		void undoMovement();
		Rectangle getCollisionRec();
		void unload();
	protected:
		Vector2 position{};
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
		float textureWidth{};
		float textureHeight{};

		void calcTextureDimens();
		virtual Vector2 calcPosition(int windowWidth, int windowHeight);
		void setPosition(Vector2 pos);
		void setSource();
		void setDestination();
		void setDirection(float leftRight);
		virtual void move();
		void animate(float dT, float updateTime);
		void draw();
};

#endif
