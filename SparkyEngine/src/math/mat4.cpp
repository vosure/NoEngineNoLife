#include "mat4.h"

namespace core {
	namespace math {

		mat4::mat4()
		{
			for (int i = 0; i < 16; i++)
			{
				elements[i] = 0.0f;
			}
		}

		mat4::mat4(float diagonal)
		{
			for (int i = 0; i < 16; i++)
			{
				elements[i] = 0.0f;
			}

			elements[0] = diagonal;
			elements[5] = diagonal;
			elements[10] = diagonal;
			elements[15] = diagonal;
		}

		mat4 mat4::identitty()
		{
			return mat4(1.0f);
		}

		mat4 &mat4::multiply(const mat4 & other)
		{
			float data[16];
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					float result = 0.0f;
					for (int k = 0; k < 4; k++)
					{
						result += elements[x + k * 4] * other.elements[k + x * 4];
					}
					data[x + y * 4] = result;
				}
			}

			memcpy(elements, data, 16 * sizeof(float));

			return *this;
		}

		mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[0 + 3 * 4] = (right + left) / (left - right);
			result.elements[1 + 3 * 4] = (top + bottom) / (bottom - top);
			result.elements[2 + 3 * 4] = (far + near) / (near - far);

			return result;
		}

		mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
		{
			//NOTE(vosure) This could be wrong!
			//NOTE(vosure) Cherno fucked up with perspective matrix formula. So I google and implemented it by myself
			//TODO(vosure) Double-check if you want to use this code in your own engine/math lib

			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 1 / (aspectRatio * tan(toRadians(fov / 2)));
			result.elements[1 + 1 * 4] = 1 / (tan(toRadians(fov / 2)));
			result.elements[2 + 2 * 4] = -((far + near) / (far - near));
			result.elements[2 + 3 * 4] = -((2 * far * near) / (far - near));
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[3 + 3 * 4] = 0.0f;

			return result;
		}

		mat4 mat4::translation(const vec3 & translation)
		{
			mat4 result(1.0f);

			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = translation.z;

			return result;
		}

		mat4 mat4::rotation(const float angle, const vec3 & axis)
		{
			//NOTE(vosure) This could be wrong!
			//NOTE(vosure) Cherno fucked up with rotation matrix formula. So I google and implemented it by myself
			//TODO(vosure) Double-check if you want to use this code in your own engine/math lib

			float cosine = cos(toRadians(angle));
			float sine = sin(toRadians(angle));
			float oneMinusCos = (1.0f - cosine);

			float rX = axis.x;
			float rY = axis.y;
			float rZ = axis.z;

			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = cosine + (rX * rX) * oneMinusCos;
			result.elements[1 + 0 * 4] = rY * rX * oneMinusCos + rZ * sine;
			result.elements[2 + 0 * 4] = rZ * rX* oneMinusCos - rY * sine;

			result.elements[0 + 1 * 4] = rX * rY * oneMinusCos - rZ * sine;
			result.elements[1 + 1 * 4] = cosine + (rY * rY) * oneMinusCos;
			result.elements[2 + 1 * 4] = rZ * rY *oneMinusCos + rX * sine;
							  
			result.elements[0 + 2 * 4] = rX * rZ *oneMinusCos + rY * sine;
			result.elements[1 + 2 * 4] = rY * rZ *oneMinusCos - rX * sine;
			result.elements[2 + 2 * 4] = cosine + (rZ * rZ) * oneMinusCos;

			return result;
		}

		mat4 mat4::scale(const vec3 & scale)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;

			return result;
		}

		mat4 operator*(mat4 left, const mat4 & right)
		{
			return left.multiply(right);
		}

		mat4 mat4::operator*=(const mat4 & other)
		{
			return multiply(other);
		}
	}
}
