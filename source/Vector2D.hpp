#ifndef GAME_VECTOR2D_HPP
#define GAME_VECTOR2D_HPP

#include <cmath>
#include "Global.hpp"

/**
 * @file Vector2D.hpp
 * @brief A 2D vector, used both as a point or position and as a direction.
 *
 * @invariant Components are expected to be finite floating-point numbers.
 */
struct Vector2D {
    float x{0.0f};
    float y{0.0f};

    constexpr Vector2D() noexcept = default;
    constexpr Vector2D(float in_x, float in_y) noexcept : x(in_x), y(in_y) {}

    // --- Length ------------------------------------------------------------

    /// Squared length. For fast distance comparison.
    [[nodiscard]] constexpr float length_squared() const noexcept {
        return x * x + y * y;
    }

    /// Euclidean length.
    [[nodiscard]] float length() const noexcept {
        return std::sqrt(length_squared());
    }

    /**
     * @brief Returns a unit-length copy with the same direction.
     * @pre length() > EPSILON (the zero vector has no defined direction).
     * @post std::abs(result.length() - 1) < EPSILON.
     */
    [[nodiscard]] Vector2D normalized() const;

    /**
     * @brief Scales this vector in place to unit length.
     * @pre length() > EPSILON.
     */
    void normalize();

    /// Dot product.
    [[nodiscard]] constexpr float dot(const Vector2D& rhs) const noexcept {
        return x * rhs.x + y * rhs.y;
    }

    /// 2D scalar cross product.
    [[nodiscard]] constexpr float cross(const Vector2D& rhs) const noexcept {
        return x * rhs.y - y * rhs.x;
    }

    /// Approximate equality within a tolerance.
    [[nodiscard]] bool equals(const Vector2D& rhs, float tolerance = EPSILON) const noexcept;


    // --- Operators ---------------------------------------------------------

    [[nodiscard]] Vector2D operator+(const Vector2D& rhs) const noexcept;
    [[nodiscard]] Vector2D operator-(const Vector2D& rhs) const noexcept;
    [[nodiscard]] Vector2D operator*(float scalar) const noexcept;

    // @pre std::abs(scalar) > EPSILON.
    [[nodiscard]] Vector2D operator/(float scalar) const;   

    Vector2D& operator+=(const Vector2D& rhs) noexcept;
    Vector2D& operator-=(const Vector2D& rhs) noexcept;
    Vector2D& operator*=(float scalar) noexcept;

    // @pre std::abs(scalar) > EPSILON.
    Vector2D& operator/=(float scalar);
};

/// Left-scalar multiplication (scalar * vector).
[[nodiscard]] Vector2D operator*(float scalar, const Vector2D& vec) noexcept;

#endif // GAME_VECTOR2D_HPP
