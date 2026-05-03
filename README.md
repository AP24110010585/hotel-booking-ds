# 🏨 Hotel Booking System — Data Structures Project

A **C++ console application** that simulates a hotel booking system using core Data Structures concepts. Built as part of the **Data Structures & Algorithms** course project.

---

## 📌 Data Structures Used

| # | Data Structure | Purpose in This Project |
|---|---------------|------------------------|
| 1 | **Array** | Room availability tracker (101–110) |
| 2 | **Singly Linked List** | Guest records — dynamic check-in/check-out |
| 3 | **Stack** | Booking history — undo last action |
| 4 | **Circular Queue** | Waiting list for fully booked rooms |
| 5 | **Binary Search Tree (BST)** | Fast guest lookup by ID |
| 6 | **Graph (Adjacency Matrix)** | Room/floor navigation map |

---

## 🗂️ Project Structure

```
hotel_booking/
│
├── main.cpp          # All DS implementations + main menu
└── README.md         # Project documentation
```

---

## ⚙️ How to Compile & Run

### Prerequisites
- GCC / G++ compiler (or any C++11-compatible compiler)

### Compile
```bash
g++ main.cpp -o hotel_booking
```

### Run
```bash
./hotel_booking        # Linux / Mac
hotel_booking.exe      # Windows
```

---

## 🔧 Features & Menu

```
[1]  Check In Guest              → Books a room; adds to Linked List, BST, updates Array
[2]  Check Out Guest             → Removes from Linked List & BST; frees room in Array
[3]  Add to Waiting List         → Enqueue into circular Queue
[4]  Process Next Waiting Guest  → Dequeue and assign next available room
[5]  Search Guest by ID (BST)    → O(log n) BST search
[6]  View All Current Guests     → Linked List traversal + BST inorder display
[7]  View Waiting List           → Queue display
[8]  View Booking History        → Stack display (most recent first)
[9]  View Room Availability      → Array display
[10] View Room Adjacency Map     → Graph adjacency matrix
[11] View Neighboring Rooms      → Graph neighbor lookup for a room
[12] Undo Last Action            → Stack pop → reverses last check-in
[0]  Exit
```

---

## 📊 Data Structure Details

### 1. Array — Room Availability
- Fixed array of 10 rooms (101–110)
- `O(1)` access to check/update room status
- Boolean flags: `true` = available, `false` = booked

### 2. Linked List — Guest Records
- Singly linked list with head pointer
- `O(1)` insertion at head
- `O(n)` search/delete by guest ID
- Dynamically grows as guests check in

### 3. Stack — Booking History (Undo)
- Array-based stack (capacity: 100)
- Each check-in/check-out pushes a `BookingRecord`
- Undo pops the last action and reverses it
- `O(1)` push and pop

### 4. Queue — Waiting List
- Circular array-based queue (capacity: 50)
- FIFO: first-come, first-served for room assignment
- `O(1)` enqueue and dequeue

### 5. BST — Guest Index
- Binary Search Tree keyed on Guest ID
- `O(log n)` average search time
- Inorder traversal prints guests sorted by ID
- Supports insert, search, and delete

### 6. Graph — Floor Navigation
- Adjacency matrix representation (10×10)
- Rooms 101–110 connected in a corridor (linear + cross connections)
- Supports neighbor lookup for any room

---

## 💡 Sample Run

```
Welcome to Hotel DS!

========== HOTEL BOOKING SYSTEM ==========
  [1] Check In Guest
  ...

Enter choice: 1
Guest Name: Ravi Kumar
Room No (101-110): 103
Number of nights: 2
Guest Ravi Kumar (ID:1001) checked into Room 103.

Enter choice: 5
Enter Guest ID to search: 1001
Found -> ID:1001 | Ravi Kumar | Room 103

Enter choice: 12
Undoing: [CHECKIN] Guest Ravi Kumar Room 103
Check-in reversed. Room 103 is now available.
```

---

## 🧑‍💻 Author

| Field | Info |
|-------|------|
| Name | Pranathi Appisetti |
| Reg No | AP24110010585 |
| Section | CSE-AA |
| Subject | Data Structures & Algorithms |

---

## 📝 How to Submit on GitHub

1. **Create a new repository** on [github.com](https://github.com)  
   - Name it: `hotel-booking-ds` (or any preferred name)  
   - Set visibility to **Public**

2. **Initialize and push** from your local machine:

```bash
# Navigate to your project folder
cd hotel_booking

# Initialize git
git init

# Add all files
git add .

# Commit
git commit -m "Initial commit: Hotel Booking System using DS"

# Link to your GitHub repo (replace YOUR_USERNAME)
git remote add origin https://github.com/YOUR_USERNAME/hotel-booking-ds.git

# Push
git branch -M main
git push -u origin main
```

3. ✅ Your project is live on GitHub!

---

## 📚 References

- Data Structures and Algorithm Analysis in C++ — Mark Allen Weiss
- Introduction to Algorithms — Cormen et al. (CLRS)
