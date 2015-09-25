#include <iostream>
#include <vector>
using namespace std;

class bigInt{
 
 public:
    bigInt(int num_digits = 0);// default constructor
    bigInt(vector<int>& the_number, bool is_negative = false);
    void setNum(string num);
    string bigIntToValue();
    bigInt operator+(bigInt& bInt);
    bigInt operator-(bigInt& bInt);
    bigInt operator*(bigInt& bInt);
    friend ostream& operator<<(ostream& os, bigInt& bgInt);
    friend istream& operator>>(istream& is, bigInt& bgInt);
    double divideBigIntToDouble(bigInt& bInt);
    bigInt divideBigInt(bigInt& bInt);
    bool isLessThan(bigInt& bInt);
    vector<int> number;
    bool negative;
    void sub(vector<int>& difference, bigInt& bInt);
 
 private:
    
    
 
    
};