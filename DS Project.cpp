#include <iostream>
#include <string>
#include <queue> 
using namespace std;

// Class to represent a Room
class Room {
public:
    int roomNumber;
    string status; // "Available" or "Occupied"
    
    Room()
    {
        roomNumber = 0;
        status = "";
    }
    Room(int roomNo, string Status) 
    {
        roomNumber = roomNo;
        status = Status;
    }
};

// Node for Binary Search Tree (BST) to store room details
class RoomNode {
public:
    Room room;
    RoomNode* left;
    RoomNode* right;

    RoomNode(Room r)
    {
        room = r;
        left = NULL;
        right = NULL;
    }

};

// Class to manage the Binary Search Tree (BST) for rooms
class RoomManager {
private:
    RoomNode* root;

    RoomNode* insert(RoomNode* curr, Room room) {
        RoomNode* parent = NULL;
        RoomNode* newNode = new RoomNode(room);
        if (curr == NULL) {
            return newNode;
        }
        RoomNode* temp = curr;
        while (temp != NULL) {
            parent = temp;
            if (room.roomNumber < temp->room.roomNumber) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }
        if (room.roomNumber < parent->room.roomNumber) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
        return curr;
    }

    RoomNode* search(RoomNode* node, int roomNumber) {
        if (node == NULL || node->room.roomNumber == roomNumber) {
            return node;
        }
        if (roomNumber < node->room.roomNumber) {
            return search(node->left, roomNumber);
        }
        return search(node->right, roomNumber);
    }

    void display(RoomNode* node) {
        if (node == NULL) {
            return;
        }
        display(node->left);
        cout << "Room " << node->room.roomNumber << ": " << node->room.status << endl;
        display(node->right);
    }

public:
    RoomManager()
    {
        root = NULL;
    }

    void addRoom(int roomNumber, string status) {
        root = insert(root, Room(roomNumber, status));
    }

    RoomNode* findRoom(int roomNumber) {
        return search(root, roomNumber);
    }

    void updateRoomStatus(int roomNumber, string status) {
        RoomNode* roomNode = findRoom(roomNumber);
        if (roomNode != NULL) {
            roomNode->room.status = status;
        }
        else {
            cout << "Room not found!\n";
        }
    }

    void displayRooms() {
        display(root);
    }
};

// Node for Linked List to store reservation history
class ReservationNode {
public:
    string customerName;
    int roomNumber;
    ReservationNode* next;

    ReservationNode(string custName, int roomNo)
    {
        customerName = custName;
        roomNumber = roomNo;
        next = NULL;
    }
};

// Class to manage reservations
class ReservationManager {
private:
    ReservationNode* head;

public:
    ReservationManager()
    {
        head = NULL;
    }

    void addReservation(string customerName, int roomNumber) {
        ReservationNode* newNode = new ReservationNode(customerName, roomNumber);
        newNode->next = head;
        head = newNode;
        cout << "Reservation added for " << customerName << " in room " << roomNumber << ".\n";
    }

    void displayReservations() {
        cout << "\n--- Reservation History ---\n";
        ReservationNode* current = head;
        while (current != NULL) {
            cout << "Customer: " << current->customerName << ", Room: " << current->roomNumber << endl;
            current = current->next;
        }
    }
};

// Class to manage the waiting queue
class WaitingQueue {
private:
    queue<pair<string, int>> waitingQueue;

public:
    void addToQueue(string customerName, int roomNumber) {
        waitingQueue.push({ customerName, roomNumber });
        cout << "Customer " << customerName << " added to the waiting queue for room " << roomNumber << ".\n";
    }

    void processQueue(RoomManager& roomManager, ReservationManager& reservationManager) {
        while (!waitingQueue.empty()) {
            string customerName = waitingQueue.front().first;
            int requestedRoom = waitingQueue.front().second;

            RoomNode* roomNode = roomManager.findRoom(requestedRoom);

            if (roomNode != NULL && roomNode->room.status == "Available") {
                roomManager.updateRoomStatus(requestedRoom, "Occupied");
                reservationManager.addReservation(customerName, requestedRoom);
                cout << "Customer " << customerName << " has been assigned room " << requestedRoom << " from the waiting queue.\n";
                waitingQueue.pop(); 
            }
            else {
                cout << "Room " << requestedRoom << " is still not available for customer " << customerName << ".\n";
                break;
            }
        }
    }

};

// Main function
int main() {
    RoomManager roomManager;
    ReservationManager reservationManager;
    WaitingQueue waitingQueue;

    // Preload some rooms into the system
    roomManager.addRoom(101, "Available");
    roomManager.addRoom(102, "Available");
    roomManager.addRoom(103, "Available");
    roomManager.addRoom(104, "Available");
    
    

    int choice;
    do {
        cout << "\n--- Hotel Management System ---\n";
        cout << "1. Display Rooms\n";
        cout << "2. Book a Room\n";
        cout << "3. Check Out\n";
        cout << "4. Display Reservation History\n";
        cout << "5. Add Customer to Waiting Queue\n";
        cout << "6. Handle Waiting Queue\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "\n--- Room Details ---\n";
            roomManager.displayRooms();
            break;
        }

        case 2: {
            int roomNumber;
            string customerName;
            cout << "Enter room number to book: ";
            cin >> roomNumber;
            cin.ignore(); 
            RoomNode* roomNode = roomManager.findRoom(roomNumber);

            if (roomNode != NULL && roomNode->room.status == "Available") {
                cout << "Enter customer name: ";
                getline(cin, customerName); 
                roomManager.updateRoomStatus(roomNumber, "Occupied");
                reservationManager.addReservation(customerName, roomNumber);
            }
            else {
                cout << "Room is either not available or does not exist!\n";
            }
            break;
        }


        case 3: {
            int roomNumber;
            cout << "Enter room number to check out: ";
            cin >> roomNumber;
            RoomNode* roomNode = roomManager.findRoom(roomNumber);

            if (roomNode != NULL && roomNode->room.status == "Occupied") {
                roomManager.updateRoomStatus(roomNumber, "Available");
                cout << "Room " << roomNumber << " is now available.\n";
            }
            else {
                cout << "Room is either not occupied or does not exist!\n";
            }
            break;
        }

        case 4: {
            reservationManager.displayReservations();
            break;
        }

        case 5: {
            string customerName;
            int roomNumber;
            cout << "Enter customer name: ";
            cin.ignore();
            getline(cin,customerName);
            cout << "Enter requested room number: ";
            cin >> roomNumber;
            waitingQueue.addToQueue(customerName, roomNumber);
            break;
        }

        case 6: {
            waitingQueue.processQueue(roomManager, reservationManager);
            break;
        }

        case 7: {
            cout << "Exiting the system. Goodbye!\n";
            break;
        }

        default: {
            cout << "Invalid choice. Please try again.\n";
        }
        }

    } while (choice != 7);

    return 0;
}

