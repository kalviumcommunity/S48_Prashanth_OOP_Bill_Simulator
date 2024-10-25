#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
    string name;
    float price;

public:
    Product(string productName = "", float productPrice = 0.0) : name(productName), price(productPrice) {}

    string getName() const { return name; }
    float getPrice() const { return price; }
};

class Item : public Product {
private:
    int quantity;
    static int totalItemsSold;

public:
    Item(string itemName = "", int itemQuantity = 0, float itemPrice = 0.0)
        : Product(itemName, itemPrice), quantity(itemQuantity) {
        totalItemsSold += itemQuantity;
    }

    ~Item() {}

    int getQuantity() const { return quantity; }

    void setQuantity(int itemQuantity) {
        if (itemQuantity >= 0) quantity = itemQuantity;
    }

    static int getTotalItemsSold() { return totalItemsSold; }

    float getTotalPrice() const { return quantity * price; }

    void displayItem() const {
        cout << name << " - Quantity: " << quantity << ", Price per unit: Rs" << price << endl;
    }
};

int Item::totalItemsSold = 0;

class IBillDisplay {
public:
    virtual void display() const = 0;
};

class Tax {
protected:
    float taxRate;

public:
    Tax(float rate = 0.1) : taxRate(rate) {}

    float calculateTax(float amount) const { return amount * taxRate; }
};

class Bill : public IBillDisplay, public Tax {
private:
    Item** items;
    int itemCount;
    int capacity;
    static int totalBillsGenerated;

public:
    Bill(int cap = 30) : itemCount(0), capacity(cap), Tax(0.1) {
        items = new Item*[capacity];
        totalBillsGenerated++;
    }

    ~Bill() {
        for (int i = 0; i < itemCount; ++i) delete items[i];
        delete[] items;
    }

    int getItemCount() const { return itemCount; }

    void addItem(const Item& item) {
        if (itemCount < capacity) {
            items[itemCount] = new Item(item);
            itemCount++;
        } else {
            cout << "Cannot add more items, bill is full!" << endl;
        }
    }

    float calculateTotal() const {
        float total = 0;
        for (int i = 0; i < itemCount; i++) {
            total += items[i]->getTotalPrice();
        }
        return total + calculateTax(total);
    }

    void display() const override {
        cout << "\nBill Details:" << endl;
        for (int i = 0; i < itemCount; i++) {
            items[i]->displayItem();
        }
        float total = calculateTotal();
        cout << "Total Amount with Tax: Rs" << total << endl;
    }

    static int getTotalBillsGenerated() { return totalBillsGenerated; }
};

int Bill::totalBillsGenerated = 0;

int main() {
    Bill bill;

    Item* menuItems[] = {
        new Item("Burger", 1, 55.00),
        new Item("Pizza", 1, 80.00),
        new Item("Fries", 1, 30.00),
        new Item("Pasta", 1, 70.00),
        new Item("Sandwich", 1, 40.00),
        new Item("Salad", 1, 50.00),
        new Item("Chicken Wings", 1, 100.00),
        new Item("Steak", 1, 250.00),
        new Item("Fish & Chips", 1, 150.00),
        new Item("Tacos", 1, 60.00),
        new Item("Nachos", 1, 45.00),
        new Item("Sushi", 1, 120.00),
        new Item("Ramen", 1, 110.00),
        new Item("Curry", 1, 90.00),
        new Item("Biryani", 1, 130.00),
        new Item("Dosa", 1, 40.00),
        new Item("Idli", 1, 20.00),
        new Item("Paneer Tikka", 1, 70.00),
        new Item("Chole Bhature", 1, 60.00),
        new Item("Gulab Jamun", 1, 30.00),
        new Item("Ice Cream", 1, 50.00),
        new Item("Brownie", 1, 60.00),
        new Item("Coffee", 1, 25.00),
        new Item("Tea", 1, 20.00)
    };

    int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);
    int choice, quantity;

    do {
        cout << "\nSelect an item to add to the bill:" << endl;
        for (int i = 0; i < menuSize; i++) {
            cout << i + 1 << ". " << menuItems[i]->getName() << " - Rs" << menuItems[i]->getPrice() << endl;
        }
        cout << menuSize + 1 << ". Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= menuSize) {
            cout << "Enter quantity: ";
            cin >> quantity;
            bill.addItem(Item(menuItems[choice - 1]->getName(), quantity, menuItems[choice - 1]->getPrice()));
        } else if (choice != menuSize + 1) {
            cout << "Invalid choice! Please select a valid option." << endl;
        }

    } while (choice != menuSize + 1);

    bill.display();
    cout << "\nTotal items sold: " << Item::getTotalItemsSold() << endl;
    cout << "Total bills generated: " << Bill::getTotalBillsGenerated() << endl;

    for (int i = 0; i < menuSize; i++) {
        delete menuItems[i];
    }

    return 0;
}
