#include "Widget.h"
#include "SpriteCodex.h" // Màn hình bắt đầu, kết thúc
#include <QGuiApplication> // quản lý luồng điều khiển và cài đặt chính của ứng dụng GUI.
#include <QMouseEvent> // chứa các tham số mô tả sự kiện chuột.
#include <QDebug>

Widget::Widget() // QWidget *parent
    : // Danh sách khởi tạo
        //QWidget(parent) // truyền vào một đối tượng widget tương đương nếu có
      gfx() // Vẽ hình, pixed
    , mouse() // lưu ý: thứ tự khởi tạo
    , button(Vei2(0,0)) // khởi tạo tọa độ
    , setting(Vei2(button.GetRect().left, button.GetRect().top)) // gán theo tọa độ button
    , field(Vei2(button.GetRect().left, button.GetRect().top), setting.GetWidth(), setting.GetHeight(), setting.GetBoms()) // Vị trí đồng nhất Vei2, chiều ngang, dọc,  khởi tạo số lượng meme(bom)
    , checkLeftClick(true) // kiểm tra có đang nhấn chuột trong meme
    , resetBackground(false) // Xóa nền
{
    setAttribute(Qt::WA_OpaquePaintEvent);   // Đảm bảo rằng nội dung của widget sẽ được vẽ đầy đủ trong hàm paintEvent
    setAttribute(Qt::WA_NoSystemBackground); // Loại bỏ bất kỳ hoạt động nào liên quan đến hệ thống của widget để tăng hiệu suất cho việc vẽ.

    timer = new QTimer(this);
        // lưu ý: sử dụng bên ngoài lớp Widget phải khai báo QObject::connect // lưu ý: đối tượng phông phải con trỏ thì phải khai báo đường dẫn, đã học trong C scanf().
    QObject::connect(timer, &QTimer::timeout, this, &Widget::Timers); // Tín hiệu này được phát ra khi bộ hẹn giờ hết giờ.
        // Bắt đầu hoặc khởi động lại bộ hẹn giờ với thời gian chờ được chỉ định trong khoảng thời gian.
    timer->start(1000); // Nếu bộ hẹn giờ đã chạy, nó sẽ bị dừng và khởi động lại. // Hàm này làm quá tải start().
}

Widget::~Widget(){}

// Cập nhật mô hình sự kiện thay đổi logic.
void Widget::UpdateModel()
{
    checkLeftClick = true; // chuột đang được nhấn
    const Vei2 mousePos = mouse.GetPos(); // Tọa độ chuột
    Mouse::Type type = mouse.GetType(); // sự kiện chuột

    if(button.GetState() != SelectButton::State::Setting) // nếu đang cài đặt thì ngừng chơi
    {
        if(field.GetState() == MemeField::State::Memeing && field.GetRect().Contains(mousePos)) // Đang chơi và tọa độ chuột trong cánh đồng
        {
            if (type == Mouse::Type::RPress || (type == Mouse::Type::LPress && button.GetFlag() == SelectButton::Flag::Flagged)) // tương thích với Android
            {                
                field.OnFlagClick(mousePos); // Gắn cờ khi nhấn chuột phải
            }
            else if (type == Mouse::Type::LPress) // Nếu loại sự kiện == nhấn chuột trái.
            {                    
                field.OnRevealClick(mousePos); // Tiết lộ khi nhấn chuột trái /// Tọa độ chuột
            }

            if (field.GetState() == MemeField::State::Winrar)
            {
                button.SetState(SelectButton::State::Win);
            }
            else if (field.GetState() == MemeField::State::Lose)
            {
                button.SetState(SelectButton::State::Lose);
            }
        }
    }else {
        if(button.GetState() == SelectButton::State::Setting) // nếu đang cài đặt
        {
            setting.OnInteractClick(mousePos); // Lấy tọa độ chuột
            if(setting.GetClose()) close(); // Nếu nhấn nút Thoát

            if(setting.GetOk()) { // nếu nhấn nút ok                
                    // Vị trí đồng nhất Vei2 button. width, height, bom lấy từ setting
                field = MemeField(Vei2(button.GetRect().left, button.GetRect().top), setting.GetWidth(), setting.GetHeight(), setting.GetBoms()); // lấy dữ liệu từ setting
                button = SelectButton(Vei2(0,0)); // reset button // timer // lưu ý: Lỗi khi không tạo mới
                setting.SettingSaveFile(); // Lưu dữ liệu setting vào file
                resetBackground = true; // xóa background
                setting.SetOk(); // đặt lại
            }
        }
    }

    if (button.GetRect().Contains(mousePos)) // Nếu tạo độ chuột nằm trong button //&& type == Mouse::Type::LPress
    {
            // Truyền tọa độ khi nhấn chuột trái
        button.OnInteractClick(mousePos); // Tọa độ chuột

        if(button.GetState() == SelectButton::State::Reset) // nếu nhấn nút Reset
        {
                // Vị trí đồng nhất Vei2 button. width, height, bom lấy từ setting
            field = MemeField(Vei2(button.GetRect().left, button.GetRect().top), setting.GetWidth(), setting.GetHeight(), setting.GetBoms()); // lấy dữ liệu từ setting
                // Tạo mới khi nhấn button resert
            button = SelectButton(Vei2(0,0)); // reset button // timer
        }
    }
}

// Khung biên soạn(tạo mô hình), lặp lại sự kiện, vòng lặp
void Widget::ComposeFrame(Graphics &gfx)
{
    if(button.GetState() != SelectButton::State::Setting) // nếu đang cài đặt thì ngừng chơi
    {        
        if(resetBackground) // nếu ok cài đặt thì xóa nền
        {
            QRect rect = QGuiApplication::primaryScreen()->geometry(); // Thuộc tính này giữ hình học của màn hình tính bằng pixel // lấy kích thước màn hình
            // Xóa khu vực bên trong hình "chữ nhật".
            gfx.DrawRect(rect.x(), rect.y(), rect.width(), rect.height(), Qt::black); // Vẽ nền đen làm sạch màn hình
            resetBackground = false;
        }

        field.Draw(gfx); // Vẽ cánh đồng meme
        if (field.GetState() == MemeField::State::Winrar) // nếu trạng thái == win
        {
            SpriteCodex::DrawWin(field.GetRect().GetCenter(), gfx); // Vẽ màn hình kết thúc
        }

        // fix nền đen, bỏ checkLeftClick
        /*
        if(checkLeftClick == true) {} // nếu đang nhấn thì làm mới
            checkLeftClick = false; // đặt lại
        */
    }
    else {
        setting.Draw(gfx); // vẽ setting
    }
    button.Draw(gfx); // Vẽ button // không ảnh hưởng hiệu suất    
}

void Widget::Timers()
{
    button.AddTimer(); // tăng thời gian
    repaint(); // gọi hàm paintEvent để vẽ lại widget
}

// Trình xử lý sự kiện này, đối với sự kiện "mouseEvent", có thể được thực hiện lại trong một lớp con để nhận các sự kiện nhấn chuột cho cảnh.
void Widget::mousePressEvent(QMouseEvent *event) // nhận sự kiện giữ chuột
{
    Mouse::Type type; // Sự kiện nhấn chuột
        // QSinglePointEvent->Qt::MouseButton(Enum)
    if (event->button() == Qt::LeftButton) // Nút bên trái được nhấn hoặc một sự kiện đề cập đến nút bên trái. /// Nếu enum sự kiện chuột == Chuột trái
    {
        type = Mouse::Type::LPress; // Khai báo Type vì LPress thuộc enum class
    }
    else if (event->button() == Qt::RightButton)
    {
        type = Mouse::Type::RPress; // type = nhấn chuột phải
    }
    QPointF pointf = event->position().toPoint();
        // QMouseEvent->QPointF().QPoint().int  // Trả về tọa độ x của điểm này.
    mouse.setXY_Type(pointf.x(), pointf.y(), type); /// Truyền dữ liệu chuột
    UpdateModel(); /// không thay đổi thứ tự 2 hàm
    repaint(); // Làm mới đồ họa mỗi khi chuột được nhấn /// gọi hàm paintEvent để vẽ lại widget // lưu ý: dùng trong hàm paintEvent sẽ gây đệ quy, thay vào đó dùng
}

// Trình xử lý sự kiện này có thể được thực hiện lại trong một lớp con để nhận các sự kiện sơn được thông qua trong "sự kiện" đó.
void Widget::paintEvent(QPaintEvent *event)
{
    (void)event; // không dùng đến
    QPainter painter(this);
    gfx.SetPaint(painter); /// chuyền dữ liệu Vẽ đồ họa
    ComposeFrame(gfx); /// không thay đổi thứ tự 2 hàm
        //repaint(); // lưu ý: dùng trong hàm paintEvent sẽ gây đệ quy, thay vào đó dùng //update(); // Cập nhật tiện ích trừ khi cập nhật bị tắt hoặc tiện ích bị ẩn.
}


/*
//#include "ui_Widget.h"

 //, ui(new Ui::Widget) // khởi tạo UI

 //ui->setupUi(this); // Thiết lập giao diện người dùng cho tiện ích được chỉ định.

 //delete ui; // hủy UI
*/

/*
//Go(); // Bắt đầu
void Widget::Go() // Bắt đầu
{
    //UpdateModel(); // Cập nhật mô hình sự kiện thay đổi logic.
    //ComposeFrame(); // Khung biên soạn(tạo mô hình), lặp lại sự kiện, vòng lặp game.
}

//show(); // Hiện widget khi ở trạng thái ẩn

//update(); // Cập nhật tiện ích trừ khi cập nhật bị tắt hoặc tiện ích bị ẩn.
//event->accept(); // Đặt cờ chấp nhận đối tượng sự kiện, tương đương với gọi setAccepted(true).

painter.end();

//resize(Graphics::ScreenWidth, Graphics::ScreenHeight); // Điều này tương ứng với thay đổi kích thước (QSize (w, h)).

// Vẽ nền đen che setting
//SpriteCodex::DrawBackground(Vei2(0, 40), gfx);

// Xóa khu vực bên trong hình "chữ nhật".
gfx.getPaint()->eraseRect(QGuiApplication::primaryScreen()->geometry()); // Thuộc tính này giữ hình học của màn hình tính bằng pixel // lấy kích thước màn hình
//QObject::connect(timer, &QTimer::timeout, this, &Widget::Timers); // Tín hiệu này được phát ra khi bộ hẹn giờ hết giờ.

//button.SetState(SelectButton::State::Playing); // Đặt trạng thái button
//#include <QScreen> // class được sử dụng để truy vấn các thuộc tính màn hình.
*/
