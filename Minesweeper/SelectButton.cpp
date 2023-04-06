#include "SelectButton.h"
#include "SpriteCodex.h" // chứa image và pixed viết sẵn
#include <assert.h> // cung cấp macro gọi là assert có thể được sử dụng để kiểm tra một giả định được tạo bởi chương trình và in một thông báo chẩn đoán tìm lỗi nếu giả định này là false.
#include <QDebug>

SelectButton::SelectButton(const Vei2& center)
    : // danh sách khởi tạo
      topLeft(center) // tọa độ hiển thị, cạnh trên trái
{    
}

void SelectButton::Button::Draw(const Vei2 screenPos, Graphics &gfx, const int &index, int timer) const
{
    if (index == 2)
    {
        int s=0;
        while(timer!=0)
        {
            s = s * 10 + timer % 10;
            timer /= 10;
        }

        for(Vei2 pos = {screenPos.x + 3, screenPos.y}; pos.x < screenPos.x + SpriteCodex::buttonSizeW; pos.x += 30)
        {
            SpriteCodex::DrawTimer(pos, gfx, s % 10); // Vẽ thời gian
            s /= 10;
        }
    }
    else
    {
        // vẽ button theo trạng thái
        switch (state)
        {
        case State::On:
            // vẽ button tại tọa độ
            SpriteCodex::DrawButtonOn(screenPos, index, gfx);
            break;
        case State::Off:
            SpriteCodex::DrawButtonOff(screenPos, index, gfx);
            break;
        }
    }
}

void SelectButton::Button::ToggleFlag(SelectButton::Flag &selectFlag) // trạng thái cờ
{
    if (state == State::Off)
    {
        state = State::On;
        selectFlag = SelectButton::Flag::Flagged; // Trạng thái gắn cờ
    }
    else {
        state = State::Off; // hiển thị
        selectFlag = SelectButton::Flag::Revealed;
    }
}

void SelectButton::Button::ToggleSmile(SelectButton::State &selectState)
{
    if(selectState == SelectButton::State::Win || selectState == SelectButton::State::Lose) // mặt cười
    {
        selectState = SelectButton::State::Reset; // đặt lại trò chơi
        state = State::Off; // đặt lại trạng thái
    }
}

void SelectButton::Button::ToggleTimer(SelectButton::State &selectState)
{
    if(selectState != SelectButton::State::Setting)
    {
        selectState = SelectButton::State::Setting; // đặt trạng thái đang cài đặt
    }else {
        selectState = SelectButton::State::Reset;
    }
}

void SelectButton::Button::SetState(const State &setState)
{
    state = setState; // nhận trạng thái
}

void SelectButton::Draw(Graphics &gfx)
{
    for(Vei2 gridPos = {0,0}; gridPos.y < height; ++gridPos.y) // số button theo chiều cao
    {
        for(gridPos.x = 0; gridPos.x < width; ++gridPos.x) // số button theo chiều rộng
        {
            // Vẽ tại vị trí
            ButtonAt(gridPos).Draw(topLeft + gridPos * SpriteCodex::buttonSizeW, gfx, gridPos.x, countTimer); //
        }
    }
}

const RectI SelectButton::GetRect() const
{
    return RectI(topLeft, width * SpriteCodex::buttonSizeW, height * SpriteCodex::buttonSizeH); // Trả về hình chữ nhật của button
}

// chuột trái
void SelectButton::OnInteractClick(const Vei2 &screenPos)
{
    const Vei2 gridPos = ScreenToGrid(screenPos); // lấy tọa độ lưới
    assert(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height); // yêu cầu tọa độ trong giới hạn
    Button& button = ButtonAt(gridPos); // Lấy vị trí button trong mảng 1d //lưu ý: & tham chiếu thay đổi giá trị
    switch (AtButton(gridPos)) // lấy index vị trí
    {
    case 0:
        button.ToggleFlag(flag); // Gắn hoặc ẩn cờ
        break;
    case 1:
        button.ToggleSmile(state); // Cười hoặc mếu
        break;
    case 2:
        button.ToggleTimer(state); // show hoặc ẩn setting
        break;
    }
}

void SelectButton::SetState(const State &setState)
{
    state = setState;
    if(setState == State::Lose)    button[1].SetState(Button::State::On); // Trạng thái thua
}

const SelectButton::State &SelectButton::GetState() const
{
    return state;
}

const SelectButton::Flag &SelectButton::GetFlag() const
{
    return flag;
}

void SelectButton::AddTimer()
{
    if (state == SelectButton::State::Playing)   ++countTimer; // tăng thời gian
}

SelectButton::Button &SelectButton::ButtonAt(const Vei2 &gridPos)
{
    return button[gridPos.y * width + gridPos.x]; // Vị trí buttom trong mảng 1d //?
}

int SelectButton::AtButton(const Vei2 &gridPos) const
{
    return gridPos.y * width + gridPos.x; // Vị trí buttom trong mảng 1d
}

Vei2 SelectButton::ScreenToGrid(const Vei2 &screenPos)
{
    return (screenPos - topLeft) / SpriteCodex::buttonSizeW; // Tọa độ chuột - tọa độ cạnh trên trái khung button / kích thước 1 ô
}
