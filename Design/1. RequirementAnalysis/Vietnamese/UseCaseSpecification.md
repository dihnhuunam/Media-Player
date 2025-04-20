# Đặc tả Trường hợp Sử dụng Trình phát Đa phương tiện (Tiếng Việt)

## Đặc tả Trường hợp Sử dụng: Trình phát Đa phương tiện

### 1. Đăng ký Người dùng (UC-001)

#### 1.1 Mô tả Ngắn gọn

Trường hợp sử dụng này mô tả cách người dùng khách đăng ký tài khoản mới để truy cập ứng dụng Trình phát Đa phương tiện ở chế độ trực tuyến.

#### 1.2 Tác nhân

- **Tác nhân Chính**: Người dùng Khách
- **Tác nhân Phụ**: Hệ thống Cơ sở Dữ liệu

#### 1.3 Điều kiện Tiên quyết

- Người dùng chưa đăng nhập và đã chọn chế độ trực tuyến.
- Ứng dụng đang chạy và kết nối với cơ sở dữ liệu.

#### 1.4 Luồng Chính

1. Người dùng Khách điều hướng đến trang đăng ký thông qua giao diện người dùng sau khi chọn chế độ trực tuyến.
2. Hệ thống hiển thị biểu mẫu đăng ký yêu cầu tên người dùng, mật khẩu và các chi tiết tùy chọn (ví dụ: email).
3. Người dùng Khách nhập thông tin cần thiết và gửi biểu mẫu.
4. Hệ thống xác thực đầu vào:
   - Tên người dùng phải là duy nhất.
   - Mật khẩu phải đáp ứng yêu cầu độ phức tạp (ví dụ: độ dài tối thiểu, ký tự đặc biệt).
5. Hệ thống lưu trữ thông tin xác thực đã mã hóa vào cơ sở dữ liệu.
6. Hệ thống hiển thị thông báo thành công và chuyển hướng người dùng đến trang đăng nhập.

#### 1.5 Luồng Phụ

- **A1: Tên Người dùng Đã Tồn tại**
  - Tại bước 4, nếu tên người dùng đã được sử dụng, hệ thống hiển thị thông báo lỗi: "Tên người dùng đã tồn tại."
  - Người dùng được yêu cầu nhập tên người dùng khác.
  - Quay lại bước 3.
- **A2: Mật khẩu Không Hợp lệ**
  - Tại bước 4, nếu mật khẩu không đáp ứng yêu cầu, hệ thống hiển thị thông báo lỗi: "Mật khẩu quá yếu."
  - Người dùng được yêu cầu nhập mật khẩu mạnh hơn.
  - Quay lại bước 3.

#### 1.6 Ngoại lệ

- **E1: Lỗi Kết nối Cơ sở Dữ liệu**
  - Nếu cơ sở dữ liệu không khả dụng, hệ thống hiển thị: "Không thể kết nối với máy chủ. Vui lòng thử lại sau."
  - Người dùng được yêu cầu thử lại hoặc chuyển sang chế độ ngoại tuyến.

#### 1.7 Điều kiện Hậu quả

- Một tài khoản người dùng mới được tạo trong cơ sở dữ liệu.
- Người dùng được chuyển hướng đến trang đăng nhập.

#### 1.8 Mức độ Ưu tiên

Cao

#### 1.9 Tần suất Sử dụng

Thỉnh thoảng (một lần cho mỗi người dùng).

#### 1.10 Giả định

- Cơ sở dữ liệu hỗ trợ lưu trữ thông tin xác thực an toàn.
- Giao diện người dùng cung cấp biểu mẫu đăng ký rõ ràng.

---

### 2. Đăng nhập Người dùng (UC-002)

#### 2.1 Mô tả Ngắn gọn

Trường hợp sử dụng này mô tả cách người dùng đã đăng ký đăng nhập vào Trình phát Đa phương tiện ở chế độ trực tuyến để truy cập các tính năng cơ sở dữ liệu.

#### 2.2 Tác nhân

- **Tác nhân Chính**: Người dùng Đã đăng ký
- **Tác nhân Phụ**: Hệ thống Cơ sở Dữ liệu

#### 2.3 Điều kiện Tiên quyết

- Người dùng có tài khoản đã đăng ký.
- Ứng dụng đang chạy và kết nối với cơ sở dữ liệu.
- Người dùng đã chọn chế độ trực tuyến.

#### 2.4 Luồng Chính

1. Người dùng Đã đăng ký điều hướng đến trang đăng nhập sau khi chọn chế độ trực tuyến.
2. Hệ thống hiển thị biểu mẫu đăng nhập yêu cầu tên người dùng và mật khẩu.
3. Người dùng nhập thông tin xác thực và gửi biểu mẫu.
4. Hệ thống xác thực thông tin với cơ sở dữ liệu.
5. Nếu hợp lệ, hệ thống lưu trữ thông tin đăng nhập để duy trì đăng nhập bền vững.
6. Hệ thống cấp quyền truy cập vào giao diện chính của Trình phát Đa phương tiện với kết nối cơ sở dữ liệu và hoạt ảnh chuyển tiếp mượt mà.

#### 2.5 Luồng Phụ

- **A1: Thông tin Xác thực Không đúng**
  - Tại bước 4, nếu thông tin không hợp lệ, hệ thống hiển thị: "Tên người dùng hoặc mật khẩu không đúng."
  - Người dùng được yêu cầu thử lại hoặc chuyển sang chế độ ngoại tuyến.
  - Quay lại bước 3.

#### 2.6 Ngoại lệ

- **E1: Lỗi Kết nối Cơ sở Dữ liệu**
  - Nếu cơ sở dữ liệu không khả dụng, hệ thống hiển thị: "Không thể kết nối với máy chủ. Vui lòng thử lại sau."
  - Người dùng được yêu cầu thử lại hoặc chuyển sang chế độ ngoại tuyến.

#### 2.7 Điều kiện Hậu quả

- Người dùng được xác thực và có quyền truy cập vào Trình phát Đa phương tiện với các tính năng cơ sở dữ liệu.
- Thông tin đăng nhập được lưu trữ để sử dụng trong các phiên trực tuyến sau.

#### 2.8 Mức độ Ưu tiên

Cao

#### 2.9 Tần suất Sử dụng

Thường xuyên (một lần mỗi phiên trừ khi được lưu trữ).

#### 2.10 Giả định

- Cơ sở dữ liệu lưu trữ thông tin xác thực đã mã hóa.
- Đăng nhập bền vững được hỗ trợ thông qua lưu trữ an toàn.

---

### 3. Chọn Chế độ Trực tuyến hoặc Ngoại tuyến (UC-009)

#### 3.1 Mô tả Ngắn gọn

Trường hợp sử dụng này mô tả cách người dùng chọn giữa chế độ trực tuyến và ngoại tuyến tại màn hình đăng nhập.

#### 3.2 Tác nhân

- **Tác nhân Chính**: Người dùng Khách hoặc Người dùng Đã đăng ký
- **Tác nhân Phụ**: Không có

#### 3.3 Điều kiện Tiên quyết

- Ứng dụng đang chạy.
- Người dùng đang ở màn hình đăng nhập.

#### 3.4 Luồng Chính

1. Người dùng được hiển thị màn hình đăng nhập, bao gồm các tùy chọn "Chế độ Trực tuyến" và "Chế độ Ngoại tuyến."
2. Người dùng chọn một trong hai:
   - **Chế độ Trực tuyến**: Chuyển đến trang đăng nhập hoặc đăng ký để truy cập cơ sở dữ liệu.
   - **Chế độ Ngoại tuyến**: Bỏ qua đăng nhập và điều hướng trực tiếp đến giao diện phát nhạc với quyền truy cập chỉ dành cho tệp cục bộ.
3. Nếu chọn Chế độ Trực tuyến, hệ thống khởi tạo UC-001 (Đăng ký Người dùng) hoặc UC-002 (Đăng nhập Người dùng).
4. Nếu chọn Chế độ Ngoại tuyến, hệ thống điều hướng đến giao diện phát nhạc với quyền truy cập bị giới hạn ở tệp cục bộ.

#### 3.5 Luồng Phụ

- **A1: Chuyển đổi Chế độ**
  - Tại bước 2, người dùng có thể chuyển đổi giữa các chế độ trước khi xác nhận.
  - Quay lại bước 2.

#### 3.6 Ngoại lệ

- Không có

#### 3.7 Điều kiện Hậu quả

- Ở Chế độ Trực tuyến: Người dùng tiếp tục đến đăng nhập/đăng ký để truy cập cơ sở dữ liệu.
- Ở Chế độ Ngoại tuyến: Người dùng truy cập giao diện phát nhạc giới hạn ở tệp cục bộ.

#### 3.8 Mức độ Ưu tiên

Cao

#### 3.9 Tần suất Sử dụng

Thường xuyên (mỗi phiên).

#### 3.10 Giả định

- Giao diện người dùng phân biệt rõ ràng giữa các tùy chọn chế độ trực tuyến và ngoại tuyến.
- Chế độ ngoại tuyến hỗ trợ phát tệp cục bộ mà không cần kết nối cơ sở dữ liệu.

---

### 4. Phát Nhạc từ Cơ sở Dữ liệu (UC-003)

#### 4.1 Mô tả Ngắn gọn

Trường hợp sử dụng này mô tả cách người dùng đã đăng nhập phát nhạc từ danh sách phát lưu trong cơ sở dữ liệu ở chế độ trực tuyến.

#### 4.2 Tác nhân

- **Tác nhân Chính**: Người dùng Đã đăng nhập
- **Tác nhân Phụ**: Hệ thống Cơ sở Dữ liệu

#### 4.3 Điều kiện Tiên quyết

- Người dùng đã đăng nhập và ở chế độ trực tuyến.
- Cơ sở dữ liệu chứa tệp nhạc hoặc tham chiếu và có thể truy cập.

#### 4.4 Luồng Chính

1. Người dùng Đã đăng nhập điều hướng đến phần danh sách phát trong giao diện người dùng.
2. Hệ thống truy xuất và hiển thị các danh sách phát có sẵn từ cơ sở dữ liệu.
3. Người dùng chọn một danh sách phát.
4. Hệ thống truy xuất và hiển thị các bài hát trong danh sách phát đã chọn.
5. Người dùng chọn một bài hát để phát.
6. Hệ thống sử dụng QMediaPlayer để phát hoặc truyền bài hát.
7. Hệ thống hiển thị siêu dữ liệu của bài hát (tiêu đề, nghệ sĩ, thời lượng) và cập nhật thanh tiến trình theo thời gian thực.

#### 4.5 Luồng Phụ

- **A1: Danh sách Phát Trống**
  - Tại bước 4, nếu danh sách phát trống, hệ thống hiển thị: "Danh sách phát này trống."
  - Người dùng được yêu cầu thêm bài hát hoặc chọn danh sách phát khác.
  - Quay lại bước 3.

#### 4.6 Ngoại lệ

- **E1: Lỗi Kết nối Cơ sở Dữ liệu**
  - Nếu cơ sở dữ liệu không khả dụng, hệ thống hiển thị: "Không thể truy xuất danh sách phát. Vui lòng thử lại hoặc chuyển sang chế độ ngoại tuyến."
  - Người dùng được yêu cầu thử lại hoặc chuyển đổi chế độ.
- **E2: Lỗi Phát Phương tiện**
  - Nếu bài hát không phát được, hệ thống hiển thị: "Lỗi phát phương tiện."
  - Hệ thống chuyển sang bài hát tiếp theo, nếu có.

#### 4.7 Điều kiện Hậu quả

- Bài hát được chọn đang được phát.
- Giao diện người dùng hiển thị siêu dữ liệu và tiến trình phát.

#### 4.8 Mức độ Ưu tiên

Cao

#### 4.9 Tần suất Sử dụng

Thường xuyên

#### 4.10 Giả định

- Cơ sở dữ liệu chứa tham chiếu tệp nhạc hợp lệ.
- QMediaPlayer hỗ trợ các định dạng âm thanh trong cơ sở dữ liệu.

---

### 5. Phát Nhạc từ Tệp/Thư mục Cục bộ (UC-004)

#### 5.1 Mô tả Ngắn gọn

Trường hợp sử dụng này mô tả cách người dùng phát một tệp nhạc đơn lẻ hoặc danh sách phát từ thư mục cục bộ ở chế độ trực tuyến hoặc ngoại tuyến.

#### 5.2 Tác nhân

- **Tác nhân Chính**: Người dùng Đã đăng nhập (chế độ trực tuyến) hoặc Người dùng Khách (chế độ ngoại tuyến)
- **Tác nhân Phụ**: Hệ thống Tệp Cục bộ

#### 5.3 Điều kiện Tiên quyết

- Người dùng ở chế độ ngoại tuyến hoặc đã đăng nhập ở chế độ trực tuyến.
- Hệ thống tệp cục bộ có thể truy cập.

#### 5.4 Luồng Chính

1. Người dùng chọn tùy chọn phát tệp hoặc thư mục cục bộ thông qua giao diện người dùng.
2. Hệ thống mở hộp thoại duyệt tệp/thư mục.
3. Người dùng chọn một tệp nhạc đơn lẻ hoặc một thư mục.
4. Nếu chọn thư mục, hệ thống quét các tệp âm thanh được hỗ trợ (ví dụ: MP3, WAV) và tạo danh sách phát.
5. Người dùng chọn một bài hát từ tệp hoặc danh sách phát.
6. Hệ thống sử dụng QMediaPlayer để phát bài hát.
7. Hệ thống hiển thị siêu dữ liệu của bài hát (tiêu đề, nghệ sĩ, thời lượng) bằng QMediaMetaData và cập nhật thanh tiến trình.

#### 5.5 Luồng Phụ

- **A1: Không Tìm thấy Tệp Hỗ trợ**
  - Tại bước 4, nếu không tìm thấy tệp được hỗ trợ, hệ thống hiển thị: "Không tìm thấy tệp âm thanh được hỗ trợ."
  - Người dùng được yêu cầu chọn tệp/thư mục khác.
  - Quay lại bước 3.

#### 5.6 Ngoại lệ

- **E1: Lỗi Truy cập Tệp**
  - Nếu tệp/thư mục không thể truy cập, hệ thống hiển thị: "Không thể truy cập tệp/thư mục."
  - Người dùng được yêu cầu thử lại.
- **E2: Lỗi Phát Phương tiện**
  - Nếu bài hát không phát được, hệ thống hiển thị: "Lỗi phát phương tiện."
  - Hệ thống chuyển sang bài hát tiếp theo, nếu có.

#### 5.7 Điều kiện Hậu quả

- Bài hát được chọn đang được phát.
- Giao diện người dùng hiển thị siêu dữ liệu và tiến trình phát.

#### 5.8 Mức độ Ưu tiên

Cao

#### 5.9 Tần suất Sử dụng

Thường xuyên

#### 5.10 Giả định

- Hệ thống tệp cục bộ chứa các tệp âm thanh có thể truy cập.
- QMediaPlayer và QMediaMetaData hỗ trợ các định dạng tệp được chọn.

---

### 6. Điều khiển Phát Nhạc (UC-005)

#### 6.1 Mô tả Ngắn gọn

Trường hợp sử dụng này mô tả cách người dùng điều khiển phát nhạc bằng các điều khiển cơ bản ở chế độ trực tuyến hoặc ngoại tuyến.

#### 6.2 Tác nhân

- **Tác nhân Chính**: Người dùng Đã đăng nhập (chế độ trực tuyến) hoặc Người dùng Khách (chế độ ngoại tuyến)
- **Tác nhân Phụ**: QMediaPlayer

#### 6.3 Điều kiện Tiên quyết

- Người dùng ở chế độ ngoại tuyến hoặc đã đăng nhập ở chế độ trực tuyến.
- Một bài hát đã được tải hoặc đang phát.

#### 6.4 Luồng Chính

1. Người dùng tương tác với các điều khiển giao diện người dùng (phát/tạm dừng, tiếp theo/trước đó, tăng/giảm âm lượng, tìm kiếm thanh tiến trình).
2. Hệ thống xử lý đầu vào:
   - Phát/Tạm dừng: Chuyển đổi trạng thái phát.
   - Tiếp theo/Trước đó: Chuyển sang bài hát tiếp theo hoặc trước đó trong danh sách phát.
   - Tăng/Giảm Âm lượng: Điều chỉnh mức âm lượng.
   - Tìm kiếm Thanh Tiến trình: Di chuyển phát lại đến vị trí được chọn.
3. Hệ thống cập nhật giao diện người dùng với trạng thái phát hiện tại, thời gian và thời lượng.
4. Hệ thống đảm bảo hoạt ảnh mượt mà cho các tương tác điều khiển.

#### 6.5 Luồng Phụ

- **A1: Không Có Bài Tiếp theo/Trước đó**
  - Tại bước 2, nếu không có bài hát tiếp theo/trước đó, hệ thống vô hiệu hóa nút tương ứng hoặc không thực hiện hành động.
- **A2: Kết thúc Danh sách Phát**
  - Tại bước 2, nếu bài hát cuối cùng kết thúc, hệ thống dừng phát hoặc lặp lại danh sách phát (dựa trên cài đặt).

#### 6.6 Ngoại lệ

- **E1: Lỗi Phát Phương tiện**
  - Nếu phát lại thất bại, hệ thống hiển thị: "Lỗi phát phương tiện."
  - Hệ thống cố gắng chuyển sang bài hát tiếp theo.

#### 6.7 Điều kiện Hậu quả

- Trạng thái phát phản ánh hành động của người dùng.
- Giao diện người dùng được cập nhật với thông tin phát lại theo thời gian thực.

#### 6.8 Mức độ Ưu tiên

Cao

#### 6.9 Tần suất Sử dụng

Rất Thường xuyên

#### 6.10 Giả định

- Giao diện người dùng cung cấp các điều khiển phản hồi nhanh.
- QMediaPlayer hỗ trợ cập nhật phát lại theo thời gian thực.

---

### 7. Tìm kiếm Bài hát hoặc Danh sách Phát (UC-006)

#### 7.1 Mô tả Ngắn gọn

Trường hợp sử dụng này mô tả cách người dùng đã đăng nhập tìm kiếm bài hát hoặc danh sách phát ở chế độ trực tuyến.

#### 7.2 Tác nhân

- **Tác nhân Chính**: Người dùng Đã đăng nhập
- **Tác nhân Phụ**: Hệ thống Cơ sở Dữ liệu

#### 7.3 Điều kiện Tiên quyết

- Người dùng đã đăng nhập và ở chế độ trực tuyến.
- Cơ sở dữ liệu có thể truy cập.

#### 7.4 Luồng Chính

1. Người dùng Đã đăng nhập điều hướng đến trang tìm kiếm bài hát hoặc danh sách phát.
2. Hệ thống hiển thị thanh tìm kiếm với giao diện hiện đại.
3. Người dùng nhập truy vấn tìm kiếm (ví dụ: tiêu đề bài hát, nghệ sĩ, tên danh sách phát).
4. Hệ thống truy vấn cơ sở dữ liệu để tìm kết quả phù hợp.
5. Hệ thống hiển thị kết quả trong danh sách với siêu dữ liệu (ví dụ: tiêu đề bài hát, nghệ sĩ, tên danh sách phát).
6. Người dùng chọn một kết quả để phát (đối với bài hát) hoặc xem (đối với danh sách phát).

#### 7.5 Luồng Phụ

- **A1: Không Tìm thấy Kết quả**
  - Tại bước 5, nếu không tìm thấy kết quả phù hợp, hệ thống hiển thị: "Không tìm thấy kết quả cho [truy vấn]."
  - Người dùng có thể sửa đổi truy vấn và thử lại.
  - Quay lại bước 3.

#### 7.6 Ngoại lệ

- **E1: Lỗi Kết nối Cơ sở Dữ liệu**
  - Nếu cơ sở dữ liệu không khả dụng, hệ thống hiển thị: "Không thể tìm kiếm. Vui lòng thử lại hoặc chuyển sang chế độ ngoại tuyến."
  - Người dùng được yêu cầu thử lại hoặc chuyển đổi chế độ.

#### 7.7 Điều kiện Hậu quả

- Các bài hát hoặc danh sách phát phù hợp được hiển thị.
- Người dùng có thể tương tác với kết quả (phát hoặc xem).

#### 7.8 Mức độ Ưu tiên

Trung bình

#### 7.9 Tần suất Sử dụng

Vừa phải

#### 7.10 Giả định

- Cơ sở dữ liệu hỗ trợ tìm kiếm dựa trên văn bản hiệu quả.
- Giao diện người dùng cung cấp cách trình bày kết quả rõ ràng.

---

### 8. Điều khiển Trình phát bằng Vi điều khiển (UC-007)

#### 8.1 Mô tả Ngắn gọn

Trường hợp sử dụng này mô tả cách người dùng điều khiển Trình phát Đa phương tiện bằng vi điều khiển bên ngoài ở chế độ trực tuyến hoặc ngoại tuyến.

#### 8.2 Tác nhân

- **Tác nhân Chính**: Người dùng Đã đăng nhập (chế độ trực tuyến) hoặc Người dùng Khách (chế độ ngoại tuyến)
- **Tác nhân Phụ**: Vi điều khiển Bên ngoài (ví dụ: S32K144)

#### 8.3 Điều kiện Tiên quyết

- Người dùng ở chế độ ngoại tuyến hoặc đã đăng nhập ở chế độ trực tuyến.
- Vi điều khiển được kết nối qua UART, USB hoặc Bluetooth.

#### 8.4 Luồng Chính

1. Người dùng đảm bảo vi điều khiển được kết nối với hệ thống.
2. Hệ thống thiết lập giao tiếp với vi điều khiển.
3. Người dùng nhấn nút trên vi điều khiển (phát/tạm dừng, tiếp theo/trước đó, tăng/giảm âm lượng).
4. Hệ thống nhận đầu vào qua giao thức giao tiếp.
5. Hệ thống xử lý đầu vào và cập nhật trạng thái phát bằng QMediaPlayer.
6. Hệ thống cập nhật giao diện người dùng để phản ánh trạng thái mới (ví dụ: biểu tượng phát/tạm dừng, mức âm lượng).

#### 8.5 Luồng Phụ

- **A1: Không Có Bài hát Đang Phát**
  - Tại bước 5, nếu không có bài hát đang phát và nhấn phát, hệ thống bắt đầu bài hát đầu tiên trong danh sách phát hiện tại.
- **A2: Không Có Bài Tiếp theo/Trước đó**
  - Tại bước 5, nếu không có bài hát tiếp theo/trước đó, hệ thống bỏ qua đầu vào.

#### 8.6 Ngoại lệ

- **E1: Lỗi Kết nối**
  - Nếu kết nối vi điều khiển thất bại, hệ thống hiển thị: "Vi điều khiển đã ngắt kết nối."
  - Người dùng được yêu cầu kết nối lại.
- **E2: Lỗi Phát Phương tiện**
  - Nếu phát lại thất bại, hệ thống hiển thị: "Lỗi phát phương tiện."
  - Hệ thống cố gắng chuyển sang bài hát tiếp theo.

#### 8.7 Điều kiện Hậu quả

- Trạng thái phát phản ánh đầu vào từ vi điều khiển.
- Giao diện người dùng được cập nhật tương ứng.

#### 8.8 Mức độ Ưu tiên

Trung bình

#### 8.9 Tần suất Sử dụng

Thỉnh thoảng (tùy thuộc vào việc sử dụng vi điều khiển).

#### 8.10 Giả định

- Vi điều khiển gửi tín hiệu điều khiển tiêu chuẩn.
- Hệ thống hỗ trợ giao thức giao tiếp được chọn.

---

### 9. Gợi ý Bài hát qua Chatbot (UC-008, Tùy chọn)

#### 9.1 Mô tả Ngắn gọn

Trường hợp sử dụng này mô tả cách người dùng đã đăng nhập tương tác với chatbot tùy chọn để nhận gợi ý bài hát ở chế độ trực tuyến.

#### 9.2 Tác nhân

- **Tác nhân Chính**: Người dùng Đã đăng nhập
- **Tác nhân Phụ**: Hệ thống Chatbot

#### 9.3 Điều kiện Tiên quyết

- Người dùng đã đăng nhập và ở chế độ trực tuyến.
- Tính năng chatbot được kích hoạt và hoạt động.

#### 9.4 Luồng Chính

1. Người dùng Đã đăng nhập điều hướng đến giao diện chatbot trong giao diện người dùng.
2. Hệ thống hiển thị giao diện hội thoại với trường nhập văn bản.
3. Người dùng nhập sở thích (ví dụ: "phát nhạc rock" hoặc "bài hát vui vẻ").
4. Chatbot xử lý đầu vào bằng cách sử dụng xử lý ngôn ngữ tự nhiên.
5. Hệ thống truy xuất các bài hát phù hợp từ cơ sở dữ liệu.
6. Hệ thống hiển thị danh sách các bài hát được đề xuất với siêu dữ liệu.
7. Người dùng chọn một bài hát để phát.

#### 9.5 Luồng Phụ

- **A1: Không Tìm thấy Bài hát Phù hợp**
  - Tại bước 6, nếu không có bài hát nào phù hợp, hệ thống hiển thị: "Không tìm thấy bài hát. Hãy thử các sở thích khác."
  - Người dùng có thể nhập sở thích mới.
  - Quay lại bước 3.

#### 9.6 Ngoại lệ

- **E1: Lỗi Xử lý Chatbot**
  - Nếu chatbot không xử lý được đầu vào, hệ thống hiển thị: "Không thể xử lý yêu cầu. Vui lòng thử lại."
  - Người dùng được yêu cầu thử lại.

#### 9.7 Điều kiện Hậu quả

- Danh sách các bài hát được đề xuất được hiển thị.
- Người dùng có thể phát bài hát được đề xuất.

#### 9.8 Mức độ Ưu tiên

Thấp

#### 9.9 Tần suất Sử dụng

Thỉnh thoảng

#### 9.10 Giả định

- Chatbot hỗ trợ hiểu ngôn ngữ tự nhiên cơ bản.
- Cơ sở dữ liệu chứa đủ bài hát để gợi ý.
