#include "RectI.h"

RectI::RectI(float left_in, float right_in, float top_in, float bottom_in)
    : // danh sách khởi tạo
    left(left_in),
    right(right_in),
    top(top_in),
    bottom(bottom_in)
{
}

RectI::RectI(const Vei2 &topLeft, const Vei2 &bottomRight)
    :
    RectI(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y) // function overloading
{
}

RectI::RectI(const Vei2 &topLeft, float width, float height)
    :
    RectI(topLeft, topLeft + Vei2(width, height)) // function overloading
{
}

// 2 hình chữ nhật(đối tượng) đang chồng chéo vào nhau, sự va chạm
bool RectI::IsOverlappingWidth(const RectI &other) const
{
    return right > other.left && left < other.right
            && bottom > other.top && top < other.bottom; // kiểm tra hình chữ nhật này có va chạm với hình chữ nhật kia
}

bool RectI::IsContainedBy(const RectI &other) const
{
    return left >= other.left && right <= other.right
            && top >= other.top && bottom <= other.bottom; // kiểm tra hình chữ nhật này có nằm trong hình chữ nhật kia không.
}

bool RectI::Contains(const Vei2 &point) const
{
    return point.x > left && point.x < right
        && point.y >= top && point.y < bottom; // Kiểm tra tọa độ có nằm trong khung chứa không
}

RectI RectI::FromCenter(const Vei2 &center, float halfWidth, float halfHeight)
{
    const Vei2 half(halfWidth, halfHeight); // một nửa chiều rộng và nửa chiều cao.
    return RectI(center - half, center + half); // trả về góc trên bên trái và góc dưới bên phải.
}

RectI RectI::GetExpanded(int offset) const
{
    // tăng giảm kích thước gạch, tạo khe hở
    return RectI(left - offset, right + offset, top - offset, bottom + offset);
}

Vei2 RectI::GetCenter() const
{
    return Vei2((left + right) / 2.0f, (top + bottom) / 2.0f); // trả về tọa độ tâm
}
