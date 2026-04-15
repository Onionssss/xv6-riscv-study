# xv6-riscv-study

This repository documents my journey through **MIT 6.1810 (Operating System Engineering)** and **MIT 6.S081 (Operating Systems)**. 
It captures my implementation of various OS components and my evolving understanding of RISC-V kernel-level programming.

---

## 🚀 Goals & Progress
"Everyday matters." My goal is to master the fundamentals of Operating Systems through rigorous hands-on lab implementation and version-to-version comparative analysis.

### 🛠️ Labs Status

#### **Lab 0: Environment Setup**
- [x] **WSL2 + Ubuntu + RISC-V Toolchain**
- [x] **VS Code Remote-WSL & GDB Integration**

#### **Lab 1: Xv6 and Unix utilities** (In Progress)
| Task | Source Course | Status | Key Concept |
| :--- | :---: | :---: | :--- |
| `sleep` | 6.1810 / 6.S081 | [x] | System Call: `pause()` (2025) / `sleep()` |
| `pingpong` | 6.S081 (Classic) | [x] | Pipe IPC, `fork()`, `read()`, `write()` |
| `primes` | 6.S081 (Classic) | [ ] | Concurrent Pipes, Recursive `fork()` |
| `sixfive` | 6.1810 (2025) | [ ] | File I/O, String Parsing |
| `memdump` | 6.1810 (2025) | [x] | Memory Layout, C Pointers Alignment |
| `find` | 6.S081 (Classic) | [ ] | Directory Traversal, `fstat()` |
| `find -exec` | 6.1810 (2025) | [ ] | Process Control: `fork()`, `exec()`, `wait()` |
| `xargs` | 6.S081 (Classic) | [ ] | Argument Parsing, `exec()` |

#### **Future Labs**
- [ ] **Lab: System calls**
- [ ] **Lab: Page tables**
- [ ] **Lab: Traps**
- [ ] **Lab: Copy-on-Write (COW)**
- [ ] **Lab: Network driver**
- [ ] **Lab: Lock**
- [ ] **Lab: File system**
- [ ] **Lab: mmap**
---

## 💻 Development Environment
- **Host OS:** Windows 11 (WSL2 / Ubuntu 24.04 LTS)
- **Architecture:** RISC-V (RV64)
- **Compiler:** `riscv64-unknown-elf-gcc`
- **Emulator:** `QEMU 7.0+`
- **Editor:** VS Code + C/C++ Extension Pack + GDB-multiarch

---

## 📖 Key Takeaways

### 🛠️ Infrastructure & Environment
* **Full-Stack Debugging:** Integrated **VS Code + WSL2 + QEMU**, mapping GDB to port 26000 for seamless kernel-level tracing.
* **xv6 Build Chain:** Mastered the `Makefile` (UPROGS) linking process and resolved `mkfs` dependencies for `fs.img` through symbolic links.

### 🧠 Systems Programming & Logic
* **Memory Manipulation (The "Lens" Theory):** Leveraged pointer casting to interpret raw memory as various data widths (`uint64`, `int`, `short`, `char`).
* **Double Indirection:** Implemented 2nd-level pointer resolution (pointer-to-pointer) to access dynamic strings in memory (`s` format).
* **Pointer Arithmetic:** Navigated complex memory topologies by calculating offsets based on type size and null-terminators (`strlen(p) + 1`).
* **Defensive & Robust Coding:**
    * Strictly validate `argc` before `argv` access to prevent Segfaults.
    * Enforce mandatory `exit()` calls to prevent execution of undefined memory.
    * Utilize block scope `{}` within `switch` cases to manage local variable lifetimes safely.

### 🔌 OS Concepts & IPC
* **Pipe Mechanics:** Implemented bidirectional IPC using dual pipes; utilized the **blocking** nature of `read()` as a natural synchronization primitive.
* **Resource Discipline:** Managed File Descriptors (FD) by proactively closing unused pipe ends to avoid leaks and potential deadlocks.
* **Syscall Adaptation:** Transitioned to modern **MIT 6.1810 (2025 Fall)** standards, substituting legacy `sleep()` with the `pause()` system call.