#include <iostream>
#include <string>
using namespace std;

// Struktur untuk data Pelanggan
struct Customer {
    string nama;        // Nama pelanggan
    string pesanan;    // Nama menu yang dipesan
    int nomorAntrian;  // Nomor antrian pelanggan
    int jumlah;        // Jumlah pesanan
    Customer* next;    // Pointer ke pelanggan berikutnya
};

// Struktur untuk Antrian
struct Queue {
    Customer* depan;    // Pointer ke pelanggan di depan antrian
    Customer* belakang; // Pointer ke pelanggan di belakang antrian
    int nomorAntrianSaatIni; // Nomor antrian saat ini
};

// Struktur untuk Menu Kantin
struct menuMerchant {
    string namaMenu;    // Nama menu
    int jumlahStok;     // Jumlah stok menu
    menuMerchant *next; // Pointer ke menu berikutnya
};

// Struktur untuk Riwayat Pesanan
struct OrderHistory {
    string nama;
    string pesanan;
    int nomorAntrian;
    int jumlah;
};

// Deklarasi array untuk riwayat pesanan (maksimal 100 pesanan untuk contoh)
OrderHistory history[100];
int historyCount = 0; // Menghitung jumlah entri riwayat

menuMerchant *head, *tail, *cur; // Pointer global untuk linked list menu

// Fungsi untuk menginisialisasi antrian
void initQueue(Queue &q) {
    q.depan = nullptr;
    q.belakang = nullptr;
    q.nomorAntrianSaatIni = 0;
}

// Fungsi untuk memeriksa apakah antrian kosong
bool isEmpty(Queue q) {
    return q.depan == nullptr;
}

// Fungsi untuk menambahkan pelanggan ke antrian
void enqueue(Queue &q, string nama, string pesanan, int jumlah) {
    Customer* pelangganBaru = new Customer;
    pelangganBaru->nama = nama;
    pelangganBaru->pesanan = pesanan;
    pelangganBaru->jumlah = jumlah;
    pelangganBaru->nomorAntrian = ++q.nomorAntrianSaatIni;
    pelangganBaru->next = nullptr;

    if (isEmpty(q)) {
        q.depan = pelangganBaru;
        q.belakang = pelangganBaru;
    } else {
        q.belakang->next = pelangganBaru;
        q.belakang = pelangganBaru;
    }
    
    cout << "Pelanggan " << nama << " ditambahkan ke antrian dengan nomor " 
         << pelangganBaru->nomorAntrian << " (Pesanan: " << pesanan << ", Jumlah: " << jumlah << ")" << endl;
}

// Fungsi untuk mengeluarkan pelanggan dari antrian dan mencatat riwayat
void dequeue(Queue &q) {
    if (isEmpty(q)) {
        cout << "Antrian kosong!" << endl;
        return;
    }

    Customer* temp = q.depan;
    cout << "Pelanggan " << temp->nama << " dengan nomor antrian " 
         << temp->nomorAntrian << " telah dikonfirmasi." << endl;

    // Simpan ke riwayat pesanan
    if (historyCount < 100) {
        history[historyCount].nama = temp->nama;
        history[historyCount].pesanan = temp->pesanan;
        history[historyCount].nomorAntrian = temp->nomorAntrian;
        history[historyCount].jumlah = temp->jumlah;
        historyCount++;
    } else {
        cout << "Riwayat pesanan penuh!" << endl;
    }

    q.depan = q.depan->next;
    delete temp;

    if (q.depan == nullptr) {
        q.belakang = nullptr;
    }
}

// Fungsi untuk menampilkan daftar pelanggan yang sedang mengantri
void displayQueue(Queue q) {
    if (isEmpty(q)) {
        cout << "Antrian kosong!" << endl;
        return;
    }

    cout << "\nDaftar Antrian Pelanggan:" << endl;
    cout << "------------------------" << endl;
    Customer* current = q.depan;
    while (current != nullptr) {
        cout << "Nomor Antrian: " << current->nomorAntrian << endl;
        cout << "Nama: " << current->nama << endl;
        cout << "Pesanan: " << current->pesanan << endl;
        cout << "Jumlah: " << current->jumlah << endl;
        cout << "------------------------" << endl;
        current = current->next;
    }
}

// Fungsi untuk membuat linked list menu pertama kali
void createMenu(string namaMenu, int jumlahStok) {
    head = new menuMerchant;
    head->namaMenu = namaMenu;
    head->jumlahStok = jumlahStok;
    head->next = nullptr;
    tail = head;
}

// Fungsi untuk menambah menu baru ke linked list
void addMenu(string namaMenu, int jumlahStok) {
    menuMerchant *newMenu = new menuMerchant;
    newMenu->namaMenu = namaMenu;
    newMenu->jumlahStok = jumlahStok;
    newMenu->next = nullptr;

    tail->next = newMenu;
    tail = newMenu;
}

// Fungsi untuk memeriksa ketersediaan stok menu
bool cekStok(string namaMenu, int jumlah) {
    cur = head;
    while (cur != nullptr) {
        if (cur->namaMenu == namaMenu) {
            return cur->jumlahStok >= jumlah;
        }
        cur = cur->next;
    }
    return false;
}

// Fungsi untuk mengurangi stok menu
void kurangiStok(string namaMenu, int jumlah) {
    if (cekStok(namaMenu, jumlah)) {
        cur = head;
        while (cur != nullptr) {
            if (cur->namaMenu == namaMenu) {
                cur->jumlahStok -= jumlah;
                cout << "Stok " << namaMenu << " berhasil dikurangi sebanyak " << jumlah << endl;
                return;
            }
            cur = cur->next;
        }
    } else {
        cout << "Stok " << namaMenu << " tidak cukup atau menu tidak ditemukan" << endl;
    }
}

// Fungsi untuk menampilkan semua menu
void displayMenu() {
    cur = head;
    if (cur == nullptr) {
        cout << "Daftar menu kosong!" << endl;
        return;
    }
    cout << "\nDaftar Menu:" << endl;
    cout << "------------" << endl;
    int index = 1;
    while (cur != nullptr) {
        cout << index << ". " << cur->namaMenu << " (Stok: " << cur->jumlahStok << ")" << endl;
        cur = cur->next;
        index++;
    }
}

// Fungsi untuk menampilkan riwayat pesanan
void displayHistory() {
    if (historyCount == 0) {
        cout << "Riwayat pesanan kosong!" << endl;
        return;
    }

    cout << "\nRiwayat Pesanan:" << endl;
    cout << "----------------" << endl;
    for (int i = 0; i < historyCount; i++) {
        cout << "Pesanan ke-" << (i + 1) << ":" << endl;
        cout << "Nama: " << history[i].nama << endl;
        cout << "Pesanan: " << history[i].pesanan << endl;
        cout << "Nomor Antrian: " << history[i].nomorAntrian << endl;
        cout << "Jumlah: " << history[i].jumlah << endl;
        cout << "----------------" << endl;
    }
}

// Fungsi untuk input data pelanggan
void inputCustomer(Queue &q) {
    string nama;
    int pilihanMenu, jumlah;
    
    cout << "Masukkan nama pelanggan: ";
    cin.ignore(1, '\n');
    getline(cin, nama);
    
    displayMenu();
    cout << "Pilih nomor menu: ";
    cin >> pilihanMenu;
    cout << "Masukkan jumlah pesanan: ";
    cin >> jumlah;

    if (jumlah <= 0) {
        cout << "Jumlah pesanan harus lebih dari 0!" << endl;
        return;
    }

    cur = head;
    int index = 1;
    string menuTerpilih;
    bool menuDitemukan = false;

    while (cur != nullptr) {
        if (index == pilihanMenu) {
            menuTerpilih = cur->namaMenu;
            menuDitemukan = true;
            break;
        }
        cur = cur->next;
        index++;
    }

    if (!menuDitemukan) {
        cout << "Pilihan menu tidak valid!" << endl;
        return;
    }

    if (cekStok(menuTerpilih, jumlah)) {
        enqueue(q, nama, menuTerpilih, jumlah);
        kurangiStok(menuTerpilih, jumlah);
    } else {
        cout << "Maaf, stok " << menuTerpilih << " tidak cukup untuk " << jumlah << " pesanan!" << endl;
    }
}

// Fungsi untuk menampilkan menu utama
void showMenu() {
    cout << "\nSistem Antrian Kantin" << endl;
    cout << "1. Tambah Pesanan" << endl;
    cout << "2. Confirm Antrian" << endl;
    cout << "3. Tampilkan Antrian" << endl;
    cout << "4. Tampilkan Daftar Menu" << endl;
    cout << "5. Riwayat Pesanan" << endl;
    cout << "6. Keluar" << endl;
    cout << "Pilih opsi (1-6): ";
}

// Fungsi utama
int main() {
    Queue q;
    initQueue(q);

    // Inisialisasi daftar menu
    createMenu("Nasi Goreng", 10);
    addMenu("Rice Bowl", 0);
    addMenu("Air Putih", 8);
    addMenu("Soto", 9);

    int pilihan;
    do {
        showMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                inputCustomer(q);
                break;
            case 2:
                dequeue(q);
                break;
            case 3:
                displayQueue(q);
                break;
            case 4: {
                displayMenu();
                cout << "\nSub-Menu Daftar Menu:" << endl;
                cout << "1. Tambah Menu" << endl;
                cout << "2. Hapus Menu" << endl;
                cout << "3. Kembali ke Menu Utama" << endl;
                cout << "Pilih opsi (1-3): ";
                int subPilihan;
                cin >> subPilihan;
                switch (subPilihan) {
                    case 1:
                        cout << "Fitur Tambah Menu belum diimplementasikan." << endl;
                        // Gunakan fungsi addMenu(namaMenu, jumlahStok) untuk implementasi
                        break;
                    case 2:
                        cout << "Fitur Hapus Menu belum diimplementasikan." << endl;
                        // Perlu fungsi baru untuk menghapus menu dari linked list
                        break;
                    case 3:
                        break;
                    default:
                        cout << "Pilihan tidak valid!" << endl;
                }
                break;
            }
            case 5:
                displayHistory();
                break;
            case 6:
                cout << "Terima Kasih" << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 6);

    // Membersihkan memori antrian
    while (!isEmpty(q)) {
        dequeue(q);
    }

    // Membersihkan memori linked list menu
    cur = head;
    while (cur != nullptr) {
        menuMerchant *temp = cur;
        cur = cur->next;
        delete temp;
    }

    return 0;
}