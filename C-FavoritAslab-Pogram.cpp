#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

const int MAX = 100;

struct Produk {
    string nama;
    int harga;
    int stok;
};

struct User {
    string username;
    string password;
};

Produk daftarProduk[MAX] = {
    {"Parfum A", 100000, 10}, {"Parfum B", 150000, 5}, {"Parfum C", 120000, 8},
    {"Parfum D", 175000, 7}, {"Parfum E", 200000, 3}, {"Parfum F", 110000, 6},
    {"Parfum G", 130000, 9}, {"Parfum H", 170000, 4}, {"Parfum I", 190000, 2},
    {"Parfum J", 160000, 12}, {"Parfum K", 125000, 11}, {"Parfum L", 140000, 10},
    {"Parfum M", 180000, 7}, {"Parfum N", 155000, 5}, {"Parfum O", 165000, 6}
};
int jumlahProduk = 15;

User dataPengguna[MAX];
int jumlahPengguna = 0;

string riwayatPembelian[MAX];
int jumlahRiwayat = 0;

void tampilkanProduk() {
    cout << "\nDaftar Produk:\n";
    cout << left << setw(5) << "No" << setw(20) << "Nama" << setw(15) << "Harga" << setw(10) << "Stok\n";
    for (int i = 0; i < jumlahProduk; i++) {
        cout << setw(5) << i + 1 << setw(20) << daftarProduk[i].nama
             << setw(15) << daftarProduk[i].harga << setw(10) << daftarProduk[i].stok << endl;
    }
}

void selectionSortHarga(bool ascending = true) {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < jumlahProduk; j++) {
            if (ascending ? daftarProduk[j].harga < daftarProduk[idx].harga :
                            daftarProduk[j].harga > daftarProduk[idx].harga) {
                idx = j;
            }
        }
        swap(daftarProduk[i], daftarProduk[idx]);
    }
}

void selectionSortNama(bool ascending = true) {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < jumlahProduk; j++) {
            if (ascending ? (daftarProduk[j].nama < daftarProduk[idx].nama) :
                            (daftarProduk[j].nama > daftarProduk[idx].nama)) {
                idx = j;
            }
        }
        swap(daftarProduk[i], daftarProduk[idx]);
    }
}

int binarySearchNama(string key) {
    int low = 0, high = jumlahProduk - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (daftarProduk[mid].nama == key) return mid;
        else if (daftarProduk[mid].nama < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void checkout() {
    string nama;
    int jumlah;
    tampilkanProduk();
    cout << "Masukkan nama produk yang ingin dibeli: ";
    cin.ignore();
    getline(cin, nama);
    int idx = -1;
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].nama == nama) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        cout << "Produk tidak ditemukan!\n";
        return;
    }
    cout << "Masukkan jumlah pembelian: ";
    cin >> jumlah;
    if (jumlah > daftarProduk[idx].stok) {
        cout << "Stok tidak mencukupi!\n";
        return;
    }
    daftarProduk[idx].stok -= jumlah;
    riwayatPembelian[jumlahRiwayat++] = nama + " x" + to_string(jumlah);
    cout << "Berhasil checkout!\n";
}

void tampilkanRiwayat() {
    cout << "\nRiwayat Pembelian:\n";
    for (int i = 0; i < jumlahRiwayat; i++) {
        cout << i + 1 << ". " << riwayatPembelian[i] << endl;
    }
}

void menuPengguna() {
    int pilihan;
    do {
        cout << "\n--- Menu Pengguna ---\n";
        cout << "1. Lihat Produk\n2. Selection Sort\n3. Binary Search (Nama)\n4. Checkout\n5. Riwayat Pembelian\n6. Keluar\n";
        cout << "Pilih: "; cin >> pilihan;
        switch (pilihan) {
            case 1: tampilkanProduk(); break;
            case 2: {
                int opsiSort, asc;
                cout << "Sorting berdasarkan:\n1. Harga\n2. Nama\nPilih: ";
                cin >> opsiSort;
                cout << "1. Ascending\n2. Descending\nPilih: ";
                cin >> asc;
                if (opsiSort == 1) selectionSortHarga(asc == 1);
                else if (opsiSort == 2) selectionSortNama(asc == 1);
                else { cout << "Pilihan tidak valid!\n"; break; }
                tampilkanProduk();
                break;
            }
            case 3: {
                string cari;
                cin.ignore();
                cout << "Masukkan nama parfum yang dicari: ";
                getline(cin, cari);
                selectionSortNama();
                int hasil = binarySearchNama(cari);
                if (hasil != -1)
                    cout << "Ditemukan: " << daftarProduk[hasil].nama << " - Rp" << daftarProduk[hasil].harga << endl;
                else
                    cout << "Produk tidak ditemukan.\n";
                break;
            }
            case 4: checkout(); break;
            case 5: tampilkanRiwayat(); break;
            case 6: cout << "Keluar dari pengguna.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 6);
}

void tambahProduk() {
    cout << "Nama produk: ";
    cin.ignore();
    getline(cin, daftarProduk[jumlahProduk].nama);
    cout << "Harga: "; cin >> daftarProduk[jumlahProduk].harga;
    cout << "Stok: "; cin >> daftarProduk[jumlahProduk].stok;
    jumlahProduk++;
    cout << "Produk ditambahkan!\n";
}

void updateProduk() {
    tampilkanProduk();
    int idx;
    cout << "Pilih nomor produk: ";
    cin >> idx;
    if (idx < 1 || idx > jumlahProduk) {
        cout << "Nomor tidak valid.\n";
        return;
    }
    idx--;
    cout << "Harga baru: "; cin >> daftarProduk[idx].harga;
    cout << "Stok baru: "; cin >> daftarProduk[idx].stok;
    cout << "Produk diperbarui.\n";
}

void hapusProduk() {
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].stok == 0) {
            for (int j = i; j < jumlahProduk - 1; j++) {
                daftarProduk[j] = daftarProduk[j + 1];
            }
            jumlahProduk--;
            i--;
        }
    }
    cout << "Produk dengan stok 0 telah dihapus.\n";
}

void selectionSortStok(bool ascending = true) {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < jumlahProduk; j++) {
            if (ascending ? daftarProduk[j].stok < daftarProduk[idx].stok :
                            daftarProduk[j].stok > daftarProduk[idx].stok) {
                idx = j;
            }
        }
        swap(daftarProduk[i], daftarProduk[idx]);
    }
}

void menuAdmin() {
    int pilihan;
    do {
        cout << "\n--- Menu Admin ---\n";
        cout << "1. Tambah Produk\n2. Lihat Produk\n3. Update Produk\n4. Hapus Produk Kosong\n5. Selection Sort\n6. Binary Search Nama\n7. Keluar\n";
        cout << "Pilih: "; cin >> pilihan;
        switch (pilihan) {
            case 1: tambahProduk(); break;
            case 2: tampilkanProduk(); break;
            case 3: updateProduk(); break;
            case 4: hapusProduk(); break;
            case 5: {
                int opsiSort, asc;
                cout << "Sorting berdasarkan:\n1. Harga\n2. Nama\nPilih: ";
                cin >> opsiSort;
                cout << "1. Ascending\n2. Descending\nPilih: ";
                cin >> asc;
                if (opsiSort == 1) selectionSortHarga(asc == 1);
                else if (opsiSort == 2) selectionSortNama(asc == 1);
                else { cout << "Pilihan tidak valid!\n"; break; }
                tampilkanProduk();
                break;
            }
            case 6: {
                string cari;
                cin.ignore();
                cout << "Masukkan nama parfum yang dicari: ";
                getline(cin, cari);
                selectionSortNama();
                int hasil = binarySearchNama(cari);
                if (hasil != -1)
                    cout << "Ditemukan: " << daftarProduk[hasil].nama << " - Rp" << daftarProduk[hasil].harga << endl;
                else
                    cout << "Produk tidak ditemukan.\n";
                break;
            }
            case 7: cout << "Keluar dari admin.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 7);
}

void registerPengguna() {
    cout << "Username: ";
    cin >> dataPengguna[jumlahPengguna].username;
    cout << "Password: ";
    cin >> dataPengguna[jumlahPengguna].password;
    jumlahPengguna++;
    cout << "Registrasi berhasil!\n";
}

void login() {
    string user, pass;
    int gagal = 0;
    while (gagal < 3) {
        cout << "Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;
        if (user == "admin" && pass == "admin") {
            menuAdmin();
            return;
        }
        for (int i = 0; i < jumlahPengguna; i++) {
            if (user == dataPengguna[i].username && pass == dataPengguna[i].password) {
                menuPengguna();
                return;
            }
        }
        cout << "Login gagal. Coba lagi.\n";
        gagal++;
    }
    cout << "Gagal login 3 kali. Keluar dari program.\n";
    exit(0);
}

int main() {
    int pilihan;
    do {
        cout << "\n=== Program Parfum ===\n";
        cout << "1. Register Pengguna\n2. Login\n3. Keluar\nPilih: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1: registerPengguna(); break;
            case 2: login(); break;
            case 3: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 3);
    return 0;
}

