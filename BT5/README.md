# CLINIC_APPOINTMENT – Session05 – Quản lý danh sách chi phí ca khám

## 1. Mô tả

Chương trình quản lý mảng `phi_kham[10]` bằng biến đếm `so_luong` (ban đầu 4 ca: 150000, 300000, 200000, 500000 VNĐ), thực hiện lần lượt: tính tổng 2 ca đầu, sửa, thêm, xóa. Toàn bộ code nằm trong `main()`, không dùng hàm tự tạo, `struct`, `char[]`; nhập dữ liệu bằng một lệnh `scanf` (không dùng vòng lặp để nhập/xuất). Vòng lặp `for` chỉ dùng để dồn dịch mảng khi xóa.

## 2. Input / Output

**Input (một dòng, 4 số nguyên):** `vi_tri_sua gia_tri_moi phi_kham_moi vi_tri_xoa`

**Output:**
1. Tổng chi phí 2 ca đầu của danh sách ban đầu (`tong_chi_phi = phi_kham[0] + phi_kham[1]`).
2. Chi phí tại vị trí vừa sửa.
3. Số lượng và chi phí của ca vừa thêm ở cuối.
4. Số lượng còn lại và chi phí tại vị trí vừa xóa (sau khi dồn), hoặc thông báo lỗi.

Lời nhắc nhập được in ra `stderr`, nên `stdout` chỉ chứa đúng các dòng kết quả theo mẫu đề bài.

## 3. Kiểm tra chỉ số và an toàn bộ nhớ

| Thao tác | Điều kiện hợp lệ | Khi vi phạm |
|---|---|---|
| Sửa | `0 <= vi_tri_sua < so_luong` | `Loi: Vi tri sua X khong hop le!`, không ghi mảng |
| Thêm | `so_luong < 10` | `Loi: Danh sach da day...`, không ghi mảng |
| Xóa | `0 <= vi_tri_xoa < so_luong` | `Loi: Vi tri xoa X khong hop le!` + `So luong ca kham giu nguyen: N`, không dồn mảng |

Sau khi xóa, ô cuối được gán về 0 để không còn dữ liệu rác. Nếu xóa đúng phần tử cuối, chương trình in "không còn phần tử" thay vì đọc ngoài phạm vi.

## 4. Kiểm thử

| Trường hợp | Input | Kết quả |
|---|---|---|
| 1 (Chuẩn) | `1 350000 250000 0` | Khớp 100% bảng ví dụ: `450000`, `350000`, `So luong = 5 ... 250000`, `So luong = 4 ... vi tri 0 moi = 350000` |
| 2 (Ngoại lệ) | `1 350000 250000 5` | `Loi: Vi tri xoa 5 khong hop le!`, không dồn mảng |
| 3 (Biên) | `9 1 1 4` | Báo lỗi vị trí sửa 9; xóa phần tử cuối (vị trí 4) an toàn |

Lưu ý ở trường hợp 2: chương trình chạy đủ 4 bước nên khi báo lỗi xóa, `so_luong` đang là 5 (đã thêm 1 ca ở bước 3). Dòng "giữ nguyên" luôn in số lượng thực tế tại thời điểm đó. Giá trị 4 trong bảng ví dụ ứng với danh sách chưa qua bước thêm.

## 5. Biên dịch và chạy

```bash
gcc -Wall -Wextra -std=c11 main.c -o main
echo "1 350000 250000 0" | ./main
```
