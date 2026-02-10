#pragma once

#include "type.h"

#include <cmath>

// Math

double Length(Vector2 v);
Vector2 Normalize(Vector2 v);
double Dot(Vector2 v1, Vector2 v2);
double Distance(Vector2 p1, Vector2 p2);
double Clamp(double value, double min, double max);
double Lerp(double a, double b, double t);

// Random
int GetRandomInt(int min, int max);
double GetRandomDouble(double min, double max);
bool GetRandomBool();

// Collision
bool IsRectRectCollision(Rect r1, Rect r2);
bool IsRectCircleCollision(Rect rect, Circle circle);
bool IsCircleCircleCollision(Circle c1, Circle c2);
bool IsPointInRect(Vector2 p, Rect r);
bool IsPointInCircle(Vector2 p, Circle c);

// Helpers
Rect CreateRect(Vector2 position, double width, double height);
Circle CreateCircle(Vector2 center, double radius);
