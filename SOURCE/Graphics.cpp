#include "Graphics.h"
#include <assert.h> // cung cấp macro gọi là assert có thể được sử dụng để kiểm tra một giả định được tạo bởi chương trình và in một thông báo chẩn đoán tìm lỗi nếu giả định này là false.
//#include <QColor> // Cung cấp màu sắc dựa trên các giá trị RGB, HSV hoặc CMYK.

#include <QDebug>

// Vẽ 1 pixel(điểm ảnh)
Graphics::Graphics()
    : // Danh sách khởi tạo
      painter(nullptr)
{    
}

void Graphics::SetPaint(QPainter &p)
{
    painter = &p;
}

RectI Graphics::GetRect() const
{
    return RectI(0, ScreenWidth, 0, ScreenHeight); // Trả về tọa độ (ScreenWidth,ScreenHeight) bằng Rect
}

void Graphics::PutPixel(const int &x, const int &y, const QColor &c) // Vẽ 1 pixel(điểm ảnh)
{
    // Yêu cầu tọa độ không ở ngoài trương trình
    if(x >= 0 && x < ScreenWidth && y >= 0 && y < ScreenHeight)
    {
        painter->setPen(c); // Xây dựng một bút đường liền mạch với 1 chiều rộng và màu sắc đã cho.
        painter->drawPoint(x, y); // Vẽ một điểm duy nhất tại vị trí (x, y).
    }    
}

void Graphics::DrawRect(const int& x0, const int& y0, const int& x1, const int& y1, const QColor& c) // vẽ chữ nhật
{
    painter->setBrush(c); // Đặt màu cọ của họa sĩ.
    painter->drawRect(x0,y0,x1-x0,y1-y0); // Vẽ hình chữ nhật
}

void Graphics::DrawImage(const Vei2 &pos, const QString &fileName)
{
    painter->drawImage(QPoint(pos.x, pos.y), QImage(fileName));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}


/*
for(int y = y0; y < y1; ++y) // Height
{
    for (int x = x0; x < x1; ++x) // Width
    {
        PutPixel(x,y,c); // Vẽ từng điểm ảnh
    }
}
*/
//painter->end(); // Kết thúc quá trình vẽ
/*
assert(x >= 0);
assert(x < int(Graphics::ScreenWidth));
assert(y >= 0);
assert(y < int(Graphics::ScreenHeight));
*/
/*
QPainter *Graphics::getPaint()
{
    return painter;
}
*/
