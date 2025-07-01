#include <iostream>
#include <iomanip>  // For formatting output
#include <string>
#include <cctype>   // For toupper()

using namespace std;

// Constants for pricing and bar weights
const double LARGE_PRICE = 27.99;    // Price per large bar (5 lbs)
const double MEDIUM_PRICE = 21.99;   // Price per medium bar (3 lbs)
const double SMALL_PRICE = 14.99;           // Price per small bar (1 lb)

char printMenu();
void printInventory(int l, int m, int s);
void processOrder(int& large, int& med, int& small);

int main() {
    // Initialize inventory counts
    int largeCt = 620;   // Starting large bars
    int medCt = 500;     // Starting medium bars
    int smallCt = 700;   // Starting small bars

    char choice = printMenu();
    while (choice != 'E') {
        switch (choice) {
        case 'F':  // Fill order
            processOrder(largeCt, medCt, smallCt);
            break;
        case 'P':  // Print inventory
            printInventory(largeCt, medCt, smallCt);
            break;
        default:
            cout << "WARNING: " << choice << " is an invalid choice. Command ignored\n\n";
            break;
        }
        choice = printMenu();
    }

    // Exit message
    cout << "Thank you for using my program!";
    return 0;
}

char printMenu() {
    char choice;
    cout << "\nChocolate Inventory System\n";
    cout << "F: Fill Order\n";
    cout << "P: Print Inventory\n";
    cout << "E: Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    choice = toupper(choice);  // Convert to uppercase

    while (choice != 'F' && choice != 'P' && choice != 'E') {
        cout << "Invalid choice. Please try again\n";
        cout << "Enter your choice: ";
        cin >> choice;
        choice = toupper(choice);
    }
    return choice;
}

// Prints current inventory levels
void printInventory(int l, int m, int s) {
    cout << "\nCurrent Inventory:\n";
    cout << "Large Bars (5 lb): " << l << endl;
    cout << "Medium Bars (3 lb): " << m << endl;
    cout << "Small Bars (1 lb): " << s << endl;
    cout << "Total pounds available: "
        << (l * 5 + m * 3 + s) << "\n\n";
}

// Process a customer order with multiple rounds if needed
void processOrder(int& large, int& med, int& small) {
    char repeat = 'Y';

    while (repeat == 'Y') {
        int pounds;
        cout << "\nEnter pounds of chocolate needed: ";
        cin >> pounds;

        // Temporary variables to preserve original inventory until order is confirmed
        int tempLarge = large;
        int tempMed = med;
        int tempSmall = small;

        int largeUsed = 0;
        int medUsed = 0;
        int smallUsed = 0;

        // Step 1: Use as many large bars as possible
        largeUsed = min(pounds / 5, tempLarge);
        pounds -= largeUsed * 5;
        tempLarge -= largeUsed;

        // Step 2: Use medium bars next
        medUsed = min(pounds / 3, tempMed);
        pounds -= medUsed * 3;
        tempMed -= medUsed;

        // Step 3: Use small bars for remaining
        smallUsed = min(pounds, tempSmall);
        pounds -= smallUsed;

        // Check if we filled the order
        if (pounds > 0) {
            cout << "ERROR: Not enough inventory to fulfill the order.\n";
            cout << "Remaining unfulfilled: " << pounds << " pound(s).\n\n";
        }
        else {
            // Update actual inventory
            large -= largeUsed;
            med -= medUsed;
            small -= smallUsed;

            // Calculate cost
            double totalCost = largeUsed * LARGE_PRICE + medUsed * MEDIUM_PRICE + smallUsed * SMALL_PRICE;

            // Print order summary
            cout << fixed << setprecision(2);
            cout << "\nOrder Summary:\n";
            cout << largeUsed << " Large bars x $" << LARGE_PRICE << " = $" << largeUsed * LARGE_PRICE << endl;
            cout << medUsed << " Medium bars x $" << MEDIUM_PRICE << " = $" << medUsed * MEDIUM_PRICE << endl;
            cout << smallUsed << " Small bars x $" << SMALL_PRICE << " = $" << smallUsed * SMALL_PRICE << endl;
            cout << "----------------------------------------------\n";
            cout << "Total Cost: $" << totalCost << "\n";

            // Print remaining inventory
            printInventory(large, med, small);
        }

        // Ask if user wants to place another order
        cout << "Would you like to place another order? (Y/N): ";
        cin >> repeat;
        repeat = toupper(repeat);
        while (repeat != 'Y' && repeat != 'N') {
            cout << "Invalid input. Enter Y or N: ";
            cin >> repeat;
            repeat = toupper(repeat);
        }
    }
}