# Nanograd: A C++ Implementation of Micrograd

This repository contains a C++ implementation of Micrograd, a minimal autograd engine designed for educational purposes. Inspired by Andrej Karpathy's Micrograd, Nanograd aims to provide a clear and concise understanding of backpropagation, the fundamental algorithm behind training neural networks.

## Features

- **Automatic Differentiation:** Nanograd automatically computes gradients of scalar-valued functions, enabling efficient backpropagation.
- **Simple and Understandable Code:** The codebase is intentionally kept minimal to focus on the core concepts of autograd and backpropagation.
- **Educational Focus:** Nanograd serves as a valuable learning resource for understanding the inner workings of automatic differentiation and neural network training.

## How it Works

Nanograd represents mathematical operations as a computational graph, where nodes represent values and edges represent operations. By traversing this graph in reverse order (backpropagation), the gradients of the output with respect to each input can be calculated.

## Usage

The `Value` class is the core building block of Nanograd. It encapsulates a numerical value and its associated gradient. You can perform arithmetic operations on `Value` objects, and Nanograd will automatically track the dependencies and compute gradients.

**Example:**

```cpp
#include "nanograd.h"

int main() {
    Value a(2.0, "a");
    Value b(3.0, "b");
    Value c = a * b;
    Value d = c.tanh();
    d.backward();

    cout << "d: " << d << endl;
    cout << "c: " << c << endl;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    return 0;
}
```

## Operators and Functions

Nanograd supports the following operators and functions:

- **Arithmetic Operators:** `+`, `-`, `*`, `/`, `-` (unary negation)
- **Power Operator:** `pow(float exponent)`
- **Activation Functions:** `tanh()`, `exp()`

## Contributing

Contributions to Nanograd are welcome! If you find any bugs or have suggestions for improvements, please feel free to open an issue or submit a pull request.

## Acknowledgments

- Andrej Karpathy for his original <b>Micrograd</b> implementation and inspiring this project.

## Disclaimer

Nanograd is primarily intended for educational purposes and may not be suitable for production use. It lacks the performance optimizations and features of more mature autograd libraries.
```
