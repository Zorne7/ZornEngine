#ifndef MATH_H
#define MATH_H

#include <cmath>

namespace Math {
    constexpr float PI = 3.14159265358979323846f;

    struct Vec3 {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        Vec3() = default;
        Vec3(float value) : x(value), y(value), z(value) {}
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    };

    inline Vec3 operator+(const Vec3& a, const Vec3& b) {
        return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    inline Vec3 operator-(const Vec3& a, const Vec3& b) {
        return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    inline Vec3 operator*(const Vec3& a, float scalar) {
        return Vec3(a.x * scalar, a.y * scalar, a.z * scalar);
    }

    inline float Dot(const Vec3& a, const Vec3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    inline Vec3 Cross(const Vec3& a, const Vec3& b) {
        return Vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    inline Vec3 Normalize(const Vec3& v) {
        float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        if (length == 0.0f)
            return Vec3(0.0f, 0.0f, 0.0f);
        return Vec3(v.x / length, v.y / length, v.z / length);
    }

    inline float ToRadians(float degrees) {
        return degrees * (PI / 180.0f);
    }

    struct Mat4 {
        float elements[16];

        static Mat4 Identity() {
            Mat4 result;
            for (int i = 0; i < 16; ++i)
                result.elements[i] = (i % 5 == 0) ? 1.0f : 0.0f;
            return result;
        }
    };

    inline Mat4 operator*(const Mat4& a, const Mat4& b) {
        Mat4 result;
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                float sum = 0.0f;
                for (int i = 0; i < 4; ++i) {
                    sum += a.elements[i * 4 + row] * b.elements[col * 4 + i];
                }
                result.elements[col * 4 + row] = sum;
            }
        }
        return result;
    }

    inline Mat4 Translate(const Vec3& translation) {
        Mat4 result = Mat4::Identity();
        result.elements[12] = translation.x;
        result.elements[13] = translation.y;
        result.elements[14] = translation.z;
        return result;
    }

    inline Mat4 Scale(const Vec3& scale) {
        Mat4 result = Mat4::Identity();
        result.elements[0] = scale.x;
        result.elements[5] = scale.y;
        result.elements[10] = scale.z;
        return result;
    }

    inline Mat4 RotateX(float angleRadians) {
        Mat4 result = Mat4::Identity();
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);
        result.elements[5] = c;
        result.elements[6] = s;
        result.elements[9] = -s;
        result.elements[10] = c;
        return result;
    }

    inline Mat4 RotateY(float angleRadians) {
        Mat4 result = Mat4::Identity();
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);
        result.elements[0] = c;
        result.elements[2] = -s;
        result.elements[8] = s;
        result.elements[10] = c;
        return result;
    }

    inline Mat4 RotateZ(float angleRadians) {
        Mat4 result = Mat4::Identity();
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);
        result.elements[0] = c;
        result.elements[1] = s;
        result.elements[4] = -s;
        result.elements[5] = c;
        return result;
    }

    inline Mat4 Perspective(float fovRadians, float aspect, float zNear, float zFar) {
        Mat4 result;
        for (int i = 0; i < 16; ++i)
            result.elements[i] = 0.0f;

        float tanHalfFov = std::tan(fovRadians / 2.0f);
        result.elements[0] = 1.0f / (aspect * tanHalfFov);
        result.elements[5] = 1.0f / tanHalfFov;
        result.elements[10] = -(zFar + zNear) / (zFar - zNear);
        result.elements[11] = -1.0f;
        result.elements[14] = -(2.0f * zFar * zNear) / (zFar - zNear);
        return result;
    }

    inline Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
        Vec3 f = Normalize(center - eye);
        Vec3 s = Normalize(Cross(f, up));
        Vec3 u = Cross(s, f);

        Mat4 result = Mat4::Identity();
        result.elements[0] = s.x;
        result.elements[4] = s.y;
        result.elements[8] = s.z;

        result.elements[1] = u.x;
        result.elements[5] = u.y;
        result.elements[9] = u.z;

        result.elements[2] = -f.x;
        result.elements[6] = -f.y;
        result.elements[10] = -f.z;

        result.elements[12] = -Dot(s, eye);
        result.elements[13] = -Dot(u, eye);
        result.elements[14] = Dot(f, eye);
        return result;
    }
}

#endif // MATH_H
