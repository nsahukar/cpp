#include "raylib.h"

struct SpriteData {
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float runningTime;
};

int main() {
	// window dimensions
	const int windowWidth = 512;
	const int windowHeight = 380;
	// initialize the window
	InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

	// defining 'nebula' texture
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
	const int numOfnebs = 6;
	SpriteData nebulae[numOfnebs];
	// initializing nebulae(s)
	const int distBetNebs = 300;
	for (int i = 0; i < numOfnebs; i++) {
		nebulae[i].rec.x = 0.0f;
		nebulae[i].rec.y = 0.0f;
		nebulae[i].rec.width = nebula.width/8.0f;
		nebulae[i].rec.height = nebula.height/8.0f;

		nebulae[i].pos.x = windowWidth + (i * distBetNebs);
		nebulae[i].pos.y = windowHeight - nebula.height/8.0f;

		nebulae[i].frame = 0;
		nebulae[i].updateTime = 1.0 / 12.0;
		nebulae[i].runningTime = 0.0;
	}
	// nebula x velocity (pixels/sec)
	int nebulaVel = -200;

	// defining 'scarfy' texture
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	SpriteData scarfyData;
	scarfyData.rec.width = scarfy.width/6.0f;
	scarfyData.rec.height = scarfy.height;
	scarfyData.rec.x = 0;
	scarfyData.rec.y = 0;
	scarfyData.pos.x = windowWidth/2.0f - scarfyData.rec.width/2.0f;
	scarfyData.pos.y = windowHeight - scarfyData.rec.height;
	scarfyData.frame = 0;
	scarfyData.updateTime = 1.0 / 10.0;
	scarfyData.runningTime = 0.0;
	// scarfy ground position
	const int scarfyGroundPosY = windowHeight - scarfyData.rec.height;
	// sacrfy jump velocity (pixels/sec)
	const int scarfyJumpVel = -600;
	// var to check if scarfy is in air
	bool scarfyIsInAir;
	// scarfy velocity (pixels/frame)
	int scarfyVelocity = 0;
	// scarfy texture animation frame

	// acceleration due to gravity (pixels/sec)/sec
	const int gravity = 1000;


	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// start drawing
		BeginDrawing();
		ClearBackground(WHITE);

		// delta time (time since last frame)
		const float dT = GetFrameTime();

		/* NEBULA */
		for (int i = 0; i < numOfnebs; i++) {
			// update nebula position with given velocity
			nebulae[i].pos.x += nebulaVel * dT;
			// animate nebula by updating its animation frame
			nebulae[i].runningTime += dT;
			if (nebulae[i].runningTime >= nebulae[i].updateTime) {
				// reset nebula running time
				nebulae[i].runningTime = 0.0;
				// jump to next frame in sprite
				nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
				nebulae[i].frame++;
				// reset frame to zero if it crosses its maximum
				if (nebulae[i].frame > 7) {
					nebulae[i].frame = 0;
				}
			}
		}
		
		/* SCARFY */
		// ground check for sacrfy,
		if (scarfyData.pos.y >= scarfyGroundPosY) {
			// setting velocity to zero, sacrfy is on the ground
			scarfyVelocity = 0;
			scarfyIsInAir = false;
		} else {
			// applying gravity, sacrfy is in the air
			scarfyVelocity += gravity * dT;
			scarfyIsInAir = true;
		}
		// make scarfy jump on spacebar press,
		// only when it is on the ground (avoid air jumping)
		if (IsKeyPressed(KEY_SPACE) && !scarfyIsInAir) {
			scarfyVelocity += scarfyJumpVel;
		}
		// update scarfy position with given velocity
		scarfyData.pos.y += scarfyVelocity * dT;
		// if sacrfy not in air, animate scarfy by updating animation frame
		if (!scarfyIsInAir) {
			scarfyData.runningTime += dT;
			if (scarfyData.runningTime >= scarfyData.updateTime) {
				// reset scarfy running time
				scarfyData.runningTime = 0.0;
				// jump to next frame in sprite
				scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
				scarfyData.frame++;
				// reset frame to zero if it crosses its maximum
				if (scarfyData.frame > 5) {
					scarfyData.frame = 0;
				}
			}
		}
		// else show a specific frame from the sprite
		else {
			scarfyData.frame = 2;
			scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
		}

		// draw 2D texture nebula
		// Color nebColors[2]{ WHITE, RED };
		for (int i = 0; i < numOfnebs; i++) {
			DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
		}
		// draw 2D texture scarfy
		DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

		// stop drawing
		EndDrawing();
	}
	UnloadTexture(nebula);
	UnloadTexture(scarfy);
	CloseWindow();
}
