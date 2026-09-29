# Mini Module Quản lý Hàng đợi & Phân bổ Số thứ tự Khám bệnh (MedCare Kiosk)

Chương trình C (C11) chạy trên Console với menu điều khiển liên tục: tiếp nhận, hiển thị, cập nhật, hủy số, tìm kiếm bệnh nhân.

## 1. Thiết kế mảng song song

Mỗi bệnh nhân là **một chỉ số `i` chung** trên tất cả các mảng. Dòng `i` của mọi mảng cùng mô tả một người.

| Mảng | Kiểu | Ý nghĩa |
|---|---|---|
| `ma_so[]` | `int` | Mã số thứ tự, cấp tăng dần, **không đổi** suốt ca |
| `ten[][30]` | `char` | Tên bệnh nhân |
| `tuoi[]` | `int` | Tuổi (1..120) |
| `mang_thai[]` | `int` | 1: phụ nữ mang thai (dùng để xét ưu tiên) |
| `uu_tien[]` | `int` | 1: ưu tiên (`tuoi > 70` hoặc mang thai) |
| `bhyt[]` | `int` | 1: có BHYT |
| `chi_phi[]` | `int` | Phí khám sơ bộ: 200000 hoặc 40000 (VNĐ) |
| `bac_si[]`, `khung_gio[]` | `int` | Bác sĩ (1..5) và khung giờ (1..4) để kiểm tra tải |

Thêm `mang_thai`, `bac_si`, `khung_gio` ngoài danh sách đề cho sẵn, vì đề yêu cầu xét ưu tiên thai phụ và giới hạn 5 bệnh nhân / bác sĩ / khung giờ.

- Biến đếm `n` là số bệnh nhân hiện có. Chỉ các chỉ số `0 .. n-1` là dữ liệu hợp lệ.
- Các mảng có kích thước `MAX + 1 = 101`. Dòng cuối (chỉ số 100) là ô đệm tạm khi cần đổi vị trí một bệnh nhân.
- **Thứ tự hàng đợi chính là thứ tự chỉ số mảng.** Cột "Vị trí" khi in ra là `i + 1`, liên tục từ 1 đến `n`.
- **Mã số thứ tự và vị trí là hai khái niệm khác nhau.** Mã số là "vé" bệnh nhân cầm, không đổi. Vị trí là thứ tự được gọi vào khám, có thể đổi khi có người ưu tiên chen vào hoặc có người hủy. Hủy, sửa, tìm kiếm đều dùng mã số.

## 2. Luồng dữ liệu

Đăng ký mới → phân loại ưu tiên / BHYT → kiểm tra tải bác sĩ → cập nhật vị trí mảng → hủy / sửa → tra cứu.

1. **Tiếp nhận:** kiểm tra `n < 100`, nhập tên (`fgets`), tuổi, mang thai, BHYT, bác sĩ, khung giờ. Đếm số bệnh nhân cùng bác sĩ + khung giờ, nếu đã có 5 thì từ chối.
2. **Phân loại:** ưu tiên nếu `tuoi > 70` hoặc mang thai. Phí = 40000 nếu có BHYT, ngược lại 200000.
3. **Chèn:** người thường vào cuối hàng. Người ưu tiên được chèn ngay sau nhóm ưu tiên hiện có (dồn phải các phần tử phía sau, `n++`), nên nhóm ưu tiên luôn đứng trước và giữ thứ tự đến trước khám trước trong từng nhóm.
4. **Sửa:** tìm theo mã số, đổi tên / tuổi / BHYT / mang thai, tính lại phí và diện ưu tiên. Nếu diện ưu tiên đổi (ví dụ sửa tuổi từ 30 lên 80), bệnh nhân được cắt ra và chèn lại đúng vị trí.
5. **Hủy:** tìm theo mã số, dồn trái các phần tử phía sau, `n--`, rồi **xóa sạch dòng cuối** (`ma_so = 0`, `ten = ""`, ...) để không còn ô nhớ rác. Vị trí luôn liên tục 1..`n`.
6. **Tìm kiếm:** theo mã số (so sánh số) hoặc theo tên (`strcmp`, phân biệt hoa thường, in tất cả người trùng tên).

## 3. An toàn nhập liệu

- Mọi dữ liệu nhập (kể cả số) đều đọc bằng `fgets()`; số được chuyển bằng `sscanf`. Không dùng `scanf` để đọc số nên không bị trôi lệnh do `\n` còn trong bộ đệm.
- Dòng dài hơn bộ đệm thì phần dư được đọc bỏ, không tràn sang lần nhập sau.
- Tên rỗng, tuổi ngoài 1..120, lựa chọn ngoài phạm vi, chữ thay vì số đều bị báo lỗi và yêu cầu nhập lại.
- Tên nhập không dấu (ví dụ `Nguyen Van A`) để hiển thị đúng trên mọi Console.

## 4. Đã kiểm thử

- Thứ tự chèn: người thường, người 75 tuổi, thai phụ, người thường → hàng đợi ra `75 tuổi, thai phụ, người thường, người thường`.
- Sửa tuổi người thường lên 80 → tự chuyển vào nhóm ưu tiên, phí được tính lại.
- Bác sĩ 2 khung giờ 3 đã đủ 5 người → người thứ 6 bị từ chối.
- Nhập đủ 100 người → người thứ 101 bị từ chối vì hàng đợi đầy.
- Hủy mã số tồn tại / không tồn tại; tìm theo mã số và theo tên.

## 5. Biên dịch và chạy

```bash
gcc -Wall -Wextra -std=c11 main.c -o main
./main
```
