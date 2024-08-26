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
        cout << this->name << " - Quantity: " << this->quantity << ", Price per unit: Rs" << this->price << endl;
    }

    string getName() const {
        return this->name;
    }

    float getPrice() const {
        return this->price;
    }

    int getQuantity() const {
        return this->quantity;
    }
};

class Bill {
private:
    static const int MAX_ITEMS = 30;
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
        cout << "\nBill Details:" << endl;
        for (int i = 0; i < itemCount; i++) {
            items[i].displayItem();
        }
        float total = calculateTotal();
        cout << "Total Amount: Rs" << total << endl;
    }
};

int main() {
    Bill bill;

    Item menuItems[] = {
        Item("Burger", 1, 55.00),
        Item("Pizza", 1, 80.00),
        Item("Fries", 1, 30.00),
        Item("Pasta", 1, 70.00),
        Item("Sandwich", 1, 40.00),
        Item("Salad", 1, 50.00),
        Item("Chicken Wings", 1, 100.00),
        Item("Steak", 1, 250.00),
        Item("Fish & Chips", 1, 150.00),
        Item("Tacos", 1, 60.00),
        Item("Nachos", 1, 45.00),
        Item("Sushi", 1, 120.00),
        Item("Ramen", 1, 110.00),
        Item("Curry", 1, 90.00),
        Item("Biryani", 1, 130.00),
        Item("Dosa", 1, 40.00),
        Item("Idli", 1, 20.00),
        Item("Paneer Tikka", 1, 70.00),
        Item("Chole Bhature", 1, 60.00),
        Item("Gulab Jamun", 1, 30.00),
        Item("Ice Cream", 1, 50.00),
        Item("Brownie", 1, 60.00),
        Item("Coffee", 1, 25.00),
        Item("Tea", 1, 20.00)
    };

    int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);
    int choice, quantity;

    do {
        cout << "\nSelect an item to add to the bill:" << endl;
        for (int i = 0; i < menuSize; i++) {
            cout << i + 1 << ". " << menuItems[i].getName() << " - Rs" << menuItems[i].getPrice() << endl;
        }
        cout << menuSize + 1 << ". Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= menuSize) {
            cout << "Enter quantity: ";
            cin >> quantity;
            bill.addItem(Item(menuItems[choice - 1].getName(), quantity, menuItems[choice - 1].getPrice()));
        } else if (choice != menuSize + 1) {
            cout << "Invalid choice! Please select a valid option." << endl;
        }

    } while (choice != menuSize + 1);

    bill.displayBill();

    return 0;
}
