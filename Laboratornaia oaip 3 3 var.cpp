#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct dish
{
    string name;
    string type;
    int price;
};

void AddDishToFile(const dish &dish)
{
    ofstream file1("menu.txt", ios::app);
    if (file1.is_open())
    {
        file1 << dish.name << "," << dish.type << "," << dish.price << endl;
        file1.close();
        cout << "Блюдо успешно добавлено." << endl;
    }
    else
    {
        cerr << "Не удалось открыть файл для записи." << endl;
    }
}

void SearchDishByName(const string& name)
{
    ifstream file2("menu.txt");
    if (file2.is_open())
    {
        string line;
        string line2;
        bool found = false;
        while (getline(file2, line))
        {
        	line2 = line;
            size_t pos = line.find(',');
            string fullname = line.substr(0, pos);
            if (fullname == name)
            {
                cout << "Найдено блюдо: " << line2 << endl;
                found = true;
                break;
            }
        }
        file2.close();
        if (!found)
        {
            cout << "Блюдо с таким названием не найдено." << endl;
        }
    }
    else
    {
        cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

void SortDishesByPrice() {
    ifstream file3_1("menu.txt");
    if (file3_1.is_open())
    {
        string lines[100];
        int count = 0;
        string line;
        while (getline(file3_1, line))
        {
            lines[count] = line;
            count++;
        }
        file3_1.close();
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                size_t pos1 = lines[j].find_last_of(',');
                size_t pos2 = lines[j + 1].find_last_of(',');
                int price1 = stod(lines[j].substr(pos1 + 1));
                int price2 = stod(lines[j + 1].substr(pos2 + 1));
                if (price1 < price2)
                {
                    swap(lines[j], lines[j + 1]);
                }
            }
        }
        ofstream file3_2("menu.txt");
        if (file3_2.is_open())
        {
            for (int i = 0; i < count; i++)
            {
            	file3_2 << lines[i] << endl;
            }
            file3_2.close();
            cout << "Блюда отсортированы по цене." << endl;
        }
        else
        {
            cerr << "Не удалось открыть файл для записи." << endl;
        }
    }
    else
    {
        cerr << "Не удалось открыть файл для чтения." << endl;
    }
}

void SortDishesByType() {
    ifstream file4_1("menu.txt");
    if (file4_1.is_open())
    {
        string lines[100];
        int count = 0;
        string line;
        while (getline(file4_1, line))
        {
            lines[count] = line;
            count++;
        }
        file4_1.close();
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
            	size_t pos1_1 = lines[j].find(',');
            	size_t pos2_1= lines[j].find_last_of(',');
            	string type1 = lines[j].substr(pos1_1 + 1, pos2_1 - pos1_1 - 1);

            	size_t pos1_2 = lines[j+1].find(',');
            	size_t pos2_2= lines[j+1].find_last_of(',');
            	string type2 = lines[j+1].substr(pos1_2 + 1, pos2_2 - pos1_2 - 1);

                if (type1 < type2)
                {
                    swap(lines[j], lines[j + 1]);
                }
            }
        }
        ofstream file4_2("menu.txt");
        if (file4_2.is_open())
        {
            for (int i = 0; i < count; i++)
            {
            	file4_2 << lines[i] << endl;
            }
            file4_2.close();
            cout << "Блюда отсортированы по типу." << endl;
        }
        else
        {
            cerr << "Не удалось открыть файл для записи." << endl;
        }
    }
    else
    {
        cerr << "Не удалось открыть файл для чтения." << endl;
    }
}

void outputDataByUserRequest() {
    ifstream file5("menu.txt");
    if (file5.is_open())
    {
        string line;
        int maxPrice;
        cout << "Введите максимальную цену: ";
        cin >> maxPrice;
        cout << "Блюда, цена которых не превышает " << maxPrice << ':' << endl;
        while (getline(file5, line))
        {
        	size_t pos = line.rfind(',');
        	size_t pos2 = line.find(',');
            int price = stod(line.substr(pos + 1));
            if (price <= maxPrice)
            {
            	string name = line.substr(0, pos2);
                string type = line.substr(line.find(',') + 1, pos - line.find(',') - 1);
                cout << "Название: " << name << ", Тип: " << type << ", Цена: " << price << endl;
            }
        }
        file5.close();
    }
    else
    {
        cout << "Не удалось открыть файл для чтения." << endl;
    }
}

int main()
{
	setlocale(LC_ALL, "rus");
    int choice;

    do {
        cout << "Меню:" << endl;
        cout << "1. Добавить блюдо" << endl;
        cout << "2. Поиск блюда по названию" << endl;
        cout << "3. Сортировать блюда по цене" << endl;
        cout << "4. Сортировать блюда по типу" << endl;
        cout << "5. Вывести все блюда до определённой цены" << endl;
        cout << "0. Выйти" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1:
            {
                cin.ignore();
                string newname, newtype;
                int newprice;
                cout << "Введите название блюда: ";
                getline(cin, newname);
                cout << "Введите тип блюда: ";
                getline(cin, newtype);
                cout << "Введите цену блюда: ";
                cin >> newprice;
                dish newdish = {newname, newtype, newprice};
                AddDishToFile(newdish);
                break;
            }
            case 2:
            {
                cin.ignore();
                string newname2;
                cout << "Введите название блюда для поиска: ";
                getline(cin, newname2);
                SearchDishByName(newname2);
                break;
            }
            case 3:
            {
                SortDishesByPrice();
                break;
            }
            case 4:
            {
            	SortDishesByType();
            	break;
            }
            case 5:
            {
            	outputDataByUserRequest();
            	break;
            }
            case 0:
            {
                cout << "Программа завершена." << endl;
                break;
            }
            default:
            {
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
