#ifndef _PONG_HEADER_H
#define _PONG_HEADER_H

#define PONG_VERSION "0.1"

#define FPS 30
#define SCR_W 640
#define SCR_H 480

typedef struct {
	float ypos;
	float yspd;
	int score;
	int height;
} Paddle;

typedef struct {
	float xpos;
	float ypos;
	float xspd;
	float yspd;
	float radius;
} Ball;

void initP1(Paddle * const pad);
void initP2(Paddle * const pad);

void inputP1(Paddle * const pad);
void inputP2(Paddle * const pad);

void moveBall(Ball * const ball);

int doesBallHitPad(const Paddle * const pad, const Ball * const ball);

// Changes the ball's direction by how much the paddle influenced it.
void padDirToBall(const Paddle * const pad, Ball * const ball);

// Y position will be hard coded here.
void drawScore(const int xpos, const int score);

// Draws a sick looking arena type thing.
void drawBoard();

void drawBall(const Ball * const ball);
void drawPaddle(const Paddle * const pad);

#endif // _PONG_HEADER_H
