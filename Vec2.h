#ifndef VEC2_H
#define VEC2_H


class Vec2{
public:
    Vec2(float x = 0.0, float y = 0.0);

    Vec2 Add(Vec2 v);
    Vec2 Subtract(Vec2 v);
    Vec2 ScalarMultiplication(float k);
    float Magnitude();
    Vec2 Normalized();
    float Distance(Vec2 v);
    float Inclination();
    float LineInclination(Vec2 v);
    Vec2 Rotate(float angle);
    void SelfRotate(float angle);
    float DotProduct(Vec2 v);

    Vec2 operator + (const Vec2& v) const;
    Vec2 operator - (const Vec2& v) const;
    Vec2 operator * (const float x) const;

    float x;
    float y;
};

#endif // VEC2_H
