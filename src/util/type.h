#pragma once

struct Vector2
{
    double x;
    double y;
};

struct Rect
{
    double left;
    double right;
    double top;
    double bottom;
};

struct Circle
{
    Vector2 center;
    double radius;
};

struct Attribute
{
    int health;
    int score;
    double speed;
    double maxBulletCd;
    double bulletCd;
};

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
