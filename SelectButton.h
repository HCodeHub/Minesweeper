#ifndef SELECTBUTTON_H
#define SELECTBUTTON_H
#pragma once

#include <Graphics.h> // Xử lý, hiển thị hình ảnh

// buttom (flag, mặt cười, score)
class SelectButton
{
public:
    enum class Flag // trạng thái
    {
        Revealed, // chưa nhấn
        Flagged // đã nhấn
    };

    // lưu ý: đặt State trước class Button để dùng trong Button
    enum class State
    {
        Playing, // đang chơi
        Win, // thắng
        Lose, // thua
        Reset, // đặt lại
        Setting // cài đặt
    };    

private:
    class Button // Tương đương Button *button // Nút nhấn
    {
    public:
        // class enum (còn được gọi là enum có phạm vi), làm cho các enum được nhấn mạnh và phạm vi mạnh hơn.
        enum class State // trạng thái
        {
            Off, // chưa nhấn
            On // đã nhấn
        };
    public:
        void Draw(const Vei2 screenPos, Graphics &gfx, const int& index, int timer) const;
        void ToggleFlag(SelectButton::Flag& selectFlag); // Hiện hoặc ẩn cờ
        void ToggleSmile(SelectButton::State& selectState); // Mặt cười
        void ToggleTimer(SelectButton::State& selectState); // Thời gian và menu kết thúc
        void SetState(const State& setState); // Nhận trạng thái
    private:
        State state = State::Off; // Trạng thái chưa nhấn
    };

public:
    SelectButton(const Vei2& center);

    void Draw(Graphics &gfx); // Vẽ tại vị trí trong mảng 1d
    const RectI GetRect() const; // Trả về hình chữ nhật
    void OnInteractClick(const Vei2& screenPos); // Chuột trái
    void SetState(const State& setState); // Nhận trạng thái
    const State &GetState() const; // Trả về trạng thái
    const Flag &GetFlag() const; // Trả về trạng cờ
    void AddTimer(); // Tăng thời gian
private:
    Button &ButtonAt(const Vei2 &gridPos); // Vị trí buttom trong mảng 1d
    int AtButton(const Vei2 &gridPos) const;
    Vei2 ScreenToGrid(const Vei2& screenPos); // convert tọa độ màn hình sang tạo độ lưới

private:
    static constexpr int width = 3; // Số lượng button theo chiều ngang
    static constexpr int height = 1; // Số lượng button theo chiều dọc
    Vei2 topLeft; // Tọa độ dịch chuyển
    State state = State::Playing; // Trạng thái đang chơi
    Flag flag = Flag::Revealed; // Chưa nhấn cờ
    Button button[3]; // Số lượng nút nhấn // mảng 1d
    int countTimer = 0; // đếm thời gian
};

#endif // SELECTBUTTON_H

//QTimer *timer; // Thời gian
