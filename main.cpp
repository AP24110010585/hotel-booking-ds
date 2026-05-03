/*
 * Hotel Booking System
 * Data Structures Project
 * Demonstrates: Linked List, Stack, Queue, BST, Graph
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ============================================================
//  GRAPH - Room adjacency map (floor navigation)
// ============================================================
#define MAX_ROOMS 10

class Graph {
    int adjMatrix[MAX_ROOMS][MAX_ROOMS];
    int numRooms;
public:
    Graph(int n) : numRooms(n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMatrix[i][j] = 0;
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    void displayAdjacency() {
        cout << "\n--- Room Adjacency Map (Graph) ---\n";
        cout << "   ";
        for (int i = 0; i < numRooms; i++) cout << "R" << i+101 << " ";
        cout << "\n";
        for (int i = 0; i < numRooms; i++) {
            cout << "R" << i+101 << " ";
            for (int j = 0; j < numRooms; j++)
                cout << "  " << adjMatrix[i][j] << "  ";
            cout << "\n";
        }
    }

    void showNeighbors(int room) {
        int idx = room - 101;
        if (idx < 0 || idx >= numRooms) { cout << "Invalid room.\n"; return; }
        cout << "Rooms adjacent to " << room << ": ";
        bool found = false;
        for (int j = 0; j < numRooms; j++) {
            if (adjMatrix[idx][j]) { cout << j+101 << " "; found = true; }
        }
        if (!found) cout << "None";
        cout << "\n";
    }
};

// ============================================================
//  LINKED LIST - Guest records
// ============================================================
struct Guest {
    int guestId;
    string name;
    int roomNo;
    int nights;
    Guest* next;

    Guest(int id, string n, int room, int nts)
        : guestId(id), name(n), roomNo(room), nights(nts), next(nullptr) {}
};

class GuestList {
    Guest* head;
public:
    GuestList() : head(nullptr) {}

    void addGuest(int id, string name, int room, int nights) {
        Guest* g = new Guest(id, name, room, nights);
        g->next = head;
        head = g;
        cout << "Guest " << name << " (ID:" << id << ") checked into Room " << room << ".\n";
    }

    bool removeGuest(int id) {
        Guest* curr = head, *prev = nullptr;
        while (curr) {
            if (curr->guestId == id) {
                if (prev) prev->next = curr->next;
                else head = curr->next;
                cout << "Guest " << curr->name << " checked out from Room " << curr->roomNo << ".\n";
                delete curr;
                return true;
            }
            prev = curr; curr = curr->next;
        }
        cout << "Guest ID " << id << " not found.\n";
        return false;
    }

    Guest* findById(int id) {
        Guest* curr = head;
        while (curr) {
            if (curr->guestId == id) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    void displayAll() {
        if (!head) { cout << "No guests currently checked in.\n"; return; }
        cout << "\n--- Current Guests (Linked List) ---\n";
        cout << left << setw(8) << "ID" << setw(20) << "Name"
             << setw(8) << "Room" << setw(8) << "Nights" << "\n";
        cout << string(44, '-') << "\n";
        Guest* curr = head;
        while (curr) {
            cout << left << setw(8) << curr->guestId
                 << setw(20) << curr->name
                 << setw(8) << curr->roomNo
                 << setw(8) << curr->nights << "\n";
            curr = curr->next;
        }
    }

    ~GuestList() {
        Guest* curr = head;
        while (curr) { Guest* tmp = curr; curr = curr->next; delete tmp; }
    }
};

// ============================================================
//  STACK - Booking history (undo last action)
// ============================================================
struct BookingRecord {
    int guestId;
    string guestName;
    int roomNo;
    string action; // "CHECKIN" or "CHECKOUT"
};

class BookingStack {
    BookingRecord arr[100];
    int top;
public:
    BookingStack() : top(-1) {}

    void push(int id, string name, int room, string action) {
        if (top >= 99) { cout << "History full.\n"; return; }
        arr[++top] = {id, name, room, action};
    }

    BookingRecord pop() {
        if (top == -1) throw runtime_error("No history to undo.");
        return arr[top--];
    }

    void displayHistory() {
        if (top == -1) { cout << "No booking history.\n"; return; }
        cout << "\n--- Booking History (Stack, top first) ---\n";
        for (int i = top; i >= 0; i--) {
            cout << "[" << arr[i].action << "] Guest " << arr[i].guestName
                 << " (ID:" << arr[i].guestId << ") Room " << arr[i].roomNo << "\n";
        }
    }

    bool isEmpty() { return top == -1; }
};

// ============================================================
//  QUEUE - Waiting list for fully booked rooms
// ============================================================
struct WaitingGuest {
    int guestId;
    string name;
    int preferredRoom;
};

class WaitingQueue {
    WaitingGuest arr[50];
    int front, rear, size;
public:
    WaitingQueue() : front(0), rear(-1), size(0) {}

    void enqueue(int id, string name, int room) {
        if (size >= 50) { cout << "Waiting list full.\n"; return; }
        rear = (rear + 1) % 50;
        arr[rear] = {id, name, room};
        size++;
        cout << name << " added to waiting list for Room " << room << ". Position: " << size << "\n";
    }

    WaitingGuest dequeue() {
        if (size == 0) throw runtime_error("Waiting list is empty.");
        WaitingGuest g = arr[front];
        front = (front + 1) % 50;
        size--;
        return g;
    }

    void displayQueue() {
        if (size == 0) { cout << "Waiting list is empty.\n"; return; }
        cout << "\n--- Waiting List (Queue) ---\n";
        cout << left << setw(6) << "Pos" << setw(8) << "ID"
             << setw(20) << "Name" << setw(10) << "Pref. Room" << "\n";
        cout << string(44, '-') << "\n";
        for (int i = 0; i < size; i++) {
            int idx = (front + i) % 50;
            cout << left << setw(6) << i+1 << setw(8) << arr[idx].guestId
                 << setw(20) << arr[idx].name << setw(10) << arr[idx].preferredRoom << "\n";
        }
    }

    bool isEmpty() { return size == 0; }
    int getSize() { return size; }
};

// ============================================================
//  BST - Fast guest search by ID
// ============================================================
struct BSTNode {
    int guestId;
    string name;
    int roomNo;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int id, string n, int r) : guestId(id), name(n), roomNo(r), left(nullptr), right(nullptr) {}
};

class GuestBST {
    BSTNode* root;

    BSTNode* insert(BSTNode* node, int id, string name, int room) {
        if (!node) return new BSTNode(id, name, room);
        if (id < node->guestId) node->left = insert(node->left, id, name, room);
        else if (id > node->guestId) node->right = insert(node->right, id, name, room);
        return node;
    }

    BSTNode* search(BSTNode* node, int id) {
        if (!node || node->guestId == id) return node;
        if (id < node->guestId) return search(node->left, id);
        return search(node->right, id);
    }

    BSTNode* minNode(BSTNode* node) {
        while (node->left) node = node->left;
        return node;
    }

    BSTNode* deleteNode(BSTNode* node, int id) {
        if (!node) return nullptr;
        if (id < node->guestId) node->left = deleteNode(node->left, id);
        else if (id > node->guestId) node->right = deleteNode(node->right, id);
        else {
            if (!node->left) { BSTNode* t = node->right; delete node; return t; }
            if (!node->right) { BSTNode* t = node->left; delete node; return t; }
            BSTNode* succ = minNode(node->right);
            node->guestId = succ->guestId;
            node->name = succ->name;
            node->roomNo = succ->roomNo;
            node->right = deleteNode(node->right, succ->guestId);
        }
        return node;
    }

    void inorder(BSTNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << "  ID:" << node->guestId << " | " << node->name << " | Room " << node->roomNo << "\n";
        inorder(node->right);
    }

public:
    GuestBST() : root(nullptr) {}

    void insert(int id, string name, int room) { root = insert(root, id, name, room); }

    void searchGuest(int id) {
        BSTNode* res = search(root, id);
        if (res) cout << "Found -> ID:" << res->guestId << " | " << res->name << " | Room " << res->roomNo << "\n";
        else cout << "Guest ID " << id << " not found in BST.\n";
    }

    void remove(int id) { root = deleteNode(root, id); }

    void displayInorder() {
        cout << "\n--- BST Guest Index (Sorted by ID) ---\n";
        if (!root) { cout << "  (empty)\n"; return; }
        inorder(root);
    }
};

// ============================================================
//  ARRAY - Room availability tracker
// ============================================================
class RoomArray {
    bool rooms[10]; // true = available, false = booked
    int roomNos[10];
public:
    RoomArray() {
        for (int i = 0; i < 10; i++) {
            rooms[i] = true;
            roomNos[i] = 101 + i;
        }
    }

    bool bookRoom(int roomNo) {
        int idx = roomNo - 101;
        if (idx < 0 || idx >= 10) return false;
        if (!rooms[idx]) return false;
        rooms[idx] = false;
        return true;
    }

    void freeRoom(int roomNo) {
        int idx = roomNo - 101;
        if (idx >= 0 && idx < 10) rooms[idx] = true;
    }

    bool isAvailable(int roomNo) {
        int idx = roomNo - 101;
        return (idx >= 0 && idx < 10) && rooms[idx];
    }

    int firstAvailable() {
        for (int i = 0; i < 10; i++) if (rooms[i]) return roomNos[i];
        return -1;
    }

    void displayRooms() {
        cout << "\n--- Room Availability (Array) ---\n";
        for (int i = 0; i < 10; i++) {
            cout << "Room " << roomNos[i] << ": " << (rooms[i] ? "[AVAILABLE]" : "[BOOKED   ]");
            if ((i+1) % 2 == 0) cout << "\n";
            else cout << "   ";
        }
        cout << "\n";
    }
};

// ============================================================
//  MAIN MENU
// ============================================================
int nextId = 1001;

void printMenu() {
    cout << "\n========== HOTEL BOOKING SYSTEM ==========\n";
    cout << "  [1] Check In Guest\n";
    cout << "  [2] Check Out Guest\n";
    cout << "  [3] Add to Waiting List\n";
    cout << "  [4] Process Next Waiting Guest\n";
    cout << "  [5] Search Guest by ID (BST)\n";
    cout << "  [6] View All Current Guests\n";
    cout << "  [7] View Waiting List\n";
    cout << "  [8] View Booking History\n";
    cout << "  [9] View Room Availability\n";
    cout << "  [10] View Room Adjacency Map\n";
    cout << "  [11] View Neighboring Rooms\n";
    cout << "  [12] Undo Last Action\n";
    cout << "  [0] Exit\n";
    cout << "===========================================\n";
    cout << "Enter choice: ";
}

int main() {
    GuestList guestList;
    BookingStack history;
    WaitingQueue waitList;
    GuestBST bst;
    RoomArray rooms;

    // Build graph: rooms 101-110 connected in a corridor
    Graph floorMap(10);
    for (int i = 0; i < 9; i++) floorMap.addEdge(i, i+1);
    // Some cross-connections (opposite rooms)
    floorMap.addEdge(0, 5); floorMap.addEdge(1, 6); floorMap.addEdge(2, 7);

    int choice;
    cout << "Welcome to Hotel DS!\n";

    do {
        printMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            // Check In
            string name;
            int roomNo, nights;
            cout << "Guest Name: "; getline(cin, name);
            cout << "Room No (101-110): "; cin >> roomNo;
            cout << "Number of nights: "; cin >> nights;
            cin.ignore();

            if (!rooms.isAvailable(roomNo)) {
                cout << "Room " << roomNo << " is not available!\n";
            } else {
                int id = nextId++;
                rooms.bookRoom(roomNo);
                guestList.addGuest(id, name, roomNo, nights);
                bst.insert(id, name, roomNo);
                history.push(id, name, roomNo, "CHECKIN");
            }

        } else if (choice == 2) {
            // Check Out
            int id;
            cout << "Enter Guest ID: "; cin >> id;
            cin.ignore();
            auto* g = guestList.findById(id);
            if (g) {
                rooms.freeRoom(g->roomNo);
                history.push(g->guestId, g->name, g->roomNo, "CHECKOUT");
                bst.remove(g->guestId);
                guestList.removeGuest(id);
            }

        } else if (choice == 3) {
            // Add to waiting list
            string name; int roomNo;
            cout << "Guest Name: "; getline(cin, name);
            cout << "Preferred Room (101-110): "; cin >> roomNo;
            cin.ignore();
            int id = nextId++;
            waitList.enqueue(id, name, roomNo);

        } else if (choice == 4) {
            // Process waiting guest
            if (waitList.isEmpty()) { cout << "No one on waiting list.\n"; }
            else {
                WaitingGuest wg = waitList.dequeue();
                int avail = rooms.firstAvailable();
                if (avail == -1) {
                    cout << "Still no rooms available. Re-queuing...\n";
                    waitList.enqueue(wg.guestId, wg.name, wg.preferredRoom);
                } else {
                    int nights;
                    cout << "Assigning Room " << avail << " to " << wg.name << ". Nights: ";
                    cin >> nights; cin.ignore();
                    rooms.bookRoom(avail);
                    guestList.addGuest(wg.guestId, wg.name, avail, nights);
                    bst.insert(wg.guestId, wg.name, avail);
                    history.push(wg.guestId, wg.name, avail, "CHECKIN");
                }
            }

        } else if (choice == 5) {
            int id; cout << "Enter Guest ID to search: "; cin >> id; cin.ignore();
            bst.searchGuest(id);

        } else if (choice == 6) {
            guestList.displayAll();
            bst.displayInorder();

        } else if (choice == 7) {
            waitList.displayQueue();

        } else if (choice == 8) {
            history.displayHistory();

        } else if (choice == 9) {
            rooms.displayRooms();

        } else if (choice == 10) {
            floorMap.displayAdjacency();

        } else if (choice == 11) {
            int r; cout << "Enter room number (101-110): "; cin >> r; cin.ignore();
            floorMap.showNeighbors(r);

        } else if (choice == 12) {
            // Undo
            if (history.isEmpty()) { cout << "Nothing to undo.\n"; }
            else {
                BookingRecord last = history.pop();
                cout << "Undoing: [" << last.action << "] Guest " << last.guestName << " Room " << last.roomNo << "\n";
                if (last.action == "CHECKIN") {
                    rooms.freeRoom(last.roomNo);
                    bst.remove(last.guestId);
                    guestList.removeGuest(last.guestId);
                    cout << "Check-in reversed. Room " << last.roomNo << " is now available.\n";
                } else {
                    cout << "Checkout cannot be auto-reversed. Please re-check-in manually.\n";
                }
            }

        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    cout << "\nThank you for using Hotel DS. Goodbye!\n";
    return 0;
}
