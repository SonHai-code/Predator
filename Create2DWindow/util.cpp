# include "util.h"

// Test collision detection 
int collision(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2)
{
	return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}


void calcSlope(float x1, float y1, float x2, float y2, float* dx, float* dy)
{
	float steps = MAX(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0)
	{
		*dx = *dy = 0;
		return;
	}

	*dx = (x1 - x2);
	*dx /= steps;

	*dy = (y1 - y2);
	*dy /= steps;
}