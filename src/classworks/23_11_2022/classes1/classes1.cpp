#include <iostream>
#include <string>
using namespace std;

class Car
{
private:
    string brand;
    string model;
    int price;
    string color;

public:
    Car() : brand(""), model(""), price(0), color("") {}
    Car(string _brand, string _model, int _price, string _color) : brand(_brand), model(_model), price(_price), color(_color) {}

    void setBrand(string _brand)
    {
        brand = _brand;
    }

    void setModel(string _model)
    {
        model = _model;
    }

    void setPrice(int _price)
    {
        price = _price;
    }

    void setColor(string _color)
    {
        color = _color;
    }

    string getBrand()
    {
        return brand;
    }

    string getModel()
    {
        return model;
    }

    int getPrice()
    {
        return price;
    }

    string getColor()
    {
        return color;
    }

    void print()
    {
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Price: " << price << endl;
        cout << "Color: " << color << endl;
    }

    void promptAll()
    {
        promptBrand();
        promptModel();
        promptPrice();
        promptColor();
    }

    void promptBrand()
    {
        cout << "Enter the brand: " << endl;
        cout << "--> ";
        cin >> brand;
        cout << endl;
    }

    void promptModel()
    {
        cout << "Enter the model: " << endl;
        cout << "--> ";
        cin >> model;
        cout << endl;
    }

    void promptPrice()
    {
        cout << "Enter the price: " << endl;
        cout << "--> ";
        cin >> price;
        cout << endl;
    }

    void promptColor()
    {
        cout << "Enter the color: " << endl;
        cout << "--> ";
        cin >> color;
        cout << endl;
    }
};

void beautifulPrint(Car car);
int promptForNumberOfCars();
void search(string criteria, string query, Car *cars, int numberOfCars);

int main()
{
    int numberOfCars = promptForNumberOfCars();
    Car *cars = new Car[numberOfCars];

    cout << "################\n\n";

    for (int i = 0; i < numberOfCars; i++)
    {
        cars[i].promptAll();
        cout << "------------------\n\n";
    }

    for (int i = 0; i < numberOfCars; i++)
    {
        beautifulPrint(cars[i]);
    }

    // prompt for search criteria
    string searchCriteria;
    cout << "Enter the search criteria (brand, model, price, color): " << endl;
    cout << "--> ";
    cin >> searchCriteria;
    cout << endl;

    // prompt for search query
    string searchQuery;
    cout << "Enter the search query: " << endl;
    cout << "--> ";
    cin >> searchQuery;
    cout << endl;

    cout << "------------------\n\n";

    search(searchCriteria, searchQuery, cars, numberOfCars);

    return 0;
}

void beautifulPrint(Car car)
{
    car.print();
    cout << "\n------------------\n\n";
}

int promptForNumberOfCars()
{
    int numberOfCars;
    cout << "Enter the number of cars: " << endl;
    cout << "--> ";
    cin >> numberOfCars;
    cout << endl;

    return numberOfCars;
}

void search(string criteria, string query, Car *cars, int numberOfCars)
{
    bool found = false;
    cout << "# Found cars: " << endl;
    if (criteria == "brand")
    {
        for (int i = 0; i < numberOfCars; i++)
        {
            if (cars[i].getBrand() == query)
            {
                found = true;
                cars[i].print();
                cout << "\n------------------\n\n";
            }
        }
    }
    else if (criteria == "model")
    {
        for (int i = 0; i < numberOfCars; i++)
        {
            if (cars[i].getModel() == query)
            {
                found = true;
                cars[i].print();
                cout << "\n------------------\n\n";
            }
        }
    }
    else if (criteria == "price")
    {
        for (int i = 0; i < numberOfCars; i++)
        {
            if (cars[i].getPrice() == stoi(query))
            {
                found = true;
                cars[i].print();
                cout << "\n------------------\n\n";
            }
        }
    }
    else if (criteria == "color")
    {
        for (int i = 0; i < numberOfCars; i++)
        {
            if (cars[i].getColor() == query)
            {
                found = true;
                cars[i].print();
                cout << "\n------------------\n\n";
            }
        }
    }
    else
    {
        cout << "- Invalid search criteria!" << endl;
    }

    if (!found)
    {
        cout << "- No cars found!" << endl;
    }
}
