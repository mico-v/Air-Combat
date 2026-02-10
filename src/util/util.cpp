#include "util.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

namespace
{
    bool g_randomInitialized = false;
}

static void InitRandom()
{
    if (!g_randomInitialized)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        g_randomInitialized = true;
    }
}

// Math

double Length(Vector2 v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

Vector2 Normalize(Vector2 v)
{
    double len = Length(v);
    if (len <= 0.000001)
        return {0.0, 0.0};
    return {v.x / len, v.y / len};
}

double Dot(Vector2 v1, Vector2 v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

double Distance(Vector2 p1, Vector2 p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

double Clamp(double value, double min, double max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

double Lerp(double a, double b, double t)
{
    return a + (b - a) * t;
}

// Random

int GetRandomInt(int min, int max)
{
    InitRandom();
    return min + std::rand() % (max - min + 1);
}

double GetRandomDouble(double min, double max)
{
    InitRandom();
    double r = std::rand() / static_cast<double>(RAND_MAX);
    return min + r * (max - min);
}

bool GetRandomBool()
{
    InitRandom();
    return (std::rand() % 2) == 1;
}

// Collision

bool IsRectRectCollision(Rect r1, Rect r2)
{
    if (r1.right < r2.left || r1.left > r2.right)
        return false;
    if (r1.bottom < r2.top || r1.top > r2.bottom)
        return false;
    return true;
}

bool IsRectCircleCollision(Rect rect, Circle circle)
{
    double closestX = Clamp(circle.center.x, rect.left, rect.right);
    double closestY = Clamp(circle.center.y, rect.top, rect.bottom);
    double dx = circle.center.x - closestX;
    double dy = circle.center.y - closestY;
    double distSq = dx * dx + dy * dy;
    return distSq <= circle.radius * circle.radius;
}

bool IsCircleCircleCollision(Circle c1, Circle c2)
{
    double dx = c1.center.x - c2.center.x;
    double dy = c1.center.y - c2.center.y;
    double r = c1.radius + c2.radius;
    return (dx * dx + dy * dy) <= r * r;
}

bool IsPointInRect(Vector2 p, Rect r)
{
    return p.x >= r.left && p.x <= r.right && p.y >= r.top && p.y <= r.bottom;
}

bool IsPointInCircle(Vector2 p, Circle c)
{
    double dx = p.x - c.center.x;
    double dy = p.y - c.center.y;
    return (dx * dx + dy * dy) <= c.radius * c.radius;
}

// Helpers

Rect CreateRect(Vector2 position, double width, double height)
{
    return {position.x, position.x + width, position.y, position.y + height};
}

Circle CreateCircle(Vector2 center, double radius)
{
    return {center, radius};
}
