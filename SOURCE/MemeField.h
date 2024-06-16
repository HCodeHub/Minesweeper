#ifndef MEMEFIELD_H
#define MEMEFIELD_H
#pragma once

#include "Graphics.h" // sử lý, hiển thị hình ảnh

class MemeField
{
public:
    // lưu ý: đặt State trước class Tile để dùng trong Tile
    enum class State
    {
        Lose, // thua
        Winrar, // thắng
        Memeing // đang chơi
    };
private:    
    class Tile // Tương đương Tile *tile // Ngói
    {
    public:
        //class enum (còn được gọi làm enum có phạm vi), làm cho các enum được nhấn mạnh và phạm vi mạnh hơn.
        // "enum class" defines this as a scoped enumeration instead of a standard enumeration.
        enum class State // Trạng thái
        {
            Hidden, // Ẩn
            Flagged, // Cờ
            Revealed // Lộ
        };
    public:
        void SpawnMeme (); // Meme đẻ trứng
        bool HasMeme () const; // Trả về Meme có hay không
        void Draw (const Vei2& screenPos, MemeField::State fieldState, Graphics& gfx) const; // vẽ
        void Reveal (); // chuyển trạng thái lộ
        bool IsRevealed () const; // trả về true nếu trạng thái lộ
        void ToggleFlag (); // gắn hoặc ẩn cờ
        bool IsFlagged () const; // kiểm tra cờ
        bool HasNoNeighborMemes () const; // không có memes hàng xóm
        void SetNeighborMemeCount (int memeCount); // Đặt số lượng meme hàng xóm
    private:
        State state = State::Hidden; // Tình trạng hiện tại ẩn
        bool hasMeme = false; // meme hiện tại = false
        int nNeighborMemes = -1; // Đếm số bom, hàng xóm.
    };
public:
    MemeField (const Vei2& center, const int &width, const int &height, const int &nMemes); // khởi tạo số lượng meme(bom)
    void Draw (Graphics& gfx); // Vẽ tại vị trí trong mảng 1d
    RectI GetRect () const; // Trả về hình chữ nhật
    void OnRevealClick (const Vei2& mousePos); // Tiết lộ khi nhấn chuột trái
    void OnFlagClick (const Vei2& screenPos); // Gắn cờ khi nhấn chột phải
    State GetState () const; // Trả về trạng thái
private:
    void RevealTile (const Vei2& gridPos); // Tiết lộ gạch, tàu quét mìn
    Tile& TileAt (const Vei2& gridPos); // Trả về tọa độ gạch
    const Tile &TileAt (const Vei2& gridPos) const; // overloaded
    Vei2 ScreenToGrid (const Vei2& screenPos); // convert tọa độ màn hình sang tạo độ lưới
    int CountNeighborMemes (const Vei2& gridPos); // Đếm các memes hàng xóm(xung quanh gạch được mở)
    bool GameIsWon () const; // Trả về true nếu thắng

private:
    int width = 17; // số lượng ô meme theo chiều ngang
    int height = 17; // số lượng meme theo chiều dọc
    static constexpr QColor borderColor = { 0u,0u,255u }; // blue // màu đường viền
    Vei2 topLeft; // Tọa độ dịch chuyển
    State state = State::Memeing; // trạng thái đang chơi
    Tile field[1764]; // số lượng meme đặt số lớn khi chưa biết trước số lượng // mảng 1d
};

#endif // MEMEFIELD_H

//int memes = 20; // số bom
