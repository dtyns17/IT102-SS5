# Bài tập 03: Trade-off mảng tĩnh – Hủy lượt khám trong hàng chờ (MediCare)

## 1. Phân tích Input / Output

**Input**
- `n`: số bệnh nhân ban đầu, `0 <= n <= MAX (100)`.
- Với mỗi bệnh nhân: tuổi (`1..120`), trạng thái BHYT (`0` hoặc `1`). Nhập sai thì yêu cầu nhập lại.
- `K`: chỉ số lượt khám cần hủy, phải thỏa `0 <= K < n`.

**Dữ liệu lưu trữ (3 mảng song song, cùng chỉ số = cùng một bệnh nhân)**
- `so_thu_tu[MAX]`: mã số thứ tự khám (kiosk cấp theo thứ tự đến).
- `tuoi[MAX]`: tuổi.
- `bhyt[MAX]`: 1 có BHYT, 0 không có.

**Output**
- Hàng chờ ban đầu, tổng doanh thu dự kiến, số bệnh nhân ưu tiên (`tuoi >= 70`).
- Hàng chờ sau khi hủy, số bệnh nhân còn lại, doanh thu và số ca ưu tiên cập nhật.

**Quy tắc phí (số nguyên):** có BHYT = 30000 VNĐ, không BHYT = 150000 VNĐ. Không dùng số thực nên không mất dữ liệu do ép kiểu.

## 2. Các giải pháp cho thao tác "Hủy lượt khám tại chỉ số K"

**Giải pháp A – Dồn dịch mảng (Shift Array / Hard Delete):** dịch trái các phần tử `K+1 .. n-1` một ô rồi giảm `n`.

**Giải pháp B – Đánh dấu trạng thái (Soft Delete):** thêm mảng `da_huy[]`, đặt `da_huy[K] = 1`, `n` giữ nguyên. Mọi thao tác in, tính tiền, đếm ưu tiên phải bỏ qua phần tử đã hủy.

**Giải pháp C – Đổi chỗ phần tử cuối (Swap with Last):** chép phần tử cuối vào vị trí K rồi giảm `n`.

## 3. Bảng so sánh

| Tiêu chí | A – Shift Array | B – Soft Delete | C – Swap with Last |
|---|---|---|---|
| Thời gian hủy | O(n) | O(1) | O(1) |
| Thời gian in / tính tổng sau đó | O(n), không có dữ liệu rác | O(n), phải lọc phần tử đã hủy, mảng ngày càng đầy "rác" | O(n), không có dữ liệu rác |
| Bộ nhớ | O(1) thêm | O(n) thêm (mảng cờ), mảng không thu nhỏ được | O(1) thêm |
| Bảo toàn thứ tự FIFO | **Có** | Có (nếu bỏ qua đúng phần tử đã hủy) | **Không** (bệnh nhân cuối nhảy lên vị trí K) |
| Độ phức tạp cài đặt | Thấp, một vòng `for` | Trung bình, mọi hàm xử lý phải nhớ kiểm tra cờ, dễ sót gây gọi khống | Rất thấp |
| Nguy cơ sự cố nghiệp vụ | Thấp | Cao nếu quên lọc cờ (chính là lỗi hiện tại) | Cao: gọi sai thứ tự, bệnh nhân đến sau được khám trước |

## 4. Lựa chọn: Giải pháp A – Dồn dịch mảng

- **Đúng nghiệp vụ FIFO:** hàng chờ khám bệnh bắt buộc giữ thứ tự đến trước khám trước. Giải pháp C loại ngay vì phá thứ tự.
- **Chi phí O(n) chấp nhận được:** `n <= 100`, tối đa khoảng 100 phép gán mỗi lần hủy, không đáng kể so với tần suất thao tác của kiosk.
- **Khắc phục triệt để sự cố:** dữ liệu hủy bị xóa hẳn khỏi phần "active" của mảng nên màn hình bác sĩ không còn số rác, và tổng tiền luôn tính trên đúng `n` phần tử hiện có. Giải pháp B dễ tái phát lỗi cũ nếu sót một chỗ lọc.
- **Đơn giản, không tốn thêm bộ nhớ.**

## 5. Luồng logic của giải pháp chọn

1. Nhập `n` (kiểm tra `0..100`), sau đó nhập tuổi và BHYT cho từng bệnh nhân (kiểm tra hợp lệ, sai thì nhập lại). Số thứ tự được cấp tăng dần theo thứ tự nhập.
2. In hàng chờ, tính tổng doanh thu và đếm ca ưu tiên.
3. Nếu `n == 0`: báo lỗi hàng chờ rỗng, kết thúc.
4. Nhập `K`. Nếu `K < 0` hoặc `K >= n`: báo lỗi, từ chối thao tác.
5. Với `i` từ `K` đến `n-2`: chép phần tử `i+1` vào `i` cho cả 3 mảng, rồi `n = n - 1`.
6. In lại hàng chờ, số bệnh nhân còn lại, doanh thu và số ca ưu tiên đã cập nhật. Mã số thứ tự của những người còn lại được giữ nguyên.

## 6. Ví dụ kiểm thử

Nhập `n = 4`: (75 tuổi, BHYT), (30, không), (70, BHYT), (5, không). Hủy `K = 1`.

| | Trước hủy | Sau hủy |
|---|---|---|
| Số bệnh nhân | 4 | 3 |
| Tổng doanh thu | 360000 VNĐ | 210000 VNĐ |
| Số ca ưu tiên | 2 | 2 |

Với `K = 9` hoặc `K = -1`, chương trình báo lỗi và không thay đổi hàng chờ. Với `n = 0`, chương trình báo hàng chờ rỗng.

## 7. Biên dịch và chạy

```bash
gcc -Wall main.c -o main
./main
```
