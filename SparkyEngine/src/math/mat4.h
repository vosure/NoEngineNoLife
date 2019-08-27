#pragma once

#include "math.h"

namespace core {
	namespace math {

		struct mat4
		{
			union
			{
				float elements[4 * 4];
				vec4 columns[4];
			};


			mat4();
			mat4(float diagonal);

			mat4 operator*=(const mat4 &other);

			static mat4 identitty();
			mat4 &multiply(const mat4 &other);

			static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static mat4 perspective(float fov, float aspectRatio, float near, float far);

			static mat4 translation(const vec3 &translation);
			static mat4 rotation(const float angle, const vec3 &axis);
			static mat4 scale(const vec3 &scale);

			inline vec4 getColumn(int index) const
			{
				index *= 4;
				return vec4(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
			}
		};

		mat4 operator*(mat4 left, const mat4 &right);

		inline float toRadians(float degrees)
		{
			return degrees * (M_PI) / 180.0f;
		}

	}
}