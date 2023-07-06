#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>

std::map<std::string, std::map<std::string, float>> drugInventory;

void AddDrug()
{
    std::string name;
    float price;
    int quantity;

    std::cout << "Enter drug name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter price: ";
    std::cin >> price;
    std::cout << "Enter quantity: ";
    std::cin >> quantity;

    drugInventory[name] = {{"price", price}, {"quantity", quantity}};

    std::cout << "Drug added successfully!" << std::endl;
}

void UpdateDrug()
{
    std::string name;

    std::cout << "Enter drug name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    auto it = drugInventory.find(name);
    if (it != drugInventory.end())
    {
        float price;
        int quantity;

        std::cout << "Enter new price: ";
        std::cin >> price;
        std::cout << "Enter new quantity: ";
        std::cin >> quantity;

        it->second["price"] = price;
        it->second["quantity"] = quantity;

        std::cout << "Drug information updated successfully!" << std::endl;
    }
    else
    {
        std::cout << "Drug not found in the inventory!" << std::endl;
    }
}

void ViewDrug()
{
    std::string name;

    std::cout << "Enter drug name (leave blank to view all drugs): ";
    std::cin.ignore();
    std::getline(std::cin, name);

    if (!name.empty())
    {
        auto it = drugInventory.find(name);
        if (it != drugInventory.end())
        {
            std::cout << "Drug Name: " << it->first << std::endl;
            std::cout << "Price: " << it->second["price"] << std::endl;
            std::cout << "Quantity: " << it->second["quantity"] << std::endl;
        }
        else
        {
            std::cout << "Drug not found in the inventory!" << std::endl;
        }
    }
    else
    {
        if (drugInventory.empty())
        {
            std::cout << "No drugs in the inventory!" << std::endl;
        }
        else
        {
            for (const auto &drug : drugInventory)
            {
                std::cout << "Drug Name: " << drug.first << std::endl;
                std::cout << "Price: " << drug.second["price"] << std::endl;
                std::cout << "Quantity: " << drug.second["quantity"] << std::endl;
            }
        }
    }
}

void RecordPurchase()
{
    std::string name;

    std::cout << "Enter drug name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    auto it = drugInventory.find(name);
    if (it != drugInventory.end())
    {
        int quantity;

        std::cout << "Enter quantity purchased: ";
        std::cin >> quantity;

        if (quantity <= it->second["quantity"])
        {
            it->second["quantity"] -= quantity;
            std::cout << "Purchase recorded successfully!" << std::endl;
        }
        else
        {
            std::cout << "Insufficient quantity in the inventory!" << std::endl;
        }
    }
    else
    {
        std::cout << "Drug not found in the inventory!" << std::endl;
    }
}

void SearchDrug()
{
    std::string keyword;

    std::cout << "Enter a keyword to search for drugs: ";
    std::cin.ignore();
    std::getline(std::cin, keyword);

    std::vector<std::string> searchResults;

    for (const auto &drug : drugInventory)
    {
        if (drug.first.find(keyword) != std::string::npos)
        {
            searchResults.push_back(drug.first);
        }
    }

    if (!searchResults.empty())
    {
        std::cout << "Search Results:" << std::endl;
        for (const auto &result : searchResults)
        {
            std::cout << result << std::endl;
        }
    }
    else
    {
        std::cout << "No drugs found matching the keyword." << std::endl;
    }
}

void DeleteDrug()
{
    std::string name;

    std::cout << "Enter drug name to delete: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    auto it = drugInventory.find(name);
    if (it != drugInventory.end())
    {
        drugInventory.erase(it);
        std::cout << name << " deleted from the inventory." << std::endl;
    }
    else
    {
        std::cout << "Drug not found in the inventory!" << std::endl;
    }
}

void SetExpirationDate()
{
    std::string name;

    std::cout << "Enter drug name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    auto it = drugInventory.find(name);
    if (it != drugInventory.end())
    {
        std::string expirationDate;

        std::cout << "Enter expiration date (YYYY-MM-DD): ";
        std::cin >> expirationDate;

        it->second["expiration_date"] = expirationDate;

        std::cout << "Expiration date set successfully!" << std::endl;
    }
    else
    {
        std::cout << "Drug not found in the inventory!" << std::endl;
    }
}

void CheckLowStockAlert()
{
    int threshold;

    std::cout << "Enter the minimum quantity threshold: ";
    std::cin >> threshold;

    std::vector<std::string> lowStockDrugs;

    for (const auto &drug : drugInventory)
    {
        if (drug.second["quantity"] <= threshold)
        {
            lowStockDrugs.push_back(drug.first);
        }
    }

    if (!lowStockDrugs.empty())
    {
        std::cout << "Low Stock Drugs:" << std::endl;
        for (const auto &drug : lowStockDrugs)
        {
            std::cout << drug << std::endl;
        }
    }
    else
    {
        std::cout << "No drugs are below the quantity threshold." << std::endl;
    }
}

void GenerateSalesReport()
{
    float totalSales = 0.0f;

    for (const auto &drug : drugInventory)
    {
        float price = drug.second["price"];
        int quantitySold = drug.second["quantity"] - drugInventory[drug.first]["quantity"];
        totalSales += price * quantitySold;
    }

    std::cout << "Total Sales: $" << std::fixed << std::setprecision(2) << totalSales << std::endl;

    std::vector<std::pair<std::string, std::map<std::string, float>>> sortedDrugs(drugInventory.begin(), drugInventory.end());
    std::sort(sortedDrugs.begin(), sortedDrugs.end(),
              [](const std::pair<std::string, std::map<std::string, float>> &a,
                 const std::pair<std::string, std::map<std::string, float>> &b) {
              return a.second["quantity"] > b.second["quantity"];
          });

    std::cout << "Top Selling Drugs:" << std::endl;
    for (int i = 0; i < std::min(static_cast<int>(sortedDrugs.size()), 5); i++)
    {
        std::cout << "Drug Name: " << sortedDrugs[i].first << std::endl;
        std::cout << "Quantity Sold: " << sortedDrugs[i].second["quantity"] - drugInventory[sortedDrugs[i].first]["quantity"] << std::endl;
    }
}

void UserAuthentication()
{
    std::string username;
    std::string password;

    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (username == "admin" && password == "password")
    {
        std::cout << "Authentication successful. Access granted." << std::endl;
    }
    else
    {
        std::cout << "Authentication failed. Access denied." << std::endl;
    }
}

void SaveData()
{
    std::ofstream file("drug_inventory.txt");

    if (file.is_open())
    {
        for (const auto &drug : drugInventory)
        {
            file << drug.first << " " << drug.second["price"] << " " << drug.second["quantity"] << std::endl;
        }

        std::cout << "Data saved successfully." << std::endl;
    }
    else
    {
        std::cout << "Failed to save data." << std::endl;
    }

    file.close();
}

void LoadData()
{
    std::ifstream file("drug_inventory.txt");

    if (file.is_open())
    {
        drugInventory.clear();

        std::string name;
        float price;
        int quantity;

        while (file >> name >> price >> quantity)
        {
            drugInventory[name] = {{"price", price}, {"quantity", quantity}};
        }

        std::cout << "Data loaded successfully." << std::endl;
    }
    else
    {
        std::cout << "No previous data found." << std::endl;
    }

    file.close();
}

void Menu()
{
    while (true)
    {
        std::cout << "\nPharmacy Management System" << std::endl;
        std::cout << "1. Add Drug" << std::endl;
        std::cout << "2. Update Drug Information" << std::endl;
        std::cout << "3. View Drug Information" << std::endl;
        std::cout << "4. Record Purchase" << std::endl;
        std::cout << "5. Search Drug" << std::endl;
        std::cout << "6. Delete Drug" << std::endl;
        std::cout << "7. Set Expiration Date" << std::endl;
        std::cout << "8. Check Low Stock Alert" << std::endl;
        std::cout << "9. Generate Sales Report" << std::endl;
        std::cout << "10. User Authentication" << std::endl;
        std::cout << "11. Save Data" << std::endl;
        std::cout << "12. Load Data" << std::endl;
        std::cout << "13. Quit" << std::endl;

        std::cout << "Enter your choice: ";
        int choice;
        std::cin >>choice;

        switch (choice)
        {
            case 1:
                AddDrug();
                break;
            case 2:
                UpdateDrug();
                break;
            case 3:
                ViewDrug();
                break;
            case 4:
                RecordPurchase();
                break;
            case 5:
                SearchDrug();
                break;
            case 6:
                DeleteDrug();
                break;
            case 7:
                SetExpirationDate();
                break;
            case 8:
                CheckLowStockAlert();
                break;
            case 9:
                GenerateSalesReport();
                break;
            case 10:
                UserAuthentication();
                break;
            case 11:
                SaveData();
                break;
            case 12:
                LoadData();
                break;
            case 13:
                return;
            default:
                std::cout << "Invalid choice. Try again!" << std::endl;
                break;
        }
    }
}

int main()
{
    Menu();
    return 0;
}
