#ifndef SPRITECODEX_H
#define SPRITECODEX_H
#pragma once

#include "Graphics.h" // xử lý pixed
#include <QDebug>

class SpriteCodex
{
public:
    static void DrawWin(const Vei2& pos, Graphics &gfx); // Vẽ màn hình chiến thắng
    // width and height of all tiles  // Chiều rộng và chiều cao của tất cả các gạch
    static constexpr int tileSize = 24; //16
    static constexpr int borderThickness = 6; // Độ dày đường viền
    // base color for all tiles  // Màu cơ bản cho tất cả các ô
    static constexpr QColor baseColor = { 192,192,192 };
    // Họa tiết gạch 16x16 giả sử (192,192,192) nền và gốc trên cùng bên trái
    // 16x16 tile sprites assume (192,192,192) background and top left origin
    static void DrawTile0( const Vei2& pos,Graphics& gfx ); // Vẽ số bom quanh ô
    static void DrawTile1( const Vei2& pos,Graphics& gfx );
    static void DrawTile2( const Vei2& pos,Graphics& gfx );
    static void DrawTile3( const Vei2& pos,Graphics& gfx );
    static void DrawTile4( const Vei2& pos,Graphics& gfx );
    static void DrawTile5( const Vei2& pos,Graphics& gfx );
    static void DrawTile6( const Vei2& pos,Graphics& gfx );
    static void DrawTile7( const Vei2& pos,Graphics& gfx );
    static void DrawTile8( const Vei2& pos,Graphics& gfx );
    // lưu ý: dùng nhiều lệnh pixed nhỏ gây ảnh hưởng tốc độ đồ họa, thay vào đó dùng 1 lệnh vẽ lớn hơn, hoặc thực hiện ít cập nhật pixed hơn
    static void DrawTileButton( const Vei2& pos,Graphics& gfx ); // Vẽ ô meme
    static void DrawTileCross( const Vei2& pos,Graphics& gfx ); // Vẽ cờ sai
    static void DrawTileFlag( const Vei2& pos,Graphics& gfx ); // Vẽ cờ
    static void DrawTileBomb( const Vei2& pos,Graphics& gfx ); // Vẽ bom
    static void DrawTileBombRed( const Vei2& pos,Graphics& gfx ); // Vẽ bom đã chạm
    // chức năng chọn gạch đầu vào hợp lệ 0-8
    // Tile selector function valid input 0-8
    static void DrawTileNumber(const Vei2& pos, int n, Graphics& gfx); // Vẽ số lượng bom quanh gạch

    static void DrawBackground(const Vei2& pos, Graphics& gfx); // vẽ nền đen
    static constexpr int buttonSizeW = 80; // kích thước button
    static constexpr int buttonSizeH = 40;
    // satic hàm toàn cục, tồn tại duy nhất và mãi mãi trong vòng đời của trương trình
    static void DrawButtonOn(const Vei2& pos, const int& index, Graphics& gfx); // vẽ button on
    static void DrawButtonOff(const Vei2& pos, const int& index, Graphics& gfx); // vẽ button off
    static void DrawTimer(const Vei2& pos, Graphics& gfx, const int& timer); // Vẽ thời gian
    static void DrawSetting(const Vei2& pos, Graphics& gfx, const int& indexW, const int& indexH); // Vẽ menu setting
};

#endif // SPRITECODEX_H
