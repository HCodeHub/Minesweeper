#ifndef GRAPHICS_H
#define GRAPHICS_H
#pragma once

#include <QPainter> // Thực hiện sơn ở mức độ thấp trên các vật dụng và thiết bị sơn khác.
#include "RectI.h" // Xử lý hình chữ nhật

// Xử lý, hiển thị hình ảnh
class Graphics //: public QWidget
{
public:
    Graphics();    
    void PutPixel(const int& x,const int& y, const int& r, const int& g, const int& b) // overloaded
    {
        PutPixel(x, y, {r , g, b}); // gọi hàm PutPixel( int x,int y,Color c );
    }
    void PutPixel(const int& x, const int& y, const QColor& c); // Vẽ 1 pixel(điểm ảnh) // hạn chế dùng, hàm gây giảm hiệu xuất

    RectI GetRect() const; // Trả về tọa độ (ScreenWidth, ScreenHeight) bằng Rect
    void DrawRect(const int& x0, const int& y0, const int& x1, const int& y1, const QColor& c); // Vẽ hình chữ nhật
    void DrawRect(const RectI& rect, const QColor& c) // overloaded
    {
        DrawRect(rect.left, rect.top, rect.right, rect.bottom, c);
    }

    void setPaint(QPainter &p); // Đặt họa sĩ vẽ
    QPainter *getPaint(); // Trả về QPainter

public:
    // nâng cấp tự động lấy kích thức màn hình
    static constexpr int ScreenWidth = 720; // Chiều rộng trương trình
    static constexpr int ScreenHeight = 768;
private:
    QPainter *painter; // Họa sĩ vẽ
};

#endif // GRAPHICS_H

//Q_OBJECT // macro signal and slost

/*
void Paint(int x, int y, int r, int g, int b);
void drawImage(const Vei2 &pos, const QString &fileName); // viết lại
*/
