#include <iostream>
#include <string>
using namespace std;

class Item {
private:
    string name;
    int quantity;
    float price;

public:
    Item(string itemName = "", int itemQuantity = 0, float itemPrice = 0.0) {
        this->name = itemName;
        this->quantity = itemQuantity;
        this->price = itemPrice;
    }

    float getTotalPrice() const {
        return this->quantity * this->price;
    }

    void displayItem() const {
        cout << this->name << " - Quantity: " << this->quantity << ", Price per unit: ₹" << this->price << endl;
    }
};

class Bill {
private: 
    static const int MAX_ITEMS = 10; 
    Item items[MAX_ITEMS];           
    int itemCount;                    

public:
    Bill() : itemCount(0) {}

    void addItem(const Item &item) {
        if (itemCount < MAX_ITEMS) {
            items[itemCount] = item;
            itemCount++;
        } else {
            cout << "Cannot add more items, bill is full!" << endl;
        }
    }

    float calculateTotal() const {
        float total = 0;
        for (int i = 0; i < itemCount; i++) {
            total += items[i].getTotalPrice();
        }
        return total;
    }

    void displayBill() const {
        cout << "Bill Details:" << endl;
        for (int i = 0; i < itemCount; i++) {
            items[i].displayItem();
        }
        float total = calculateTotal();
        cout << "Total Amount: ₹" << total << endl;
    }
};

int main() {
    Bill bill;
    
    Item item1("Burger", 10, 55.00);
    Item item2("Pizza", 5, 80.00);

    bill.addItem(item1);
    bill.addItem(item2);

    bill.displayBill();

    return 0;
}
