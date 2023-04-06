#ifndef VEI2_H
#define VEI2_H
#pragma once // lưu ý: khai báo chống đè lớp

// điểm, tọa độ
class Vei2
{
public:
    Vei2() = default; // khởi tạo không tham số
    Vei2(int x_in, int y_in); // tọa độ x,y
    // Toán tử cộng
    // Trả về tọa độ 2 Vec + nhau
    // const cuối không thay đổi giá trị trong lớp hiện tại
    Vei2 operator +(const Vei2& rhs) const; // lhs + rhs // const& tham chiếu hằng
    Vei2& operator +=(const Vei2& rhs); // Tọa độ Vec += Vec // trả về tham chiếu
    // cộng Vec với số nguyên
    Vei2 operator +(const int& rhs) const; // lhs + rhs // const& tham chiếu hằng
    Vei2& operator +=(const int& rhs); // Tọa độ Vec += rhs // trả về tham chiếu

    Vei2 operator *(int rhs) const; // Tọa độ Vec * rhs
    Vei2& operator *=(int rhs); // Tọa độ Vec *= rhs

    Vei2 operator -(const Vei2& rhs) const; // Tọa độ Vec - Vec
    Vei2& operator -=(const Vei2& rhs) ; // Tọa độ Vec -= Vec

    Vei2 operator /(int rhs) const; // Tọa độ Vec / rhs
    Vei2& operator /=(int rhs) ; // Tọa độ Vec /= rhs

    float GetLength() const; // Trả về độ dài cạnh C, tam giác cân
    int GetLengthSq() const; // Tinh cạnh C, tam giác cân

    static Vei2 topLeft(); // cố định cạnh trên trái khung
public:
    int x; // tọa độ xy
    int y;
};

#endif // VEI2_H
