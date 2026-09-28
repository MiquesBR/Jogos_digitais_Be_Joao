#include "Transform2D.hpp"

#include <cmath>

Transform2D Transform2D::translation(
    float tx,
    float ty
) noexcept {

    Transform2D result;

    result.m[2][0] = tx;
    result.m[2][1] = ty;

    return result;
}

Transform2D Transform2D::rotation(
    float angle_rad
) noexcept {

    Transform2D result;

    const float cosine = std::cos(angle_rad);
    const float sine = std::sin(angle_rad);

    result.m[0][0] = cosine;
    result.m[0][1] = sine;

    result.m[1][0] = -sine;
    result.m[1][1] = cosine;

    return result;
}

Transform2D Transform2D::scale(
    float sx,
    float sy
) noexcept {

    Transform2D result;

    result.m[0][0] = sx;
    result.m[1][1] = sy;

    return result;
}

Transform2D Transform2D::operator*(
    const Transform2D& rhs
) const noexcept {

    Transform2D result;

    for (int row = 0; row < 3; ++row) {

        for (int column = 0; column < 3; ++column) {

            result.m[row][column] = 0.0f;

            for (int k = 0; k < 3; ++k) {

                result.m[row][column] +=
                    m[row][k] *
                    rhs.m[k][column];
            }
        }
    }

    return result;
}

Transform2D& Transform2D::operator*=(
    const Transform2D& rhs
) noexcept {

    *this = *this * rhs;

    return *this;
}

Vector2D Transform2D::transform_point(
    const Vector2D& point
) const noexcept {

    const float new_x =
        point.x * m[0][0] +
        point.y * m[1][0] +
        m[2][0];

    const float new_y =
        point.x * m[0][1] +
        point.y * m[1][1] +
        m[2][1];

    return Vector2D(
        new_x,
        new_y
    );
}

Vector2D Transform2D::transform_vector(
    const Vector2D& direction
) const noexcept {

    const float new_x =
        direction.x * m[0][0] +
        direction.y * m[1][0];

    const float new_y =
        direction.x * m[0][1] +
        direction.y * m[1][1];

    return Vector2D(
        new_x,
        new_y
    );
}