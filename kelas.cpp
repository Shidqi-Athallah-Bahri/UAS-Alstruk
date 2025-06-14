#include <iostream>
#include <string>
#include <limits>
using namespace std;

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

// Global untuk riwayat
OrderHistory historyArr[100];
int historyCount = 0;

// Kelas Customer node
class Customer {
public:
    string nama;
    string pesanan;
    int nomorAntrian;
    int jumlah;
    int totalHarga;
    int uangDibayar;
    int kembalian;
    Customer* next;

    Customer(const string& _nama, const string& _pesanan, int _jumlah, int _totalHarga, int _uangDibayar, int _kembalian, int _nomor)
        : nama(_nama), pesanan(_pesanan), jumlah(_jumlah), totalHarga(_totalHarga), uangDibayar(_uangDibayar), kembalian(_kembalian), nomorAntrian(_nomor), next(nullptr) {}
};

// Kelas Queue
class Queue {
private:
    Customer* depan;
    Customer* belakang;
    int nomorAntrianSaatIni;
public:
    Queue() : depan(nullptr), belakang(nullptr), nomorAntrianSaatIni(0) {}

    bool isEmpty() const {
        return depan == nullptr;
    }

    void enqueue(const string& nama, const string& pesanan, int jumlah, int totalHarga, int uangDibayar, int kembalian) {
        int nomor = ++nomorAntrianSaatIni;
        Customer* pelangganBaru = new Customer(nama, pesanan, jumlah, totalHarga, uangDibayar, kembalian, nomor);
        if (isEmpty()) {
            depan = belakang = pelangganBaru;
        } else {
            belakang->next = pelangganBaru;
            belakang = pelangganBaru;
        }
        cout << "Pelanggan " << nama << " ditambahkan ke antrian dengan nomor "
             << pelangganBaru->nomorAntrian << " (Pesanan: " << pesanan << ", Jumlah: " << jumlah
             << ", Total: Rp" << totalHarga << ", Uang Dibayar: Rp" << uangDibayar
             << ", Kembalian: Rp" << kembalian << ")" << endl;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Antrian kosong!" << endl;
            return;
        }
        Customer* temp = depan;
        cout << "Pelanggan " << temp->nama << " dengan nomor antrian "
             << temp->nomorAntrian << " telah dikonfirmasi." << endl;
        // Simpan ke riwayat pesanan
        if (historyCount < 100) {
            historyArr[historyCount].nama = temp->nama;
            historyArr[historyCount].pesanan = temp->pesanan;
            historyArr[historyCount].nomorAntrian = temp->nomorAntrian;
            historyArr[historyCount].jumlah = temp->jumlah;
            historyArr[historyCount].totalHarga = temp->totalHarga;
            historyArr[historyCount].uangDibayar = temp->uangDibayar;
            historyArr[historyCount].kembalian = temp->kembalian;
            historyCount++;
        } else {
            cout << "Riwayat pesanan penuh!" << endl;
        }
        depan = depan->next;
        delete temp;
        if (depan == nullptr) {
            belakang = nullptr;
        }
    }

    void displayQueue() const {
        if (isEmpty()) {
            cout << "Antrian kosong!" << endl;
            return;
        }
        cout << "\nDaftar Antrian Pelanggan:" << endl;
        cout << "------------------------" << endl;
        Customer* current = depan;
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

    // Untuk membersihkan memori saat program selesai
    void clear() {
        while (!isEmpty()) {
            Customer* temp = depan;
            depan = depan->next;
            delete temp;
        }
        belakang = nullptr;
    }
};

// Node untuk menu
class MenuNode {
public:
    string namaMenu;
    int jumlahStok;
    int hargaMenu;
    MenuNode* next;
    MenuNode(const string& _nama, int _stok, int _harga)
        : namaMenu(_nama), jumlahStok(_stok), hargaMenu(_harga), next(nullptr) {}
};

// Kelas LinkedList untuk menu merchant
class MenuList {
private:
    MenuNode* head;
    MenuNode* tail;
public:
    MenuList() : head(nullptr), tail(nullptr) {}

    void addMenu(const string& namaMenu, int jumlahStok, int hargaMenu) {
        MenuNode* newMenu = new MenuNode(namaMenu, jumlahStok, hargaMenu);
        if (head == nullptr) {
            head = tail = newMenu;
        } else {
            tail->next = newMenu;
            tail = newMenu;
        }
        cout << "Menu " << namaMenu << " ditambahkan." << endl;
    }

    void deleteMenu(const string& namaMenu) {
        MenuNode* cur = head;
        MenuNode* prev = nullptr;
        while (cur != nullptr) {
            if (cur->namaMenu == namaMenu) {
                if (prev == nullptr) {
                    head = cur->next;
                } else {
                    prev->next = cur->next;
                }
                if (cur == tail) {
                    tail = prev;
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

    bool cekMenu(const string& namaMenu) const {
        MenuNode* current = head;
        while (current != nullptr) {
            if (current->namaMenu == namaMenu) return true;
            current = current->next;
        }
        return false;
    }

    bool cekStok(const string& namaMenu, int jumlah) const {
        MenuNode* current = head;
        while (current != nullptr) {
            if (current->namaMenu == namaMenu) return current->jumlahStok >= jumlah;
            current = current->next;
        }
        return false;
    }

    void kurangiStok(const string& namaMenu, int jumlah) {
        if (cekStok(namaMenu, jumlah)) {
            MenuNode* current = head;
            while (current != nullptr) {
                if (current->namaMenu == namaMenu) {
                    current->jumlahStok -= jumlah;
                    cout << "Stok " << namaMenu << " dikurangi sebanyak " << jumlah << endl;
                    return;
                }
                current = current->next;
            }
        } else {
            cout << "Stok tidak cukup atau menu tidak ditemukan." << endl;
        }
    }

    void tambahStokMenu(const string& namaMenu) {
        MenuNode* current = head;
        while (current != nullptr) {
            if (current->namaMenu == namaMenu) {
                int tambah;
                cout << "Masukkan jumlah stok yang ingin ditambah: ";
                while (!(cin >> tambah)) {
                    cout << "Invalid input. Masukkan tolong masukkan angka: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
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

    void ubahHargaMenu(const string& namaMenu) {
        MenuNode* current = head;
        while (current != nullptr) {
            if (current->namaMenu == namaMenu) {
                int hargaBaru;
                cout << "Masukkan harga baru: ";
                while (!(cin >> hargaBaru)) {
                    cout << "Invalid input. Masukkan tolong masukkan angka: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
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

    void kosongkanStok(const string& namaMenu) {
        MenuNode* current = head;
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

    void ubahStok(const string& namaMenu) {
        int pilih;
        cout << "Mengubah Stok" << endl;
        cout << "1. Tambah Stok" << endl;
        cout << "2. Kurangi Stok" << endl;
        cout << "3. Kosongkan Stok" << endl;
        cout << "Pilih opsi: ";
        while (!(cin >> pilih)) {
                    cout << "Invalid input. Masukkan tolong masukkan angka: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

        int jumlah;
        switch (pilih) {
            case 1:
                tambahStokMenu(namaMenu);
                break;
            case 2:
                cout << "Masukkan jumlah yang ingin dikurangi: ";
                while (!(cin >> jumlah)) {
                    cout << "Invalid input. Masukkan tolong masukkan angka: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (jumlah <= 0) {
                    cout << "Jumlah harus lebih dari 0!" << endl;
                    return;
                }
                kurangiStok(namaMenu, jumlah);
                break;
            case 3:
                kosongkanStok(namaMenu);
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    }

    MenuNode* getMenuByNumber(int nomor) const {
        int index = 1;
        MenuNode* current = head;
        while (current != nullptr) {
            if (index == nomor) {
                return current;
            }
            current = current->next;
            index++;
        }
        return nullptr;
    }

    void displayMenu() const {
        if (head == nullptr) {
            cout << "Daftar menu kosong!" << endl;
            return;
        }
        int i = 1;
        cout << "\nDaftar Menu:" << endl;
        MenuNode* current = head;
        while (current != nullptr) {
            cout << i++ << ". " << current->namaMenu << " (Stok: " << current->jumlahStok
                 << ") Harga: Rp" << current->hargaMenu << endl;
            current = current->next;
        }
    }

    void displayMenuPelanggan() const {
        if (head == nullptr) {
            cout << "Daftar menu kosong!" << endl;
            return;
        }
        int i = 1;
        cout << "\nDaftar Menu:" << endl;
        MenuNode* current = head;
        while (current != nullptr) {
            if (current->jumlahStok <= 0) {
                current = current->next;
                continue;
            }
            cout << i++ << ". " << current->namaMenu << " (Stok: " << current->jumlahStok
                 << ") Harga: Rp" << current->hargaMenu << endl;
            current = current->next;
        }
    }

    void displayHistory() const {
        if (historyCount == 0) {
            cout << "Riwayat pesanan kosong!" << endl;
            return;
        }
        cout << "\nRiwayat Pesanan:" << endl;
        cout << "----------------" << endl;
        for (int i = 0; i < historyCount; i++) {
            cout << "Pesanan ke-" << (i + 1) << ":" << endl;
            cout << "Nama: " << historyArr[i].nama << endl;
            cout << "Pesanan: " << historyArr[i].pesanan << endl;
            cout << "Nomor Antrian: " << historyArr[i].nomorAntrian << endl;
            cout << "Jumlah: " << historyArr[i].jumlah << endl;
            cout << "Total Harga: Rp" << historyArr[i].totalHarga << endl;
            cout << "Uang Dibayar: Rp" << historyArr[i].uangDibayar << endl;
            cout << "Kembalian: Rp" << historyArr[i].kembalian << endl;
            cout << "----------------" << endl;
        }
    }

    // Fungsi untuk mengubah menu berdasarkan nomor (interactive)
    void modifyMenu(int nomorMenu) {
        MenuNode* selectedMenu = getMenuByNumber(nomorMenu);
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
            while (!(cin >> pilihan)) {
                    cout << "Invalid input. Masukkan tolong masukkan angka: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            switch (pilihan) {
                case 1:
                    deleteMenu(namaMenu);
                    return;
                case 2:
                    ubahStok(namaMenu);
                    break;
                case 3:
                    ubahHargaMenu(namaMenu);
                    break;
                case 4:
                    cout << "Kembali ke menu sebelumnya." << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid!" << endl;
            }
        } while (pilihan != 4);
    }
};

// Inisialisasi global
MenuList merchant1Menu;
MenuList merchant2Menu;
Queue queue1;
Queue queue2;

bool inputCustomer(Queue &q, MenuList &menuList) {
    string nama;
    int pilihanMenu, jumlah;
    cout << "Masukkan nama pelanggan: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nama);
    menuList.displayMenuPelanggan();
    cout << "Pilih nomor menu: ";
    cin >> pilihanMenu;
    cout << "Masukkan jumlah pesanan: ";
    cin >> jumlah;
    if (jumlah <= 0) {
        cout << "Jumlah pesanan harus lebih dari 0!" << endl;
        return false;
    }
    MenuNode* selected = menuList.getMenuByNumber(pilihanMenu);
    if (!selected) {
        cout << "Pilihan menu tidak valid!" << endl;
        return false;
    }
    string menuTerpilih = selected->namaMenu;
    int hargaMenu = selected->hargaMenu;

    if (menuList.cekStok(menuTerpilih, jumlah)) {
        int totalHarga = jumlah * hargaMenu;
        cout << "Total pembayaran: Rp" << totalHarga << endl;
        int uangDibayar;
        cout << "Masukkan jumlah uang yang dibayar: Rp";
        cin >> uangDibayar;
        if (uangDibayar >= totalHarga) {
            int kembalian = uangDibayar - totalHarga;
            cout << "Pembayaran berhasil! Kembalian: Rp" << kembalian << endl;
            q.enqueue(nama, menuTerpilih, jumlah, totalHarga, uangDibayar, kembalian);
            menuList.kurangiStok(menuTerpilih, jumlah);
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

void customerMenu(int merchantPilihan) {
    Queue& q = (merchantPilihan == 1) ? queue1 : queue2;
    MenuList& menuList = (merchantPilihan == 1) ? merchant1Menu : merchant2Menu;
    bool hasOrdered = false;
    int pilihan;
    do {
        menuList.displayMenuPelanggan();
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
        if (!hasOrdered && pilihan == 2) {
            pilihan = 3;
        }
        switch (pilihan) {
            case 1:
                if (inputCustomer(q, menuList)) {
                    hasOrdered = true;
                }
                break;
            case 2:
                if (hasOrdered) {
                    q.displayQueue();
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

void merchantMenu(int merchantPilihan) {
    MenuList& menuList = (merchantPilihan == 1) ? merchant1Menu : merchant2Menu;
    Queue& q = (merchantPilihan == 1) ? queue1 : queue2;
    int opsi = 0;
    do {
        cout << "\n=== Menu Merchant " << merchantPilihan << " ===" << endl;
        cout << "1. Confirm Antrian" << endl;
        cout << "2. Tampilkan Antrian" << endl;
        cout << "3. Tampilkan Daftar Menu" << endl;
        cout << "4. Riwayat Pesanan" << endl;
        cout << "5. Kembali" << endl;
        cout << "Pilih opsi (1-5): ";
        while (!(cin >> opsi)) {
                    cout << "Invalid input. Masukkan tolong masukkan angka: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
        
        switch (opsi) {
            case 1:
                q.dequeue();
                break;
            case 2:
                q.displayQueue();
                break;
            case 3: {
                menuList.displayMenu();
                cout << "\nSub-Menu Daftar Menu:" << endl;
                cout << "1. Tambah Menu" << endl;
                cout << "2. Ubah Menu" << endl;
                cout << "3. Kembali" << endl;
                cout << "Pilih opsi (1-3): ";
                int subPilihan;
                while (!(cin >> subPilihan)) {
                    cout << "Invalid input. Masukkan tolong masukkan angka: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                switch (subPilihan) {
                    case 1: {
                        string dummy;
                        // flush newline
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        string nama;
                        int stok, harga;
                        cout << "Masukkan nama menu: ";
                        getline(cin, nama);
                        cout << "Masukkan jumlah stok: ";
                        while (!(cin >> stok)) {
                            cout << "Invalid input. Masukkan tolong masukkan angka: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        if (stok <= 0) {
                            cout << "Jumlah stok harus lebih dari 0!" << endl;
                            break;
                        }
                        cout << "Masukkan Harga: ";
                        while (!(cin >> harga)) {
                            cout << "Invalid input. Masukkan tolong masukkan angka: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        if (harga <= 0) {
                            cout << "Harga harus lebih dari 0!" << endl;
                            break;
                        }
                        menuList.addMenu(nama, stok, harga);
                        break;
                    }
                    case 2: {
                        int nomorMenu;
                        cout << "Masukkan nomor menu: ";
                        while (!(cin >> nomorMenu)) {
                            cout << "Invalid input. Masukkan tolong masukkan angka: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        menuList.modifyMenu(nomorMenu);
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
                merchant1Menu.displayHistory(); // history is global; displayHistory reads global
                break;
            case 5:
                cout << "Kembali ke menu sebelumnya." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (opsi != 5);
}

int main() {
    // Inisialisasi daftar menu awal
    merchant1Menu.addMenu("Rice Bowl", 10, 13000);
    merchant1Menu.addMenu("Air Putih", 8, 3000);
    merchant1Menu.addMenu("Soto Sapi", 9, 12000);
    merchant1Menu.addMenu("Soto Ayam", 100, 12000);
    merchant1Menu.addMenu("Soto Babi", 12, 12000);

    merchant2Menu.addMenu("Babi Guling", 10, 15000);
    merchant2Menu.addMenu("Ayam Panggang", 6, 12000);

    int role;
    do {
        cout << "\n=== Sistem Antrian Kantin ===" << endl;
        cout << "Pilih peran:" << endl;
        cout << "1. Merchant 1" << endl;
        cout << "2. Merchant 2" << endl;
        cout << "3. Pelanggan" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih opsi: ";
        while (!(cin >> role)) {
                    cout << "Invalid input. Masukkan tolong masukkan angka: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
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
            while (!(cin >> merchantPilihan)) {
                    cout << "Invalid input. Masukkan tolong masukkan angka: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
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

    // Membersihkan memori sebelum keluar
    queue1.clear();
    queue2.clear();
    // Untuk menu, kita bisa mengabaikan pembersihan karena program akan selesai, OS akan reclaim memory.
    return 0;
}
