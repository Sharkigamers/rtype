/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Vector2
*/

#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

class Vector2 {
    public:
        Vector2():x(0.0f), y(0.0f) {};
        Vector2(float const mX, float const mY):x(mX), y(mY) {};

        ~Vector2() {};

        Vector2 operator+(Vector2 const& vector)
        {
            return Vector2(
                x + vector.x,
                y + vector.y
            );
        }

        Vector2 operator-(Vector2 const& vector)
        {
            return Vector2(
                x - vector.x,
                y - vector.y
            );
        }

        Vector2 operator/(Vector2 const& vector)
        {
            return Vector2(
                x / vector.x,
                y / vector.y
            );
        }

        Vector2 operator*(Vector2 const& vector)
        {
            return Vector2(
                x * vector.x,
                y * vector.y
            );
        }

        Vector2 operator+=(Vector2 const& vector)
        {
            x += vector.x;
            y += vector.y;

            return *this;
        }

        Vector2 operator-=(Vector2 const& vector)
        {
            x -= vector.x;
            y -= vector.y;

            return *this;
        }

        Vector2 operator/=(Vector2 const& vector)
        {
            x /= vector.x;
            y /= vector.y;

            return *this;
        }

        Vector2 operator*=(Vector2 const& vector)
        {
            x *= vector.x;
            y *= vector.y;

            return *this;
        }

        float x;
        float y;
};

#endif /* !VECTOR2_HPP_ */
