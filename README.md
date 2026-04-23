# 🏨 Hotel Management System (C++)
### Data Structures & Algorithms Project - CUST

A comprehensive Hotel Management System implemented in C++ that demonstrates the practical application of multiple data structures to solve real-world resource management problems.

## 🚀 Overview
This system manages room bookings, customer reservations, and a priority waiting list. It ensures efficient room searching and systematic handling of customer check-ins and check-outs.

## 🛠️ Data Structures Used

* **Binary Search Tree (BST):** Used for **Room Management**. By storing rooms in a BST ordered by room number, the system achieves $O(\log n)$ average time complexity for searching and updating room availability.
* **Singly Linked List:** Used for **Reservation History**. This provides a dynamic way to store a growing list of past bookings without the overhead of array resizing.
* **Queue (STL):** Used for the **Waiting List**. It follows the FIFO (First-In, First-Out) principle to ensure that customers waiting for a specific room are served in the order they arrived.

## ✨ Key Features
1.  **Room Discovery:** Display all rooms and their current status (Available/Occupied).
2.  **Efficient Booking:** Real-time search for room numbers using BST logic.
3.  **Check-out System:** Updates room status back to "Available" and triggers waiting queue checks.
4.  **Waiting Queue:** Automatically handles customers when rooms are currently occupied.
5.  **History Tracking:** Maintains a running log of all successful reservations.

## 📂 Code Structure
* `Room` / `RoomNode`: Classes defining the room entity and BST structure.
* `RoomManager`: Logic for BST insertion, searching, and status updates.
* `ReservationManager`: Linked List logic to track customer names and assigned rooms.
* `WaitingQueue`: Queue-based logic to manage pending customer requests.

## 💻 How to Run
1.  Ensure you have a C++ compiler (like `g++`) installed.
2.  Compile the project:
    ```bash
    g++ "DS Project.cpp" -o HotelSystem
    ```
3.  Run the executable:
    ```bash
    ./HotelSystem
    ```

---
**Author:** Shaheer  
**Department:** Computer Science, CUST  
**Batch:** 233
