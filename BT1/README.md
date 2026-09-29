# CLINIC_APPOINTMENT_Session05_Debug

## 1. Phân tích lỗi

**Dòng lệnh sai logic:**

```c
queue_numbers[patient_position] = new_queue_number;
```

**Nguyên nhân kỹ thuật:**

- Mảng `queue_numbers[4]` có 4 phần tử với chỉ số hợp lệ từ **0 đến 3** (0-based).
- Biến `patient_position = 4` là **vị trí thực tế** theo cách nói của lễ tân (1-based: bệnh nhân thứ 1, 2, 3, 4).
- Code dùng trực tiếp vị trí thực tế làm chỉ số mảng, nên `queue_numbers[4]` truy cập **phần tử thứ 5**, nằm ngoài mảng (Out-of-bounds).
- Trong C, việc này gây ra **hành vi không xác định (Undefined Behavior)**. Trình biên dịch không kiểm tra biên nên không báo lỗi crash. Giá trị 1099 bị ghi vào một ô nhớ ngay sau mảng, có thể là biến khác hoặc dữ liệu của stack.
- Kết quả là `queue_numbers[3]` (bệnh nhân thứ 4) không được cập nhật và vẫn hiển thị 1004, trong khi vùng nhớ bên ngoài mảng có thể bị ghi đè sai.

**Cách sửa:** chuyển đổi vị trí thực tế sang chỉ số mảng bằng công thức `index = vị_trí - 1`.

## 2. Bảng Test Cases

| Trường hợp kiểm thử | Dữ liệu đầu vào | Kết quả sai thực tế (code lỗi) | Kết quả đúng mong đợi (code đã sửa) |
|---|---|---|---|
| TC01: Cập nhật bệnh nhân vị trí cuối (thứ 4) | `patient_position = 4`, `new_queue_number = 1099` | Ghi vào `queue_numbers[4]` (ngoài mảng). BN 4 vẫn hiển thị **1004**, dữ liệu 1099 bị mất hoặc ghi đè vùng nhớ lạ. | BN 4 hiển thị **1099**. BN 1, 2, 3 giữ nguyên 1001, 1002, 1003. |
| TC02: Cập nhật bệnh nhân vị trí đầu (thứ 1) | `patient_position = 1`, `new_queue_number = 1050` | Ghi vào `queue_numbers[1]`, tức ghi đè nhầm BN 2 (1002 thành **1050**). BN 1 vẫn là 1001. | BN 1 hiển thị **1050**. BN 2, 3, 4 giữ nguyên 1002, 1003, 1004. |

TC02 cho thấy lỗi lệch 1 đơn vị (off-by-one) xảy ra với mọi vị trí, không chỉ vị trí cuối.

## 3. Kết quả sau khi sửa (TC01)

```
--- DANH SACH SO THU TU KHAM BENH ---
Benh nhan 1 (Index 0): 1001
Benh nhan 2 (Index 1): 1002
Benh nhan 3 (Index 2): 1003
Benh nhan 4 (Index 3): 1099
```

## 4. Biên dịch và chạy

```bash
gcc main.c -o main
./main
```
