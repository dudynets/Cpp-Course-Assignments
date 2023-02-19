#include <iostream>
#include <iomanip> // required for setw

using namespace std;

class CartItem
{
private:
    string id;
    string title;
    int quantity;
    double price;

public:
    // Constructors
    CartItem() {}
    CartItem(const CartItem &item) : id(item.id), title(item.title), quantity(item.quantity), price(item.price) {}
    CartItem(string id, string title, int quantity, double price)
        : id(id), title(title), quantity(quantity), price(price) {}

    // Getters
    string getId() const { return id; }
    string getTitle() const { return title; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    // Friend function to overload the output operator
    friend ostream &operator<<(ostream &os, const CartItem &item)
    {
        // Define the width of each column
        const int idWidth = 11;
        const int titleWidth = 16;
        const int quantityWidth = 13;
        const int priceWidth = 7;

        // Print the item details with specified width
        os << left << setw(idWidth) << item.id << " "
           << left << setw(titleWidth) << item.title << " "
           << left << setw(quantityWidth) << item.quantity << " "
           << left << setw(priceWidth) << item.price << endl;

        return os;
    }
};

class Cart
{
private:
    CartItem *items;
    int count;

public:
    // Constructor and destructor
    Cart() : items(new CartItem[100]), count(0) {}
    ~Cart() { delete[] items; }

    // Add an item to the cart
    void addItem(const CartItem &item)
    {
        items[count++] = item;
        cout << "Item with id \"" << item.getId() << "\" and title \"" << item.getTitle() << "\" has been added.\n";
    }

    // Delete an item from the cart by ID
    void deleteItem(const string &id)
    {
        // Search for the item to delete.
        int indexToDelete = -1;
        for (int i = 0; i < count; i++)
        {
            if (items[i].getId() == id)
            {
                indexToDelete = i;
                break;
            }
        }

        // Save item title before deleting it
        string title = items[indexToDelete].getTitle();

        // If the item is found, delete it.
        if (indexToDelete != -1)
        {
            for (int i = indexToDelete; i < count - 1; i++)
            {
                items[i] = items[i + 1];
            }

            // Set the last item to default value
            items[count - 1] = CartItem();
            count--;
        }

        cout << "Item with id \"" << id << "\" and title \"" << title << "\" has been deleted.\n";
    }

    // List all items in the cart
    void listItems()
    {
        cout << "\nCART ITEMS:\n";
        cout << "-----------------------------------------------------------\n";
        cout << "ID:         Title:           Quantity:     Price:\n";
        cout << "-----------------------------------------------------------\n";
        for (int i = 0; i < count; i++)
        {
            cout << items[i];
        }
        cout << "\n";
    }
};

int main()
{
    // Create a new cart
    Cart *cart = new Cart();

    // Print a divider
    cout << "\n";

    // Add some items to the cart
    cart->addItem(CartItem("product1", "Milk", 2, 25));
    cart->addItem(CartItem("product2", "Bread", 1, 15));
    cart->addItem(CartItem("product3", "Eggs", 3, 30));
    cart->addItem(CartItem("product4", "Butter", 1, 50));
    cart->addItem(CartItem("product5", "Cheese", 1, 100));
    cart->addItem(CartItem("product6", "Yogurt", 2, 20));
    cart->addItem(CartItem("product7", "Chicken", 1, 200));

    // List all items in the cart before deleting an item
    cart->listItems();

    // Delete an item from the cart
    cart->deleteItem("product3");

    // List all items in the cart after deleting an item
    cart->listItems();

    // Add some more items
    cart->addItem(CartItem("product8", "Apple", 5, 10));
    cart->addItem(CartItem("product9", "Orange", 3, 15));

    // List all items in the cart after adding some more items
    cart->listItems();

    // Delete the cart
    delete cart;

    return 0;
}
