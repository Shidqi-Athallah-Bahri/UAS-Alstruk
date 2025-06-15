#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Class untuk riwayat pesanan
class OrderHistory {
private:
    string nama;
    string pesanan;
    int nomorAntrian;
    int jumlah;
    int totalHarga;
    int uangDibayar;
    int kembalian;
    string merchant;

public:
    // Konstruktor default
    OrderHistory()
        : nama(""), pesanan(""), nomorAntrian(0), jumlah(0), totalHarga(0), uangDibayar(0), kembalian(0), merchant("") {}

    // Konstruktor parameter
    OrderHistory(const string& _nama, const string& _pesanan, int _nomorAntrian,
                 int _jumlah, int _totalHarga, int _uangDibayar, int _kembalian, const string& _merchant)
        : nama(_nama), pesanan(_pesanan), nomorAntrian(_nomorAntrian), jumlah(_jumlah),
          totalHarga(_totalHarga), uangDibayar(_uangDibayar), kembalian(_kembalian), merchant(_merchant) {}

    // Setter
    void setData(const string& _nama, const string& _pesanan, int _nomorAntrian,
                 int _jumlah, int _totalHarga, int _uangDibayar, int _kembalian, const string& _merchant) {
        nama = _nama;
        pesanan = _pesanan;
        nomorAntrian = _nomorAntrian;
        jumlah = _jumlah;
        totalHarga = _totalHarga;
        uangDibayar = _uangDibayar;
        kembalian = _kembalian;
        merchant = _merchant;
    }

    // Getters
    string getNama() const { return nama; }
    string getPesanan() const { return pesanan; }
    int getNomorAntrian() const { return nomorAntrian; }
    int getJumlah() const { return jumlah; }
    int getTotalHarga() const { return totalHarga; }
    int getUangDibayar() const { return uangDibayar; }
    int getKembalian() const { return kembalian; }
    string getMerchant() const { return merchant; }
};

// Class untuk pelanggan (node dalam queue)
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

// Class untuk mengelola antrian pelanggan (Queue)
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
             << pelangganBaru->nomorAntrian << endl;
        cout << "Pesanan: " << pesanan << endl;
        cout << "Jumlah: " << jumlah << endl;
        cout << "Total: Rp" << totalHarga << endl;
        cout << "Uang Dibayar: Rp" << uangDibayar << endl;
        cout << "Kembalian: Rp" << kembalian << endl;
    }

    Customer* dequeue() {
        if (isEmpty()) {
            cout << "Antrian kosong!" << endl;
            return nullptr;
        }
        Customer* temp = depan;
        cout << "Pelanggan " << temp->nama << " dengan nomor antrian "
             << temp->nomorAntrian << " telah dikonfirmasi." << endl;
        depan = depan->next;
        if (depan == nullptr) {
            belakang = nullptr;
        }
        return temp; // Kembalikan untuk riwayat
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
            cout << "Nomor " << current->nomorAntrian << endl;
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

// Class untuk mengelola daftar menu (LinkedList)
class MenuList {
private:
    MenuNode* head;
    MenuNode* tail;

public:
    MenuList() : head(nullptr), tail(nullptr) {}

    void addMenu(const string& namaMenu, int jumlahStok, int hargaMenu) {
        if (jumlahStok <= 0 || hargaMenu <= 0) {
            cout << "Stok dan harga harus lebih dari 0!" << endl;
            return;
        }
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

    void tambahStok(const string& namaMenu, int jumlah) {
        if (jumlah <= 0) {
            cout << "Jumlah harus lebih dari 0!" << endl;
            return;
        }
        MenuNode* current = head;
        while (current != nullptr) {
            if (current->namaMenu == namaMenu) {
                current->jumlahStok += jumlah;
                cout << "Stok " << namaMenu << " ditambah " << jumlah << "." << endl;
                cout << "Stok sekarang: " << current->jumlahStok << endl;
                return;
            }
            current = current->next;
        }
        cout << "Menu " << namaMenu << " tidak ditemukan." << endl;
    }

    void kurangiStokManual(const string& namaMenu, int jumlah) {
        if (jumlah <= 0) {
            cout << "Jumlah harus lebih dari 0!" << endl;
            return;
        }
        MenuNode* current = head;
        while (current != nullptr) {
            if (current->namaMenu == namaMenu) {
                if (current->jumlahStok >= jumlah) {
                    current->jumlahStok -= jumlah;
                    cout << "Stok " << namaMenu << " dikurangi " << jumlah << "." << endl;
                    cout << "Stok sekarang: " << current->jumlahStok << endl;
                } else {
                    cout << "Stok tidak cukup!" << endl;
                }
                return;
            }
            current = current->next;
        }
        cout << "Menu " << namaMenu << " tidak ditemukan." << endl;
    }

    void kosongkanStok(const string& namaMenu) {
        MenuNode* current = head;
        while (current != nullptr) {
            if (current->namaMenu == namaMenu) {
                if (current->jumlahStok > 0) {
                    current->jumlahStok = 0;
                    cout << "Stok " << namaMenu << " telah dikosongkan." << endl;
                    cout << "Stok sekarang: " << current->jumlahStok << endl;
                } else {
                    cout << "Stok " << namaMenu << " sudah kosong!" << endl;
                }
                return;
            }
            current = current->next;
        }
        cout << "Menu " << namaMenu << " tidak ditemukan." << endl;
    }

    void ubahHarga(const string& namaMenu, int hargaBaru) {
        if (hargaBaru <= 0) {
            cout << "Harga harus lebih dari 0!" << endl;
            return;
        }
        MenuNode* current = head;
        while (current != nullptr) {
            if (current->namaMenu == namaMenu) {
                current->hargaMenu = hargaBaru;
                cout << "Harga " << namaMenu << " diubah menjadi Rp" << hargaBaru << endl;
                return;
            }
            current = current->next;
        }
        cout << "Menu " << namaMenu << " tidak ditemukan." << endl;
    }

    void kurangiStok(const string& namaMenu, int jumlah) {
        if (cekStok(namaMenu, jumlah)) {
            MenuNode* current = head;
            while (current != nullptr) {
                if (current->namaMenu == namaMenu) {
                    current->jumlahStok -= jumlah;
                    cout << "Stok " << namaMenu << " berkurang " << jumlah << endl;
                    return;
                }
                current = current->next;
            }
        } else {
            cout << "Stok tidak cukup atau menu tidak ditemukan." << endl;
        }
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

    int getHarga(const string& namaMenu) const {
        MenuNode* current = head;
        while (current != nullptr) {
            if (current->namaMenu == namaMenu) return current->hargaMenu;
            current = current->next;
        }
        return 0;
    }

    MenuNode* getMenuByNumber(int nomor) const {
        int index = 1;
        MenuNode* current = head;
        while (current != nullptr) {
            if (index == nomor) return current;
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
        cout << "\nDaftar Menu:" << endl;
        MenuNode* current = head;
        int i = 1;
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
        cout << "\nDaftar Menu:" << endl;
        MenuNode* current = head;
        int i = 1;
        bool adaMenu = false;
        while (current != nullptr) {
            cout << i++ << ". " << current->namaMenu << " (Stok: " << current->jumlahStok;
            if (current->jumlahStok == 0) {
                cout << " - Habis";
            }
            cout << ") Harga: Rp" << current->hargaMenu << endl;
            if (current->jumlahStok > 0) {
                adaMenu = true;
            }
            current = current->next;
        }
        if (!adaMenu) {
            cout << "Tidak ada menu dengan stok tersedia!" << endl;
        }
    }

    void clear() {
        while (head != nullptr) {
            MenuNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
};

// Class untuk merepresentasikan merchant
class Merchant {
private:
    string nama;
    MenuList menuList;
    Queue queue;

public:
    Merchant(const string& _nama) : nama(_nama) {}

    void initializeMenu() {
        if (nama == "Merchant 1") {
            menuList.addMenu("Rice Bowl", 10, 13000);
            menuList.addMenu("Air Putih", 8, 3000);
            menuList.addMenu("Soto Sapi", 9, 12000);
            menuList.addMenu("Soto Ayam", 10, 12000);
            menuList.addMenu("Soto Babi", 12, 12000);
        } else if (nama == "Merchant 2") {
            menuList.addMenu("Babi Guling", 10, 15000);
            menuList.addMenu("Ayam Panggang", 6, 12000);
        }
    }

    string getNama() const { return nama; }
    MenuList& getMenuList() { return menuList; }
    Queue& getQueue() { return queue; }
};

// Class untuk mengelola sistem kantin
class CanteenSystem {
private:
    Merchant merchants[2]; // Array untuk dua merchant
    OrderHistory* history; // Pointer untuk riwayat pesanan
    int historyCount;
    bool hasOrdered[2]; // Array untuk melacak status pemesanan per merchant

    // Validasi input angka
    int inputNumber(const string& prompt) {
        int value;
        cout << prompt;
        while (!(cin >> value)) {
            cout << "Input tidak valid. Masukkan angka: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return value;
    }

    // Fungsi untuk input pesanan pelanggan
    bool inputCustomer(Merchant& merchant, int merchantIndex) {
        string nama;
        cout << "Masukkan nama pelanggan: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, nama);
        if (nama.empty()) {
            cout << "Nama tidak boleh kosong!" << endl;
            return false;
        }

        merchant.getMenuList().displayMenuPelanggan();
        int pilihanMenu = inputNumber("Pilih nomor menu: ");
        MenuNode* selected = merchant.getMenuList().getMenuByNumber(pilihanMenu);
        if (!selected) {
            cout << "Pilihan menu tidak valid!" << endl;
            return false;
        }
        string menuTerpilih = selected->namaMenu;

        // Validasi stok menu sebelum melanjutkan
        if (selected->jumlahStok == 0) {
            cout << "Maaf, stok " << menuTerpilih << " sudah habis!" << endl;
            return false;
        }

        int jumlah = inputNumber("Masukkan jumlah pesanan: ");
        if (jumlah <= 0) {
            cout << "Jumlah pesanan harus lebih dari 0!" << endl;
            return false;
        }

        if (merchant.getMenuList().cekStok(menuTerpilih, jumlah)) {
            int totalHarga = jumlah * merchant.getMenuList().getHarga(menuTerpilih);
            cout << "Total pembayaran: Rp" << totalHarga << endl;
            int uangDibayar = inputNumber("Masukkan jumlah uang yang dibayar: Rp");
            if (uangDibayar < totalHarga) {
                cout << "Uang yang dibayar kurang! Pembayaran gagal." << endl;
                return false;
            }
            int kembalian = uangDibayar - totalHarga;
            cout << "Pembayaran berhasil! Kembalian: Rp" << kembalian << endl;
            merchant.getQueue().enqueue(nama, menuTerpilih, jumlah, totalHarga, uangDibayar, kembalian);
            merchant.getMenuList().kurangiStok(menuTerpilih, jumlah);
            hasOrdered[merchantIndex - 1] = true; // Tandai bahwa pelanggan telah memesan
            return true;
        } else {
            cout << "Maaf, stok " << menuTerpilih << " tidak cukup untuk " << jumlah << " pesanan!" << endl;
            return false;
        }
    }

    // Fungsi untuk sub-menu pengelolaan stok
    void manageStock(Merchant& merchant, const string& namaMenu) {
        int pilihan;
        do {
            cout << "\n=== Pengaturan Stok untuk " << namaMenu << " ===" << endl;
            cout << "1. Tambah Stok" << endl;
            cout << "2. Kurangi Stok" << endl;
            cout << "3. Kosongkan Stok" << endl;
            cout << "4. Kembali" << endl;
            cout << "Pilih opsi (1-4): ";
            pilihan = inputNumber("");

            if (pilihan == 1) {
                int jumlah = inputNumber("Masukkan jumlah stok: ");
                merchant.getMenuList().tambahStok(namaMenu, jumlah);
            } else if (pilihan == 2) {
                int jumlah = inputNumber("Masukkan jumlah stok: ");
                merchant.getMenuList().kurangiStokManual(namaMenu, jumlah);
            } else if (pilihan == 3) {
                merchant.getMenuList().kosongkanStok(namaMenu);
            } else if (pilihan == 4) {
                cout << "Kembali ke menu ubah menu." << endl;
            } else {
                cout << "Pilihan tidak valid!" << endl;
            }
        } while (pilihan != 4);
    }

    // Fungsi untuk sub-menu ubah menu
    void modifyMenu(Merchant& merchant, int nomorMenu) {
        MenuNode* selected = merchant.getMenuList().getMenuByNumber(nomorMenu);
        if (!selected) {
            cout << "Nomor menu tidak valid!" << endl;
            return;
        }
        string namaMenu = selected->namaMenu;
        int pilihan;
        do {
            cout << "\n=== Ubah Menu: " << namaMenu << " ===" << endl;
            cout << "1. Hapus Menu" << endl;
            cout << "2. Pengaturan Stok" << endl;
            cout << "3. Ubah Harga" << endl;
            cout << "4. Kembali" << endl;
            cout << "Pilih opsi (1-4): ";
            pilihan = inputNumber("");

            if (pilihan == 1) {
                merchant.getMenuList().deleteMenu(namaMenu);
                return; // Keluar setelah hapus untuk menghindari akses menu yang sudah dihapus
            } else if (pilihan == 2) {
                manageStock(merchant, namaMenu);
            } else if (pilihan == 3) {
                int hargaBaru = inputNumber("Masukkan harga baru: ");
                merchant.getMenuList().ubahHarga(namaMenu, hargaBaru);
            } else if (pilihan == 4) {
                cout << "Kembali ke menu kelola menu." << endl;
            } else {
                cout << "Pilihan tidak valid!" << endl;
            }
        } while (pilihan != 4);
    }

    // Fungsi untuk sub-menu pengelolaan menu
    void manageMenu(Merchant& merchant) {
        int pilihan;
        do {
            merchant.getMenuList().displayMenu();
            cout << "\n=== Kelola Menu ===" << endl;
            cout << "1. Tambah Menu" << endl;
            cout << "2. Ubah Menu" << endl;
            cout << "3. Kembali" << endl;
            cout << "Pilih opsi (1-3): ";
            pilihan = inputNumber("");

            if (pilihan == 1) {
                string nama;
                cout << "Masukkan nama menu: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, nama);
                int stok = inputNumber("Masukkan jumlah stok: ");
                int harga = inputNumber("Masukkan harga: ");
                merchant.getMenuList().addMenu(nama, stok, harga);
            } else if (pilihan == 2) {
                merchant.getMenuList().displayMenu();
                int nomorMenu = inputNumber("Pilih nomor menu untuk diubah: ");
                modifyMenu(merchant, nomorMenu);
            } else if (pilihan == 3) {
                cout << "Kembali ke menu merchant." << endl;
            } else {
                cout << "Pilihan tidak valid!" << endl;
            }
        } while (pilihan != 3);
    }

    // Fungsi untuk menu pelanggan
    void customerMenu(int merchantPilihan) {
        if (merchantPilihan < 1 || merchantPilihan > 2) {
            cout << "Pilihan merchant tidak valid!" << endl;
            return;
        }
        Merchant& merchant = merchants[merchantPilihan - 1];
        int pilihan;
        do {
            merchant.getMenuList().displayMenuPelanggan();
            cout << "\n=== Menu Pelanggan ===" << endl;
            cout << "1. Pesan Menu" << endl;
            if (hasOrdered[merchantPilihan - 1]) {
                cout << "2. Lihat Antrian" << endl;
                cout << "3. Kembali" << endl;
                cout << "Pilih opsi (1-3): ";
            } else {
                cout << "2. Kembali" << endl;
                cout << "Pilih opsi (1-2): ";
            }
            pilihan = inputNumber("");

            if (pilihan == 1) {
                inputCustomer(merchant, merchantPilihan);
            } else if (pilihan == 2 && hasOrdered[merchantPilihan - 1]) {
                merchant.getQueue().displayQueue();
            } else if ((pilihan == 2 && !hasOrdered[merchantPilihan - 1]) || (pilihan == 3 && hasOrdered[merchantPilihan - 1])) {
                cout << "Kembali ke menu utama." << endl;
                break;
            } else {
                cout << "Pilihan tidak valid!" << endl;
            }
        } while (true);
    }

    // Fungsi untuk menu merchant
    void merchantMenu(int merchantPilihan) {
        if (merchantPilihan < 1 || merchantPilihan > 2) {
            cout << "Pilihan merchant tidak valid!" << endl;
            return;
        }
        Merchant& merchant = merchants[merchantPilihan - 1];
        int pilihan;
        do {
            cout << "\n=== Menu Merchant " << merchant.getNama() << " ===" << endl;
            cout << "1. Konfirmasi Antrian" << endl;
            cout << "2. Tampilkan Antrian" << endl;
            cout << "3. Tampilkan Daftar Menu" << endl;
            cout << "4. Lihat Riwayat Pesanan" << endl;
            cout << "5. Kembali" << endl;
            cout << "Pilih opsi (1-5): ";
            pilihan = inputNumber("");

            if (pilihan == 1) {
                Customer* pelanggan = merchant.getQueue().dequeue();
                if (pelanggan && historyCount < 100) {
                    history[historyCount] = OrderHistory(
                        pelanggan->nama,
                        pelanggan->pesanan,
                        pelanggan->nomorAntrian,
                        pelanggan->jumlah,
                        pelanggan->totalHarga,
                        pelanggan->uangDibayar,
                        pelanggan->kembalian,
                        merchant.getNama()
                    );
                    historyCount++;
                    delete pelanggan;
                }
            } else if (pilihan == 2) {
                merchant.getQueue().displayQueue();
            } else if (pilihan == 3) {
                manageMenu(merchant);
            } else if (pilihan == 4) {
                if (historyCount == 0) {
                    cout << "Riwayat pesanan kosong!" << endl;
                } else {
                    cout << "\nRiwayat Pesanan:" << endl;
                    cout << "----------------" << endl;
                    bool found = false;
                    for (int i = 0; i < historyCount; i++) {
                        if (history[i].getMerchant() == merchant.getNama()) {
                            cout << "Pesanan ke-" << (i + 1) << endl;
                            cout << "Nama: " << history[i].getNama() << endl;
                            cout << "Pesanan: " << history[i].getPesanan() << endl;
                            cout << "Nomor Antrian: " << history[i].getNomorAntrian() << endl;
                            cout << "Jumlah: " << history[i].getJumlah() << endl;
                            cout << "Total Harga: Rp" << history[i].getTotalHarga() << endl;
                            cout << "Uang Dibayar: Rp" << history[i].getUangDibayar() << endl;
                            cout << "Kembalian: Rp" << history[i].getKembalian() << endl;
                            cout << "Merchant: " << history[i].getMerchant() << endl;
                            cout << "----------------" << endl;
                            found = true;
                        }
                    }
                    if (!found) {
                        cout << "Tidak ada riwayat untuk merchant ini." << endl;
                    }
                }
            } else if (pilihan == 5) {
                cout << "Kembali ke menu utama." << endl;
            } else {
                cout << "Pilihan tidak valid!" << endl;
            }
        } while (pilihan != 5);
    }

public:
    CanteenSystem() : merchants{Merchant("Merchant 1"), Merchant("Merchant 2")}, historyCount(0) {
        history = new OrderHistory[100]; // Alokasi dinamis untuk riwayat
        for (int i = 0; i < 2; i++) {
            merchants[i].initializeMenu();
            hasOrdered[i] = false; // Inisialisasi status pemesanan
        }
    }

    ~CanteenSystem() {
        // Bersihkan memori
        delete[] history; // Bebaskan memori riwayat
        for (int i = 0; i < 2; i++) {
            merchants[i].getQueue().clear();
            merchants[i].getMenuList().clear();
        }
    }

    void run() {
        int role;
        do {
            cout << "\n=== Sistem Antrian Kantin ===" << endl;
            cout << "1. Pelanggan" << endl;
            cout << "2. Merchant" << endl;
            cout << "3. Keluar" << endl;
            cout << "Pilih opsi (1-3): ";
            role = inputNumber("");

            if (role == 1) {
                int merchantPilihan;
                cout << "\nPilih Merchant:" << endl;
                cout << "1. Merchant 1" << endl;
                cout << "2. Merchant 2" << endl;
                cout << "3. Kembali" << endl;
                merchantPilihan = inputNumber("Pilih opsi (1-3): ");
                if (merchantPilihan == 1 || merchantPilihan == 2) {
                    customerMenu(merchantPilihan);
                } else if (merchantPilihan == 3) {
                    cout << "Kembali ke menu utama." << endl;
                } else {
                    cout << "Pilihan tidak valid!" << endl;
                }
            } else if (role == 2) {
                int merchantPilihan;
                cout << "\nPilih Merchant:" << endl;
                cout << "1. Merchant 1" << endl;
                cout << "2. Merchant 2" << endl;
                cout << "3. Kembali" << endl;
                merchantPilihan = inputNumber("Pilih opsi (1-3): ");
                if (merchantPilihan == 1 || merchantPilihan == 2) {
                    merchantMenu(merchantPilihan);
                } else if (merchantPilihan == 3) {
                    cout << "Kembali ke menu utama." << endl;
                } else {
                    cout << "Pilihan tidak valid!" << endl;
                }
            } else if (role == 3) {
                cout << "Terima kasih! Program selesai." << endl;
            } else {
                cout << "Pilihan tidak valid!" << endl;
            }
        } while (role != 3);
    }
};

int main() {
    CanteenSystem system;
    system.run();
    return 0;
}