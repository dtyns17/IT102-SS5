#include <stdio.h>

#define SUC_CHUA_TOI_DA 10   /* Dung luong mang phi_kham */

int main(void) {
    /* ===== Du lieu ban dau: 4 ca kham, mang toi da 10 phan tu ===== */
    int phi_kham[SUC_CHUA_TOI_DA] = {150000, 300000, 200000, 500000};
    int so_luong = 4;        /* So ca kham thuc te dang hoat dong */

    int vi_tri_sua = 0;
    int gia_tri_moi = 0;
    int phi_kham_moi = 0;
    int vi_tri_xoa = 0;
    int tong_chi_phi = 0;
    int i;

    /* ===== Nhap du lieu (loi nhac ghi ra stderr de stdout chi chua ket qua) ===== */
    fprintf(stderr, "Nhap: vi_tri_sua gia_tri_moi phi_kham_moi vi_tri_xoa\n");
    if (scanf("%d %d %d %d", &vi_tri_sua, &gia_tri_moi, &phi_kham_moi, &vi_tri_xoa) != 4) {
        printf("Loi: Du lieu nhap khong hop le!\n");
        return 1;
    }

    /* ===== 1. Tong chi phi 2 ca kham dau tien (danh sach ban dau) ===== */
    tong_chi_phi = phi_kham[0] + phi_kham[1];
    printf("Tong chi phi 2 ca dau: %d VND\n", tong_chi_phi);

    /* ===== 2. Cap nhat chi phi tai vi_tri_sua (hop le: 0 .. so_luong - 1) ===== */
    if (vi_tri_sua >= 0 && vi_tri_sua < so_luong) {
        phi_kham[vi_tri_sua] = gia_tri_moi;
        printf("Sau khi sua vi tri %d: Chi phi moi = %d VND\n", vi_tri_sua, phi_kham[vi_tri_sua]);
    } else {
        printf("Loi: Vi tri sua %d khong hop le!\n", vi_tri_sua);
    }

    /* ===== 3. Them ca kham moi vao cuoi danh sach (con cho trong thi moi them) ===== */
    if (so_luong < SUC_CHUA_TOI_DA) {
        phi_kham[so_luong] = phi_kham_moi;
        so_luong++;
        printf("Sau khi them ca moi: So luong = %d, Chi phi ca cuoi = %d VND\n",
               so_luong, phi_kham[so_luong - 1]);
    } else {
        printf("Loi: Danh sach da day, khong the them ca kham moi!\n");
    }

    /* ===== 4. Xoa ca kham tai vi_tri_xoa (hop le: 0 .. so_luong - 1) ===== */
    if (vi_tri_xoa >= 0 && vi_tri_xoa < so_luong) {
        /* Don cac phan tu phia sau sang trai 1 vi tri */
        for (i = vi_tri_xoa; i < so_luong - 1; i++) {
            phi_kham[i] = phi_kham[i + 1];
        }
        so_luong--;
        phi_kham[so_luong] = 0;   /* Xoa o cuoi de khong con du lieu rac */

        if (vi_tri_xoa < so_luong) {
            printf("Sau khi xoa vi tri %d: So luong = %d, Chi phi vi tri %d moi = %d VND\n",
                   vi_tri_xoa, so_luong, vi_tri_xoa, phi_kham[vi_tri_xoa]);
        } else {
            /* Da xoa phan tu cuoi cung nen khong con phan tu tai vi tri nay */
            printf("Sau khi xoa vi tri %d: So luong = %d, Vi tri %d khong con phan tu\n",
                   vi_tri_xoa, so_luong, vi_tri_xoa);
        }
    } else {
        printf("Loi: Vi tri xoa %d khong hop le!\n", vi_tri_xoa);
        printf("So luong ca kham giu nguyen: %d\n", so_luong);
    }

    return 0;
}
