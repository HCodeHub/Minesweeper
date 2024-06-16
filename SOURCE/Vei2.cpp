#include "Vei2.h"
#include <cmath> // thư viện toán học

Vei2::Vei2(int x_int, int y_int)
    :
    x(x_int),
    y(y_int) // danh sách khởi tạo
{
}

Vei2 Vei2::topLeft()
{
    return Vei2{1,1}; // cố định cạnh trên trái khung
}

Vei2 Vei2::operator +(const Vei2 &rhs) const
{
    return Vei2(x + rhs.x, y + rhs.y); // Trả về tọa độ 2 Vec + nhau
}

Vei2 &Vei2::operator +=(const Vei2 &rhs)
{
    return *this = *this + rhs; // overloaded
}

Vei2 Vei2::operator +(const int &rhs) const
{
    return Vei2(x + rhs, y + rhs); // Trả về tọa độ 2 Vec + nhau
}

Vei2 &Vei2::operator +=(const int &rhs)
{
    return *this = *this + rhs;
}

Vei2 Vei2::operator *(int rhs) const
{
    return Vei2(x * rhs, y * rhs); // Trả về tọa độ Vec * rhs
}

Vei2 &Vei2::operator *=(int rhs)
{
    return *this = *this * rhs;
}

Vei2 Vei2::operator -(const Vei2 &rhs) const
{
    return Vei2(x - rhs.x, y - rhs.y); // Trả về tọa độ 2 Vec - nhau
}

Vei2 &Vei2::operator -=(const Vei2 &rhs)
{
    return *this = *this - rhs;
}

Vei2 Vei2::operator /(int rhs) const
{
    return Vei2(x/rhs, y/rhs); // Trả về tọa độ 2 Vec / rhs
}

Vei2 &Vei2::operator /=(int rhs)
{
    return *this = *this / rhs;
}

float Vei2::GetLength() const
{
    // Trả về căn bậc 2 cạnh C
    return std::sqrt(float(GetLengthSq()));
}

int Vei2::GetLengthSq() const
{
    // Tính tam giác cân
    // c^2 = a^2 + b^2
    return x * x + y * y;
}
