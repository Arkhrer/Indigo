#include <algorithm>
#include "Collision.h"

bool Collision::IsColliding(Rect &a, Rect &b, float angleOfA, float angleOfB){
    Vec2 A[] = { Vec2( a.x, a.y + a.h ),
        Vec2( a.x + a.w, a.y + a.h ),
        Vec2( a.x + a.w, a.y ),
        Vec2( a.x, a.y )
    };
    Vec2 B[] = { Vec2( b.x, b.y + b.h ),
        Vec2( b.x + b.w, b.y + b.h ),
        Vec2( b.x + b.w, b.y ),
        Vec2( b.x, b.y )
    };

    for (auto& v : A) {
        v = (v - a.Center()).Rotate(angleOfA) + a.Center();
    }

    for (auto& v : B) {
        v = (v - b.Center()).Rotate(angleOfB) + b.Center();
    }

    Vec2 axes[] = { (A[0] - A[1]).Normalized(), (A[1] - A[2]).Normalized(), (B[0] - B[1]).Normalized(), (B[1] - B[2]).Normalized() };

    for (auto& axis : axes) {
        float P[4];

//        for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);
        for (int i = 0; i < 4; ++i) P[i] = A[i].DotProduct(axis);

        float minA = *std::min_element(P, P + 4);
        float maxA = *std::max_element(P, P + 4);

//        for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);
        for (int i = 0; i < 4; ++i) P[i] = B[i].DotProduct(axis);

        float minB = *std::min_element(P, P + 4);
        float maxB = *std::max_element(P, P + 4);

        if (maxA < minB || minA > maxB)
            return false;
    }

    return true;
}
