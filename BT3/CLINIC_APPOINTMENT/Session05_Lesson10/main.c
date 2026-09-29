#include <stdio.h>

#define MAX 100
#define GIA_NIEM_YET 150000   /* VND / luot kham */
#define GIA_BHYT      30000   /* Thuc chi khi co BHYT (20%) */

/* Doc mot so nguyen trong [min, max]; nhap sai thi bao loi va yeu cau nhap lai.
   Tra ve 0 neu het du lieu dau vao (EOF), 1 neu doc thanh cong. */
static int doc_so_nguyen(const char *loi_nhac, int min, int max, int *ket_qua) {
    int gia_tri;
    int c;
    while (1) {
        printf("%s", loi_nhac);
        if (scanf("%d", &gia_tri) != 1) {
            /* Nhap khong phai so: bo qua het dong hien tai */
            c = getchar();
            if (c == EOF) {
                return 0;
            }
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
            printf("  Loi: vui long nhap mot so nguyen.\n");
            continue;
        }
        if (gia_tri < min || gia_tri > max) {
            printf("  Loi: gia tri phai nam trong khoang [%d, %d].\n", min, max);
            continue;
        }
        *ket_qua = gia_tri;
        return 1;
    }
}

/* Tinh phi thuc chi cua mot benh nhan (so nguyen, khong ep kieu thuc) */
static int tinh_phi(int bhyt) {
    if (bhyt == 1) {
        return GIA_BHYT;
    }
    return GIA_NIEM_YET;
}

/* In hang cho, tra ve tong doanh thu; so ca uu tien tra qua con tro */
static int in_hang_cho(const int so_thu_tu[], const int tuoi[], const int bhyt[],
                       int n, int *so_uu_tien) {
    int tong = 0;
    int i;
    *so_uu_tien = 0;
    if (n == 0) {
        printf("(Hang cho trong)\n");
    }
    for (i = 0; i < n; i++) {
        int phi = tinh_phi(bhyt[i]);
        int uu_tien = (tuoi[i] >= 70);
        printf("[Index %d] STT: %d | Tuoi: %d | BHYT: %d | Phi: %d VND%s\n",
               i, so_thu_tu[i], tuoi[i], bhyt[i], phi, uu_tien ? " | UU TIEN" : "");
        tong += phi;
        if (uu_tien) {
            (*so_uu_tien)++;
        }
    }
    return tong;
}

int main(void) {
    int so_thu_tu[MAX];   /* Ma so thu tu kham */
    int tuoi[MAX];        /* Tuoi benh nhan */
    int bhyt[MAX];        /* 1: co BHYT, 0: khong */
    int n = 0;
    int k = 0;
    int i;
    int tong, so_uu_tien;

    /* ===== 1. Nhap danh sach ban dau ===== */
    if (!doc_so_nguyen("Nhap so benh nhan n (0..100): ", 0, MAX, &n)) {
        return 1;
    }
    for (i = 0; i < n; i++) {
        printf("--- Benh nhan %d (STT %d) ---\n", i + 1, i + 1);
        so_thu_tu[i] = i + 1;   /* Kiosk cap so theo thu tu den, FIFO */
        if (!doc_so_nguyen("  Tuoi (1..120): ", 1, 120, &tuoi[i])) {
            return 1;
        }
        if (!doc_so_nguyen("  BHYT (1: Co, 0: Khong): ", 0, 1, &bhyt[i])) {
            return 1;
        }
    }

    /* ===== 2. In hang cho ban dau ===== */
    printf("\n===== HANG CHO BAN DAU =====\n");
    tong = in_hang_cho(so_thu_tu, tuoi, bhyt, n, &so_uu_tien);
    printf("Tong doanh thu du kien: %d VND\n", tong);
    printf("So benh nhan uu tien (>= 70 tuoi): %d\n", so_uu_tien);

    /* ===== 3. Huy luot kham tai chi so K ===== */
    if (n == 0) {
        printf("\nLoi: hang cho dang rong, khong the huy luot kham.\n");
        return 0;
    }
    printf("\n");
    if (!doc_so_nguyen("Nhap chi so K can huy: ", -2147483647 - 1, 2147483647, &k)) {
        return 1;
    }
    if (k < 0 || k >= n) {
        printf("Loi: chi so K = %d nam ngoai pham vi hang cho [0, %d]. Tu choi thao tac.\n",
               k, n - 1);
        return 0;
    }

    /* Hard delete: don (dich trai) cac phan tu phia sau K de giu nguyen thu tu FIFO */
    for (i = k; i < n - 1; i++) {
        so_thu_tu[i] = so_thu_tu[i + 1];
        tuoi[i] = tuoi[i + 1];
        bhyt[i] = bhyt[i + 1];
    }
    n--;

    /* ===== 4. In hang cho sau khi tai cau truc ===== */
    printf("\n===== HANG CHO SAU KHI HUY INDEX %d =====\n", k);
    tong = in_hang_cho(so_thu_tu, tuoi, bhyt, n, &so_uu_tien);
    printf("So benh nhan con lai: %d\n", n);
    printf("Tong doanh thu cap nhat: %d VND\n", tong);
    printf("So benh nhan uu tien (>= 70 tuoi): %d\n", so_uu_tien);

    return 0;
}
