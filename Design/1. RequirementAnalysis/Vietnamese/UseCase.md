# Các Trường hợp Sử dụng Trình phát Đa phương tiện (Tiếng Việt)

## 1. Trường hợp sử dụng: Đăng ký Người dùng

- **Mã số**: UC-001
- **Tác nhân**: Người dùng Khách
- **Mô tả**: Người dùng khách tạo tài khoản mới để truy cập Trình phát Đa phương tiện ở chế độ trực tuyến cho các tính năng cơ sở dữ liệu.
- **Điều kiện tiên quyết**: Người dùng chưa đăng nhập và đã chọn chế độ trực tuyến.
- **Điều kiện hậu quả**: Người dùng có tài khoản đã đăng ký và có thể đăng nhập ở chế độ trực tuyến.
- **Luồng chính**:
  1. Người dùng điều hướng đến trang đăng ký sau khi chọn chế độ trực tuyến.
  2. Người dùng nhập tên người dùng, mật khẩu và các chi tiết yêu cầu khác.
  3. Hệ thống xác thực đầu vào (ví dụ: tên người dùng duy nhất, độ mạnh mật khẩu).
  4. Hệ thống lưu trữ thông tin xác thực của người dùng trong cơ sở dữ liệu.
  5. Hệ thống chuyển hướng người dùng đến trang đăng nhập.
- **Luồng phụ**:
  - A1: Nếu tên người dùng đã được sử dụng, hệ thống yêu cầu người dùng chọn tên khác.
  - A2: Nếu mật khẩu yếu, hệ thống hiển thị lỗi và yêu cầu mật khẩu mạnh hơn.
- **Ngoại lệ**:
  - Lỗi kết nối cơ sở dữ liệu: Hiển thị thông báo lỗi và yêu cầu thử lại hoặc chuyển sang chế độ ngoại tuyến.
- **Ưu tiên**: Cao

## 2. Trường hợp sử dụng: Đăng nhập Người dùng

- **Mã số**: UC-002
- **Tác nhân**: Người dùng Đã đăng ký
- **Mô tả**: Người dùng đã đăng ký đăng nhập vào Trình phát Đa phương tiện ở chế độ trực tuyến để sử dụng các tính năng cơ sở dữ liệu.
- **Điều kiện tiên quyết**: Người dùng có tài khoản đã đăng ký và đã chọn chế độ trực tuyến.
- **Điều kiện hậu quả**: Người dùng đã đăng nhập và có thể sử dụng Trình phát Đa phương tiện với quyền truy cập cơ sở dữ liệu.
- **Luồng chính**:
  1. Người dùng điều hướng đến trang đăng nhập sau khi chọn chế độ trực tuyến.
  2. Người dùng nhập tên người dùng và mật khẩu.
  3. Hệ thống xác thực thông tin với cơ sở dữ liệu.
  4. Hệ thống lưu trữ thông tin đăng nhập để duy trì đăng nhập bền vững.
  5. Hệ thống cấp quyền truy cập vào giao diện chính của Trình phát Đa phương tiện với kết nối cơ sở dữ liệu.
- **Luồng phụ**:
  - A1: Nếu thông tin không đúng, hệ thống hiển thị lỗi và cho phép thử lại hoặc chuyển sang chế độ ngoại tuyến.
- **Ngoại lệ**:
  - Lỗi kết nối cơ sở dữ liệu: Hiển thị thông báo lỗi và yêu cầu thử lại hoặc chuyển sang chế độ ngoại tuyến.
- **Ưu tiên**: Cao

## 3. Trường hợp sử dụng: Chọn Chế độ Trực tuyến hoặc Ngoại tuyến

- **Mã số**: UC-009
- **Tác nhân**: Người dùng Khách, Người dùng Đã đăng ký
- **Mô tả**: Người dùng chọn giữa chế độ trực tuyến (yêu cầu đăng nhập để truy cập cơ sở dữ liệu) hoặc chế độ ngoại tuyến (bỏ qua đăng nhập để phát nhạc cục bộ) tại màn hình đăng nhập.
- **Điều kiện tiên quyết**: Ứng dụng đang chạy và người dùng đang ở màn hình đăng nhập.
- **Điều kiện hậu quả**: Người dùng được chuyển đến giao diện phù hợp dựa trên chế độ đã chọn.
- **Luồng chính**:
  1. Hệ thống hiển thị màn hình đăng nhập với các tùy chọn cho chế độ trực tuyến và ngoại tuyến.
  2. Người dùng chọn chế độ trực tuyến hoặc ngoại tuyến.
  3. Nếu chọn chế độ trực tuyến, hệ thống chuyển người dùng đến trang đăng nhập hoặc đăng ký.
  4. Nếu chọn chế độ ngoại tuyến, hệ thống điều hướng trực tiếp đến giao diện phát nhạc với quyền truy cập giới hạn ở tệp cục bộ.
- **Luồng phụ**:
  - A1: Người dùng chuyển đổi giữa các chế độ trước khi xác nhận, quay lại bước 2.
- **Ngoại lệ**:
  - Không có
- **Ưu tiên**: Cao

## 4. Trường hợp sử dụng: Phát Nhạc từ Cơ sở Dữ liệu

- **Mã số**: UC-003
- **Tác nhân**: Người dùng Đã đăng nhập
- **Mô tả**: Người dùng chọn và phát nhạc từ danh sách phát lưu trong cơ sở dữ liệu ở chế độ trực tuyến.
- **Điều kiện tiên quyết**: Người dùng đã đăng nhập, ở chế độ trực tuyến và cơ sở dữ liệu có thể truy cập.
- **Điều kiện hậu quả**: Nhạc được chọn được phát và siêu dữ liệu được hiển thị.
- **Luồng chính**:
  1. Người dùng điều hướng đến phần danh sách phát.
  2. Người dùng chọn một danh sách phát từ cơ sở dữ liệu.
  3. Hệ thống truy xuất các bài hát trong danh sách phát.
  4. Người dùng chọn một bài hát để phát.
  5. Hệ thống phát bài hát và hiển thị tiêu đề, nghệ sĩ và thời lượng.
- **Luồng phụ**:
  - A1: Nếu danh sách phát trống, hệ thống yêu cầu người dùng thêm bài hát.
- **Ngoại lệ**:
  - Lỗi kết nối cơ sở dữ liệu: Hiển thị thông báo lỗi và yêu cầu chuyển sang chế độ ngoại tuyến.
- **Ưu tiên**: Cao

## 5. Trường hợp sử dụng: Phát Nhạc từ Tệp/Thư mục Cục bộ

- **Mã số**: UC-004
- **Tác nhân**: Người dùng Đã đăng nhập (chế độ trực tuyến), Người dùng Khách (chế độ ngoại tuyến)
- **Mô tả**: Người dùng phát một tệp nhạc đơn lẻ hoặc tạo danh sách phát từ thư mục cục bộ ở chế độ trực tuyến hoặc ngoại tuyến.
- **Điều kiện tiên quyết**: Người dùng ở chế độ ngoại tuyến hoặc đã đăng nhập ở chế độ trực tuyến, và tệp cục bộ có thể truy cập.
- **Điều kiện hậu quả**: Nhạc được chọn được phát và siêu dữ liệu được hiển thị.
- **Luồng chính**:
  1. Người dùng chọn tùy chọn phát tệp hoặc thư mục cục bộ.
  2. Người dùng duyệt và chọn tệp hoặc thư mục.
  3. Nếu chọn thư mục, hệ thống tải tất cả tệp nhạc được hỗ trợ thành danh sách phát.
  4. Người dùng chọn một bài hát để phát.
  5. Hệ thống phát bài hát và hiển thị tiêu đề, nghệ sĩ và thời lượng.
- **Luồng phụ**:
  - A1: Nếu không tìm thấy tệp được hỗ trợ, hệ thống hiển thị lỗi.
- **Ngoại lệ**:
  - Lỗi truy cập tệp: Hiển thị thông báo lỗi.
- **Ưu tiên**: Cao

## 6. Trường hợp sử dụng: Điều khiển Phát Nhạc

- **Mã số**: UC-005
- **Tác nhân**: Người dùng Đã đăng nhập (chế độ trực tuyến), Người dùng Khách (chế độ ngoại tuyến)
- **Mô tả**: Người dùng điều khiển phát nhạc bằng các điều khiển cơ bản ở chế độ trực tuyến hoặc ngoại tuyến.
- **Điều kiện tiên quyết**: Người dùng ở chế độ ngoại tuyến hoặc đã đăng nhập ở chế độ trực tuyến, và một bài hát đang phát.
- **Điều kiện hậu quả**: Trạng thái phát được cập nhật dựa trên hành động của người dùng.
- **Luồng chính**:
  1. Người dùng tương tác với các điều khiển phát (phát/tạm dừng, tiếp theo/trước đó, tăng/giảm âm lượng).
  2. Hệ thống cập nhật trạng thái phát tương ứng.
  3. Hệ thống cập nhật thanh tiến trình và hiển thị thời gian/thời lượng theo thời gian thực.
- **Luồng phụ**:
  - A1: Nếu không có bài tiếp theo/trước đó, hệ thống vô hiệu hóa nút tương ứng.
- **Ngoại lệ**:
  - Lỗi phát phương tiện: Hiển thị thông báo lỗi.
- **Ưu tiên**: Cao

## 7. Trường hợp sử dụng: Tìm kiếm Bài hát hoặc Danh sách Phát

- **Mã số**: UC-006
- **Tác nhân**: Người dùng Đã đăng nhập
- **Mô tả**: Người dùng tìm kiếm bài hát hoặc danh sách phát bằng các trang tìm kiếm chuyên dụng ở chế độ trực tuyến.
- **Điều kiện tiên quyết**: Người dùng đã đăng nhập, ở chế độ trực tuyến và cơ sở dữ liệu có thể truy cập.
- **Điều kiện hậu quả**: Các bài hát hoặc danh sách phát phù hợp được hiển thị.
- **Luồng chính**:
  1. Người dùng điều hướng đến trang tìm kiếm bài hát hoặc danh sách phát.
  2. Người dùng nhập truy vấn tìm kiếm.
  3. Hệ thống truy vấn cơ sở dữ liệu và hiển thị kết quả phù hợp.
  4. Người dùng chọn một kết quả để phát hoặc xem.
- **Luồng phụ**:
  - A1: Nếu không tìm thấy kết quả, hệ thống hiển thị thông báo “không có kết quả”.
- **Ngoại lệ**:
  - Lỗi kết nối cơ sở dữ liệu: Hiển thị thông báo lỗi và yêu cầu chuyển sang chế độ ngoại tuyến.
- **Ưu tiên**: Trung bình

## 8. Trường hợp sử dụng: Điều khiển Trình phát bằng Vi điều khiển

- **Mã số**: UC-007
- **Tác nhân**: Người dùng Đã đăng nhập (chế độ trực tuyến), Người dùng Khách (chế độ ngoại tuyến), Vi điều khiển Bên ngoài
- **Mô tả**: Người dùng điều khiển Trình phát Đa phương tiện bằng vi điều khiển bên ngoài ở chế độ trực tuyến hoặc ngoại tuyến.
- **Điều kiện tiên quyết**: Người dùng ở chế độ ngoại tuyến hoặc đã đăng nhập ở chế độ trực tuyến, và vi điều khiển được kết nối.
- **Điều kiện hậu quả**: Trạng thái phát được cập nhật dựa trên đầu vào từ vi điều khiển.
- **Luồng chính**:
  1. Người dùng kết nối vi điều khiển (ví dụ: qua UART, USB hoặc Bluetooth).
  2. Người dùng nhấn các nút trên vi điều khiển (phát/tạm dừng, tiếp theo/trước đó, tăng/giảm âm lượng).
  3. Hệ thống nhận và xử lý đầu vào.
  4. Hệ thống cập nhật trạng thái phát tương ứng.
- **Luồng phụ**:
  - A1: Nếu không có bài hát đang phát, phát/tạm dừng sẽ bắt đầu bài hát đầu tiên trong danh sách.
- **Ngoại lệ**:
  - Lỗi kết nối: Hiển thị thông báo lỗi.
- **Ưu tiên**: Trung bình

## 9. Trường hợp sử dụng: Gợi ý Bài hát qua Chatbot (Tùy chọn)

- **Mã số**: UC-008
- **Tác nhân**: Người dùng Đã đăng nhập
- **Mô tả**: Người dùng tương tác với chatbot để nhận gợi ý bài hát ở chế độ trực tuyến.
- **Điều kiện tiên quyết**: Người dùng đã đăng nhập, ở chế độ trực tuyến và chatbot được kích hoạt.
- **Điều kiện hậu quả**: Người dùng nhận được danh sách các bài hát được đề xuất.
- **Luồng chính**:
  1. Người dùng truy cập giao diện chatbot.
  2. Người dùng nhập sở thích (ví dụ: thể loại, tâm trạng).
  3. Hệ thống xử lý đầu vào và truy xuất các bài hát phù hợp.
  4. Hệ thống hiển thị các bài hát được đề xuất.
  5. Người dùng chọn một bài hát để phát.
- **Luồng phụ**:
  - A1: Nếu không có bài hát nào phù hợp, hệ thống đề xuất mở rộng tiêu chí.
- **Ngoại lệ**:
  - Lỗi xử lý: Hiển thị thông báo lỗi.
- **Ưu tiên**: Thấp
