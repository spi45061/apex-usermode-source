#pragma once
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h

struct Matrix {
	float matrix[16];
};
struct Bone {
	BYTE thing[0xCC];
	float x;
	BYTE thing2[0xC];
	float y;
	BYTE thing3[0xC];
	float z;
};
class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	float x;
	float y;
	float z;

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	inline double Length() {
		return sqrt(x * x + y * y + z * z);
	}
	//inline FRotator ToFRotator() {

	//}

	void Normalize()
	{
		while (x > 89.0f)
			x -= 180.f;

		while (x < -89.0f)
			x += 180.f;

		while (y > 180.f)
			y -= 360.f;

		while (y < -180.f)
			y += 360.f;
	}
	float DistTo(Vector3 ape)
	{
		return (*this - ape).Length();
	}
	float distance(Vector3 vec)
	{
		return sqrt(
			pow(vec.x - x, 2) +
			pow(vec.y - y, 2)
		);
	}
	struct Vector3 ScreenPosition(Matrix matrix) {
		struct Vector3 out;
		float w = matrix.matrix[12] * x + matrix.matrix[13] * y + matrix.matrix[14] * z + matrix.matrix[15];
		if (w < 0.01f) return Vector3(0, 0, 0);
		float _x = matrix.matrix[0] * x + matrix.matrix[1] * y + matrix.matrix[2] * z + matrix.matrix[3];
		float _y = matrix.matrix[4] * x + matrix.matrix[5] * y + matrix.matrix[6] * z + matrix.matrix[7];
		out.z = matrix.matrix[12] * x + matrix.matrix[13] * y + matrix.matrix[14] * z + matrix.matrix[15];
		float invw = 1.0f / w;
		_x *= 1.f / out.z;
		_y *= 1.f / out.z;
		out.x *= invw;
		out.y *= invw;
		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);

		out.x = width * .5f;
		out.y = height * .5f;

		out.x += 0.5f * _x * width + 0.5f;
		out.y -= 0.5f * _y * height + 0.5f;

		return out;
	}
	Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(float flNum) { return Vector3(x * flNum, y * flNum, z * flNum); }
};
class Vector2
{
public:
	Vector2() : x(0.f), y(0.f)
	{

	}

	Vector2(float _x, float _y) : x(_x), y(_y)
	{

	}
	~Vector2()
	{

	}

	float x;
	float y;

};
struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};
float GetCrossDistance(float x1, float y1, float z1, float x2, float y2, float z2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
inline float dist(const Vector3 p1, const Vector3 p2)
{
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;
	float z = p1.z - p2.z;
	return sqrt(x * x + y * y + z * z);
}