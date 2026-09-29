#include <stdio.h>

int main() {
    // ===== Hang so nghiep vu =====
    int phi_goc = 200000;      // Phi kham goc (VND)
    int phi_bhyt = 40000;      // Phi kham khi co BHYT (20% phi goc)

    // ===== Mang luu tru song song (cung chi so = cung benh nhan) =====
    int tuoi_benh_nhan[4];     // Tuoi cua 4 benh nhan
    int co_bao_hiem[4];        // 1: Co BHYT, 0: Khong co BHYT
    int phi_kham[4];           // Tien kham thuc te phai thu
    int loai_luong[4];         // 1: UU TIEN, 0: THUONG, -1: LOI DU LIEU

    int tong_doanh_thu = 0;
    int so_ca_uu_tien = 0;

    // ===== Buoc 1: Tiep nhan du lieu =====
    printf("--- TIEP NHAN 4 BENH NHAN ---\n");
    printf("Benh nhan 1 - Nhap tuoi: ");
    scanf("%d", &tuoi_benh_nhan[0]);
    printf("Benh nhan 1 - Nhap BHYT (1: Co, 0: Khong): ");
    scanf("%d", &co_bao_hiem[0]);

    printf("Benh nhan 2 - Nhap tuoi: ");
    scanf("%d", &tuoi_benh_nhan[1]);
    printf("Benh nhan 2 - Nhap BHYT (1: Co, 0: Khong): ");
    scanf("%d", &co_bao_hiem[1]);

    printf("Benh nhan 3 - Nhap tuoi: ");
    scanf("%d", &tuoi_benh_nhan[2]);
    printf("Benh nhan 3 - Nhap BHYT (1: Co, 0: Khong): ");
    scanf("%d", &co_bao_hiem[2]);

    printf("Benh nhan 4 - Nhap tuoi: ");
    scanf("%d", &tuoi_benh_nhan[3]);
    printf("Benh nhan 4 - Nhap BHYT (1: Co, 0: Khong): ");
    scanf("%d", &co_bao_hiem[3]);

    // ===== Buoc 2: Kiem tra du lieu, tinh phi, phan luong =====

    // --- Benh nhan 1 (index 0) ---
    if (co_bao_hiem[0] != 0 && co_bao_hiem[0] != 1) {
        co_bao_hiem[0] = 0; // BHYT sai quy chuan => mac dinh 0
    }
    if (tuoi_benh_nhan[0] <= 0 || tuoi_benh_nhan[0] > 120) {
        phi_kham[0] = 0;
        loai_luong[0] = -1;
    } else {
        if (co_bao_hiem[0] == 1) {
            phi_kham[0] = phi_bhyt;
        } else {
            phi_kham[0] = phi_goc;
        }
        if (tuoi_benh_nhan[0] > 70) {
            loai_luong[0] = 1;
            so_ca_uu_tien = so_ca_uu_tien + 1;
        } else {
            loai_luong[0] = 0;
        }
    }

    // --- Benh nhan 2 (index 1) ---
    if (co_bao_hiem[1] != 0 && co_bao_hiem[1] != 1) {
        co_bao_hiem[1] = 0;
    }
    if (tuoi_benh_nhan[1] <= 0 || tuoi_benh_nhan[1] > 120) {
        phi_kham[1] = 0;
        loai_luong[1] = -1;
    } else {
        if (co_bao_hiem[1] == 1) {
            phi_kham[1] = phi_bhyt;
        } else {
            phi_kham[1] = phi_goc;
        }
        if (tuoi_benh_nhan[1] > 70) {
            loai_luong[1] = 1;
            so_ca_uu_tien = so_ca_uu_tien + 1;
        } else {
            loai_luong[1] = 0;
        }
    }

    // --- Benh nhan 3 (index 2) ---
    if (co_bao_hiem[2] != 0 && co_bao_hiem[2] != 1) {
        co_bao_hiem[2] = 0;
    }
    if (tuoi_benh_nhan[2] <= 0 || tuoi_benh_nhan[2] > 120) {
        phi_kham[2] = 0;
        loai_luong[2] = -1;
    } else {
        if (co_bao_hiem[2] == 1) {
            phi_kham[2] = phi_bhyt;
        } else {
            phi_kham[2] = phi_goc;
        }
        if (tuoi_benh_nhan[2] > 70) {
            loai_luong[2] = 1;
            so_ca_uu_tien = so_ca_uu_tien + 1;
        } else {
            loai_luong[2] = 0;
        }
    }

    // --- Benh nhan 4 (index 3) ---
    if (co_bao_hiem[3] != 0 && co_bao_hiem[3] != 1) {
        co_bao_hiem[3] = 0;
    }
    if (tuoi_benh_nhan[3] <= 0 || tuoi_benh_nhan[3] > 120) {
        phi_kham[3] = 0;
        loai_luong[3] = -1;
    } else {
        if (co_bao_hiem[3] == 1) {
            phi_kham[3] = phi_bhyt;
        } else {
            phi_kham[3] = phi_goc;
        }
        if (tuoi_benh_nhan[3] > 70) {
            loai_luong[3] = 1;
            so_ca_uu_tien = so_ca_uu_tien + 1;
        } else {
            loai_luong[3] = 0;
        }
    }

    // ===== Buoc 3: Tong hop doanh thu =====
    tong_doanh_thu = phi_kham[0] + phi_kham[1] + phi_kham[2] + phi_kham[3];

    // ===== Buoc 4: In bao cao =====
    printf("\n--- BAO CAO CA TIEP NHAN ---\n");

    printf("Benh nhan 1 (Index 0): Tuoi %d | BHYT %d | Phi %d VND | Luong: ",
           tuoi_benh_nhan[0], co_bao_hiem[0], phi_kham[0]);
    if (loai_luong[0] == 1) printf("UU TIEN\n");
    else if (loai_luong[0] == 0) printf("THUONG\n");
    else printf("LOI DU LIEU\n");

    printf("Benh nhan 2 (Index 1): Tuoi %d | BHYT %d | Phi %d VND | Luong: ",
           tuoi_benh_nhan[1], co_bao_hiem[1], phi_kham[1]);
    if (loai_luong[1] == 1) printf("UU TIEN\n");
    else if (loai_luong[1] == 0) printf("THUONG\n");
    else printf("LOI DU LIEU\n");

    printf("Benh nhan 3 (Index 2): Tuoi %d | BHYT %d | Phi %d VND | Luong: ",
           tuoi_benh_nhan[2], co_bao_hiem[2], phi_kham[2]);
    if (loai_luong[2] == 1) printf("UU TIEN\n");
    else if (loai_luong[2] == 0) printf("THUONG\n");
    else printf("LOI DU LIEU\n");

    printf("Benh nhan 4 (Index 3): Tuoi %d | BHYT %d | Phi %d VND | Luong: ",
           tuoi_benh_nhan[3], co_bao_hiem[3], phi_kham[3]);
    if (loai_luong[3] == 1) printf("UU TIEN\n");
    else if (loai_luong[3] == 0) printf("THUONG\n");
    else printf("LOI DU LIEU\n");

    printf("-----------------------------------\n");
    printf("Tong doanh thu ca: %d VND\n", tong_doanh_thu);
    printf("Tong so ca UU TIEN: %d\n", so_ca_uu_tien);

    return 0;
}
