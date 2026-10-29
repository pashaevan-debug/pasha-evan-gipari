#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PERALATAN 5
#define MAX_TRANSAKSI 10

// Array Global untuk Data Peralatan (Ketentuan D.6)
const char *NAMA_PERALATAN[MAX_PERALATAN] = {
    "Tenda Kapasitas 4 Orang",
    "Sleeping Bag",
    "Kompor Portable",
    "Matras Camping",
    "Lampu Camping"
};

const int HARGA_PERALATAN[MAX_PERALATAN] = {
    50000,
    15000,
    20000,
    10000,
    12000
};

// Array Parallel Global untuk Riwayat Transaksi (Ketentuan C.6 & D.7)
char riwayat_nama[MAX_TRANSAKSI][50];
char riwayat_peralatan[MAX_TRANSAKSI][50];
int riwayat_unit[MAX_TRANSAKSI];
int riwayat_lama[MAX_TRANSAKSI];
long riwayat_subtotal[MAX_TRANSAKSI];
long riwayat_diskon[MAX_TRANSAKSI];
long riwayat_total[MAX_TRANSAKSI];
int jumlah_transaksi = 0;

// Deklarasi Fungsi Modular (Ketentuan D.5)
void tampilkan_daftar_peralatan();
float hitung_persen_diskon(int lama_sewa);
void tambah_penyewaan();
void tampilkan_riwayat();

int main() {
    int pilihan;

    // Perulangan Menu Utama (Ketentuan C.1)
    do {
        printf("\n========================================\n");
        printf("            ADVENTURE CAMP              \n");
        printf("      SISTEM PENYEWAAN PERALATAN        \n");
        printf("========================================\n");
        printf("1. Lihat Daftar Peralatan\n");
        printf("2. Sewa Peralatan\n");
        printf("3. Lihat Riwayat Transaksi\n");
        printf("4. Keluar\n");
        printf("----------------------------------------\n");
        printf("Pilih menu [1-4]: ");

        if (scanf("%d", &pilihan) != 1) {
            while (getchar() != '\n'); // Clear buffer
            printf("\nMasukan harus berupa angka! Tekan Enter untuk mencoba lagi...");
            getchar();
            continue;
        }

        switch (pilihan) {
            case 1:
                tampilkan_daftar_peralatan();
                printf("\nTekan Enter untuk kembali ke menu utama...");
                getchar(); // Catch newline
                getchar();
                break;
            case 2:
                tambah_penyewaan();
                break;
            case 3:
                tampilkan_riwayat();
                printf("\nTekan Enter untuk kembali ke menu utama...");
                getchar(); // Catch newline
                getchar();
                break;
            case 4:
                printf("\nTerima kasih telah menggunakan sistem Adventure Camp!\n");
                break;
            default:
                printf("\nPilihan tidak valid! Pilih angka 1-4.\n");
        }
    } while (pilihan != 4);

    return 0;
}

// Fungsi 1: Menampilkan Daftar Peralatan (Ketentuan C.2)
void tampilkan_daftar_peralatan() {
    printf("\n==================================================\n");
    printf("                DAFTAR PERALATAN                  \n");
    printf("==================================================\n");
    printf("%-4s | %-28s | %-12s\n", "No.", "Peralatan", "Harga/Hari");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < MAX_PERALATAN; i++) {
        printf("%-4d | %-28s | Rp%-10d\n", i + 1, NAMA_PERALATAN[i], HARGA_PERALATAN[i]);
    }
    printf("==================================================\n");
}

// Fungsi 2: Menghitung Persentase Diskon (Ketentuan C.4)
float hitung_persen_diskon(int lama_sewa) {
    if (lama_sewa >= 5) {
        return 0.15f; // 15%
    } else if (lama_sewa >= 3) {
        return 0.10f; // 10%
    } else {
        return 0.0f;  // 0%
    }
}

// Fungsi 3: Melakukan Penyewaan & Struk Transaksi (Ketentuan C.3, C.4, C.5)
void tambah_penyewaan() {
    // Validasi Kapasitas Transaksi (Ketentuan C.6)
    if (jumlah_transaksi >= MAX_TRANSAKSI) {
        printf("\n[PERINGATAN] Kapasitas penyimpanan transaksi penuh! Tidak dapat menerima transaksi baru.\n");
        printf("Tekan Enter untuk kembali...");
        getchar(); getchar();
        return;
    }

    char nama[50];
    int pilihan_item, unit, lama;
    char kembali;

    printf("\n========================================\n");
    printf("            SEWA PERALATAN              \n");
    printf("========================================\n");

    // Input Nama
    printf("Nama Penyewa : ");
    getchar(); // Clear buffer
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = 0; // Hapus newline

    // Validasi Pilihan Peralatan
    tampilkan_daftar_peralatan();
    do {
        printf("Pilih peralatan [1-%d] : ", MAX_PERALATAN);
        scanf("%d", &pilihan_item);
        if (pilihan_item < 1 || pilihan_item > MAX_PERALATAN) {
            printf("Pilihan tidak valid! Silakan pilih kembali.\n");
        }
    } while (pilihan_item < 1 || pilihan_item > MAX_PERALATAN);

    // Validasi Jumlah Unit
    do {
        printf("Jumlah Unit (minimal 1) : ");
        scanf("%d", &unit);
        if (unit < 1) {
            printf("Jumlah unit minimal 1!\n");
        }
    } while (unit < 1);

    // Validasi Lama Penyewaan
    do {
        printf("Lama Sewa / Hari (minimal 1) : ");
        scanf("%d", &lama);
        if (lama < 1) {
            printf("Lama penyewaan minimal 1 hari!\n");
        }
    } while (lama < 1);

    // Perhitungan Biaya
    int idx = pilihan_item - 1;
    long subtotal = (long)HARGA_PERALATAN[idx] * unit * lama;
    float persen_diskon = hitung_persen_diskon(lama);
    long diskon = subtotal * persen_diskon;
    long total_bayar = subtotal - diskon;

    // Simpan ke Riwayat Transaksi
    strcpy(riwayat_nama[jumlah_transaksi], nama);
    strcpy(riwayat_peralatan[jumlah_transaksi], NAMA_PERALATAN[idx]);
    riwayat_unit[jumlah_transaksi] = unit;
    riwayat_lama[jumlah_transaksi] = lama;
    riwayat_subtotal[jumlah_transaksi] = subtotal;
    riwayat_diskon[jumlah_transaksi] = diskon;
    riwayat_total[jumlah_transaksi] = total_bayar;
    jumlah_transaksi++;

    // Tampilkan Struk Penyewaan (Ketentuan C.5)
    printf("\n========================================\n");
    printf("            ADVENTURE CAMP              \n");
    printf("            STRUK PENYEWAAN             \n");
    printf("========================================\n");
    printf("Nama Penyewa   : %s\n", nama);
    printf("Peralatan      : %s\n", NAMA_PERALATAN[idx]);
    printf("Harga per Hari : Rp%d\n", HARGA_PERALATAN[idx]);
    printf("Jumlah Unit    : %d\n", unit);
    printf("Lama Sewa      : %d hari\n", lama);
    printf("----------------------------------------\n");
    printf("Subtotal       : Rp%ld\n", subtotal);
    printf("Diskon (%.0f%%)  : Rp%ld\n", persen_diskon * 100, diskon);
    printf("----------------------------------------\n");
    printf("TOTAL BAYAR    : Rp%ld\n", total_bayar);
    printf("========================================\n");
    printf("Terima kasih telah menggunakan\nlayanan Adventure Camp!\n");
    printf("========================================\n");

    // Menu Kembali (Ketentuan C.5)
    printf("Kembali ke menu utama? (Y/T): ");
    scanf(" %c", &kembali);
    if (kembali == 'T' || kembali == 't') {
        printf("\nTerima kasih! Program diakhiri.\n");
        exit(0);
    }
}

// Fungsi 4: Menampilkan Riwayat Transaksi (Ketentuan C.6)
void tampilkan_riwayat() {
    printf("\n==================================================\n");
    printf("                RIWAYAT TRANSAKSI                 \n");
    printf("==================================================\n");

    if (jumlah_transaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        printf("==================================================\n");
        return;
    }

    long total_pendapatan = 0;
    printf("%-3s | %-12s | %-20s | %-10s\n", "No", "Nama", "Peralatan", "Total");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < jumlah_transaksi; i++) {
        printf("%-3d | %-12s | %-20s | Rp%-10ld\n",
               i + 1, riwayat_nama[i], riwayat_peralatan[i], riwayat_total[i]);
        total_pendapatan += riwayat_total[i];
    }

    printf("--------------------------------------------------\n");
    printf("Jumlah Transaksi : %d\n", jumlah_transaksi);
    printf("Total Pendapatan : Rp%ld\n", total_pendapatan);
    printf("==================================================\n");
}
