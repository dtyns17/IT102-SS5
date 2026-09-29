# Module Tiếp nhận & Xếp hàng Khám bệnh

## 1. Phân tích bài toán (I/O)

**Dữ liệu đầu vào (nhập từ bàn phím, 4 bệnh nhân):**

| Mảng                | Ý nghĩa         | Giá trị hợp lệ |
| ------------------- | --------------- | -------------- |
| `tuoi_benh_nhan[4]` | Tuổi bệnh nhân  | 1 đến 120      |
| `co_bao_hiem[4]`    | Trạng thái BHYT | 0 hoặc 1       |

**Dữ liệu cần tính (lưu song song, cùng chỉ số = cùng một bệnh nhân):**

| Đại lượng        | Ý nghĩa                                |
| ---------------- | -------------------------------------- |
| `phi_kham[4]`    | Tiền khám thực tế phải thu             |
| `loai_luong[4]`  | 1: ƯU TIÊN, 0: THƯỜNG, -1: LỖI DỮ LIỆU |
| `tong_doanh_thu` | Tổng `phi_kham[0..3]`                  |
| `so_ca_uu_tien`  | Số bệnh nhân thuộc luồng ƯU TIÊN       |

**Dữ liệu đầu ra:** thông tin từng bệnh nhân (tuổi, BHYT, phí, luồng), tổng doanh thu ca, tổng số ca ưu tiên.

## 2. Đề xuất giải pháp

- **Kiểm tra biên tuổi:** `tuoi <= 0 || tuoi > 120` là dữ liệu bất hợp lệ, gán `phi_kham = 0`, `loai_luong = -1` và không cộng vào số ca ưu tiên.
- **Kiểm tra BHYT:** nếu `co_bao_hiem != 0 && co_bao_hiem != 1` thì tự động đưa về 0 để không thất thoát doanh thu.
- **Lưu kết quả:** mỗi kết quả ghi vào đúng chỉ số mảng của bệnh nhân đó (index 0, 1, 2, 3), dùng mảng song song.
- **Ưu tiên:** chỉ xét khi tuổi hợp lệ, điều kiện `tuoi > 70` (đúng 70 tuổi vẫn là THƯỜNG).

## 3. Thiết kế các bước

1. Khai báo hằng nghiệp vụ (phí gốc 200000, phí BHYT 40000) và 4 mảng.
2. Nhập tuổi và BHYT cho 4 bệnh nhân vào các chỉ số 0 đến 3.
3. Với từng bệnh nhân, lần lượt:
   1. Chuẩn hóa BHYT (giá trị lạ thì về 0).
   2. Nếu tuổi ngoài khoảng 1 đến 120: phí = 0, luồng = LỖI DỮ LIỆU, dừng xử lý bệnh nhân này.
   3. Ngược lại: phí = 40000 nếu BHYT = 1, 200000 nếu BHYT = 0.
   4. Nếu tuổi > 70: luồng ƯU TIÊN và tăng `so_ca_uu_tien`; ngược lại luồng THƯỜNG.
4. Tính `tong_doanh_thu = phi_kham[0] + phi_kham[1] + phi_kham[2] + phi_kham[3]`.
5. In báo cáo từng bệnh nhân và phần tổng hợp.

## 4. Kiểm thử

Đầu vào: `75 1`, `30 2`, `150 1`, `70 0` (tuổi, BHYT).

| Bệnh nhân | Tuổi | BHYT nhập | Phí    | Luồng       | Ghi chú                |
| --------- | ---- | --------- | ------ | ----------- | ---------------------- |
| 1         | 75   | 1         | 40000  | ƯU TIÊN     | Có BHYT, trên 70 tuổi  |
| 2         | 30   | 2         | 200000 | THƯỜNG      | BHYT sai, tự về 0      |
| 3         | 150  | 1         | 0      | LỖI DỮ LIỆU | Tuổi ngoài biên        |
| 4         | 70   | 0         | 200000 | THƯỜNG      | Biên 70, không ưu tiên |

Tổng doanh thu: **440000 VNĐ**. Số ca ưu tiên: **1**.

## 5. Biên dịch và chạy

```bash
gcc main.c -o main
./main
```
