#include "raylib.h"

class Character {
	public:
		Character(Texture2D idleTexture, Texture2D runTexture, int frames, int windowWidth, int windowHeight);
		void setScale(float val);
		void setSpeed(float val);
		Vector2 getMovement();
		void tick(float dT, float updateTime);
		void undoMovement();
		void unloadTextures();
	private:
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

		void setIdle(Texture2D idleTexture);
		void setRun(Texture2D runTexture);
		void setSource(int frames);
		void setDestination(int windowWidth, int windowHeight);
		void setDirection(float leftRight);
		void move();
		void animate(float dT, float updateTime);
		void draw();
};
