#pragma once

#include <iostream>

namespace core {
	namespace math {

		struct vec2
		{
			float x, y;
			
			vec2();
			vec2(const float &x, const float &y);

			vec2 &add(const vec2 &other);
			vec2 &substract(const vec2 &other);
			vec2 &multiply(const vec2 &other);
			vec2 &divide(const vec2 &other);

			vec2& operator+=(const vec2 &right);
			vec2& operator-=(const vec2 &right);
			vec2& operator*=(const vec2 &right);
			vec2& operator/=(const vec2 &right);

			bool operator==(const vec2 right);
			bool operator!=(const vec2 right);
		};

		vec2 operator+(vec2 left, const vec2 &right);
		vec2 operator-(vec2 left, const vec2 &right);
		vec2 operator*(vec2 left, const vec2 &right);
		vec2 operator/(vec2 left, const vec2 &right);

		std::ostream &operator<<(std::ostream &stream, const vec2 &vector);

	}
}