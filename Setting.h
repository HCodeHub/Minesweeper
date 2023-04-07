#ifndef SETTING_H
#define SETTING_H
#pragma once

#include "Graphics.h" // Xử lý, hiển thị hình ảnh
#include <QString> // cung cấp một chuỗi ký tự Unicode

class Setting
{
private:
    class Button
    {
    public:
        void Draw(const Vei2& screenPos, Graphics& gfx, const int& indexW, const int& indexH);
    public:
    };
public:
    Setting(const Vei2& center);

    void Draw(Graphics& gfx);
    void OnInteractClick(const Vei2& screenPos); // Chuột trái
    const bool &GetClose() const; // thoát trương trình
    const bool &GetOk() const; // đặt giá trị cho game //
    void SetOk(); // đặt lại
    const int &GetWidth() const;
    const int &GetHeight() const;  // Trả về số ô theo chiều dọc
    const int &GetBoms() const; // Trả về số bom
    void SettingSaveFile() const; // Lưu dữ liệu setting vào file
private:    
    Button &ButtonAt(const Vei2& gridPos);
    int AtButton(const Vei2& gridPos) const;
    Vei2 ScreenToGrid(const Vei2& screenPos) const; // convert tọa độ màn hình sang tọa độ lưới
    void FileSaveSetting(); // Gán dữ liệu file vào setting
private:
    const QString jsonSetting;
    Vei2 topLeft; // góc trên trái
    Button button[20]; // số ô setting    

    int width = 5; // Số ô setting
    int height = 4;
    int sizeWidth = 70; // pixel
    bool close = false; // thoát
    bool ok = false; // đặt giá trị
};

#endif // SETTING_H
