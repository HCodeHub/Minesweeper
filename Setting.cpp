#include "Setting.h"
#include "SpriteCodex.h" // vẽ pixel
#include <assert.h> // Cung cấp macro gọi là assert có thể được sử dụng để kiểm tra một giả định được tạo bởi chương trình và in một thông báo chẩn đoán tìm lỗi nếu giả định này là false.
#include <QFile> // Cung cấp một giao diện để đọc và ghi vào tệp.
#include <QJsonDocument> // Cung cấp một cách để đọc và viết các tài liệu JSON.
#include <QJsonObject> // Đóng gói một đối tượng JSON.
#include <QStandardPaths> // cung cấp các phương thức để truy cập các đường dẫn chuẩn(android).

int memeWidth = 15; // số ô meme
int memeHeight = 15;
int memeBom = 30;

Setting::Setting(const Vei2 &center)
    : // danh sách khởi tạo
      jsonSetting(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/Minesweeper.json") // Lưu đường dẫn file
    , topLeft(center.x  + SpriteCodex::borderThickness, center.y  + SpriteCodex::borderThickness + SpriteCodex::buttonSizeH) // tọa độ + đường viền + chiều cao button
{

    FileSaveSetting();  // Gán dữ liệu file vào setting
}

void Setting::Button::Draw(const Vei2 &screenPos, Graphics &gfx, const int &indexW, const int& indexH)
{
    SpriteCodex::DrawSetting(screenPos, gfx, indexW, indexH);
    switch (indexH) {
    case 0:
        switch (indexW) {
        case 2:
            SpriteCodex::DrawTimer(screenPos, gfx, memeWidth / 10); // Vẽ số lượng
            break;
        case 3:
            SpriteCodex::DrawTimer(screenPos, gfx, memeWidth % 10); // Vẽ số lượng
            break;
        }
        break;
    case 1:
        switch (indexW) {
        case 2:
            SpriteCodex::DrawTimer(screenPos, gfx, memeHeight / 10); // Vẽ số lượng
            break;
        case 3:
            SpriteCodex::DrawTimer(screenPos, gfx, memeHeight % 10); // Vẽ số lượng
            break;
        }
        break;
    case 2:
        switch (indexW) {
        case 2:
            SpriteCodex::DrawTimer(screenPos, gfx, memeBom / 10); // Vẽ số lượng
            break;
        case 3:
            SpriteCodex::DrawTimer(screenPos, gfx, memeBom % 10); // Vẽ số lượng
            break;
        }
        break;
    }
}

void Setting::Draw(Graphics &gfx)
{
    for(Vei2 gridPos = {0,0}; gridPos.y < height; ++gridPos.y)
    {
        for(gridPos.x = 0; gridPos.x < width; ++gridPos.x)
        {
            // Vẽ tại vị trí
            ButtonAt(gridPos).Draw(topLeft + gridPos * sizeWidth, gfx, gridPos.x, gridPos.y); //
        }
    }
}

void Setting::OnInteractClick(const Vei2 &screenPos)
{
    const Vei2 gridPos = ScreenToGrid(screenPos); // Lấy tọa độ lưới
    if(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height)
    {
        //assert(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height); // yêu cầu tọa độ trong giới hạn
        switch (AtButton(gridPos)) {
        case 1:
            if(memeWidth * memeHeight > memeBom +3) --memeWidth;
            break;
        case 4:
            if(memeWidth < 42) ++memeWidth;
            break;
        case 6:
            if(memeHeight * memeWidth > memeBom +3) --memeHeight;
            break;
        case 9:
            if(memeHeight < 42) ++memeHeight;
            break;
        case 11:
            if(memeBom > 1) --memeBom;
            break;
        case 14:
            if(memeBom+1 < memeWidth * memeHeight)  ++memeBom;
            break;
        case 15:
            close = !close; // Thoát
            break;
        case 19:
            ok = true; // Đặt giá trị cho game
            break;
        }
    }
}

const bool &Setting::GetClose() const
{
    return close; // Thoát = true
}

const bool &Setting::GetOk() const
{
    return ok; // Đặt giá trị
}

void Setting::SetOk()
{
    ok = false;
}

const int &Setting::GetWidth() const
{
    return memeWidth;
}

const int &Setting::GetHeight() const
{
    return memeHeight;
}

const int &Setting::GetBoms() const
{
    return memeBom;
}

void Setting::SettingSaveFile() const
{
    QJsonDocument doc; // Tạo một tài liệu trống và không hợp lệ.
    QJsonObject obj; // Tạo một đối tượng JSON trống.
    // Gán dữ liệu từ setting vào file
    obj["memeWidth"] = memeWidth;
    obj["memeHeight"] = memeHeight;
    obj["memeBom"] = memeBom;

    doc.setObject(obj); // Đặt "đối tượng" làm đối tượng chính của tài liệu này.
    QByteArray data_json = doc.toJson(); // Chuyển đổi QJSonDocument thành tài liệu JSON được mã hóa UTF-8 thụt lề.
    QFile output(jsonSetting); // Xây dựng một đối tượng tệp mới để đại diện cho tệp với "tên" đã cho.
    // WriteOnly, Thiết bị đang mở để viết.
    // Text, Khi đọc các dấu cuối dòng được dịch thành '\n'.
    if(output.open(QIODevice::WriteOnly | QIODevice::Text)) // Mở thiết bị và đặt OpenMode ở "chế độ".
    {

        output.write(data_json); // Ghi nhiều nhất "maxSize" byte dữ liệu từ "dữ liệu" vào thiết bị.
        output.close(); // Đầu tiên phát ra aboutToClose(), sou đó đóng thiết bị và đặt OpenMode của nó thành NotOpen.
    }
}

Setting::Button &Setting::ButtonAt(const Vei2 &gridPos)
{
    return button[gridPos.y * width + gridPos.x]; // Vị trí button trong mảng 1d
}

int Setting::AtButton(const Vei2 &gridPos) const
{
    return gridPos.y * width + gridPos.x; // Vị trí button trong mảng 1d
}

Vei2 Setting::ScreenToGrid(const Vei2 &screenPos) const
{
    return (screenPos - topLeft) / sizeWidth; // Tọa độ chuột - tọa dộ cạnh trên trái khung button / kích thước 1 ô
}

void Setting::FileSaveSetting()
{
    QJsonDocument doc; // Tạo một tài liệu trống và không hợp lệ.
    QJsonObject obj; // Tạo một đối tượng JSON trống.
    QByteArray data_json; // Tạo một mảng byte trống.
    QFile input(jsonSetting); // Xây dựng một đối tượng tệp mới để đại diện cho tệp với "tên" đã cho.
    // ReadOnly, Thiết bị đang mở để đọc.
    // Text, Khi đọc các dấu cuối dòng được dịch thành '\n'.
    if(input.open(QIODevice::ReadOnly | QIODevice::Text)) // Mở thiết bị và đặt OpenMode ở "chế độ".
    {
        // Trả về true nếu vị trí đọc và ghi hiện tại nằm ở cuối thiết bị (tức là không còn dữ liệu nào để đọc trên thiết bị) nếu không trả về false.
        if(!input.atEnd()) // Nếu tệp chứa dữ liệu
        {
            data_json = input.readAll(); // Đọc tất cả dữ liệu còn lại từ thiết bị và trả về dưới dạng một mảng byte.
            doc = doc.fromJson(data_json); // Phân tích cú pháp "json" dưới dạng tài liệu JSON được mã hóa UTF-8 và tạo tài liệu JSON từ đó.
            obj = doc.object(); // Trả về QJsonObject có trong tài liệu.
            // Gán dữ liệu từ file vào setting
            memeWidth = obj["memeWidth"].toInt();
            memeHeight = obj["memeHeight"].toInt();
            memeBom = obj["memeBom"].toInt();

            input.close(); // Đầu tiên phát ra aboutToClose(), sou đó đóng thiết bị và đặt OpenMode của nó thành NotOpen.
        } else { // Nếu tệp rỗng
            input.close();
            SettingSaveFile(); // Lưu dữ liệu setting vào file
        }
    }
}


