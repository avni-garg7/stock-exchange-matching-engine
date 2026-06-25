#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

struct Order {
    string id;
    double price;
    int quantity;
    int time;
};

struct Trade {
    string buyer;
    string seller;
    int quantity;
    double price;
};

bool compareBuy(Order a, Order b) {
    if (a.price == b.price)
        return a.time < b.time;
    return a.price > b.price;
}

bool compareSell(Order a, Order b) {
    if (a.price == b.price)
        return a.time < b.time;
    return a.price < b.price;
}

int main() {

    vector<Order> buyOrders;
    vector<Order> sellOrders;
    vector<Trade> trades;

    int nBuy, nSell;
    int timer = 0;

    cout << "====================================\n";
    cout << "   STOCK EXCHANGE MATCHING ENGINE\n";
    cout << "====================================\n\n";

    // BUY ORDERS
    cout << "Number of BUY orders: ";
    cin >> nBuy;

    for (int i = 0; i < nBuy; i++) {
        Order temp;

        temp.id = "B" + to_string(i + 1);

        cout << "\nOrder " << temp.id << endl;

        cout << "Price: ";
        cin >> temp.price;

        cout << "Quantity: ";
        cin >> temp.quantity;

        temp.time = timer++;

        buyOrders.push_back(temp);
    }

    // SELL ORDERS
    cout << "\nNumber of SELL orders: ";
    cin >> nSell;

    for (int i = 0; i < nSell; i++) {
        Order temp;

        temp.id = "S" + to_string(i + 1);

        cout << "\nOrder " << temp.id << endl;

        cout << "Price: ";
        cin >> temp.price;

        cout << "Quantity: ";
        cin >> temp.quantity;

        temp.time = timer++;

        sellOrders.push_back(temp);
    }

    // CANCEL ORDER
    char choice;

    cout << "\nDo you want to cancel any order? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        string cancelID;

        cout << "Enter Order ID: ";
        cin >> cancelID;

        bool found = false;

        for(auto &o : buyOrders){
        if(o.id == cancelID){
            o.quantity = 0;
            found = true;
        }
    }

    for(auto &o : sellOrders){
        if(o.id == cancelID){
            o.quantity = 0;
            found = true;
        }
    }

    if(found)
        cout << "Order cancelled successfully.\n";
    else
        cout << "Invalid Order ID.\n";
    }

    // SORTING
    sort(buyOrders.begin(), buyOrders.end(), compareBuy);
    sort(sellOrders.begin(), sellOrders.end(), compareSell);

    cout << "\n====================================\n";
    cout << "       MATCHING ENGINE STARTED\n";
    cout << "====================================\n";

    bool tradeHappened = false;

    int totalVolume = 0;
    double totalTurnover = 0;

    for (size_t i = 0; i < buyOrders.size(); i++) {

        for (size_t j = 0; j < sellOrders.size(); j++) {

            if (buyOrders[i].quantity > 0 &&
                sellOrders[j].quantity > 0 &&
                buyOrders[i].price >= sellOrders[j].price) {

                int tradeQty =
                    min(buyOrders[i].quantity,
                        sellOrders[j].quantity);

                double tradePrice =
                    sellOrders[j].price;

                cout << "\nTRADE EXECUTED\n";
                cout << buyOrders[i].id
                     << " matched with "
                     << sellOrders[j].id
                     << " | Qty: "
                     << tradeQty
                     << " @ "
                     << tradePrice << endl;

                trades.push_back({
                    buyOrders[i].id,
                    sellOrders[j].id,
                    tradeQty,
                    tradePrice
                });

                buyOrders[i].quantity -= tradeQty;
                sellOrders[j].quantity -= tradeQty;

                totalVolume += tradeQty;
                totalTurnover += tradeQty * tradePrice;

                tradeHappened = true;
            }
        }
    }

    if (!tradeHappened) {
        cout << "\nNo trades executed.\n";
    }

    // TRADE HISTORY
    cout << "\n====================================\n";
    cout << "          TRADE HISTORY\n";
    cout << "====================================\n";

    for (auto t : trades) {
        cout << t.buyer
             << " bought from "
             << t.seller
             << " | Qty: "
             << t.quantity
             << " | Price: "
             << t.price
             << endl;
    }

    // MARKET STATISTICS
    cout << "\n====================================\n";
    cout << "         MARKET STATISTICS\n";
    cout << "====================================\n";

    cout << "Total Volume: "
         << totalVolume << endl;

    if (totalVolume != 0) {
        cout << fixed << setprecision(2);

        cout << "Average Trade Price: "
             << totalTurnover / totalVolume
             << endl;
    }

    // REMAINING ORDER BOOK
    cout << "\n====================================\n";
    cout << "      REMAINING BUY ORDERS\n";
    cout << "====================================\n";

    for (auto o : buyOrders) {
        if (o.quantity > 0) {
            cout << o.id
                 << " Price: "
                 << o.price
                 << " Qty: "
                 << o.quantity
                 << endl;
        }
    }

    cout << "\n====================================\n";
    cout << "     REMAINING SELL ORDERS\n";
    cout << "====================================\n";

    for (auto o : sellOrders) {
        if (o.quantity > 0) {
            cout << o.id
                 << " Price: "
                 << o.price
                 << " Qty: "
                 << o.quantity
                 << endl;
        }
    }

    // ORDER BOOK
    cout << "\n====================================\n";
    cout << "           ORDER BOOK\n";
    cout << "====================================\n";

    cout << "BUY SIDE\t\tSELL SIDE\n";

    size_t mx =
        max(buyOrders.size(),
            sellOrders.size());

    for (size_t i = 0; i < mx; i++) {

        if (i < buyOrders.size())
            cout << buyOrders[i].price
                 << "("
                 << buyOrders[i].quantity
                 << ")";
        else
            cout << "----";

        cout << "\t\t";

        if (i < sellOrders.size())
            cout << sellOrders[i].price
                 << "("
                 << sellOrders[i].quantity
                 << ")";
        else
            cout << "----";

        cout << endl;
    }

    // EXPORT CSV
    ofstream file("trades.csv");

    file << "Buyer,Seller,Quantity,Price\n";

    for (auto t : trades) {
        file << t.buyer << ","
             << t.seller << ","
             << t.quantity << ","
             << t.price << "\n";
    }

    file.close();

    cout << "\nTrade history saved to trades.csv\n";

    cout << "\n====================================\n";
    cout << "        PROGRAM COMPLETED\n";
    cout << "====================================\n";

    return 0;
}