#pragma once

#include <math.h>
#include <cstdlib>
#include <iostream>

inline float SqrDistance(float x1, float y1, float x2, float y2) { return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2); }
inline float SqrDistance(const olc::vf2d& v1, const olc::vf2d& v2) { return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y); }
inline float Distance(float x1, float y1, float x2, float y2) { return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); }
inline float Distance(const olc::vf2d& v1, const olc::vf2d& v2) { return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y)); }
inline float GetRandomFloat(float min, float max) { return min + (float)(rand()) / ((float)(RAND_MAX / (max - min))); }
