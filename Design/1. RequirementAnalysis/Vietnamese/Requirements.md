# Yêu cầu Dự án Trình phát Đa phương tiện (Tiếng Việt)

## Mục tiêu

Thiết kế một ứng dụng **Trình phát đa phương tiện** chủ yếu để phát **tệp âm nhạc**, với khả năng mở rộng sang **tệp video** trong tương lai.

---

## Các tính năng bắt buộc

### 1. Phát nhạc từ cơ sở dữ liệu

- Kết nối ứng dụng với **Cơ sở dữ liệu**.
- **Tạo danh sách phát** từ các tệp âm nhạc được lưu trữ trong cơ sở dữ liệu.

### 2. Phát nhạc từ tệp/thư mục cục bộ

- Phát một **tệp âm nhạc duy nhất** từ máy tính cục bộ.
- **Tạo danh sách phát** bằng cách tải tất cả các tệp âm nhạc từ một **thư mục cục bộ**.

### 3. Điều khiển nhạc cơ bản

- **Tăng/Giảm âm lượng**.
- **Bài tiếp theo/Bài trước**.
- **Phát/Tạm dừng** bài nhạc.
- **Hiển thị thời gian phát hiện tại và tổng thời lượng** của bài nhạc (vị trí/thời lượng).
- **Thanh tiến trình** để tìm kiếm.
- **Hiển thị tiêu đề bài hát** và **tên nghệ sĩ**.

### 4. Tài khoản người dùng

- **Đăng ký người dùng** (Sign Up).
- **Đăng nhập người dùng** bắt buộc trước khi sử dụng Trình phát đa phương tiện.

### 5. Tính năng tìm kiếm

- **Thanh tìm kiếm bài hát** (trên một trang chuyên dụng).
- **Thanh tìm kiếm danh sách phát** (trên một trang chuyên dụng riêng biệt).

### 6. Điều khiển bằng vi điều khiển bên ngoài

- Kết nối với một **vi điều khiển bên ngoài** (ví dụ: bo mạch S32K144 hoặc tương tự).
- Điều khiển Trình phát đa phương tiện thông qua các nút trên vi điều khiển:
  - **Tăng/Giảm âm lượng**.
  - **Bài tiếp theo/Bài trước**.
  - **Phát/Tạm dừng** bài nhạc.

### 7. Tính năng tùy chọn

- Thêm một **chatbot** để gợi ý bài hát dựa trên **thể loại**, **tâm trạng**, v.v.

---

## Yêu cầu phi chức năng

1. **Đăng nhập bền vững**:
   - Sau khi đăng nhập vào tài khoản trên máy tính cá nhân, thông tin đăng nhập phải được **lưu trữ tạm thời**.
   - Ứng dụng sẽ **tự động đăng nhập** khi khởi động lần tiếp theo mà không yêu cầu xác thực lại.

2. **Giao diện và hoạt ảnh**:
   - Ứng dụng phải có **giao diện hấp dẫn** với **hoạt ảnh mượt mà**.
   - Giao diện người dùng cần **hấp dẫn về mặt thị giác** và mang lại **trải nghiệm người dùng hiện đại**.

---

## Công nghệ sử dụng

- **Qt Framework** cho giao diện người dùng, phát lại phương tiện, xử lý siêu dữ liệu.
- **QMediaPlayer** và **QMediaMetaData** để phát và quản lý tệp phương tiện.
- **Cơ sở dữ liệu SQL** (ví dụ: SQLite) để quản lý dữ liệu người dùng và âm nhạc.
- **Giao tiếp với vi điều khiển bên ngoài** (ví dụ: qua UART, USB hoặc Bluetooth).
