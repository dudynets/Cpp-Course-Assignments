#include <iostream>

using namespace std;

class Client {
private:
    string id;
    string name;
    string address;
    string phone;
public:
    Client(): id(""), name(""), address(""), phone("") {}
    Client(string _id, string _name, string _address, string _phone): id(_id), name(_name), address(_address), phone(_phone) {}

    friend ostream &operator<<(ostream &os, Client &client) {
        os << "Client ID: " << client.id << endl;
        os << "Client name: " << client.name << endl;
        os << "Client address: " << client.address << endl;
        os << "Client phone: " << client.phone << endl;
        return os;
    }

    string getId() {
        return id;
    }

    string getName() {
        return name;
    }

    string getAddress() {
        return address;
    }

    string getPhone() {
        return phone;
    }
};

class Account {
private:
    Client client;
    string *accountNumbers;
    int balance;
public:
    Account(): client(), accountNumbers(new string[10]), balance(0) {}
    Account(Client _client, string *_accountNumbers, int _balance): client(_client), accountNumbers(_accountNumbers), balance(_balance) {}

    void deposit(int amount) {
        balance += amount;

        cout << "Money have been deposited successfully!" << endl;
    }

    void withdraw(int amount) {
        if (amount > balance) {
            cout << "Not enough money" << endl;
            return;
        }

        balance -= amount;

        cout << "Money have been withdrew successfully!" << endl;
    }

    Client getClient() {
        return client;
    }

    string *getAccountNumbers() {
        return accountNumbers;
    }

    int getBalance() const {
        return balance;
    }

    void printClientInfo() {
        cout << client;
        cout << "Account numbers: " << endl;
        for (int i = 0; i < 10; i++) {
            if (accountNumbers[i] == "") {
                continue;
            }
            cout << "    - " << accountNumbers[i] << endl;
        }
        cout << "Balance: " << balance << " UAH" << endl;
    }

    void showMenu() {
        cout << "ACCOUNT MENU:" << endl << endl;
        printClientInfo();

        cout << "\nChoose an option:" << endl;
        cout << "- 1. Deposit" << endl;
        cout << "- 2. Withdraw" << endl;
        cout << "- 3. Return" << endl;

        int choice;
        cout << "\nEnter your choice:\n";
        cout << "--> ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n------------------------\n\n";
                cout << "DEPOSIT MONEY:\n\n";

                int amount;
                cout << "Enter amount to deposit:\n";
                cout << "--> ";
                cin >> amount;

                cout << "\n------------------------\n\n";

                deposit(amount);

                cout << "\n------------------------\n\n";

                showMenu();

                break;
            }
            case 2: {
                cout << "\n------------------------\n\n";
                cout << "WITHDRAW MONEY:\n\n";

                int amount;
                cout << "Enter amount to withdraw:\n";
                cout << "--> ";
                cin >> amount;

                cout << "\n------------------------\n\n";

                withdraw(amount);

                cout << "\n------------------------\n\n";

                showMenu();

                break;
            }
            case 3: {
                cout << "\n------------------------\n\n";

                break;
            }
            default: {
                cout << "\n------------------------\n\n";

                cout << "Invalid choice!\n";

                cout << "\n------------------------\n\n";
                showMenu();
            }
        }
    }
};

class Bank {
private:
    Account *accounts;
    int count;
public:
    Bank(): accounts(new Account[100]), count(0) {}

    ~Bank() {
        delete[] accounts;
    }

    void addAccount(Account account) {
        accounts[count++] = account;
    }

    void printAllAccounts() {
         if (count == 0) {
            cout << "There are no accounts in the bank!" << endl;

            cout << "\n------------------------\n\n";
            return;
         }

        for (int i = 0; i < count; i++) {
            cout << "Account: #" << i + 1 << "\n\n";
            accounts[i].printClientInfo();

            if (i != count - 1) {
                cout << "\n------------------------\n\n";
            }
        }

        cout << "\n------------------------\n\n";
    }

    Account* findByClientId(string id) {
        for (int i = 0; i < count; i++) {
            if (accounts[i].getClient().getId() == id) {
                return &accounts[i];
            }
        }

        return nullptr;
    }

    Account* findByClientName(string name) {
        for (int i = 0; i < count; i++) {
            if (accounts[i].getClient().getName() == name) {
                return &accounts[i];
            }
        }

        return nullptr;
    }

    Account* findByClientAddress(string address) {
        for (int i = 0; i < count; i++) {
            if (accounts[i].getClient().getAddress() == address) {
                return &accounts[i];
            }
        }

        return nullptr;
    }

    void showMenu() {
        cout << "BANK MENU:" << endl << endl;

        cout << "Choose an option:" << endl;
        cout << "- 1. Add account" << endl;
        cout << "- 2. Find account by client ID" << endl;
        cout << "- 3. Find account by client name" << endl;
        cout << "- 4. Find account by client address" << endl;
        cout << "- 5. Print all accounts" << endl;
        cout << "- 6. Exit" << endl << endl;

        int choice;
        cout << "Enter your choice:\n";
        cout << "--> ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n------------------------\n\n";
                cout << "CREATING A NEW CLIENT:\n\n";

                string name, address, phone;
                cout << "1. Enter client name (DO NOT ENTER SPACES IN YOUR INPUT):\n";
                cout << "--> ";
                cin >> name;

                cout << "\n2. Enter client address (DO NOT ENTER SPACES IN YOUR INPUT):\n";
                cout << "--> ";
                cin >> address;

                cout << "\n3. Enter client phone (DO NOT ENTER SPACES IN YOUR INPUT):\n";
                cout << "--> ";
                cin >> phone;

                cout << "\n------------------------\n\n";

                cout << "Client has been created successfully!\n";

                cout << "\n------------------------\n\n";

                string id = "";
                for (int j = 0; j < 16; j++) {
                    id += to_string(rand() % 10);
                }

                Client client(id, name, address, phone);

                // Generating random account numbers
                string accountNumbers[10] = {};
                string number = "";
                for (int j = 0; j < 16; j++) {
                    number += to_string(rand() % 10);
                }
                accountNumbers[1] = number;

                Account account(client, accountNumbers, 0);
                addAccount(account);

                Account* newAccount = findByClientId(id);
                newAccount->showMenu();

                break;
            }
            case 2: {
                cout << "\n------------------------\n\n";
                cout << "FIND ACCOUNT BY CLIENT ID:\n\n";

                string id;
                cout << "Enter client ID:\n";
                cout << "--> ";
                cin >> id;

                Account* account = findByClientId(id);

                if (account != nullptr) {
                    cout << "\n------------------------\n\n";

                    cout << "Account has been found!\n";

                    cout << "\n------------------------\n\n";

                    account->showMenu();
                } else {
                    cout << "\n------------------------\n\n";

                    cout << "No account found!\n";

                    cout << "\n------------------------\n\n";
                    break;
                }

                break;
            }
            case 3: {
                cout << "\n------------------------\n\n";
                cout << "FIND ACCOUNT BY CLIENT NAME:\n\n";

                string name;
                cout << "Enter client name:\n";
                cout << "--> ";
                cin >> name;

                Account* account = findByClientName(name);

                if (account != nullptr) {
                    cout << "\n------------------------\n\n";

                    cout << "Account has been found!\n";

                    cout << "\n------------------------\n\n";

                    account->showMenu();
                } else {
                    cout << "\n------------------------\n\n";

                    cout << "No account found!\n";

                    cout << "\n------------------------\n\n";
                    break;
                }

                break;
            }
            case 4: {
                cout << "\n------------------------\n\n";
                cout << "FIND ACCOUNT BY CLIENT ADDRESS:\n\n";

                string address;
                cout << "Enter client address:\n";
                cout << "--> ";
                cin >> address;

                Account* account = findByClientAddress(address);

                if (account != nullptr) {
                    cout << "\n------------------------\n\n";

                    cout << "Account has been found!\n";

                    cout << "\n------------------------\n\n";

                    account->showMenu();
                } else {
                    cout << "\n------------------------\n\n";

                    cout << "No account found!\n";

                    cout << "\n------------------------\n\n";
                    break;
                }

                break;
            }
            case 5: {
                cout << "\n------------------------\n\n";
                cout << "ALL ACCOUNTS:\n\n";

                printAllAccounts();
                break;
            }
            case 6: {
                exit(0);
            }
            default: {
                cout << "\n------------------------\n\n";

                cout << "Invalid choice!\n";

                cout << "\n------------------------\n\n";
                showMenu();
            }
        }
    }
};

int main() {
    // Create a bank
    Bank bank;


    // Add some default accounts to the bank
    Client client1("001", "John", "London", "123456789");
    string accountNumbers1[10] = {"4716973291629728"};
    Account account1(client1, accountNumbers1, 1000);
    bank.addAccount(account1);

    Client client2("002", "Mary", "Paris", "987654321");
    string accountNumbers2[10] = {"4716973291629728"};
    Account account2(client2, accountNumbers2, 2000);
    bank.addAccount(account2);

    Client client3("003","Peter", "New York", "123987456");
    string accountNumbers3[10] = {"4716973291629728"};
    Account account3(client3, accountNumbers3, 3000);
    bank.addAccount(account3);

    Client client4("004","Jane", "Tokyo", "456123789");
    string accountNumbers4[10] = {"4716973291629728"};
    Account account4(client4, accountNumbers4, 4000);
    bank.addAccount(account4);

    Client client5("005","Oleksandr", "Kyiv", "789456123");
    string accountNumbers5[10] = {"4716973291629728"};
    Account account5(client5, accountNumbers5, 5000);
    bank.addAccount(account5);

    Client client6("006","Sara", "Berlin", "123789456");
    string accountNumbers6[10] = {"4716973291629728"};
    Account account6(client6, accountNumbers6, 6000);
    bank.addAccount(account6);

    Client client7("007","Paul", "Rome", "456789123");
    string accountNumbers7[10] = {"4716973291629728"};
    Account account7(client7, accountNumbers7, 7000);
    bank.addAccount(account7);

    Client client8("008","David", "Madrid", "789123456");
    string accountNumbers8[10] = {"4716973291629728"};
    Account account8(client8, accountNumbers8, 8000);
    bank.addAccount(account8);

    Client client9("009","Laura", "Barcelona", "123456789");
    string accountNumbers9[10] = {"4716973291629728"};
    Account account9(client9, accountNumbers9, 9000);
    bank.addAccount(account9);

    Client client10("010","Emily", "Milan", "987654321");
    string accountNumbers10[10] = {"4716973291629728"};
    Account account10(client10, accountNumbers10, 10000);
    bank.addAccount(account10);


    // Show the bank menu
    while (true) {
        bank.showMenu();
    }

    return 0;
}