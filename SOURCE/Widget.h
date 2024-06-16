#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget> // Là lớp cơ sở của tất cả các đối tượng giao diện người dùng.
#include <QTimer> // Lớp QTimer cung cấp các bộ hẹn giờ lặp đi lặp lại và một lần chụp

#include "Mouse.h" // Nhận sự kiện chuột
#include "Graphics.h" // Xử lý, hiển thị hình ảnh

#include "MemeField.h" // Cánh đồng Meme
#include "SelectButton.h" // vẽ button
#include "Setting.h" // Cài đặt

class Widget : public QWidget // lớp main dự án
{
    Q_OBJECT // macro // Để một lớp có thể sử dụng signal và slot
public:
    Widget(); // khởi tạo không tham số // QWidget *parent = nullptr
    ~Widget(); // hàm hủy
private:
    // Trình xử lý sự kiện này có thể được thực hiện lại trong một lớp con để nhận các sự kiện sơn được thông qua trong "sự kiện" đó.
    void paintEvent(QPaintEvent *event) override;
    // Trình xử lý sự kiện này, đối với sự kiện "mouseEvent", có thể được thực hiện lại trong một lớp con để nhận các sự kiện nhấn chuột cho cảnh.
    void mousePressEvent(QMouseEvent *event) override; // ghi đè
private:
    void UpdateModel();
    void ComposeFrame(Graphics &gfx);
    /********************************/
    /*  User Functions              */
    void Timers();
    /********************************/    
private:
    Graphics gfx; // Vẽ hình, pixed
    Mouse mouse; // Sự kiện chuột
    /********************************/
    /*  User Variables              */
    SelectButton button; // Nút tương tác
    Setting setting; // Cài đặt
    MemeField field; // Cánh đồng Meme    
    QTimer *timer; // đếm thời gian    
    bool checkLeftClick; // kiểm tra có đang chơi không
    bool resetBackground; // Xóa nền
    /********************************/
};
#endif // WIDGET_H

/*
//void Go(); // bắt đầu
*/

/*
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

private:
    //Ui::Widget *ui; // UI
*/

/*
Overriding thường được sử dụng trong method ở lớp con.
Một số quy tắc sử dụng phương thức overriding:
Các phương thức được mô tả static thì không overriden nhưng được mô tả lại.
Các phương thức không kế thừa sẽ không được overriden (hiển nhiên).
*/
