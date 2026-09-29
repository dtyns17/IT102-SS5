#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX          100      /* So benh nhan toi da trong mot ca */
#define TEN_DAI      30       /* Do dai toi da chuoi ten (ke ca '\0') */
#define TOI_DA_BS_KG 5        /* Toi da 5 benh nhan / bac si / khung gio */
#define SO_BAC_SI    5
#define SO_KHUNG_GIO 4
#define PHI_GOC      200000   /* VND */
#define PHI_BHYT     40000    /* VND (giam 80%) */

/* ===== MANG SONG SONG: cung chi so i = cung mot benh nhan =====
   Kich thuoc MAX + 1: dong cuoi (chi so MAX) la o tam khi doi vi tri. */
static int  ma_so[MAX + 1];              /* Ma so thu tu (cap tang dan, khong doi) */
static char ten[MAX + 1][TEN_DAI];       /* Ten benh nhan */
static int  tuoi[MAX + 1];               /* Tuoi */
static int  mang_thai[MAX + 1];          /* 1: phu nu mang thai, 0: khong */
static int  uu_tien[MAX + 1];            /* 1: uu tien (>70 tuoi hoac mang thai) */
static int  bhyt[MAX + 1];               /* 1: co BHYT, 0: khong */
static int  chi_phi[MAX + 1];            /* Phi kham so bo (VND) */
static int  bac_si[MAX + 1];             /* Bac si duoc dang ky (1..SO_BAC_SI) */
static int  khung_gio[MAX + 1];          /* Khung gio (1..SO_KHUNG_GIO) */

static int n = 0;                        /* Bien dem: so benh nhan dang cho */
static int ma_so_ke_tiep = 1;            /* Ma so se cap cho nguoi ke tiep */

/* ---------- Nhap lieu an toan ---------- */

/* Doc mot dong bang fgets, bo '\n', xoa phan du neu dong qua dai.
   Het du lieu (EOF) thi ket thuc chuong trinh. */
static void doc_dong(char *buf, int size) {
    int c;
    if (fgets(buf, size, stdin) == NULL) {
        printf("\nHet du lieu nhap. Ket thuc chuong trinh.\n");
        exit(0);
    }
    if (strchr(buf, '\n') != NULL) {
        buf[strcspn(buf, "\n")] = '\0';
    } else {
        /* Dong dai hon bo dem: bo phan con lai de khong troi lenh */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
}

/* Nhap so nguyen trong [min, max], sai thi nhap lai */
static int doc_so(const char *nhac, int min, int max) {
    char buf[16];
    int v, pos;
    while (1) {
        printf("%s", nhac);
        doc_dong(buf, (int)sizeof(buf));
        if (strlen(buf) > 9 || sscanf(buf, "%d %n", &v, &pos) != 1 || buf[pos] != '\0') {
            printf("  Loi: vui long nhap mot so nguyen.\n");
            continue;
        }
        if (v < min || v > max) {
            printf("  Loi: gia tri phai nam trong [%d, %d].\n", min, max);
            continue;
        }
        return v;
    }
}

/* Nhap chuoi khong rong vao dich (toi da TEN_DAI - 1 ky tu) */
static void doc_ten(const char *nhac, char *dich) {
    while (1) {
        printf("%s", nhac);
        doc_dong(dich, TEN_DAI);
        if (strlen(dich) == 0) {
            printf("  Loi: ten khong duoc de trong.\n");
            continue;
        }
        return;
    }
}

/* ---------- Nghiep vu ---------- */

static int tinh_phi(int co_bhyt) {
    if (co_bhyt == 1) {
        return PHI_BHYT;
    }
    return PHI_GOC;
}

static int xet_uu_tien(int tuoi_bn, int thai) {
    if (tuoi_bn > 70 || thai == 1) {
        return 1;
    }
    return 0;
}

/* Sao chep toan bo thong tin dong src sang dong dst (tren moi mang song song) */
static void sao_chep_dong(int dst, int src) {
    ma_so[dst] = ma_so[src];
    strcpy(ten[dst], ten[src]);
    tuoi[dst] = tuoi[src];
    mang_thai[dst] = mang_thai[src];
    uu_tien[dst] = uu_tien[src];
    bhyt[dst] = bhyt[src];
    chi_phi[dst] = chi_phi[src];
    bac_si[dst] = bac_si[src];
    khung_gio[dst] = khung_gio[src];
}

/* Vi tri chen: uu tien -> ngay sau nhom uu tien hien co; thuong -> cuoi hang */
static int vi_tri_chen(int la_uu_tien) {
    int i = 0;
    if (la_uu_tien == 0) {
        return n;
    }
    while (i < n && uu_tien[i] == 1) {
        i++;
    }
    return i;
}

/* Mo o trong tai vi tri pos: don phai cac phan tu tu pos den n-1, tang n */
static void chen_tai(int pos) {
    int i;
    for (i = n; i > pos; i--) {
        sao_chep_dong(i, i - 1);
    }
    n++;
}

/* Xoa dong pos: don trai cac phan tu phia sau, giam n, xoa sach o cuoi */
static void xoa_tai(int pos) {
    int i;
    for (i = pos; i < n - 1; i++) {
        sao_chep_dong(i, i + 1);
    }
    n--;
    ma_so[n] = 0;
    ten[n][0] = '\0';
    tuoi[n] = 0;
    mang_thai[n] = 0;
    uu_tien[n] = 0;
    bhyt[n] = 0;
    chi_phi[n] = 0;
    bac_si[n] = 0;
    khung_gio[n] = 0;
}

static int tim_theo_ma(int ma) {
    int i;
    for (i = 0; i < n; i++) {
        if (ma_so[i] == ma) {
            return i;
        }
    }
    return -1;
}

static int dem_tai_bs_khung_gio(int bs, int kg) {
    int i, dem = 0;
    for (i = 0; i < n; i++) {
        if (bac_si[i] == bs && khung_gio[i] == kg) {
            dem++;
        }
    }
    return dem;
}

/* ---------- Hien thi ---------- */

static void in_tieu_de(void) {
    printf("%-7s %-7s %-29s %-5s %-9s %-6s %-4s %-5s %s\n",
           "Vi tri", "Ma so", "Ten", "Tuoi", "Uu tien", "BHYT", "BS", "Gio", "Phi (VND)");
}

static void in_dong(int i) {
    printf("%-7d %-7d %-29s %-5d %-9s %-6s %-4d %-5d %d\n",
           i + 1, ma_so[i], ten[i], tuoi[i],
           uu_tien[i] == 1 ? "UU TIEN" : "THUONG",
           bhyt[i] == 1 ? "Co" : "Khong",
           bac_si[i], khung_gio[i], chi_phi[i]);
}

static void in_chi_tiet(int i) {
    printf("  Vi tri trong hang : %d\n", i + 1);
    printf("  Ma so thu tu      : %d\n", ma_so[i]);
    printf("  Ten               : %s\n", ten[i]);
    printf("  Tuoi              : %d\n", tuoi[i]);
    printf("  Mang thai         : %s\n", mang_thai[i] == 1 ? "Co" : "Khong");
    printf("  Dien              : %s\n", uu_tien[i] == 1 ? "UU TIEN" : "THUONG");
    printf("  BHYT              : %s\n", bhyt[i] == 1 ? "Co" : "Khong");
    printf("  Bac si / Khung gio: %d / %d\n", bac_si[i], khung_gio[i]);
    printf("  Phi kham so bo    : %d VND\n", chi_phi[i]);
}

/* ---------- Chuc nang ---------- */

static void tiep_nhan(void) {
    char ten_moi[TEN_DAI];
    int tuoi_moi, thai, co_bhyt, bs, kg, pos;

    if (n >= MAX) {
        printf("Loi: hang doi da day (%d benh nhan). Khong the tiep nhan them.\n", MAX);
        return;
    }
    doc_ten("Ten benh nhan: ", ten_moi);
    tuoi_moi = doc_so("Tuoi (1..120): ", 1, 120);
    thai = doc_so("Phu nu mang thai? (1: Co, 0: Khong): ", 0, 1);
    co_bhyt = doc_so("Co BHYT? (1: Co, 0: Khong): ", 0, 1);
    bs = doc_so("Bac si (1..5): ", 1, SO_BAC_SI);
    kg = doc_so("Khung gio (1: 7-9h, 2: 9-11h, 3: 13-15h, 4: 15-17h): ", 1, SO_KHUNG_GIO);

    if (dem_tai_bs_khung_gio(bs, kg) >= TOI_DA_BS_KG) {
        printf("Tu choi: bac si %d khung gio %d da du %d benh nhan. Vui long chon bac si/khung gio khac.\n",
               bs, kg, TOI_DA_BS_KG);
        return;
    }

    pos = vi_tri_chen(xet_uu_tien(tuoi_moi, thai));
    chen_tai(pos);
    ma_so[pos] = ma_so_ke_tiep;
    ma_so_ke_tiep++;
    strcpy(ten[pos], ten_moi);
    tuoi[pos] = tuoi_moi;
    mang_thai[pos] = thai;
    uu_tien[pos] = xet_uu_tien(tuoi_moi, thai);
    bhyt[pos] = co_bhyt;
    chi_phi[pos] = tinh_phi(co_bhyt);
    bac_si[pos] = bs;
    khung_gio[pos] = kg;

    printf("Da tiep nhan. Ma so thu tu: %d | Vi tri trong hang: %d | Dien: %s | Phi: %d VND\n",
           ma_so[pos], pos + 1, uu_tien[pos] == 1 ? "UU TIEN" : "THUONG", chi_phi[pos]);
}

static void hien_thi(void) {
    int i, tong = 0;
    if (n == 0) {
        printf("Hang doi dang trong.\n");
        return;
    }
    printf("\n===== HANG DOI (%d benh nhan) =====\n", n);
    in_tieu_de();
    for (i = 0; i < n; i++) {
        in_dong(i);
        tong += chi_phi[i];
    }
    printf("Tong phi du kien: %d VND\n", tong);
}

static void cap_nhat(void) {
    int ma, idx, chon, uu_tien_cu, pos;
    char ten_moi[TEN_DAI];

    if (n == 0) {
        printf("Hang doi dang trong, khong co gi de cap nhat.\n");
        return;
    }
    ma = doc_so("Nhap ma so thu tu can sua: ", 1, 2147483647);
    idx = tim_theo_ma(ma);
    if (idx < 0) {
        printf("Khong tim thay ma so %d trong hang doi.\n", ma);
        return;
    }
    printf("Dang sua benh nhan:\n");
    in_chi_tiet(idx);
    chon = doc_so("Sua: 1-Ten, 2-Tuoi, 3-BHYT, 4-Mang thai (0: huy): ", 0, 4);
    if (chon == 0) {
        return;
    }
    uu_tien_cu = uu_tien[idx];
    if (chon == 1) {
        doc_ten("Ten moi: ", ten_moi);
        strcpy(ten[idx], ten_moi);
    } else if (chon == 2) {
        tuoi[idx] = doc_so("Tuoi moi (1..120): ", 1, 120);
    } else if (chon == 3) {
        bhyt[idx] = doc_so("BHYT moi (1: Co, 0: Khong): ", 0, 1);
    } else {
        mang_thai[idx] = doc_so("Mang thai (1: Co, 0: Khong): ", 0, 1);
    }

    /* Tinh lai phi va dien uu tien */
    chi_phi[idx] = tinh_phi(bhyt[idx]);
    uu_tien[idx] = xet_uu_tien(tuoi[idx], mang_thai[idx]);

    /* Doi dien thi phai chuyen vi tri cho dung quy tac hang doi */
    if (uu_tien[idx] != uu_tien_cu) {
        sao_chep_dong(MAX, idx);          /* Cat tam ra dong dem */
        xoa_tai(idx);
        pos = vi_tri_chen(uu_tien[MAX]);
        chen_tai(pos);
        sao_chep_dong(pos, MAX);          /* Dat vao vi tri moi */
        idx = pos;
        printf("Dien uu tien thay doi, benh nhan duoc chuyen den vi tri %d.\n", idx + 1);
    }
    printf("Da cap nhat:\n");
    in_chi_tiet(idx);
}

static void huy_so(void) {
    int ma, idx;
    if (n == 0) {
        printf("Hang doi dang trong, khong co gi de huy.\n");
        return;
    }
    ma = doc_so("Nhap ma so thu tu can huy: ", 1, 2147483647);
    idx = tim_theo_ma(ma);
    if (idx < 0) {
        printf("Khong tim thay ma so %d trong hang doi.\n", ma);
        return;
    }
    printf("Da huy ma so %d (%s). Hang doi con %d benh nhan.\n", ma, ten[idx], n - 1);
    xoa_tai(idx);
}

static void tim_kiem(void) {
    int chon, ma, idx, i, thay = 0;
    char ten_tim[TEN_DAI];

    if (n == 0) {
        printf("Hang doi dang trong.\n");
        return;
    }
    chon = doc_so("Tim theo: 1-Ma so thu tu, 2-Ten: ", 1, 2);
    if (chon == 1) {
        ma = doc_so("Nhap ma so thu tu: ", 1, 2147483647);
        idx = tim_theo_ma(ma);
        if (idx < 0) {
            printf("Khong tim thay ma so %d.\n", ma);
        } else {
            in_chi_tiet(idx);
        }
    } else {
        doc_ten("Nhap ten can tim (phan biet hoa/thuong): ", ten_tim);
        for (i = 0; i < n; i++) {
            if (strcmp(ten[i], ten_tim) == 0) {
                printf("--- Ket qua ---\n");
                in_chi_tiet(i);
                thay = 1;
            }
        }
        if (thay == 0) {
            printf("Khong tim thay benh nhan ten \"%s\".\n", ten_tim);
        }
    }
}

int main(void) {
    int chon;
    do {
        printf("\n===== KIOSK DANG KY KHAM BENH MEDCARE =====\n");
        printf("1. Tiep nhan benh nhan moi\n");
        printf("2. Hien thi hang doi\n");
        printf("3. Cap nhat thong tin\n");
        printf("4. Huy so thu tu\n");
        printf("5. Tim kiem benh nhan\n");
        printf("0. Thoat\n");
        chon = doc_so("Chon chuc nang: ", 0, 5);
        switch (chon) {
            case 1: tiep_nhan(); break;
            case 2: hien_thi();  break;
            case 3: cap_nhat();  break;
            case 4: huy_so();    break;
            case 5: tim_kiem();  break;
            default: printf("Tam biet!\n"); break;
        }
    } while (chon != 0);
    return 0;
}
