#pragma once

#define MY_PI 3.14159265f
#define DEG2RAD MY_PI/180.0f
#define RAD2DEG 180/MY_PI

#define FLOATCOMPACCURATE 0.0001f

namespace EmMaths
{
    // ----------------- [Vector] -----------------
#pragma region Vector

    class Float2
    {
    public:
        float x;
        float y;

        float CrossProduct2D(Float2 other) const;

        float DotProduct(const Float2* other) const;

        void PlanRotation(float angle);

        Float2 operator+(Float2& other);
        Float2 operator*(float& multiplicator);
        bool operator==(Float2& other) { return (x == other.x) && (y == other.y); }

        float Magnitude();

        Float2 operator/(float divider);
    };

    class Float3
    {
    public:
        float x;
        float y;
        float z;

        Float3 CrossProduct(const Float3& other) const;

        float DotProduct(const Float3 vec3) const;

        Float3 operator+(Float3& other);
        Float3 operator-(Float3& other);
        Float3 operator-();
        Float3 operator*(float& multiplicator);
        Float3 operator*(int& multiplicator);
        friend Float3 operator+(const Float3& left, const Float3& right);
        friend Float3 operator-(const Float3& left, const Float3& right);
        friend Float3 operator*(const Float3& left, const float multiplier);
        friend Float3 operator/(const Float3& left, const float divider);

        friend Float3& operator+=(Float3& left, const Float3& right);
        friend Float3& operator-=(Float3& left, const Float3& right);
        friend Float3& operator*=(Float3& left, const float multipler);
        friend Float3& operator/=(Float3& left, const float divider);

        friend bool operator<(const Float3& left, const Float3& right);
        friend bool operator<=(const Float3& left, const Float3& right);
        friend bool operator>(const Float3& left, const Float3& right);
        friend bool operator>=(const Float3& left, const Float3& right);


        Float3(float x = 0, float y = 0, float z = 0);

        float magnitude();

        void normalize();

        Float3 getNormalized();

        bool operator==(Float3 other)
        {
            return (x <= other.x + FLOATCOMPACCURATE && x >= other.x - FLOATCOMPACCURATE) && (y <= other.y +
                FLOATCOMPACCURATE && y >= other.y - FLOATCOMPACCURATE) && (z <= other.z + FLOATCOMPACCURATE && z >=
                other.z - FLOATCOMPACCURATE);
        }


        static Float3 getSphericalCoords(float r, float theta, float phi);
        static Float3 Lerp(const Float3& a, const Float3& b, const float& time);
    };

    inline bool operator==(const EmMaths::Float3& f1, const EmMaths::Float3& f2)
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

    class Quaternion;
    
    class Mat4
    {
    private:
        Mat4 getSubmat(int l, int c);

    public:
        Mat4();
        Mat4(float matrix[4][4]);
        
        static Mat4 getRotationX(const float& angle);
        static Mat4 getRotationY(const float& angle);
        static Mat4 getRotationZ(const float& angle);

        static Mat4 getTranslation(const Float3& translation);
        static Mat4 getScale(const Float3& scale);

        float mat[4][4] = {
            {1.f, 0.f, 0.f, 0.f},
            {0.f, 1.f, 0.f, 0.f},
            {0.f, 0.f, 1.f, 0.f},
            {0.f, 0.f, 0.f, 1.f}
        };

        void operator=(const Mat4& other);
        void operator=(const float matrix[4][4]);

        static Mat4 CreateTransformMatrix(const Float3& position, const Float3& rotationDEG, const Float3& scale);
        static Mat4 CreateTransformMatrix(const Float3& position, const Quaternion& rotation, const Float3& scale);

        Mat4 operator*(const Mat4& other) const;
        Float4 operator*(const Float4& ft4);
        Mat4 operator*(const float& mult);
        Mat4 operator*(const int& mult);

        const float* AsPtr() const;
        
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

    // --------------- [Quaternion] ---------------
#pragma region Quaternion

    class Quaternion
    {
    public:
        float a, b, c, d;

        Quaternion();
        Quaternion(const float& _a, const float& _b, const float& _c, const float& _d);
        Quaternion(const float& roll, const float& pitch, const float& yaw);
        Quaternion(const Float3& eulerAngles);

        void Normalize();
        Quaternion GetNormalized() const; 

        float Modulus() const;
        float SquaredModulus() const;

        //Return corresponding rotation matrix
        Mat4 GetRotationMatrix() const;
        
        static Quaternion Hamilton(const Quaternion& right, const Quaternion& left);
        
        //Return a Quaternion from corresponding Euler Angles
        static Quaternion Euler(const float& roll, const float& pitch, const float& yaw);
        //Return a Quaternion from corresponding Euler Angles
        static Quaternion Euler(const Float3& eulerAngles);
        
        //Return a Quaternion from corresponding axis and radian angle
        static Quaternion AngleAxis(const Float3& axis, const float& angle);
        
        static Quaternion SLerp(const Quaternion& first, const Quaternion& second, float t);
        static Quaternion NLerp(const Quaternion& first, const Quaternion& second, float t);

        static float DotProduct(const Quaternion& first, const Quaternion& second);
        
        Quaternion operator*(const Quaternion& other) const;
        Quaternion operator*(const float& other) const;
        Quaternion operator+(const Quaternion& other) const;
    }; 


#pragma endregion

    // ------------------ [Misc] ------------------
#pragma region Misc
    namespace Misc
    {
        class Circle
        {
        public:
            Float2 center;
            float radius;
        };

        typedef struct Triangle
        {
            Float2 vertex[3];
        } Triangle;

        template <typename T>
        T Min(const T& a, const T& b)
        {
            return a < b ? a : b;
        }

        template <typename T>
        T Max(const T& a, const T& b)
        {
            return a > b ? a : b;
        }
        
        template <typename T>
        T Abs(const T& a)
        {
            return a < 0 ? -a : a;
        }

        float Lerp(const float& t, const float& a, const float& b);
        
        float Pythagoreantheorem(int nb_values, ...);

        float getPointYByLineEquation(Float2 line, Float2 point);

        Float2 barrycentre(int nb_values, ...);

        Float3 barrycentreF3(Float3 point1, Float3 point2, Float3 point3);

        Float3 calcNormal(const Float3& p1, const Float3& p2, const Float3& p3);
    }
#pragma endregion
}
