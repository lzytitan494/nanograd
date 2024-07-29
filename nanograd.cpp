#include <iostream>
#include <math.h>
#include <set>
using namespace std;

class Value {
    private:
        float data;
        float grad;
        set<Value> prev = {};

    public:
        Value(float data, pair<Value, Value> children) {
            this->data = data;
            this->grad = 0.0;
            this->prev = {children.first, children.second};
        }

        // Overloading the + operator
        Value operator+(const Value& other) const {
            return Value(this->data + other.data, {});
        }

        // friends function to overload + for float + Value
        friend Value operator+(float left, const Value& right);

        // Overloading the * operator
        Value operator*(const Value& other) const {
            return Value(this->data * other.data);
        }

        // friends function to overload * for float * Value
        friend Value operator*(float left, const Value& right);

        // Overloading the - operator
        Value operator-(const Value& other) const {
            return Value(this->data - other.data);
        }

        // friends function to overload - for float - Value
        friend Value operator-(float left, const Value& right);


        // Overloading the / operator
        Value operator/(const Value& other) const {
            return Value(this->data / other.data);
        }

        // friends function to overload / for float / Value
        friend Value operator/(float left, const Value& right);

        // Overloading for the Unary operator
        Value operator-() const {
            return Value(-data); 
        }

        // Overloading the << operator
        friend ostream& operator<<(ostream& out, const Value& obj) {
            out << "Value(data = " << obj.data << ")";
            return out;
        }
};

// Non-member function to overload + for float + Value
Value operator+(float left, const Value& right) {
    return Value(left + right.data);
}

// Non-member function to overload - for float - Value
Value operator-(float left, const Value& right) {
    return Value(left - right.data);
}
// Non-member function to overload * for float * Value
Value operator*(float left, const Value& right) {
    return Value(left * right.data);
}
// Non-member function to overload / for float / Value
Value operator/(float left, const Value& right) {
    return Value(left / right.data);
}


int main() {
    Value a(10);
    Value b(20);

    Value c = a / b;
    // Value d = a - b;
    // Value e = c * d;
    cout << c << "\n";
}