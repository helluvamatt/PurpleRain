#include "Drop.h"

const float MIN_Z = 0;
const float MAX_Z = 20;
const float MIN_SIZE = 0;
const float MAX_SIZE = 3;
const float MIN_GRAV = 0;
const float MAX_GRAV = 0.2;
const float MIN_LEN = 10;
const float MAX_LEN = 20;
const float MIN_SPEED = 1;
const float MAX_SPEED = 20;

void CreateDrop(PDrop d, int screenWidth, int color)
{
	if (d == NULL) return;
	d->Color = color;
	d->X = randfx(0, screenWidth);
	d->Y = randfx(-50, -200); // start offscreen
	d->Z = randfx(MIN_Z, MAX_Z);
	d->Len = map(d->Z, MIN_Z, MAX_Z, MIN_LEN, MAX_LEN);
	d->Yspeed = map(d->Z, MIN_Z, MAX_Z, MIN_SPEED, MAX_SPEED);
}

void DropFall(PDrop d, int screenHeight)
{
	if (d == NULL) return;
	d->Y = d->Y + d->Yspeed;
	float grav = map(d->Z, MIN_Z, MAX_Z, MIN_GRAV, MAX_GRAV);
	d->Yspeed = d->Yspeed + grav;
	if (d->Y > screenHeight)
	{
		d->Y = randi(-50, -200);
		d->Yspeed = map(d->Z, MIN_Z, MAX_Z, MIN_SPEED, MAX_SPEED);
	}
}

float DropGetThickness(PDrop d)
{
	if (d == NULL) return 0;
	return map(d->Z, MIN_Z, MAX_Z, MIN_SIZE, MAX_SIZE);
}