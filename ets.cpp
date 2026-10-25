
#include <iostream>
#include <string>
using namespace std;

struct product {
    string namapro;
    int hargapro;
    int stokpro;
    int stokmin;
};

struct itempesanan {
    int index;
    int kuantitas;
};

struct pesanan {
    string namapelanggan;
    itempesanan item[3];
    int jumlah_item_berbeda;
    double subtotal;
    double diskon;
    double total;
};

product daftarproduk[10];
int jumlahproduk = 0;

pesanan orderan[20];
int jumlahorder = 0;


// FUNCTION TAMBAH PRODUK
void tmbahproduk() {
    if (jumlahproduk >= 10) {
        cout << "Maaf, jumlah produk telah mencapai batas!\n";
        return;
    }

    cout << "\n----- REGISTRASI PRODUK GUDANG -----\n";

    cout << "Masukkan nama produk: ";
    cin >> ws;
    getline(cin, daftarproduk[jumlahproduk].namapro);

    do {
        cout << "Harga produk: Rp";
        cin >> daftarproduk[jumlahproduk].hargapro;

        if (daftarproduk[jumlahproduk].hargapro < 0) {
            cout << "Harga tidak boleh negatif!\n";
        }
    } while (daftarproduk[jumlahproduk].hargapro < 0);

    do {
        cout << "Stok produk: ";
        cin >> daftarproduk[jumlahproduk].stokpro;

        if (daftarproduk[jumlahproduk].stokpro < 0) {
            cout << "Stok tidak boleh negatif!\n";
        }
    } while (daftarproduk[jumlahproduk].stokpro < 0);

    do {
        cout << "Stok minimal produk: ";
        cin >> daftarproduk[jumlahproduk].stokmin;

        if (daftarproduk[jumlahproduk].stokmin < 0) {
            cout << "Stok minimal tidak boleh negatif!\n";
        }
    } while (daftarproduk[jumlahproduk].stokmin < 0);

    jumlahproduk++;

    cout << "Produk berhasil ditambahkan!\n";
}


// FUNCTION TAMPILKAN PRODUK
void tampilkanproduk() {
    if (jumlahproduk <= 0) {
        cout << "Maaf, produk belum tersedia.\n";
        return;
    }

    cout << "\n=== DAFTAR PRODUK GUDANG ===\n";
    cout << "--------------------------------------------------\n";
    cout << "No | Nama Produk | Harga | Stok | Stok Min\n";
    cout << "--------------------------------------------------\n";

    for (int i = 0; i < jumlahproduk; i++) {
        cout << i + 1 << " | "
             << daftarproduk[i].namapro << " | Rp"
             << daftarproduk[i].hargapro << " | "
             << daftarproduk[i].stokpro << " | "
             << daftarproduk[i].stokmin << "\n";
    }

    cout << "--------------------------------------------------\n";
}


// FUNCTION CEK STOK
bool cekStok(int index, int kuantitas) {
    if (index < 0 || index >= jumlahproduk) {
        return false;
    }

    if (kuantitas < 1) {
        return false;
    }

    if (kuantitas > daftarproduk[index].stokpro) {
        return false;
    }

    return true;
}


// FUNCTION HITUNG DISKON
double hitungDiskon(double subtotal) {
    if (subtotal >= 300000) {
        return subtotal * 0.10;
    }
    else if (subtotal >= 100000) {
        return subtotal * 0.05;
    }
    else {
        return 0;
    }
}


// FUNCTION PROSES TRANSAKSI
void prosesTransaksi() {
    if (jumlahorder >= 20) {
        cout << "Maaf, batas jumlah pesanan telah tercapai!\n";
        return;
    }

    if (jumlahproduk <= 0) {
        cout << "Maaf, belum ada produk yang terdaftar!\n";
        return;
    }

    cout << "\n=== PESANAN PELANGGAN ===\n";

    cout << "Masukkan nama pelanggan: ";
    cin >> ws;
    getline(cin, orderan[jumlahorder].namapelanggan);

    do {
        cout << "Berapa jenis produk yang ingin dibeli (1-3)? ";
        cin >> orderan[jumlahorder].jumlah_item_berbeda;

        if (orderan[jumlahorder].jumlah_item_berbeda < 1 ||
            orderan[jumlahorder].jumlah_item_berbeda > 3) {
            cout << "Jumlah jenis produk harus antara 1 sampai 3!\n";
        }
        else if (orderan[jumlahorder].jumlah_item_berbeda > jumlahproduk) {
            cout << "Jumlah jenis produk melebihi produk yang tersedia!\n";
        }

    } while (orderan[jumlahorder].jumlah_item_berbeda < 1 ||
             orderan[jumlahorder].jumlah_item_berbeda > 3 ||
             orderan[jumlahorder].jumlah_item_berbeda > jumlahproduk);

    orderan[jumlahorder].subtotal = 0;

    // PILIH PRODUK
    for (int i = 0; i < orderan[jumlahorder].jumlah_item_berbeda; i++) {
        tampilkanproduk();

        int pilihan_produk;
        bool produk_sudah_dipilih;

        do {
            cout << "Pilih nomor produk: ";
            cin >> pilihan_produk;

            if (pilihan_produk < 1 || pilihan_produk > jumlahproduk) {
                cout << "Pilihan produk tidak valid!\n";
                produk_sudah_dipilih = true;
                continue;
            }

            produk_sudah_dipilih = false;

            for (int j = 0; j < i; j++) {
                if (orderan[jumlahorder].item[j].index == pilihan_produk - 1) {
                    produk_sudah_dipilih = true;
                    cout << "Produk sudah dipilih. Pilih produk lain!\n";
                    break;
                }
            }

        } while (pilihan_produk < 1 ||
                 pilihan_produk > jumlahproduk ||
                 produk_sudah_dipilih);

        orderan[jumlahorder].item[i].index = pilihan_produk - 1;

        cout << "Produk: "
             << daftarproduk[pilihan_produk - 1].namapro << "\n";

        cout << "Stok tersedia: "
             << daftarproduk[pilihan_produk - 1].stokpro << "\n";

        cout << "Jumlah yang ingin dibeli: ";
        cin >> orderan[jumlahorder].item[i].kuantitas;

        // CEK KETERSEDIAAN STOK
        if (!cekStok(pilihan_produk - 1,
                     orderan[jumlahorder].item[i].kuantitas)) {
            cout << "Pesanan ditolak karena jumlah tidak valid "
                 << "atau stok tidak mencukupi!\n";
            cout << "Stok tidak berubah dan transaksi tidak dicatat.\n";
            return;
        }

        // HITUNG SUBTOTAL
        orderan[jumlahorder].subtotal +=
            (double)daftarproduk[pilihan_produk - 1].hargapro *
            orderan[jumlahorder].item[i].kuantitas;
    }

    // HITUNG DISKON DAN TOTAL
    orderan[jumlahorder].diskon =
        hitungDiskon(orderan[jumlahorder].subtotal);

    orderan[jumlahorder].total =
        orderan[jumlahorder].subtotal -
        orderan[jumlahorder].diskon;

    // UPDATE STOK SETELAH SEMUA PRODUK VALID
    for (int i = 0; i < orderan[jumlahorder].jumlah_item_berbeda; i++) {
        int index_produk = orderan[jumlahorder].item[i].index;
        int qty = orderan[jumlahorder].item[i].kuantitas;

        daftarproduk[index_produk].stokpro -= qty;
    }

    jumlahorder++;

    cout << "\n=== TRANSAKSI BERHASIL ===\n";
    cout << "Nama pelanggan: "
         << orderan[jumlahorder - 1].namapelanggan << "\n";

    cout << "\nRincian pesanan:\n";

    for (int i = 0; i < orderan[jumlahorder - 1].jumlah_item_berbeda; i++) {
        int index_produk = orderan[jumlahorder - 1].item[i].index;
        int qty = orderan[jumlahorder - 1].item[i].kuantitas;

        cout << daftarproduk[index_produk].namapro
             << " x " << qty << " = Rp"
             << (double)daftarproduk[index_produk].hargapro * qty
             << "\n";
    }

    cout << "Subtotal : Rp" << orderan[jumlahorder - 1].subtotal << "\n";
    cout << "Diskon   : Rp" << orderan[jumlahorder - 1].diskon << "\n";
    cout << "Total    : Rp" << orderan[jumlahorder - 1].total << "\n";
    cout << "============================\n";
}


// FUNCTION LAPORAN
void tampilkanLaporan() {
    cout << "\n=== LAPORAN INVENTARIS DAN PENJUALAN ===\n";

    tampilkanproduk();

    cout << "\n=== PRODUK DI BAWAH STOK MINIMUM ===\n";

    bool ada_stok_minimum = false;

    for (int i = 0; i < jumlahproduk; i++) {
        if (daftarproduk[i].stokpro < daftarproduk[i].stokmin) {
            cout << "Nama produk : " << daftarproduk[i].namapro << "\n";
            cout << "Stok tersisa: " << daftarproduk[i].stokpro << "\n";
            cout << "Stok minimum: " << daftarproduk[i].stokmin << "\n";
            cout << "-----------------------------\n";

            ada_stok_minimum = true;
        }
    }

    if (!ada_stok_minimum) {
        cout << "Tidak ada produk di bawah stok minimum.\n";
    }

    cout << "\n=== RIWAYAT TRANSAKSI ===\n";

    double totalpenjualan = 0;

    if (jumlahorder == 0) {
        cout << "Belum ada transaksi yang berhasil.\n";
    }
    else {
        for (int i = 0; i < jumlahorder; i++) {
            cout << "\nTransaksi ke-" << i + 1 << "\n";
            cout << "Pelanggan : " << orderan[i].namapelanggan << "\n";
            cout << "Subtotal  : Rp" << orderan[i].subtotal << "\n";
            cout << "Diskon    : Rp" << orderan[i].diskon << "\n";
            cout << "Total     : Rp" << orderan[i].total << "\n";

            totalpenjualan += orderan[i].total;
        }
    }

    cout << "\n=== RINGKASAN PENJUALAN ===\n";
    cout << "Total pesanan berhasil: " << jumlahorder << "\n";
    cout << "Total pendapatan: Rp" << totalpenjualan << "\n";
}


// FUNCTION MENU UTAMA
int main() {
    int selesai = 0;
    int pil;
    char ulangi;

    do {
        cout << "\n=== SISTEM GUDANG DAN PENJUALAN ===\n";
        cout << "1. Tambah Produk Baru\n";
        cout << "2. Lihat Daftar Produk\n";
        cout << "3. Proses Transaksi / Pesanan\n";
        cout << "4. Lihat Laporan Inventaris & Penjualan\n";
        cout << "5. Keluar\n";

        cout << "Silakan pilih menu (1-5): ";
        cin >> pil;

        if (pil == 1) {
            tmbahproduk();
        }
        else if (pil == 2) {
            tampilkanproduk();
        }
        else if (pil == 3) {
            prosesTransaksi();
        }
        else if (pil == 4) {
            tampilkanLaporan();
        }
        else if (pil == 5) {
            cout << "Terima kasih telah menggunakan layanan kami!\n";
            selesai = 1;
        }
        else {
            cout << "Pilihan Anda tidak valid!\n";
        }

        if (selesai == 0) {
            cout << "\nKembali ke menu utama? (y/n): ";
            cin >> ulangi;

            if (ulangi == 'n' || ulangi == 'N') {
                selesai = 1;
                cout << "Terima kasih!\n";
            }
        }

    } while (selesai == 0);

    return 0;
}
