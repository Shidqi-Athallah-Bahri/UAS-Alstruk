#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Struktur untuk menu makanan
struct MenuItem {
    string name;
    double price;
};

// Fungsi untuk menampilkan menu makanan
void displayMenu() {
    cout << "=== Menu Kantin ===" << endl;
    cout << "1. Rice Bowl - Rp 15.000" << endl;
    cout << "2. Yamin Pangsit - Rp 12.000" << endl;
    cout << "3. Katsu - Rp 18.000" << endl;
    cout << "4. Penyet - Rp 10.000" << endl;
    cout << "5. Sate Ika - Rp 5.000" << endl;
    cout << "===================" << endl;
}

// Fungsi untuk menambahkan pesanan ke dalam keranjang
void addToCart(queue<pair<MenuItem, int>>& cart, const MenuItem& item, int quantity) {
    cart.push(make_pair(item, quantity));
}

// Fungsi untuk menampilkan keranjang belanja
void displayCart(const queue<pair<MenuItem, int>>& cart) {
    queue<pair<MenuItem, int>> temp = cart;
    double totalPrice = 0;

    cout << "\n=== Keranjang Belanja ===" << endl;
    while (!temp.empty()) {
        pair<MenuItem, int> order = temp.front();
        temp.pop();
        cout << order.second << " x " << order.first.name << " - Rp " << order.first.price * order.second << endl;
        totalPrice += order.first.price * order.second;
    }
    cout << "=========================" << endl;
    cout << "Total Harga: Rp " << totalPrice << endl;
}

// Fungsi untuk proses pembayaran
bool processPayment(double totalPrice) {
    double payment;
    cout << "\nMasukkan jumlah pembayaran: Rp ";
    cin >> payment;

    if (payment >= totalPrice) {
        cout << "Pembayaran berhasil. Kembalian: Rp " << payment - totalPrice << endl;
        return true;
    } else {
        cout << "Pembayaran gagal, jumlah uang kurang." << endl;
        return false;
    }
}

// Fungsi untuk menghasilkan nomor antrian
int generateQueueNumber(queue<int>& queue) {
    static int queueNumber = 1;
    queue.push(queueNumber);
    return queueNumber++;
}

int main() {
    // Inisialisasi menu
    MenuItem menu[] = {
        {"Rice Bowl", 15000},
        {"Yamin Pangsit", 12000},
        {"Katsu", 18000},
        {"Penyet", 10000},
        {"Sate Ika", 5000}
    };

    // Queue untuk keranjang belanja dan antrian
    queue<pair<MenuItem, int>> cart;
    queue<int> orderQueue;

    int choice;
    bool ordering = true;

    while (ordering) {
        displayMenu();
        cout << "\nPilih menu (1-5) atau tekan 0 untuk selesai: ";
        cin >> choice;

        if (choice == 0) {
            break;
        } else if (choice >= 1 && choice <= 5) {
            int quantity;
            cout << "Masukkan jumlah: ";
            cin >> quantity;

            // Menambahkan pesanan ke keranjang
            addToCart(cart, menu[choice - 1], quantity);
            cout << "Pesanan ditambahkan ke keranjang." << endl;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }

    // Menampilkan keranjang dan total harga
    displayCart(cart);

    // Proses pembayaran
    double totalPrice = 0;
    queue<pair<MenuItem, int>> tempCart = cart;
    while (!tempCart.empty()) {
        totalPrice += tempCart.front().first.price * tempCart.front().second;
        tempCart.pop();
    }

    if (processPayment(totalPrice)) {
        // Setelah pembayaran berhasil, generate nomor antrian
        int queueNumber = generateQueueNumber(orderQueue);
        cout << "Nomor antrian Anda adalah: " << queueNumber << endl;
    } else {
        cout << "Pesanan dibatalkan karena pembayaran gagal." << endl;
    }

    return 0;
}
