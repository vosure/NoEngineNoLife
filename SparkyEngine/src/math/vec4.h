#pragma once

#include <iostream>

namespace core {
	namespace math {

		struct vec4
		{
			float x, y, z, w;
			
			vec4();
			vec4(const float &x, const float &y, const float &z, const float &w);

			vec4 &add(const vec4 &other);
			vec4 &substract(const vec4 &other);
			vec4 &multiply(const vec4 &other);
			vec4 &divide(const vec4 &other);

			vec4& operator+=(const vec4 &right);
			vec4& operator-=(const vec4 &right);
			vec4& operator*=(const vec4 &right);
			vec4& operator/=(const vec4 &right);

			bool operator==(const vec4 right);
			bool operator!=(const vec4 right);
		};

		vec4 operator+(vec4 left, const vec4 &right);
		vec4 operator-(vec4 left, const vec4 &right);
		vec4 operator*(vec4 left, const vec4 &right);
		vec4 operator/(vec4 left, const vec4 &right);

		std::ostream& operator<<(std::ostream &stream, const vec4 &vector);

	}
}