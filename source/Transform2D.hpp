#ifndef GAME_TRANSFORM2D_HPP
#define GAME_TRANSFORM2D_HPP

#include "Vector2D.hpp"

/**
 * @file Transform2D.hpp
 * @brief 3x3 affine transform for 2D points and directions.
 *
 * ---------------------------------------------------------------------------
 * MATRIX CONVENTION (DirectX-style). A correct implementation requires:
 *   1. Storage is ROW-MAJOR: m[row][col].
 *   2. Vectors are ROW vectors.
 *   3. A point is [x, y, 1]; a direction is [x, y, 0].
 *   4. TRANSLATION lives in the THIRD ROW: m[2][0] = tx, m[2][1] = ty.
 *   5. The third column is [0, 0, 1]^T for the affine transforms here.
 *
 * Rotation by angle a (positive = counter-clockwise):
 *      m[0][0] =  cos(a)   m[0][1] = sin(a)
 *      m[1][0] = -sin(a)   m[1][1] = cos(a)
 *
 * COMPOSITION ORDER: because v * (A * B) == (v * A) * B, the product A * B is
 * the transform that applies A FIRST, then B. Composed transforms read LEFT TO
 * RIGHT (the opposite of the column-vector M*v convention).
 *
 * @invariant Every entry is finite; the third column is [0, 0, 1]^T.
 */
class Transform2D {
public:
    /// Row-major storage, m[row][col]. Defaults to the identity.
    float m[3][3]{
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    /// Constructs the identity transform.
    Transform2D() noexcept = default;

    // --- Factories ---------------------------------------------------------
    [[nodiscard]] static Transform2D translation(float tx, float ty) noexcept;   
    [[nodiscard]] static Transform2D rotation(float angle_rad) noexcept;
    [[nodiscard]] static Transform2D scale(float sx, float sy) noexcept;

    /**
     * @brief Matrix product.
     * @return The transform equivalent to applying *this FIRST, then rhs.
     */
    [[nodiscard]] Transform2D operator*(const Transform2D& rhs) const noexcept;
    Transform2D& operator*=(const Transform2D& rhs) noexcept;

    /**
     * @brief Transforms a POINT (w = 1): translation IS applied.
     * @return [p.x, p.y, 1] * M.
     */
    [[nodiscard]] Vector2D transform_point(const Vector2D& point) const noexcept;

    /**
     * @brief Transforms a DIRECTION (w = 0): translation is NOT applied.
     * @return [d.x, d.y, 0] * M (third row ignored).
     */
    [[nodiscard]] Vector2D transform_vector(const Vector2D& direction) const noexcept;
};

#endif // GAME_TRANSFORM2D_HPP
