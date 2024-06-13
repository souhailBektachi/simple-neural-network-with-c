# Basic Neural Network Training in C

This project demonstrates a basic implementation of a neural network in C programming language. The neural network is trained using the MNIST dataset to recognize handwritten digits.

## Requirements

- C compiler (e.g., GCC)
- Make (for compilation)
- MNIST dataset
- Linux environment (recommended); if using Windows, WSL (Windows Subsystem for Linux) is recommended due to potential issues with floating-point accumulation.

## Compilation

Compile the project using `make`:

```bash
make
```

### Get the training dataset

```
kaggle datasets download -d oddrationale/mnist-in-csv
unzip mnist-in-csv.zip -d data
```
