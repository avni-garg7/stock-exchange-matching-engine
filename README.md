# Stock Exchange Matching Engine

## Overview

A C++-based Stock Exchange Matching Engine that simulates buy and sell order matching using the **Price-Time Priority** algorithm. The engine executes trades automatically, maintains an order book, supports order cancellation, and exports trade history to a CSV file.

---

## Features

- Price-Time Priority matching
- Buy & Sell Order Book
- Partial order execution
- Order cancellation
- Trade history generation
- Market statistics
- CSV export (`trades.csv`)

---

## Technologies

- C++
- STL (Vector, Algorithm)
- File Handling

---

## Working

1. Enter buy and sell orders.
2. Sort orders based on price and time priority.
3. Match compatible orders.
4. Execute trades and update quantities.
5. Display remaining order book and market statistics.
6. Export trade history to `trades.csv`.

---

## Time Complexity

| Operation | Complexity |
|-----------|------------|
| Sorting | O(n log n) |
| Matching | O(n × m) |
| CSV Export | O(k) |

---

## Future Improvements

- Market and Limit Orders
- Order Modification
- Multiple Stock Support
- Multithreaded Matching
- GUI Dashboard
