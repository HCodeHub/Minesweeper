#include "Mouse.h"

Mouse::Mouse()
    : // Danh sách khởi tạo
      x(0)
    , y(0)
{
}

void Mouse::setXY_Type(const int &xm, const int &ym, const Type &typeM)
{
    // Cập nhật
    x = xm;
    y = ym;
    type = typeM;
}

const int &Mouse::GetX() const
{
    return x; // Trả về tọa độ x
}

const int &Mouse::GetY() const
{
    return y; // Trả về tọa độ y
}

Vei2 Mouse::GetPos() const
{
    return {x, y}; // Trả về tọa độ dưới dạng Vei2
}

Mouse::Type Mouse::GetType() const
{
    return type; // Trả về Sự kiện nhấn chuột
}


