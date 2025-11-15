# Parallel-Differential-Equation-Solver
*A high-performance C++ implementation for solving PDEs using parallel computation.*

[![C++](https://img.shields.io/badge/Language-C%2B%2B11-blue.svg)]()
[![Parallel Computing](https://img.shields.io/badge/Parallel-Enabled-brightgreen.svg)]()
[![Python](https://img.shields.io/badge/Python-3.x-yellow.svg)]()
[![Plotting-matplotlib](https://img.shields.io/badge/Plots-matplotlib-orange.svg)]()
[![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)]()

---

## 🚀 Overview  
This project implements **parallel solvers** for classical partial differential equations (PDEs) such as:

- **Laplace's Equation**
- **Wave Equation**

Written in **C++ (with optional OpenMP)** for high performance and accompanied by **Python visualization scripts**, the repository demonstrates speed-ups using multi-core processors.

---

## 🔥 Features  
- ✔️ Fast parallel solver for **Laplace PDE** (`laplace.cpp`)  
- ✔️ Parallel solver for the **Wave Equation** (`wave.cpp`)  
- ✔️ Python plotting utilities (`plot.py`, `plotwave.py`)  
- ✔️ Sample output datasets (`slice_XY.dat`, `slice_XZ.dat`, `slice_YZ.dat`)  
- ✔️ Example rendered output (`laplace-outputs.jpeg`)  
- ✔️ Clean, modular structure  

---

## 📦 Requirements

### **C++ Requirements**
- C++11 compatible compiler (`g++`, `clang++`)
- Optional: **OpenMP** support (`-fopenmp`)

### **Python Requirements**
```bash
numpy
matplotlib
````

Install using:

```bash
pip install numpy matplotlib
```

---

## 🔧 Build Instructions

### **1️⃣ Clone the Repository**

```bash
git clone https://github.com/pipinstallaadit/Parallel-Differential-Equation-Solver.git
cd Parallel-Differential-Equation-Solver
```

### **2️⃣ Compile the PDE Solvers**

Laplace solver:

```bash
g++ -std=c++11 -O3 laplace.cpp -o laplace
# or with OpenMP
g++ -std=c++11 -O3 -fopenmp laplace.cpp -o laplace
```

Wave equation solver:

```bash
g++ -std=c++11 -O3 wave.cpp -o wave
# or with OpenMP
g++ -std=c++11 -O3 -fopenmp wave.cpp -o wave
```

---

## ▶️ Running the Solvers

```bash
./laplace
./wave
```

This generates `.dat` slice files such as:

* `slice_XY.dat`
* `slice_XZ.dat`
* `slice_YZ.dat`

---

## 🖼 Visualising Results

Use the Python scripts provided:

Laplace output:

```bash
python3 plot.py
```

Wave output:

```bash
python3 plotwave.py
```

The repository includes an example Laplace output image:
📁 `laplace-outputs.jpeg`

---

## 📁 Repository Structure

```
├── laplace.cpp               # Laplace PDE solver
├── wave.cpp                  # Wave equation solver
├── slice_XY.dat              # Sample output slice files
├── slice_XZ.dat
├── slice_YZ.dat
├── plot.py                   # Plot Laplace outputs
├── plotwave.py               # Plot wave equation results
├── laplace-outputs.jpeg      # Example Laplace solution visual
└── README.md                 # This documentation
```

---

## ⚙️ Customization

You can modify:

* Grid size
* Boundary conditions
* Iteration count
* Parallelization strategy (threads, loop chunking)
  inside the C++ source files.

---

## 👨‍💻 Authors

**Aadit Pujari**

**Krish Shah**

**Mudit Jain**


---

## 📄 License

This project is licensed under the **MIT License**.
Feel free to use, modify, and distribute.

---

## ⭐ Contributing

Contributions, issues, and pull requests are welcome!
If you improve performance or add a new PDE solver, feel free to submit a PR.


