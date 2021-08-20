#include "raylib.h"

struct SpriteData {
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float runningTime;
};

SpriteData animateSprite(SpriteData data, float deltaTime, int maxFrame) {
	data.runningTime += deltaTime;
	if (data.runningTime >= data.updateTime) {
		// reset running time
		data.runningTime = 0.0;
		// jump to next frame in sprite
		data.rec.x = data.frame * data.rec.width;
		data.frame++;
		// reset frame to zero if it crosses its maximum
		if (data.frame > maxFrame) {
			data.frame = 0;
		}
	}
	return data;
}

int main() {
	// window dimensions
	const int windowWidth = 512;
	const int windowHeight = 380;
	// initialize the window
	InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

	// defining 'background' texture
	Texture2D background = LoadTexture("textures/far-buildings.png");
	// background position
	Vector2 bg1Pos{};
	Vector2 bg2Pos{};
	// background scroll x velocity
	const float bgScrollX = -20;

	// defining 'midground' texture
	Texture2D midground = LoadTexture("textures/back-buildings.png");
	// midground position
	Vector2 mg1Pos{};
	Vector2 mg2Pos{};
	// midground scroll x velocity
	const float mgScrollX = -40;

	// defining 'foreground' textures
	Texture2D foreground = LoadTexture("textures/foreground.png");
	// foreground position
	Vector2 fg1Pos{};
	Vector2 fg2Pos{};
	// foreground scroll x velocity
	const float fgScrollX = -80;

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
	const int nebulaVel = -200;

	// defining finish line
	float finishLine = nebulae[numOfnebs - 1].pos.x + 500;

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

	// collision detection var
	bool collision{};

	// font size
	const int fontSize{30};


	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// delta time (time since last frame)
		const float dT = GetFrameTime();

		// start drawing
		BeginDrawing();
		ClearBackground(WHITE);

		/* BACKGROUND */
		bg1Pos.x += bgScrollX * dT;
		if (bg1Pos.x <= -background.width * 2) {
			bg1Pos.x = 0.0f;
		}
		bg2Pos.x = bg1Pos.x + background.width * 2;
		DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
		DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

		/* MIDGROUND */
		mg1Pos.x += mgScrollX * dT;
		if (mg1Pos.x <= -midground.width * 2) {
			mg1Pos.x = 0.0f;
		}
		mg2Pos.x = mg1Pos.x + midground.width * 2;
		DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
		DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

		/* FOREGROUND */
		fg1Pos.x += fgScrollX * dT;
		if (fg1Pos.x <= -foreground.width * 2) {
			fg1Pos.x = 0.0f;
		}
		fg2Pos.x = fg1Pos.x + foreground.width * 2;
		DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
		DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

		// check for collision
		for (SpriteData nebula: nebulae) {
			float nebPad{40};
			Rectangle nebRec{
				nebula.pos.x + nebPad,
				nebula.pos.y + nebPad,
				nebula.rec.width - 2 * nebPad,
				nebula.rec.height - 2 * nebPad
			};
			Rectangle scarfyRec{
				scarfyData.pos.x,
				scarfyData.pos.y,
				scarfyData.rec.width,
				scarfyData.rec.height
			};
			if (CheckCollisionRecs(nebRec, scarfyRec)) {
				collision = true;
			}
		}

		if (collision) {
			// collision occured, GAME OVER!
			DrawText("Game Over!", windowWidth/2.0f - fontSize * 2.5f, windowHeight/2.0f, fontSize, WHITE);
		} else if (scarfyData.pos.x >= finishLine) {
			// scarfy crossed the finish line, YOU WIN!
			DrawText("You Win!", windowWidth/2.0f - fontSize * 2.5f, windowHeight/2.0f, fontSize, WHITE);
		} else {
			/* NEBULA */
			for (int i = 0; i < numOfnebs; i++) {
				// update nebula position with given velocity
				nebulae[i].pos.x += nebulaVel * dT;
				// animate each nebula
				nebulae[i] = animateSprite(nebulae[i], dT, 7);
				// draw 2D texture nebula
				DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
			}

			// updating finish line
			finishLine += nebulaVel * dT;
			
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
				scarfyData = animateSprite(scarfyData, dT, 5);
			} else { 
				// else show a specific frame from the sprite
				scarfyData.frame = 2;
				scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
			}
			// draw 2D texture scarfy
			DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
		}

		// stop drawing
		EndDrawing();
	}
	UnloadTexture(background);
	UnloadTexture(midground);
	UnloadTexture(foreground);
	UnloadTexture(nebula);
	UnloadTexture(scarfy);
	CloseWindow();
}
