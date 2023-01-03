#include <myMaths.hpp>
#include <math.h>

namespace myMaths
{
    // ----------------------------[Float 2]----------------------------

    float Float2::crossProduct2D(Float2 other) const
    {
        return this->x * other.y - this->y * other.x;
    }

    float Float2::dotProduct(Float2* other) const
    {
        return (this->x * other->x) + (this->y * other->y);
    }

    void Float2::planRotation(float angle)
    {
        float tmpx = this->x;
        this->x = this->x * cosf(DEG2RAD * angle) - this->y * sinf(DEG2RAD * angle);
        this->y = tmpx * sinf(DEG2RAD * angle) + this->y * cosf(DEG2RAD * angle);
    }

    Float2 Float2::operator+(Float2& other)
    {
        Float2 result;
        result.x = x + other.x;
        result.y = y + other.y;
        return result;
    }

    Float2 Float2::operator*(float& multiplicator)
    {
        return { x * multiplicator, y * multiplicator };
    }

    float Float2::magnitude()
    {
        return sqrtf(x * x + y * y);
    }

    Float2 Float2::operator/(float divider)
    {
        Float2 result;
        result.x = x / divider;
        result.y = y / divider;
        return result;
    }

    // ----------------------------[Float 3]----------------------------

    Float3::Float3(float inx, float iny, float inz)
    {
        x = inx;
        y = iny;
        z = inz;
    }



    Float3 Float3::crossProduct(Float3& other) const
    {
        Float3 result;

        result.x = y * other.z - z * other.y;
        result.y = x * other.z - z * other.x;
        result.z = y * other.x - x * other.y;

        return result;
    }

    float Float3::dotProduct(Float3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Float3 Float3::operator+(Float3& other)
    {
        Float3 result;
        result.x = x + other.x;
        result.y = y + other.y;
        result.z = z + other.z;
        return result;
    }

    Float3 Float3::operator-(Float3& other)
    {
        Float3 result;
        result.x = x - other.x;
        result.y = y - other.y;
        result.z = z - other.z;
        return result;
    }

    Float3 Float3::operator-()
    {
        return { -x, -y, -z };
    }

    Float3 Float3::operator*(float& multiplicator)
    {
        return { x * multiplicator, y * multiplicator, z * multiplicator };
    }

    Float3 Float3::operator*(int& multiplicator)
    {
        return { x * multiplicator, y * multiplicator, z * multiplicator };
    }

    float Float3::magnitude()
    {
        return sqrtf(x * x + y * y + z * z);
    }

    void Float3::normalize()
    {
        float mag = magnitude();

        x = x / mag;
        y = y / mag;
        z = z / mag;
    }

    Float3 Float3::getNormalized()
    {
        float mag = magnitude();

        return { x / mag, y / mag, z / mag };
    }



    // ----------------------------[Float 4]----------------------------

    Float4::Float4(float inx, float iny, float inz, float inw)
    {
        x = inx;
        y = iny;
        z = inz;
        w = inw;
    }

    Float4::Float4(const Float3& f3, float inw)
    {
        x = f3.x;
        y = f3.y;
        z = f3.z;
        w = inw;
    }

    float Float4::dotProduct(Float4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    Float4 Float4::operator+(Float4& other)
    {
        Float4 result;
        result.x = x + other.x;
        result.y = y + other.y;
        result.z = z + other.z;
        return result;
    }

    Float4 Float4::operator*(float& multiplicator)
    {
        return { x * multiplicator, y * multiplicator, z * multiplicator, w * multiplicator };
    }

    float Float4::magnitude()
    {
        return sqrtf(x * x + y * y + z * z);
    }

    void Float4::normalize()
    {
        float mag = magnitude();

        x = x / mag;
        y = y / mag;
        z = z / mag;
        w = w / mag;
    }

    Float4 Float4::getNormalized()
    {
        float mag = magnitude();

        return { x / mag, y / mag, z / mag, w / mag };
    }

    void Float4::homogenize()
    {
        if (w != 0)
        {
            x = x / w;
            y = y / w;
            z = z / w;
            w = w / w;
        }
    }

    Float4 Float4::getHomogenized()
    {
        if (w != 0)
            return { x / w, y / w, z / w, w / w };
        return { x, y, z, w };
    }

    Float3 Float4::getXYZF3()
    {
        return { x, y, z };
    }

    // ----------------------------[Matrix]----------------------------

    void Mat4::operator=(const Mat4& other)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat[i][j] = other.mat[i][j];
            }
        }
    }

    void Mat4::operator=(const float matrix[4][4])
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat[i][j] = matrix[i][j];
            }
        }
    }

    Float4 Mat4::operator*(const Float4& ft4)
    {
        Float4 result;

        result.x = mat[0][0] * ft4.x + mat[0][1] * ft4.y + mat[0][2] * ft4.z + mat[0][3] * ft4.w;
        result.y = mat[1][0] * ft4.x + mat[1][1] * ft4.y + mat[1][2] * ft4.z + mat[1][3] * ft4.w;
        result.z = mat[2][0] * ft4.x + mat[2][1] * ft4.y + mat[2][2] * ft4.z + mat[2][3] * ft4.w;
        result.w = mat[3][0] * ft4.x + mat[3][1] * ft4.y + mat[3][2] * ft4.z + mat[3][3] * ft4.w;

        return result;
    }

    Mat4 Mat4::operator*(const Mat4& other)
    {
        Mat4 res;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res.mat[i][j] = mat[i][0] * other.mat[0][j] + mat[i][1] * other.mat[1][j] + mat[i][2] * other.mat[2][j] + mat[i][3] * other.mat[3][j];
            }
        }
        return res;
    }

    Mat4 Mat4::operator*(const float& mult)
    {
        Mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.mat[i][j] = mat[i][j] * mult;
            }
        }
        return result;
    }

    Mat4 operator*(const float& mult, const Mat4& matrix)
    {
        Mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.mat[i][j] = matrix.mat[i][j] * mult;
            }
        }
        return result;
    }


    Mat4 Mat4::operator*(const int& mult)
    {
        Mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.mat[i][j] = mat[i][j] * mult;
            }
        }
        return result;
    }

    Float4 operator*(const Float4& ft4, const Mat4& matrix)
    {
        Float4 result;

        result.x = matrix.mat[0][0] * ft4.x + matrix.mat[0][1] * ft4.y + matrix.mat[0][2] * ft4.z + matrix.mat[0][3] * ft4.w;
        result.y = matrix.mat[1][0] * ft4.x + matrix.mat[1][1] * ft4.y + matrix.mat[1][2] * ft4.z + matrix.mat[1][3] * ft4.w;
        result.z = matrix.mat[2][0] * ft4.x + matrix.mat[2][1] * ft4.y + matrix.mat[2][2] * ft4.z + matrix.mat[2][3] * ft4.w;
        result.w = matrix.mat[3][0] * ft4.x + matrix.mat[3][1] * ft4.y + matrix.mat[3][2] * ft4.z + matrix.mat[3][3] * ft4.w;

        return result;
    }

    Mat4 Mat4::getRotationX(const float& angle)
    {
        Mat4 result;
        result.mat[0][0] = 1;

        result.mat[1][1] = cosf(angle);
        result.mat[1][2] = -sinf(angle);
        result.mat[2][1] = sinf(angle);
        result.mat[2][2] = cosf(angle);

        return result;
    }

    Mat4 Mat4::getRotationY(const float& angle)
    {
        Mat4 result;
        result.mat[1][1] = 1;

        result.mat[0][0] = cosf(angle);
        result.mat[2][0] = -sinf(angle);
        result.mat[0][2] = sinf(angle);
        result.mat[2][2] = cosf(angle);

        return result;
    }

    Mat4 Mat4::getRotationZ(const float& angle)
    {
        Mat4 result;
        result.mat[2][2] = 1;

        result.mat[0][0] = cosf(angle);
        result.mat[0][1] = -sinf(angle);
        result.mat[1][0] = sinf(angle);
        result.mat[1][1] = cosf(angle);

        return result;
    }

    Mat4 Mat4::getTranslation(const Float3& translation)
    {
        Mat4 result;

        result.mat[0][0] = 1;
        result.mat[1][1] = 1;
        result.mat[2][2] = 1;
        result.mat[3][3] = 1;

        result.mat[0][3] = translation.x;
        result.mat[1][3] = translation.y;
        result.mat[2][3] = translation.z;

        return result;
    }

    Mat4 Mat4::getScale(const Float3& scale)
    {
        Mat4 result;
        result.mat[0][0] = scale.x;
        result.mat[1][1] = scale.y;
        result.mat[2][2] = scale.z;
        result.mat[3][3] = 1;

        return result;
    }

    Mat4 Mat4::CreateTransformMatrix(const Float3& position, const Float3& rotationDEG, const Float3& scale)
    {
        return  getTranslation(position) * getRotationY(DEG2RAD * rotationDEG.y) * getRotationX(DEG2RAD * rotationDEG.x) * getRotationZ(DEG2RAD * rotationDEG.z) * getScale(scale);
    }

    Mat4 Mat4::getTransposedMatrix()
    {
        Mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.mat[i][j] = mat[j][i];
            }
        }
        return result;
    }

    float Mat4::getDeterminent()
    {
        return mat[0][0] * (mat[1][1] * mat[2][2] * mat[3][3] //afkp
            - mat[1][1] * mat[2][3] * mat[3][2] //aflo
            - mat[1][2] * mat[2][1] * mat[3][3] //agjp
            + mat[1][2] * mat[2][3] * mat[3][1] //agln
            + mat[1][3] * mat[2][1] * mat[3][2] //ahjo
            - mat[1][3] * mat[2][2] * mat[3][1]) //ahkn '

            - mat[0][1] * (mat[1][0] * mat[2][2] * mat[3][3] //bekp
                - mat[1][0] * mat[2][3] * mat[3][2] //belo
                - mat[1][2] * mat[2][0] * mat[3][3] //bgip
                + mat[1][2] * mat[2][3] * mat[3][0] //bglm
                + mat[1][3] * mat[2][0] * mat[3][2] //bhio
                - mat[1][3] * mat[2][2] * mat[3][0]) //bhkm 

            + mat[0][2] * (mat[1][0] * mat[2][1] * mat[3][3] //cejp
                - mat[1][0] * mat[2][3] * mat[3][1] //celn
                - mat[1][1] * mat[2][0] * mat[3][3] //cfip
                + mat[1][1] * mat[2][3] * mat[3][0] //cflm
                + mat[1][3] * mat[2][0] * mat[3][1] //chin
                - mat[1][3] * mat[2][1] * mat[3][0]) //chjm 

            - mat[0][3] * (mat[1][0] * mat[2][1] * mat[3][2] //dejo
                - mat[1][0] * mat[2][2] * mat[3][1] //dekn
                - mat[1][1] * mat[2][0] * mat[3][2] //dfio
                + mat[1][1] * mat[2][2] * mat[3][0] //dfkm
                + mat[1][2] * mat[2][0] * mat[3][1] //dgin
                - mat[1][2] * mat[2][1] * mat[3][0]) //dgjm
            ;
    }

    Mat4 Mat4::getIndentityMatrix()
    {
        Mat4 res;
        float matrice[4][4] = { {1.f, 0.f, 0.f, 0.f},
                               {0.f, 1.f, 0.f, 0.f},
                               {0.f, 0.f, 1.f, 0.f},
                               {0.f, 0.f, 0.f, 1.f} };

        res = matrice;
        return res;
    }

    Mat4 Mat4::getSubmat(int l, int c)
    {
        Mat4 sub;
        int line = 0;
        int collumn = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i != l && j != c)
                {
                    sub.mat[line][collumn] = mat[i][j];
                    collumn++;
                    if (collumn == 3)
                    {
                        collumn = 0;
                        line++;
                    }
                }
            }
        }
        return sub;
    }

    Mat4 Mat4::getCoMatrix()
    {
        Mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if ((i + j + 1) % 2 == 0)
                    result.mat[i][j] = -getSubmat(i, j).getDeterminent();
                else
                    result.mat[i][j] = getSubmat(i, j).getDeterminent();

            }
        }

        return result;
    }

    Mat4 Mat4::getComplementaryMat()
    {
        return getCoMatrix().getTransposedMatrix();
    }

    //If determinent is nul, return identity
    Mat4 Mat4::getInverseMatrix()
    {
        float det = getDeterminent();

        if (absoluteValue<float>(det) < 0.000005f)
            return getIndentityMatrix();

        return getComplementaryMat() * (1.f / det);
    }

    Float4 Mat4::getMatLine(int index)
    {
        if (index < 0 && index > 3)
            return 0;

        return (Float4) ( mat[index][0], mat[index][1], mat[index][2], mat[index][3] );
    }

    // -----------------------------------------------------------------
    float Pythagoreantheorem(int nb_values, ...)
    {
        va_list args;
        float nextValue;
        float result;

        va_start(args, nb_values);

        result = 0;
        for (int i = 0; i < nb_values; i++)
        {
            nextValue = va_arg(args, double);
            result += nextValue * nextValue;
        }
        va_end(args);

        return sqrt(result);
    }

    float getPointYByLineEquation(Float2 line, Float2 point)
    {
        return line.x * point.x + line.y;
    }

    Float2 barrycentre(int nb_values, ...)
    {
        va_list args;
        Float2 nextValue;
        Float2 result = { 0, 0 };

        va_start(args, nb_values);

        for (int i = 0; i < nb_values; i++)
        {
            nextValue = va_arg(args, Float2);
            result.x += nextValue.x;
            result.y += nextValue.y;
        }
        va_end(args);

        result.x = result.x / nb_values;
        result.y = result.y / nb_values;

        return result;
    }

    Float3 barrycentreF3(Float3 point1, Float3 point2, Float3 point3)
    {
        Float3 result = { 0, 0, 0 };

        result.x += point1.x + point2.x + point3.x;
        result.y += point1.y + point2.y + point3.y;
        result.z += point1.z + point2.z + point3.z;

        result.x = result.x / 3;
        result.y = result.y / 3;
        result.z = result.z / 3;

        return result;
    }

    Float3 calcNormal(const Float3& p1, const Float3& p2, const Float3& p3)
    {
        Float3 result{ 0 };
        // Calculate vectors
        float var1x = p2.x - p1.x;
        float var1y = p2.y - p1.y;
        float var1z = p2.z - p1.z;

        float var2x = p3.x - p1.x;
        float var2y = p3.y - p1.y;
        float var2z = p3.z - p1.z;

        // Get cross product of vectors
        result.x = (var1y * var2z) - (var2y * var1z);
        result.y = (var1z * var2x) - (var2z * var1x);
        result.z = (var1x * var2y) - (var2x * var1y);

        // Normalise final vector
        float vLen = sqrtf((result.x * result.x) + (result.y * result.y) + (result.z * result.z));

        result.x = result.x / vLen;
        result.y = result.y / vLen;
        result.z = result.z / vLen;

        return result;
    }
}
