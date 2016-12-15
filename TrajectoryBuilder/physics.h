#ifndef PHYSICS_H
#define PHYSICS_H
#include <cmath>

typedef struct _Point2F
{
    float x;
    float y;
}Point2F;

typedef struct _Vec2F
{
    float i;
    float j;
}Vec2F;

typedef struct _Velocity
{
    Vec2F   direction;
    float   velocityValue;
}Velocity;

inline float PointDistance(Point2F pt1,Point2F pt2)
{
    return sqrt((pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y));
}

#endif // PHYSICS_H
