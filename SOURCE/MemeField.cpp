#include "MemeField.h"
#include "SpriteCodex.h" // chứa code pixed
#include <assert.h> // cung cấp macro gọi là assert có thể được sử dụng để kiểm tra một giả định được tạo bởi chương trình và in một thông báo chẩn đoán tìm lỗi nếu giả định này là false.
#include <random> // Thư viện số ngẫu nhiên cung cấp các lớp tạo số ngẫu nhiên và giả ngẫu nhiên.

void MemeField::Tile::SpawnMeme()
{
    assert(!hasMeme); // yêu cầu chưa có meme trước khi tạo
    hasMeme = true; // có meme
}

bool MemeField::Tile::HasMeme() const
{
    return hasMeme; // trả về có Meme hay không
}

void MemeField::Tile::Draw(const Vei2 &screenPos, MemeField::State fieldState , Graphics &gfx) const
{
    if(fieldState != MemeField::State::Lose) // nếu chưa chạm bom
    {
        switch(state) // trạng thái hiện tại
        {
        case State::Hidden: // Ẩn
            SpriteCodex::DrawTileButton(screenPos, gfx); // vẽ ô gạch tại tọa độ
            break; // thoát
        case State::Flagged: // Cờ
            SpriteCodex::DrawTileFlag(screenPos, gfx); // vẽ cờ
            break;
        case State::Revealed: // Lộ
            if(!hasMeme)
            {
                SpriteCodex::DrawTileNumber(screenPos, nNeighborMemes, gfx); // vẽ số lượng bom quanh gạch
            }else {
                SpriteCodex::DrawTileBomb(screenPos, gfx); // vẽ bom
            }
        }
    }else { // we are fucked
        switch(state) // trạng thái hiện tại
        {
            case State::Hidden: // Ẩn
            if (HasMeme()) // nếu có Meme
            {
                SpriteCodex::DrawTileBomb(screenPos, gfx); // vẽ bom
            }else {
                SpriteCodex::DrawTileButton(screenPos, gfx); // vẽ ô gạch tại tọa độ
            }
            break; // thoát
        case State::Flagged: // Cờ
            if (HasMeme()) // nếu có Meme
            {
                SpriteCodex::DrawTileBomb(screenPos, gfx); // vẽ bom
                SpriteCodex::DrawTileFlag(screenPos, gfx); // vẽ cờ
            }else {
                SpriteCodex::DrawTileBomb(screenPos, gfx); // vẽ bom
                SpriteCodex::DrawTileCross(screenPos, gfx); // vẽ gạch chéo
            }
            break;
        case State::Revealed: // Lộ
            if(!HasMeme()) // nếu không có meme
            {
                SpriteCodex::DrawTileNumber(screenPos, nNeighborMemes, gfx); // vẽ số lượng bom quanh gạch
            }else {
                SpriteCodex::DrawTileBombRed(screenPos, gfx); // vẽ bom chạm
            }
        }
    }
}

void MemeField::Tile::Reveal()
{
    assert(state == State::Hidden); // yêu cầu tình trạng hiện tại ẩn
    state = State::Revealed; // Tình trạng hiện tại lộ
}

bool MemeField::Tile::IsRevealed() const
{
    return state == State::Revealed; // trả về true nếu trạng thái lộ
}

void MemeField::Tile::ToggleFlag()
{
    assert(!IsRevealed()); // yêu cầu trạng thái chưa lộ
    if(state == State::Hidden) // nếu trạng thái == ẩn
    {
        state = State::Flagged; // trạng thái gắn cờ
    }else {
        state = State::Hidden; // trạng thái ẩn
    }
}

bool MemeField::Tile::IsFlagged() const
{
    return state == State::Flagged; // trả về true nếu trạng thái là gắn cờ
}

bool MemeField::Tile::HasNoNeighborMemes() const
{
    return nNeighborMemes == 0; // trả về true nếu không có memes hàng xóm
}

void MemeField::Tile::SetNeighborMemeCount(int memeCount)
{
    assert(nNeighborMemes == -1); // yêu cầu chưa có số lượng meme hàng xóm từ trước
    nNeighborMemes = memeCount; // memes hàng xóm = số lượng meme đếm được quanh gạch
}

MemeField::MemeField(const Vei2 &center, const int& nWidth, const int& nHeight, const int &nMemes)
    : // góc trên trái khung
      width(nWidth) // số ô theo chiều ngang
    , height(nHeight)
    , topLeft(center.x + SpriteCodex::borderThickness, center.y + SpriteCodex::borderThickness + SpriteCodex::buttonSizeH) // vị trí đồng nhất
{
    assert(width <= 42 && height <= 42); // giới hạn mảng
    assert(nMemes > 0 && nMemes < width * height); // yêu cầu số lượng nMeme > 0 và < kích thước khung
    std::random_device rd; // một trình tạo số nguyên ngẫu nhiên được phân phối đồng đềum, tạp ra các số ngẫu nhiên không xác định.
    // Nó tạo ra các số giả ngẫu nhiên 32 bit bằng cách sử dụng thuật toán nổi tiếng và phổ biến có tên là thuật toán Mersenne twister.
    std::mt19937 rng(rd()); // rng(seed_value) là một thể hiện của lớp mt19937 và nó nhận một giá trị gốc để tạo toàn bộ chuỗi.
    std::uniform_int_distribution<int> xDist(0, width -1); // Trả về một số ngẫu nhiên mới tuân theo các tham số của phân phối.
    std::uniform_int_distribution<int> yDist(0, height -1);

    for(int nSpawned = 0; nSpawned < nMemes; ++nSpawned)
    {
        Vei2 spawnPos; // Tọa độ meme
        do {
            spawnPos = {xDist(rng), yDist(rng)}; // Tọa độ meme mới ngẫu nhiên
        } while (TileAt(spawnPos).HasMeme()); // nếu tạo độ có gạch thì tạo lại
        TileAt(spawnPos).SpawnMeme(); // tạo meme mới
    }
    //?
    for(Vei2 gridPos = {0, 0}; gridPos.y < height; ++gridPos.y) // height
    {
        for (gridPos.x = 0; gridPos.x < width; ++gridPos.x) // width
        {
            // Đặt số lượng memes hàng xóm
            TileAt(gridPos).SetNeighborMemeCount(CountNeighborMemes(gridPos)); // Đếm số lượng meme hàng xóm // tọa độ
        }
    }
}

void MemeField::Draw(Graphics &gfx)
{
    // Vẽ hình chữ nhật bị che, làm viền
    gfx.DrawRect(GetRect().GetExpanded(SpriteCodex::borderThickness), borderColor); // Hình chữ nhật của cánh đồng, độ dày đường viền, màu đường viền

    for (Vei2 gridPos = {0,0}; gridPos.y < height; ++gridPos.y) // duyệt chiều cao khung
    {
        for (gridPos.x = 0; gridPos.x < width; ++gridPos.x) // Chiều rộng khung
        {
            // Vẽ tại vị trí
            TileAt(gridPos).Draw(topLeft + gridPos * SpriteCodex::tileSize, state, gfx);
        }
    }
}

RectI MemeField::GetRect() const
{
    return RectI(topLeft, width * SpriteCodex::tileSize, height * SpriteCodex::tileSize); // Trả về hình chữ nhật của cánh đồng
}

// chuột trái
void MemeField::OnRevealClick(const Vei2 &mousePos)
{
    if (state == State::Memeing) // chưa chạm bom
    {
        const Vei2 gridPos = ScreenToGrid(mousePos); // lấy tọa độ lưới
        assert(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height); // yêu cầu tọa độ trong giới hạn
        RevealTile(gridPos); // Truyền tọa độ lưới, quét meme
        if (GameIsWon()) // Nếu win
        {
            state = State::Winrar; // Trạng thái win
        }
    }
}

void MemeField::OnFlagClick(const Vei2 &screenPos)
{
    if(state == State::Memeing) // Chưa chạm bom
    {
        const Vei2 gridPos = ScreenToGrid(screenPos); // lấy tọa độ lưới
        assert(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height); // yêu cầu tọa độ trong giới hạn
        Tile& tile = TileAt(gridPos); // Lấy vị trí gạch
        if (!tile.IsRevealed()) // Nếu trạng thái không lộ và không gắn cờ
        {
            tile.ToggleFlag(); // Gắn hoặc ẩn cờ
        }
        if (GameIsWon()) // Nếu win
        {
            state = State::Winrar; // Trạng thái win
        }
    }
}

// Lớp enum State nằm trong MemeField nên phải khai báo MemeField::State
MemeField::State MemeField::GetState() const
{
    return state; // Trả về trạng thái
}

void MemeField::RevealTile(const Vei2 &gridPos)
{
    Tile& tile = TileAt(gridPos); // Lấy vị trí gạch
    if(!tile.IsRevealed() && !tile.IsFlagged()) // Nếu trạng thái không lộ và không gắn cờ
    {
        tile.Reveal(); // Đặt trạng thái là lộ
        if(tile.HasMeme()) // nếu có bom
        {
            state = State::Lose; // Trạng thái chạm bom
            //sndLose.Play(); // Phát nhạc
        } else if (tile.HasNoNeighborMemes()) // nếu không có meme hàng xóm
        {
            const int xStart = std::max(0, gridPos.x -1);
            const int yStart = std::max(0, gridPos.y -1); // Từ y -1
            const int xEnd = std::min(width -1, gridPos.x +1);
            const int yEnd = std::min(height -1, gridPos.y +1); // đến y +1

            // Duyệt 9 ô trong khu vực nhấn chuột
            for(Vei2 gridPos = {xStart, yStart}; gridPos.y <= yEnd; ++gridPos.y) // y -1 đến y +1
            {
                for (gridPos.x = xStart; gridPos.x <= xEnd; ++gridPos.x) // x -1 đến x +1
                {
                    RevealTile(gridPos); // Đệ quy, tàu quét mìn
                }
            }
        }
    }
}

MemeField::Tile &MemeField::TileAt(const Vei2 &gridPos)
{
    return field[gridPos.y * width + gridPos.x]; // Vị trí gạch trong mảng 1d
}

const MemeField::Tile &MemeField::TileAt(const Vei2 &gridPos) const
{
    return field[gridPos.y * width + gridPos.x]; // Vị trí gạch trong mảng 1d
}

Vei2 MemeField::ScreenToGrid(const Vei2 &screenPos)
{
    return (screenPos - topLeft) / SpriteCodex::tileSize; // Tọa độ chuột - tọa độ cạnh trên trái khung meme / kích thước 1 ô
}

int MemeField::CountNeighborMemes(const Vei2 &gridPos)
{
    const int xStart = std::max(0, gridPos.x -1);
    const int yStart = std::max(0, gridPos.y -1); // Từ y -1
    const int xEnd = std::min(width -1, gridPos.x +1);
    const int yEnd = std::min(height -1, gridPos.y +1); // đến y +1

    int count = 0; // đếm meme
    // Duyệt 9 ô trong khu vực nhấn chuột
    for(Vei2 gridPos = {xStart, yStart}; gridPos.y <= yEnd; ++gridPos.y) // y -1 đến y +1
    {
        for (gridPos.x = xStart; gridPos.x <= xEnd; ++gridPos.x) // x -1 đến x +1
        {
            // có meme thì tăng 1
            if(TileAt(gridPos).HasMeme()) // Vị trí gạch trong mảng
            {
                ++count;
            }
        }
    }
    return count; // Trả về số lượng meme
}

bool MemeField::GameIsWon() const
{
    for(int i = 0; i < width * height; ++i) // duyệt số ô đã đặt
    {
        if ((field[i].HasMeme() && !field[i].IsFlagged()) ||   // nếu có meme và chưa gắn cờ
            (!field[i].HasMeme() && !field[i].IsRevealed()) ) // nếu không có meme và trạng thái không lộ
        {
            return false; // chưa win
        }
    }

    return true;
}

// Vẽ hình chữ nhật // Bỏ
//gfx.DrawRect(GetRect(), SpriteCodex::baseColor); // Hình chữ nhật, màu
//gfx.DrawRect(GetRect().GetExpanded(borderThickness), borderColor); // Hình chữ nhật của cánh đồng, độ dày đường viền, màu đường viền
//, memes(nMemes)
