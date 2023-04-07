#include "SpriteCodex.h"
#include "Sprite.cpp" // vẽ màn hình chiến thắng
#include <assert.h> // cung cấp một macro gọi là assert có thể được sử dụng để kiểm tra một giả định được tạo bởi chương trình và in một thông báo chẩn đoán tìm lỗi nếu giả định này là false.

void SpriteCodex::DrawWin(const Vei2 &pos, Graphics &gfx)
{
    DrawWon(pos, gfx); // Vẽ màn hình chiến thắng
}

void SpriteCodex::DrawTile0(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tile0.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTile1(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tile1.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTile2(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tile2.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTile3(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tile3.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTile4(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tile4.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTile5(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tile5.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTile6(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tile6.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTile7(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tile7.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTile8(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tile8.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTileButton(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tileButton.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTileCross(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tileCross.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTileFlag(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tileFlag.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTileBomb(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tileBomb.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawTileBombRed(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/tileBombRed.png"));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawBackground(const Vei2 &pos, Graphics &gfx)
{
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(":/Image/background.png")); // Vẽ nền đen che setting
}

void SpriteCodex::DrawTileNumber(const Vei2 & pos, int n, Graphics & gfx)
{
    assert(n >= 0 && n <= 8); // yêu cầu nằm trong khoảng 0-8
    // vẽ số lượng bom quanh gạch
    switch (n)
    {
    case 0:
        DrawTile0(pos, gfx);
        break;
    case 1:
        DrawTile1(pos, gfx);
        break;
    case 2:
        DrawTile2(pos, gfx);
        break;
    case 3:
        DrawTile3(pos, gfx);
        break;
    case 4:
        DrawTile4(pos, gfx);
        break;
    case 5:
        DrawTile5(pos, gfx);
        break;
    case 6:
        DrawTile6(pos, gfx);
        break;
    case 7:
        DrawTile7(pos, gfx);
        break;
    case 8:
        DrawTile8(pos, gfx);
        break;
    }
}

void SpriteCodex::DrawButtonOn(const Vei2 &pos, const int &index, Graphics &gfx)
{
    QString fileName = ":/Image/"; // đường dẫn image
    if(index == 0)
    {
        fileName += "notFlag.png";
    }
    else if (index == 1)
    {
        fileName += "los.png";
    }
    // QPainter. Vẽ hình ảnh đã cho tại điểm nhất định.
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(fileName));  // Xây dựng một hình ảnh và cố gắng tải hình ảnh từ tệp với tên tệp đã cho.
}

void SpriteCodex::DrawButtonOff(const Vei2 &pos, const int &index, Graphics &gfx)
{
    QString fileName = ":/Image/";
    if(index == 0)
    {
        fileName += "buttonFlag.png";
    }
    else if (index == 1)
    {
        fileName += "playing.png";
    }
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(fileName));
}

void SpriteCodex::DrawTimer(const Vei2 &pos, Graphics &gfx, const int &timer) // Vẽ thời gian
{
    assert(timer >= 0 && timer <= 9);
    QString fileName = ":/Image/";
    switch (timer)
    {
    case 0:
        fileName += "frame0.png";
        break;
    case 1:
        fileName += "frame1.png";
        break;
    case 2:
        fileName += "frame2.png";
        break;
    case 3:
        fileName += "frame3.png";
        break;
    case 4:
        fileName += "frame4.png";
        break;
    case 5:
        fileName += "frame5.png";
        break;
    case 6:
        fileName += "frame6.png";
        break;
    case 7:
        fileName += "frame7.png";
        break;
    case 8:
        fileName += "frame8.png";
        break;
    case 9:
        fileName += "frame9.png";
        break;
    }
    gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(fileName));
}

void SpriteCodex::DrawSetting(const Vei2 &pos, Graphics &gfx, const int &indexW, const int &indexH) // Vẽ cài đặt
{
    assert(indexW >= 0 && indexW <= 4 && indexH >= 0 && indexH <= 3);
    QString fileName = ":/Image/";
    switch (indexH) {
    case 0:
        switch (indexW) {
        case 0:
            fileName += "frameW.png";
            break;
        case 1:
            fileName += "frame-.png";
            break;
        case 4:
            fileName += "frame+.png";
            break;
        }
        break;
    case 1:
        switch (indexW) {
        case 0:
            fileName += "frameH.png";
            break;
        case 1:
            fileName += "frame-.png";
            break;
        case 4:
            fileName += "frame+.png";
            break;
        }
        break;
    case 2:
        switch (indexW) {
        case 0:
            fileName += "frameBom.png";
            break;
        case 1:
            fileName += "frame-.png";
            break;
        case 4:
            fileName += "frame+.png";
            break;
        }
        break; // luu y
    case 3:
        switch (indexW) {
        case 0:
            fileName += "frameClose.png";
            break;
        case 4:
            fileName += "frameOk.png";
            break;
        }
        break;
    }
    if (fileName != ":/Image/") // nếu có file được chọn
    {
        gfx.getPaint()->drawImage(QPoint(pos.x, pos.y), QImage(fileName));
    }
}
