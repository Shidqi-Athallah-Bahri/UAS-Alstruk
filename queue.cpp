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

menuMerchant *head, *tail, *cur; // Pointer global untuk linked list menu

// Fungsi untuk menginisialisasi antrian
// Parameter: q (referensi ke struktur Queue)
// Output: Mengatur depan, belakang, dan nomorAntrianSaatIni ke nilai awal
void initQueue(Queue &q) {
    q.depan = nullptr;
    q.belakang = nullptr;
    q.nomorAntrianSaatIni = 0; // Nomor antrian dimulai dari 0
}

// Fungsi untuk memeriksa apakah antrian kosong
// Parameter: q (struktur Queue)
// Return: true jika antrian kosong, false jika tidak
bool isEmpty(Queue q) {
    return q.depan == nullptr;
}

// Fungsi untuk menambahkan pelanggan ke antrian
// Parameter: q (referensi ke Queue), nama (nama pelanggan), pesanan (nama menu), jumlah (jumlah pesanan)
// Output: Menambahkan pelanggan ke antrian dengan nomor antrian otomatis
void enqueue(Queue &q, string nama, string pesanan, int jumlah) {
    Customer* pelangganBaru = new Customer;
    pelangganBaru->nama = nama;
    pelangganBaru->pesanan = pesanan;
    pelangganBaru->jumlah = jumlah;
    pelangganBaru->nomorAntrian = ++q.nomorAntrianSaatIni; // Increment nomor antrian
    pelangganBaru->next = nullptr;

    // Jika antrian kosong, pelanggan menjadi depan dan belakang
    if (isEmpty(q)) {
        q.depan = pelangganBaru;
        q.belakang = pelangganBaru;
    } else {
        // Tambahkan pelanggan di belakang antrian
        q.belakang->next = pelangganBaru;
        q.belakang = pelangganBaru;
    }
    
    cout << "Pelanggan " << nama << " ditambahkan ke antrian dengan nomor " 
         << pelangganBaru->nomorAntrian << " (Pesanan: " << pesanan << ", Jumlah: " << jumlah << ")" << endl;
}

// Fungsi untuk mengeluarkan pelanggan dari antrian
// Parameter: q (referensi ke Queue)
// Output: Menghapus pelanggan dari depan antrian dan menampilkan informasi
void dequeue(Queue &q) {
    if (isEmpty(q)) {
        cout << "Antrian kosong!" << endl;
        return;
    }

    Customer* temp = q.depan;
    cout << "Pelanggan " << temp->nama << " dengan nomor antrian " 
         << temp->nomorAntrian << " telah dilayani." << endl;

    q.depan = q.depan->next;
    delete temp;

    // Jika antrian menjadi kosong, atur belakang ke nullptr
    if (q.depan == nullptr) {
        q.belakang = nullptr;
    }
}

// Fungsi untuk menampilkan daftar pelanggan yang sedang mengantri
// Parameter: q (struktur Queue)
// Output: Menampilkan nomor antrian, nama, pesanan, dan jumlah untuk setiap pelanggan
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
// Parameter: namaMenu (nama menu), jumlahStok (stok awal)
// Output: Membuat node pertama dari linked list menu
void createMenu(string namaMenu, int jumlahStok) {
    head = new menuMerchant;
    head->namaMenu = namaMenu;
    head->jumlahStok = jumlahStok;
    head->next = nullptr;
    tail = head;
}

// Fungsi untuk menambah menu baru ke linked list
// Parameter: namaMenu (nama menu), jumlahStok (stok awal)
// Output: Menambahkan node menu baru di akhir linked list
void addMenu(string namaMenu, int jumlahStok) {
    menuMerchant *newMenu = new menuMerchant;
    newMenu->namaMenu = namaMenu;
    newMenu->jumlahStok = jumlahStok;
    newMenu->next = nullptr;

    tail->next = newMenu;
    tail = newMenu;
}

// Fungsi untuk memeriksa ketersediaan stok menu
// Parameter: namaMenu (nama menu), jumlah (jumlah yang diperlukan)
// Return: true jika stok cukup, false jika tidak
bool cekStok(string namaMenu, int jumlah) {
    cur = head;
    while (cur != nullptr) {
        if (cur->namaMenu == namaMenu) {
            return cur->jumlahStok >= jumlah; // Periksa apakah stok cukup
        }
        cur = cur->next;
    }
    return false; // Menu tidak ditemukan
}

// Fungsi untuk mengurangi stok menu
// Parameter: namaMenu (nama menu), jumlah (jumlah yang dipesan)
// Output: Mengurangi stok jika tersedia, menampilkan pesan error jika tidak
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
// Parameter: Tidak ada
// Output: Menampilkan daftar menu dengan nomor dan stok
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

// Fungsi untuk input data pelanggan
// Parameter: q (referensi ke Queue)
// Output: Meminta nama, pilihan menu, dan jumlah pesanan, lalu menambah ke antrian jika valid
void inputCustomer(Queue &q) {
    string nama;
    int pilihanMenu, jumlah;
    
    cout << "Masukkan nama pelanggan: ";
    cin.ignore(1, '\n'); // Bersihkan buffer untuk getline
    getline(cin, nama);
    
    displayMenu();
    cout << "Pilih nomor menu: ";
    cin >> pilihanMenu;
    cout << "Masukkan jumlah pesanan: ";
    cin >> jumlah;

    // Validasi jumlah pesanan
    if (jumlah <= 0) {
        cout << "Jumlah pesanan harus lebih dari 0!" << endl;
        return;
    }

    // Mendapatkan nama menu berdasarkan pilihan
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

    // Periksa stok dan proses pesanan
    if (cekStok(menuTerpilih, jumlah)) {
        enqueue(q, nama, menuTerpilih, jumlah);
        kurangiStok(menuTerpilih, jumlah);
    } else {
        cout << "Maaf, stok " << menuTerpilih << " tidak cukup untuk " << jumlah << " pesanan!" << endl;
    }
}

// Fungsi untuk menampilkan menu utama
// Parameter: Tidak ada
// Output: Menampilkan opsi sistem antrian
void showMenu() {
    cout << "\nSistem Antrian Kantin" << endl;
    cout << "1. Tambah Pelanggan ke Antrian" << endl;
    cout << "2. Layani Pelanggan" << endl;
    cout << "3. Tampilkan Antrian" << endl;
    cout << "4. Tampilkan Daftar Menu" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih opsi (1-5): ";
}

// Fungsi utama
// Output: Menjalankan sistem antrian dengan menu interaktif
int main() {
    Queue q;
    initQueue(q);

    // Inisialisasi daftar menu
    createMenu("Nasi Goreng", 10);
    addMenu("Rice Bowl", 0);
    addMenu("Air Putih", 8);

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
            case 4:
                displayMenu();
                break;
            case 5:
                cout << "Terima Kasih" << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);

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