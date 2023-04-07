#ifndef RECTI_H
#define RECTI_H
#pragma once

#include "Vei2.h" // điểm, tọa độ

// Xử lý hình chữ nhật
class RectI
{
public:
    RectI() = default;
    RectI(float left_in, float right_in, float top_in, float bottom_in); // cạnh trái, phải, trên, dưới
    RectI(const Vei2& topLeft, const Vei2& bottomRight); // điểm trên trái, dưới phải
    RectI(const Vei2& topLeft, float width, float height); // điểm trên trái, chiều rộng, chiều cao
    bool IsOverlappingWidth(const RectI& other) const; // Sự va chạm. Hai hình chữ nhật(đối tượng) đang chồng chéo lên nhau.
    bool IsContainedBy(const RectI& other) const; // kiểm tra hình chữ nhật này có nằm trong hình chữ nhật kia không.
    bool Contains(const Vei2& point) const; // kiểm tra tọa độ có nằm trong khung chứa không
    // trả về góc trên bên trái và góc dưới bên phải
    static RectI FromCenter(const Vei2& center, float halfWidth, float halfHeight);
    RectI GetExpanded(int offset) const; // mở rộng hình
    Vei2 GetCenter() const; // trả về tọa độ tâm
public:
    int left; // trái
    int right; // phải
    int top; // trên
    int bottom; // dưới
};

#endif // RECTI_H
