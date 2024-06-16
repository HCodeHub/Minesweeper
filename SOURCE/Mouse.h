#ifndef MOUSE_H
#define MOUSE_H
#pragma once

#include "Vei2.h" // điểm, tọa độ

// Sự kiện chuột
class Mouse
{
public:
    // class enum (còn được gọi là enum có phạm vi), làm cho các enum được nhấn mạnh và phạm vi mạnh hơn.
    enum class Type // Sự kiện nhấn chuột
    {
        LPress, // Chuột trái
        RPress // Chuột phải
    };
public:
    Mouse(); // khởi tạo mặc định
    void setXY_Type(const int &xm, const int &ym, const Mouse::Type &typeM);
    // trả về tọa độ x
    const int& GetX() const; // Tham chiếu hằng
    const int& GetY() const;
    Vei2 GetPos() const; // Trả về tọa độ dưới dạng Vei2
    Type GetType() const; // Trả về Sự kiện nhấn chuột

private:
    int x;
    int y;
    Type type; // Sự kiện nhấn chuột
};

#endif // MOUSE_H
