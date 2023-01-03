#pragma once
#include <stdarg.h>

#define MY_PI 3.14159265
#define DEG2RAD MY_PI/180
#define RAD2DEG 180/MY_PI

#define FLOATCOMPACCURATE 0.0001f

namespace myMaths
{
    // ----------------- [Vector] -----------------
#pragma region Vector

    class Float2
    {
    public:
        float x;
        float y;

        float crossProduct2D(Float2 other) const;

        float dotProduct(Float2* other) const;

        void planRotation(float angle);

        Float2 operator+(Float2& other);
        Float2 operator*(float& multiplicator);
        bool operator==(Float2 other) { return (x == other.x) && (y == other.y); }

        float magnitude();

        Float2 operator/(float divider);
    };

    class Float3
    {
    public:
        float x;
        float y;
        float z;

        Float3 crossProduct(Float3& other) const;

        float dotProduct(Float3& other) const;

        Float3 operator+(Float3& other);
        Float3 operator-(Float3& other);
        Float3 operator-();
        Float3 operator*(float& multiplicator);
        Float3 operator*(int& multiplicator);

        Float3(float x = 0, float y = 0, float z = 0);

        float magnitude();

        void normalize();

        Float3 getNormalized();
        bool operator==(Float3 other) { return (x <= other.x + FLOATCOMPACCURATE && x >= other.x - FLOATCOMPACCURATE) && (y <= other.y + FLOATCOMPACCURATE && y >= other.y - FLOATCOMPACCURATE) && (z <= other.z + FLOATCOMPACCURATE && z >= other.z - FLOATCOMPACCURATE); }
    };

    inline bool operator==(const myMaths::Float3& f1, const myMaths::Float3& f2)
    {
        return ((f1.x == f2.x) && (f1.y == f2.y) && (f1.z == f2.z));
    }

    class Float4
    {
    public:
        float x;
        float y;
        float z;
        float w;

        float dotProduct(Float4& other) const;

        Float4 operator+(Float4& other);
        Float4 operator*(float& multiplicator);

        Float4(const Float3& f3, float w = 1.0f);
        Float4(float x = 0, float y = 0, float z = 0, float w = 1.0f);

        float magnitude();

        void normalize();
        Float4 getNormalized();

        void homogenize();
        Float4 getHomogenized();
        Float3 getXYZF3();

        inline void operator=(const Float3& f3)
        {
            x = f3.x;
            y = f3.y;
            z = f3.z;

            w = 1;
        }
    };

#pragma endregion Vector

    // ----------------- [Matrix] -----------------
#pragma region Matrix

    class Mat4
    {
    private:

        Mat4 getSubmat(int l, int c);

    public:
        static Mat4 getRotationX(const float& angle);
        static Mat4 getRotationY(const float& angle);
        static Mat4 getRotationZ(const float& angle);

        static Mat4 getTranslation(const Float3& translation);
        static Mat4 getScale(const Float3& scale);

        float mat[4][4] = { {1.f, 0.f, 0.f, 0.f},
                           {0.f, 1.f, 0.f, 0.f},
                           {0.f, 0.f, 1.f, 0.f},
                           {0.f, 0.f, 0.f, 1.f} };

        void operator=(const Mat4& other);
        void operator=(const float matrix[4][4]);

        static Mat4 CreateTransformMatrix(const Float3& position, const Float3& rotationDEG, const Float3& scale);

        Mat4 operator*(const Mat4& other);
        Float4 operator*(const Float4& ft4);
        Mat4 operator*(const float& mult);
        Mat4 operator*(const int& mult);

        Mat4 getTransposedMatrix();

        float getDeterminent();
        Mat4 getComplementaryMat();
        Mat4 getCoMatrix();
        Mat4 getInverseMatrix();
        static Mat4 getIndentityMatrix();

        Float4 getMatLine(int index);
    };

    Mat4 operator*(const float& mult, const Mat4& matrix);
    Float4 operator*(const Float4& ft4, const Mat4& matrix);

#pragma endregion Matrix

    // ----------------- [Misc] -----------------

    class Circle
    {
    public:
        Float2 center;
        float radius;
    };

    typedef struct Triangle
    {
        Float2 vertex[3];
    }Triangle;

    template <typename T>
    T absoluteValue(T value)
    {
        if (value < 0)
            return -value;
        else
            return value;
    }

    template <typename T>
    T lerp(T a, T b, float t)
    {
        return a * (1 - t) + b * t;
    }

    float Pythagoreantheorem(int nb_values, ...);

    float getPointYByLineEquation(Float2 line, Float2 point);

    Float2 barrycentre(int nb_values, ...);

    Float3 barrycentreF3(Float3 point1, Float3 point2, Float3 point3);

    Float3 calcNormal(const Float3& p1, const Float3& p2, const Float3& p3);
}
