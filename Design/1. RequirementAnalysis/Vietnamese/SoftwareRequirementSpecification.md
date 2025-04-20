# Đặc tả Yêu cầu Phần mềm (SRS) - Trình phát Đa phương tiện (Tiếng Việt)

## 1. Giới thiệu

### 1.1 Mục đích

Bản Đặc tả Yêu cầu Phần mềm (SRS) này xác định các yêu cầu chức năng và phi chức năng cho ứng dụng **Trình phát đa phương tiện** được thiết kế để phát tệp âm nhạc với khả năng mở rộng sang tệp video.

### 1.2 Phạm vi

Trình phát đa phương tiện cho phép người dùng phát nhạc từ cơ sở dữ liệu hoặc tệp cục bộ, quản lý danh sách phát, điều khiển phát lại và tương tác với vi điều khiển bên ngoài. Ứng dụng bao gồm xác thực người dùng, chức năng tìm kiếm và chatbot tùy chọn để gợi ý bài hát. Ứng dụng sẽ có giao diện hiện đại với hoạt ảnh mượt mà và khả năng đăng nhập bền vững.

### 1.3 Định nghĩa, Từ viết tắt

- **Qt**: Khung đa nền tảng cho giao diện và phát triển ứng dụng.
- **QMediaPlayer**: Thành phần Qt để phát phương tiện.
- **QMediaMetaData**: Thành phần Qt để truy cập siêu dữ liệu phương tiện.
- **SQL**: Ngôn ngữ truy vấn có cấu trúc để quản lý cơ sở dữ liệu.
- **UART**: Bộ truyền nhận không đồng bộ phổ quát cho giao tiếp nối tiếp.
- **UI**: Giao diện người dùng.

## 2. Mô tả tổng quan

### 2.1 Nhu cầu người dùng

- Người dùng cần một trình phát đa phương tiện đáng tin cậy để phát nhạc từ bộ nhớ cục bộ hoặc cơ sở dữ liệu.
- Người dùng yêu cầu các điều khiển trực quan để phát lại, âm lượng và chuyển bài.
- Người dùng mong muốn hệ thống đăng nhập an toàn với xác thực bền vững.
- Người dùng muốn tìm kiếm bài hát và danh sách phát một cách hiệu quả.
- Người dùng có thể muốn điều khiển trình phát qua vi điều khiển bên ngoài.
- Người dùng mong muốn giao diện hấp dẫn với tương tác mượt mà.

### 2.2 Giả định và Phụ thuộc

- Ứng dụng giả định có quyền truy cập vào hệ thống tệp cục bộ và kết nối cơ sở dữ liệu ổn định.
- Vi điều khiển bên ngoài hỗ trợ giao tiếp qua UART, USB hoặc Bluetooth.
- Qt Framework và SQLite tương thích với nền tảng mục tiêu.

## 3. Tính năng hệ thống

### 3.1 Phát nhạc từ cơ sở dữ liệu

- **Mô tả**: Kết nối với cơ sở dữ liệu SQL để truy xuất và phát tệp âm nhạc.
- **Đầu vào**: Chi tiết kết nối cơ sở dữ liệu, danh sách phát do người dùng chọn.
- **Đầu ra**: Phát nhạc đã chọn, hiển thị tiêu đề bài hát và nghệ sĩ.
- **Chức năng**: Người dùng có thể tạo và quản lý danh sách phát từ nhạc lưu trong cơ sở dữ liệu.

### 3.2 Phát nhạc từ tệp/thư mục cục bộ

- **Mô tả**: Phát tệp âm nhạc đơn lẻ hoặc tải thư mục để tạo danh sách phát.
- **Đầu vào**: Đường dẫn tệp hoặc thư mục.
- **Đầu ra**: Phát nhạc, hiển thị siêu dữ liệu bài hát.
- **Chức năng**: Hỗ trợ các định dạng âm thanh phổ biến (ví dụ: MP3, WAV).

### 3.3 Điều khiển nhạc cơ bản

- **Mô tả**: Cung cấp các điều khiển phát lại cơ bản.
- **Đầu vào**: Hành động người dùng (nhấp chuột, nhấn phím, đầu vào từ vi điều khiển).
- **Đầu ra**: Điều chỉnh âm lượng, chuyển bài, phát/tạm dừng, cập nhật thanh tiến trình, hiển thị thời gian/thời lượng.
- **Chức năng**: Điều khiển mượt mà và phản hồi nhanh với phản hồi thời gian thực.

### 3.4 Tài khoản người dùng

- **Mô tả**: Triển khai đăng ký và đăng nhập người dùng.
- **Đầu vào**: Tên người dùng, mật khẩu, chi tiết tài khoản.
- **Đầu ra**: Truy cập an toàn vào ứng dụng, thông tin đăng nhập được lưu trữ tạm thời.
- **Chức năng**: Đăng nhập bền vững cho người dùng quay lại.

### 3.5 Tính năng tìm kiếm

- **Mô tả**: Cho phép tìm kiếm bài hát và danh sách phát.
- **Đầu vào**: Truy vấn tìm kiếm.
- **Đầu ra**: Danh sách các bài hát hoặc danh sách phát phù hợp.
- **Chức năng**: Các trang chuyên dụng cho tìm kiếm bài hát và danh sách phát.

### 3.6 Điều khiển bằng vi điều khiển bên ngoài

- **Mô tả**: Cho phép điều khiển qua vi điều khiển bên ngoài.
- **Đầu vào**: Nhấn nút trên vi điều khiển.
- **Đầu ra**: Các hành động tương ứng của trình phát (âm lượng, bài hát, phát/tạm dừng).
- **Chức năng**: Tích hợp liền mạch với giao thức UART/USB/Bluetooth.

### 3.7 Chatbot tùy chọn

- **Mô tả**: Gợi ý bài hát dựa trên sở thích người dùng.
- **Đầu vào**: Thể loại, tâm trạng hoặc tiêu chí khác.
- **Đầu ra**: Danh sách các bài hát được đề xuất.
- **Chức năng**: Tương tác ngôn ngữ tự nhiên để gợi ý.

## 4. Yêu cầu phi chức năng

- **Hiệu suất**: Ứng dụng nên tải và phát phương tiện trong vòng 2 giây.
- **Tính khả dụng**: Giao diện phải trực quan, với hoạt ảnh nâng cao trải nghiệm.
- **Bảo mật**: Thông tin xác thực người dùng phải được mã hóa và lưu trữ an toàn.
- **Tương thích**: Ứng dụng phải chạy trên Windows, macOS và Linux.
- **Độ tin cậy**: Ứng dụng nên xử lý các đầu vào không hợp lệ một cách nhẹ nhàng.

## 5. Yêu cầu giao diện bên ngoài

### 5.1 Giao diện người dùng

- Giao diện hiện đại với thanh tiến trình, điều khiển phát lại và trang tìm kiếm.
- Hoạt ảnh mượt mà cho các chuyển đổi và tương tác.

### 5.2 Giao diện phần cứng

- Giao tiếp với vi điều khiển bên ngoài qua UART, USB hoặc Bluetooth.

### 5.3 Giao diện phần mềm

- Qt Framework cho giao diện và xử lý phương tiện.
- SQLite cho quản lý cơ sở dữ liệu.

## 6. Yêu cầu khác

- **Khả năng mở rộng**: Ứng dụng nên hỗ trợ phát lại video trong tương lai.
- **Tài liệu**: Cung cấp hướng dẫn sử dụng và tài liệu dành cho nhà phát triển.
