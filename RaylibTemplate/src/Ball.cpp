#include "Ball.h"

Ball::Ball()
{
	position.x = 350;
	position.y = 195;
	radius = 20;
	color = BLUE;
	isTravelingDown = true;
	isTravelingRight = true;
	horizontalSpeed = 5;
	verticalSpeed = 3.77;
	seth = LoadSound("sounds\\seth.mp3");
}

void Ball::Draw()
{
	DrawCircle((int)position.x, (int)position.y, radius, color);
}

void Ball::Move()
{
	if (CheckBounds())
		PlaySound(seth);

	if (isTravelingRight)
		position.x += horizontalSpeed;
	else
		position.x -= horizontalSpeed;

	if (isTravelingDown)
		position.y += verticalSpeed;
	else
		position.y -= verticalSpeed;
}

bool Ball::CheckBounds()
{
	if (position.x + radius >= GetScreenWidth())
	{
		isTravelingRight = false;
		return true;
	}

	if (position.x - radius <= 0)
	{
		isTravelingRight = true;
		return true;
	}

	if (position.y + radius >= GetScreenHeight())
	{
		isTravelingDown = false;
		return true;
	}

	if (position.y - radius <= 0)
	{
		isTravelingDown = true;
		return true;
	}

	return false;
}