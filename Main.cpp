#include <iostream>
#include <string>
using namespace std;

// Struktur untuk data Pelanggan
struct Customer {
    string nama;
    string pesanan;
    int nomorAntrian;
    int jumlah;
    int totalHarga;
    int uangDibayar;
    int kembalian;
    Customer* next;
};

// Struktur untuk Antrian
struct Queue {
    Customer* depan;
    Customer* belakang;
    int nomorAntrianSaatIni;
};

// Struktur untuk Menu Kantin
struct menuMerchant {
    string namaMenu;
    int jumlahStok;
    int hargaMenu;
    menuMerchant* next;
};

// Dua linked list untuk dua merchant
menuMerchant *head1 = nullptr, *tail1 = nullptr;
menuMerchant *head2 = nullptr, *tail2 = nullptr;

// Struktur untuk Riwayat Pesanan
struct OrderHistory {
    string nama;
    string pesanan;
    int nomorAntrian;
    int jumlah;
    int totalHarga;
    int uangDibayar;
    int kembalian;
};

// Deklarasi array untuk riwayat pesanan
OrderHistory history[100];
int historyCount = 0;

// Inisialisasi antrian untuk setiap merchant
Queue queue1, queue2;

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

// Fungsi untuk mencari harga menu
int getMenuPrice(menuMerchant* head, string namaMenu) {
    menuMerchant* current = head;
    while (current != nullptr) {
        if (current->namaMenu == namaMenu) {
            return current->hargaMenu;
        }
        current = current->next;
    }
    return 0;
}

// Fungsi untuk mencari menu berdasarkan nomor
menuMerchant* getMenuByNumber(menuMerchant* head, int nomor) {
    int index = 1;
    menuMerchant* current = head;
    while (current != nullptr) {
        if (index == nomor) {
            return current;
        }
        current = current->next;
        index++;
    }
    return nullptr;
}

// Fungsi untuk menambahkan pelanggan ke antrian
void enqueue(Queue &q, string nama, string pesanan, int jumlah, int totalHarga, int uangDibayar, int kembalian) {
    Customer* pelangganBaru = new Customer;
    pelangganBaru->nama = nama;
    pelangganBaru->pesanan = pesanan;
    pelangganBaru->jumlah = jumlah;
    pelangganBaru->totalHarga = totalHarga;
    pelangganBaru->uangDibayar = uangDibayar;
    pelangganBaru->kembalian = kembalian;
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
         << pelangganBaru->nomorAntrian << " (Pesanan: " << pesanan << ", Jumlah: " << jumlah
         << ", Total: Rp" << totalHarga << ", Uang Dibayar: Rp" << uangDibayar
         << ", Kembalian: Rp" << kembalian << ")" << endl;
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
        history[historyCount].totalHarga = temp->totalHarga;
        history[historyCount].uangDibayar = temp->uangDibayar;
        history[historyCount].kembalian = temp->kembalian;
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
        cout << "Total Harga: Rp" << current->totalHarga << endl;
        cout << "Uang Dibayar: Rp" << current->uangDibayar << endl;
        cout << "Kembalian: Rp" << current->kembalian << endl;
        cout << "------------------------" << endl;
        current = current->next;
    }
}

// Fungsi untuk menambah menu baru ke linked list
void addMenu(menuMerchant*& head, menuMerchant*& tail, string namaMenu, int jumlahStok, int hargaMenu) {
    menuMerchant* newMenu = new menuMerchant{namaMenu, jumlahStok, hargaMenu, nullptr};

    if (head == nullptr) {
        head = tail = newMenu;
    } else {
        tail->next = newMenu;
        tail = newMenu;
    }
}

// Fungsi untuk menghapus menu
void deleteMenu(menuMerchant*& head, string namaMenu) {
    menuMerchant *cur = head, *prev = nullptr;
    while (cur != nullptr) {
        if (cur->namaMenu == namaMenu) {
            if (prev == nullptr) {
                head = cur->next;
            } else {
                prev->next = cur->next;
            }
            delete cur;
            cout << "Menu " << namaMenu << " telah dihapus." << endl;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    cout << "Menu " << namaMenu << " tidak ditemukan." << endl;
}

// Fungsi untuk memeriksa ketersediaan menu
bool cekMenu(menuMerchant* head, string namaMenu) {
    while (head != nullptr) {
        if (head->namaMenu == namaMenu) return true;
        head = head->next;
    }
    return false;
}

// Fungsi untuk memeriksa ketersediaan stok menu
bool cekStok(menuMerchant* head, string namaMenu, int jumlah) {
    while (head != nullptr) {
        if (head->namaMenu == namaMenu) return head->jumlahStok >= jumlah;
        head = head->next;
    }
    return false;
}

// Fungsi untuk mengurangi stok
void kurangiStok(menuMerchant* head, string namaMenu, int jumlah) {
    if (cekStok(head, namaMenu, jumlah)) {
        while (head != nullptr) {
            if (head->namaMenu == namaMenu) {
                head->jumlahStok -= jumlah;
                cout << "Stok " << namaMenu << " dikurangi sebanyak " << jumlah << endl;
                return;
            }
            head = head->next;
        }
    } else {
        cout << "Stok tidak cukup atau menu tidak ditemukan." << endl;
    }
}

// Fungsi untuk menambah stok menu
void tambahStokMenu(menuMerchant* head, string namaMenu) {
    menuMerchant* current = head;
    while (current != nullptr) {
        if (current->namaMenu == namaMenu) {
            int tambah;
            cout << "Masukkan jumlah stok yang ingin ditambah: ";
            cin >> tambah;
            if (tambah > 0) {
                current->jumlahStok += tambah;
                cout << "Stok berhasil ditambah. Stok sekarang: " << current->jumlahStok << endl;
            } else {
                cout << "Jumlah harus lebih dari 0!" << endl;
            }
            return;
        }
        current = current->next;
    }
    cout << "Menu tidak ditemukan." << endl;
}

// Fungsi untuk mengubah harga menu
void ubahHargaMenu(menuMerchant* head, string namaMenu) {
    menuMerchant* current = head;
    while (current != nullptr) {
        if (current->namaMenu == namaMenu) {
            int hargaBaru;
            cout << "Masukkan harga baru: ";
            cin >> hargaBaru;
            if (hargaBaru > 0) {
                current->hargaMenu = hargaBaru;
                cout << "Harga berhasil diubah. Harga sekarang: Rp" << current->hargaMenu << endl;
            } else {
                cout << "Harga harus lebih dari 0!" << endl;
            }
            return;
        }
        current = current->next;
    }
    cout << "Menu tidak ditemukan." << endl;
}

// Fungsi untuk mengosongkan stok
void kosongkanStok(menuMerchant* head, const string& namaMenu) {
    menuMerchant* current = head;
    while (current != nullptr) {
        if (current->namaMenu == namaMenu) {
            current->jumlahStok = 0;
            cout << "Stok menu \"" << namaMenu << "\" telah dikosongkan." << endl;
            return;
        }
        current = current->next;
    }
    cout << "Menu tidak ditemukan." << endl;
}

// Fungsi untuk mengubah stok
void ubahStok(menuMerchant* head, string namaMenu) {
    int pilih;
    cout << "Mengubah Stok" << endl;
    cout << "1. Tambah Stok" << endl;
    cout << "2. Kurangi Stok" << endl;
    cout << "3. Kosongkan Stok" << endl;
    cout << "Pilih opsi: ";
    cin >> pilih;

    int jumlah;
    switch (pilih) {
        case 1:
            tambahStokMenu(head, namaMenu);
            break;
        case 2:
            cout << "Masukkan jumlah yang ingin dikurangi: ";
            cin >> jumlah;
            kurangiStok(head, namaMenu, jumlah);
            break;
        case 3:
            kosongkanStok(head, namaMenu);
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
    }
}

// Fungsi untuk mengubah menu berdasarkan nomor
void ubahMenu(menuMerchant*& head, menuMerchant*& tail, int nomorMenu) {
    menuMerchant* selectedMenu = getMenuByNumber(head, nomorMenu);
    if (selectedMenu == nullptr) {
        cout << "Nomor menu tidak valid!" << endl;
        return;
    }
    string namaMenu = selectedMenu->namaMenu;

    int pilihan;
    do {
        cout << "\n=== Menu Edit Menu Merchant ===" << endl;
        cout << "Menu yang dipilih: " << namaMenu << endl;
        cout << "1. Hapus Menu" << endl;
        cout << "2. Ubah Stok Menu" << endl;
        cout << "3. Ubah Harga Menu" << endl;
        cout << "4. Kembali" << endl;
        cout << "Pilih opsi (1-4): ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                deleteMenu(head, namaMenu);
                return; // Keluar setelah hapus
            case 2:
                ubahStok(head, namaMenu);
                break;
            case 3:
                ubahHargaMenu(head, namaMenu);
                break;
            case 4:
                cout << "Kembali ke menu sebelumnya." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 4);
}

// Fungsi untuk menambah menu baru
void tambahMenu(menuMerchant*& head, menuMerchant*& tail) {
    string namaMenu;
    int jumlahStok, hargaMenu;
    cout << "Masukkan nama menu: ";
    cin.ignore();
    getline(cin, namaMenu);
    cout << "Masukkan jumlah stok: ";
    cin >> jumlahStok;
    cout << "Masukkan Harga: ";
    cin >> hargaMenu;

    addMenu(head, tail, namaMenu, jumlahStok, hargaMenu);
    cout << "Menu " << namaMenu << " ditambahkan." << endl;
}

// Fungsi untuk menampilkan semua menu
void displayMenu(menuMerchant* head) {
    if (head == nullptr) {
        cout << "Daftar menu kosong!" << endl;
        return;
    }
    int i = 1;
    cout << "\nDaftar Menu:" << endl;
    while (head != nullptr) {
        cout << i++ << ". " << head->namaMenu << " (Stok: " << head->jumlahStok
             << ") Harga: Rp" << head->hargaMenu << endl;
        head = head->next;
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
        cout << "Total Harga: Rp" << history[i].totalHarga << endl;
        cout << "Uang Dibayar: Rp" << history[i].uangDibayar << endl;
        cout << "Kembalian: Rp" << history[i].kembalian << endl;
        cout << "----------------" << endl;
    }
}

// Fungsi untuk input data pelanggan dan proses pembayaran
bool inputCustomer(Queue &q, menuMerchant* head) {
    string nama;
    int pilihanMenu, jumlah;

    cout << "Masukkan nama pelanggan: ";
    cin.ignore();
    getline(cin, nama);

    displayMenu(head);
    cout << "Pilih nomor menu: ";
    cin >> pilihanMenu;
    cout << "Masukkan jumlah pesanan: ";
    cin >> jumlah;

    if (jumlah <= 0) {
        cout << "Jumlah pesanan harus lebih dari 0!" << endl;
        return false;
    }

    int index = 1;
    string menuTerpilih;
    int hargaMenu = 0;
    bool menuDitemukan = false;
    menuMerchant* current = head;

    while (current != nullptr) {
        if (index == pilihanMenu) {
            menuTerpilih = current->namaMenu;
            hargaMenu = current->hargaMenu;
            menuDitemukan = true;
            break;
        }
        current = current->next;
        index++;
    }

    if (!menuDitemukan) {
        cout << "Pilihan menu tidak valid!" << endl;
        return false;
    }

    if (cekStok(head, menuTerpilih, jumlah)) {
        int totalHarga = jumlah * hargaMenu;
        cout << "Total pembayaran: Rp" << totalHarga << endl;
        int uangDibayar;
        cout << "Masukkan jumlah uang yang dibayar: Rp";
        cin >> uangDibayar;

        if (uangDibayar >= totalHarga) {
            int kembalian = uangDibayar - totalHarga;
            cout << "Pembayaran berhasil! Kembalian: Rp" << kembalian << endl;
            enqueue(q, nama, menuTerpilih, jumlah, totalHarga, uangDibayar, kembalian);
            kurangiStok(head, menuTerpilih, jumlah);
            return true;
        } else {
            cout << "Uang yang dibayar kurang! Pembayaran gagal." << endl;
            return false;
        }
    } else {
        cout << "Maaf, stok " << menuTerpilih << " tidak cukup untuk " << jumlah << " pesanan!" << endl;
        return false;
    }
}

// Fungsi untuk menu pelanggan
void customerMenu(int merchantPilihan) {
    Queue* q = (merchantPilihan == 1) ? &queue1 : &queue2;
    menuMerchant* head = (merchantPilihan == 1) ? head1 : head2;
    bool hasOrdered = false;

    int pilihan;
    do {
        displayMenu(head);
        cout << "\n=== Menu Pelanggan ===" << endl;
        cout << "1. Pesan Menu" << endl;
        if (hasOrdered) {
            cout << "2. Lihat Antrian" << endl;
            cout << "3. Kembali" << endl;
        } else {
            cout << "2. Kembali" << endl;
        }
        cout << "Pilih opsi: ";
        cin >> pilihan;

        // Adjust pilihan based on whether Lihat Antrian is available
        if (!hasOrdered && pilihan == 2) {
            pilihan = 3; // Map to Kembali
        }

        switch (pilihan) {
            case 1:
                if (inputCustomer(*q, head)) {
                    hasOrdered = true;
                }
                break;
            case 2:
                if (hasOrdered) {
                    displayQueue(*q);
                }
                break;
            case 3:
                cout << "Kembali ke menu sebelumnya." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 3);
}

// Fungsi untuk menu merchant
void merchantMenu(int merchantPilihan) {
    menuMerchant* head = (merchantPilihan == 1) ? head1 : head2;
    menuMerchant* tail = (merchantPilihan == 1) ? tail1 : tail2;
    Queue* q = (merchantPilihan == 1) ? &queue1 : &queue2;

    int pilihan;
    do {
        cout << "\n=== Menu Merchant " << merchantPilihan << " ===" << endl;
        cout << "1. Confirm Antrian" << endl;
        cout << "2. Tampilkan Antrian" << endl;
        cout << "3. Tampilkan Daftar Menu" << endl;
        cout << "4. Riwayat Pesanan" << endl;
        cout << "5. Kembali" << endl;
        cout << "Pilih opsi (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                dequeue(*q);
                break;
            case 2:
                displayQueue(*q);
                break;
            case 3: {
                displayMenu(head);
                cout << "\nSub-Menu Daftar Menu:" << endl;
                cout << "1. Tambah Menu" << endl;
                cout << "2. Ubah Menu" << endl;
                cout << "3. Kembali" << endl;
                cout << "Pilih opsi (1-3): ";
                int subPilihan;
                cin >> subPilihan;
                switch (subPilihan) {
                    case 1:
                        tambahMenu(head, tail);
                        break;
                    case 2: {
                        int nomorMenu;
                        cout << "Masukkan nomor menu: ";
                        cin >> nomorMenu;
                        ubahMenu(head, tail, nomorMenu);
                        break;
                    }
                    case 3:
                        break;
                    default:
                        cout << "Pilihan tidak valid!" << endl;
                }
                break;
            }
            case 4:
                displayHistory();
                break;
            case 5:
                cout << "Kembali ke menu sebelumnya." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);
}

// Fungsi utama
int main() {
    // Inisialisasi antrian
    initQueue(queue1);
    initQueue(queue2);

    // Inisialisasi daftar menu
    addMenu(head1, tail1, "Rice Bowl", 10, 13000);
    addMenu(head1, tail1, "Air Putih", 8, 3000);
    addMenu(head1, tail1, "Soto Sapi", 9, 12000);
    addMenu(head1, tail1, "Soto Ayam", 100, 12000);
    addMenu(head1, tail1, "Soto Babi", 12, 12000);

    addMenu(head2, tail2, "Babi Guling", 10, 15000);
    addMenu(head2, tail2, "Ayam Panggang", 6, 12000);

    int role;
    do {
        cout << "\n=== Sistem Antrian Kantin ===" << endl;
        cout << "Pilih peran:" << endl;
        cout << "1. Merchant 1" << endl;
        cout << "2. Merchant 2" << endl;
        cout << "3. Pelanggan" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih opsi: ";
        cin >> role;

        if (role == 1) {
            merchantMenu(1);
        } else if (role == 2) {
            merchantMenu(2);
        } else if (role == 3) {
            int merchantPilihan;
            cout << "\nPilih Merchant:" << endl;
            cout << "1. Merchant 1" << endl;
            cout << "2. Merchant 2" << endl;
            cout << "3. Kembali" << endl;
            cout << "Pilih opsi: ";
            cin >> merchantPilihan;
            if (merchantPilihan == 1 || merchantPilihan == 2) {
                customerMenu(merchantPilihan);
            } else if (merchantPilihan == 3) {
                cout << "Kembali ke menu sebelumnya." << endl;
            } else {
                cout << "Pilihan tidak valid!" << endl;
            }
        } else if (role == 4) {
            cout << "Terima kasih! Program selesai." << endl;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (role != 4);

    // Membersihkan memori
    while (!isEmpty(queue1)) {
        Customer* temp = queue1.depan;
        queue1.depan = queue1.depan->next;
        delete temp;
        if (queue1.depan == nullptr) queue1.belakang = nullptr;
    }
    while (!isEmpty(queue2)) {
        Customer* temp = queue2.depan;
        queue2.depan = queue2.depan->next;
        delete temp;
        if (queue2.depan == nullptr) queue2.belakang = nullptr;
    }

    while (head1 != nullptr) {
        menuMerchant* temp = head1;
        head1 = head1->next;
        delete temp;
    }

    while (head2 != nullptr) {
        menuMerchant* temp = head2;
        head2 = head2->next;
        delete temp;
    }

    return 0;
}