#include "vec2.h"

namespace core {
	namespace math {


		vec2::vec2()
		{
			x = 0.0f;
			y = 0.0f;
		}

		vec2::vec2(const float &x, const float &y)
		{
			this->x = x;
			this->y = y;
		}

		vec2 &vec2::add(const vec2 & other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		vec2 &vec2::substract(const vec2 &other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		vec2 &vec2::multiply(const vec2 &other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		vec2 &vec2::divide(const vec2 &other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}

		vec2 &vec2::operator+=(const vec2 & right)
		{
			return add(right);
		}

		vec2 &vec2::operator-=(const vec2 & right)
		{
			return substract(right);
		}

		vec2 &vec2::operator*=(const vec2 & right)
		{
			return multiply(right);
		}

		vec2 &vec2::operator/=(const vec2 & right)
		{
			return divide(right);
		}

		bool vec2::operator==(const vec2 right)
		{
			return x == right.x && y == right.y;
		}

		bool vec2::operator!=(const vec2 right)
		{
			return !(*this == right);
		}

		vec2 operator+(vec2  left, const vec2 &right)
		{
			return left.add(right);
		}

		vec2 operator-(vec2 left, const vec2 &right)
		{
			return left.substract(right);
		}

		vec2 operator*(vec2  left, const vec2 &right)
		{
			return left.multiply(right);
		}

		vec2 operator/(vec2  left, const vec2 &right)
		{
			return left.divide(right);
		}

		std::ostream & operator<<(std::ostream &stream, const vec2 &vector)
		{
			stream << "vec2 (" << vector.x << ", " << vector.y << ")";
			return stream;
		}

	}
}