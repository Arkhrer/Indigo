#include <cmath>
#include "Vec2.h"

Vec2::Vec2(float x, float y){
    this->x = x;
    this->y = y;
}

Vec2 Vec2::Add(Vec2 v){
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::Subtract(Vec2 v){
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::ScalarMultiplication(float k){
    return Vec2(x * k, y * k);
}

float Vec2::Magnitude(){
    return std::sqrt(x * x + y * y);
}

Vec2 Vec2::Normalized(){
    float magnitude = Magnitude();
    if (magnitude != 0){
        return Vec2(x / magnitude, y / magnitude);
    }
    else{
        return Vec2(0.0, 0.0);
    }
}

float Vec2::Distance(Vec2 v){
    return Subtract(v).Magnitude();
}

float Vec2::Inclination(){
    return std::atan2(y, x);
}

float Vec2::LineInclination(Vec2 v){
    return v.Subtract(*this).Inclination();
}

Vec2 Vec2::Rotate(float angle){
    float cs = std::cos(angle);
    float sn = std::sin(angle);
    return Vec2(x * cs - y * sn, y * cs + x * sn);
}
void Vec2::SelfRotate(float angle){
    float oldX = x;
    float cs = std::cos(angle);
    float sn = std::sin(angle);
    x = x * cs - y * sn;
    y = y * cs + oldX * sn;
}

float Vec2::DotProduct(Vec2 v){
    return x * v.x + y * v.y;
}

Vec2 Vec2::operator + (const Vec2& v) const {
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator - (const Vec2& v) const {
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator * (const float x) const {
    return Vec2(x * x, y * x);
 }
