# Round Robin CPU Scheduling Simulator (C Project)

This project simulates **Round Robin CPU scheduling** using a **queue-based approach** in C.  
It reads process data from an input file, applies time-sliced scheduling, and prints the execution order.

---

## 📂 Project Structure
```
.
|-- main.c        # Source code
|-- input.txt     # Input file containing process data
`-- README.md     # Project documentation
```

---

## ✨ Features
- Implements **Round Robin Scheduling**
- **Queue Data Structure** for managing processes
- Supports **idle CPU cycles** when no process is ready
- Reads process data from a **text file**
- Prints execution order with start and end times
- Marks process termination (`aborts`) when completed

---

## ▶️ Compilation & Execution

### Compile
```bash
gcc main.c -o scheduler
```

### Run
```bash
./scheduler
```

You will be prompted to enter the input file name.

---

## 📘 Input File Format
The first line specifies the total number of **time slots**.

Each subsequent line represents a process with:
```
ProcessName  StartingTime  RemainingTime
```

### Example (`processes.txt`)
```
TimeSlots=10
P1 0 3
P2 2 2
P3 4 1
```

---

## 🧪 Example Run
**Input File (`processes.txt`)**
```
TimeSlots=5
P1 0 2
P2 1 1
```

**Program Execution**
```
Enter file name or Ctrl+Z to exit:
----------------------------------
processes.txt
P1    (0-->1)
P2    (1-->2)        P2 aborts
P1    (2-->3)        P1 aborts
idle  (3-->4)
idle  (4-->5)
stop
```

---

## 🚀 Possible Improvements
- Allow custom **time quantum** instead of `1`
- Add support for **waiting time** and **turnaround time** calculation
- Visualize Gantt chart for scheduling
- Extend to **multi-core scheduling**

---

## 🛠️ Requirements
- A C compiler (e.g., GCC)
- Works on Linux, macOS, or Windows with `gcc`

---
