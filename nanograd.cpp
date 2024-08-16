#include <iostream>
#include <math.h>
#include <set>
#include <vector>
#include <unordered_map>

using namespace std;

class Value {
private:
    float data;
    float grad;
    set<Value*> prev; // Store pointers to previous nodes
    string op;
    string label;

    // Function to perform topological sort
    void build_topo(vector<Value*>& topo, unordered_map<Value*, bool>& visited) {
        if (visited[this]) return;
        visited[this] = true;
        for (auto child : prev) {
            child->build_topo(topo, visited);
        }
        topo.push_back(this);
    }

public:
    Value(float data, const string& label = "") : data(data), grad(0.0), label(label) {}

    // Overloading the + operator
    Value operator+(const Value& other) const {
        Value out(data + other.data, label + "+" + other.label);
        out.prev.insert(const_cast<Value*>(this));
        out.prev.insert(const_cast<Value*>(&other));
        out.op = "+";

        // Correctly assign the _backward function using a lambda
        out._backward = [this, &other]() mutable {
            const_cast<Value*>(this)->grad += 1.0 * other.grad; // Use const_cast to modify grad
            const_cast<Value*>(&other)->grad += 1.0 * this->grad; // Use const_cast to modify grad
        };

        return out;
    }

    // Overloading the - operator
    Value operator-(const Value& other) const {
        Value out(data - other.data, label + "-" + other.label);
        out.prev.insert(const_cast<Value*>(this));
        out.prev.insert(const_cast<Value*>(&other));
        out.op = "-";
        return out;
    }

    // Overloading the * operator
    Value operator*(const Value& other) const {
        Value out(data * other.data, label + "*" + other.label);
        out.prev.insert(const_cast<Value*>(this));
        out.prev.insert(const_cast<Value*>(&other));
        out.op = "*";
        return out;
    }

    // Overloading the / operator
    Value operator/(const Value& other) const {
        Value out(data / other.data, label + "/" + other.label);
        out.prev.insert(const_cast<Value*>(this));
        out.prev.insert(const_cast<Value*>(&other));
        out.op = "/";
        return out;
    }

    // Overloading for the Unary operator
    Value operator-() const {
        Value out(-data, "-" + label);
        out.prev.insert(const_cast<Value*>(this));
        out.op = "neg";
        return out;
    }

    // Overloading the << operator
    friend ostream& operator<<(ostream& out, const Value& obj) {
        out << "Value(data = " << obj.data << ", grad = " << obj.grad << ")";
        return out;
    }

    // Power operator
    Value pow(float other) const {
        Value out(std::pow(data, other), label + "^" + to_string(other)); // Use std::pow
        out.prev.insert(const_cast<Value*>(this));
        out.op = "^";
        return out;
    }

    // tanh function
    Value tanh() const {
        float t = (std::exp(2 * data) - 1) / (std::exp(2 * data) + 1); // Use std::exp
        Value out(t, "tanh(" + label + ")");
        out.prev.insert(const_cast<Value*>(this));
        out.op = "tanh";
        return out;
    }

    // exp function
    Value exp() const {
        Value out(std::exp(data), "exp(" + label + ")"); // Use std::exp
        out.prev.insert(const_cast<Value*>(this));
        out.op = "exp";
        return out;
    }

    // Backward pass for backpropagation
    void backward() {
        vector<Value*> topo;
        unordered_map<Value*, bool> visited;
        build_topo(topo, visited);

        this->grad = 1.0;
        for (int i = topo.size() - 1; i >= 0; i--) {
            topo[i]->_backward();
        }
    }

private:
    // Internal backward function (to be overridden by subclasses)
    mutable std::function<void()> _backward = [](){}; 
};

// Example usage:
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
