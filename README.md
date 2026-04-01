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
| `memdump` | 6.1810 (2025) | [ ] | Memory Layout, C Pointers Alignment |
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
- **[2026-03-27] Environment Success:** Successfully interfaced VS Code with WSL2 and mapped the GDB debugger to QEMU's port 26000.
- **[2026-03-27] User Program Flow:** Understood that adding a user program requires modifying the `UPROGS` section in the `Makefile` to link the object files into the `fs.img`.
- **[2026-03-27] Exit Protocol:** Learned that every xv6 user program *must* call `exit()` to avoid executing undefined memory regions.
- [2026-03-30] **Defensive Programming:** Realized that `argc` must be checked *before* accessing `argv[1]` to prevent Segmentation Faults. Order of execution matters in low-level C.
- [2026-03-30] **System Call Evolution:** Observed that MIT 6.1810 (2025 Fall) uses `pause()` instead of the legacy `sleep()` system call, though the functional logic remains similar.
- [2026-03-30] **Build Dependencies:** Learned that `mkfs` requires a physical `README` file in the root directory to build the `fs.img`. Solved the dependency by creating a symbolic link.
- [2026-03-31] **IPC & Synchronization (pingpong):** Successfully implemented bidirectional communication using two pipes. 
- [2026-03-31] **Blocking I/O:** Learned that `read()` on a pipe blocks until data is available, which is a natural synchronization mechanism between parent and child processes.
- [2026-03-31] **File Descriptor Management:** Realized the importance of closing unused pipe ends to prevent resource leaks and potential deadlocks (though more critical in the upcoming `primes` lab).