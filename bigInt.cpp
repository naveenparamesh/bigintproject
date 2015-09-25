#include <iostream>
#include <string>
#include "bigInt.h"
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

// whenever the object of class bigInt is created, this constructor
// gets called because num_digits is given a default value of 0 if
// no value is actully given. The bigInt's vector is initialized to the size
// of the given number and its bool data member is set to false;
bigInt::bigInt(int num_digits): number(num_digits){
    negative = false;
}

//this is a constructor that takes in a a vector,representing the number
// and a boolean that's true if the number is negative or not
// the :number(0) is a member initialization list that initializes 
// the vector to the size 0 before it resizes the bigInt's vector to the given
// vector's size. It also sets the the bigInt's bool to the given bool
bigInt::bigInt(vector<int>& the_number, bool is_negative): number(0){
    number.resize(the_number.size());
    number = the_number;
    negative = is_negative;
}

//takes the given string, takes off the negative sign if necessary and 
// assigns each character of the string to an element of the vector
// this way the number that the user inputs gets loaded into a vector of ints
// where each element of the vector represents a digit of the number
void bigInt::setNum(string str_num){
    //if number given is negative, take off the '-' character so that 
    // the negative sign isn't loaded into the vector of ints
    if(str_num.at(0) == '-'){
        str_num = str_num.substr(1);// from one till the end
        negative = true;
    }
    else{
        negative = false;
    }
    
    int str_length = str_num.length();
    
    // allocates enough spaces in the vector to suit the string number
    if(str_length > number.size()){
        number.resize(str_length);
    }
    
    //break down each digit from the string and assign it into an element in the vector
    // so that the vector can have each digit of the number
    for(int i = 0; i < number.size(); i++){
        number.at(i) = str_num.at(i) - '0';//this -'0' turns char into an int
    }
}

// converts the vector of ints that represents the number and
// converts it into one big number that's in a string format and returns it
// as a string. This way overflow can never occur because a string can resize
// and allocate more memory whenever needed.
string bigInt::bigIntToValue(){
    string str_num = "";
    for(int i = 0; i < number.size(); i++){
        str_num += number.at(i) + '0';
    }
    if(number.size() > 1){
        for(int i = 0; i < number.size(); i++){
            if(i == number.size() - 1 && str_num.at(0) == '0'){
                str_num = "0";
            }
            else if(number.at(i) == 0){
                str_num = str_num.substr(1);
            }
            else { 
                break;
            }
        }
    }
    
    return str_num;
}

// is a helper function that is called by a bigInt and takes in another
// bigInt, and it returns true if the bigInt's number that called this function is
// less than the given bigInt's number, false otherwise
// first checks if the digit all the way on the left is less that the given bigInt's number's
// left most digit. If it is this implies the given number is bigger, else if it isn't it
// returns false. If the left most digit of both numbers are the same then it runs through
// the rest of the digits and whenever the given bigInt's digit is bigger, it returns true,
// else it returns false
bool bigInt::isLessThan(bigInt& bInt){
        if(number.at(0) < bInt.number.at(0)){
          return true;
        }
        else if(number.at(0) > bInt.number.at(0)){
            return false;
        }
        else {
            for(int i = 0; i < number.size(); i++){
                if(number.at(i) < bInt.number.at(i)){
                    return true;
                }
            }
        }
    return false;
}

// overloaded addition operator that takes 2 bigInts and returns a new bigInt whose
// vector represents the sum. 
bigInt bigInt::operator+(bigInt& bInt){
    // this huge while loop just makes sure both the vectors of the bigInts are of the same
    // size, meaning they both have the same number of digits, which will make the actual
    // addition process easier. If they aren't the same size just keep on padding zeros
    // onto the left until they are the same size
    while(number.size() != bInt.number.size()){
        if(number.size() > bInt.number.size()){
            bInt.number.insert(bInt.number.begin(), 0);
        }
        else {
            number.insert(number.begin(), 0);
        }
    }
    
    vector<int> final_sum(number.size());// the vector that holds the final sum
    int carry = 0;// the carry variable
    int sum = 0;// the variable that holds the sum of each of the corresponding digits
    
     //if both negative just add them and makes sure the negative variable is true at the end
     // so that when the vector of ints get converted to a string the program knows if it should
     // append a negative sign in the beginning
    if(negative && bInt.negative){
        // run through the digits of the vectors starting all the way at the right,
        // meaning the one's digit and adding each corresponding digit from the vectors.
        // This algorithm just simulates the process of adding two numbers on paper.
        for(int i = number.size() - 1; i >= 0; i--){
        sum = (number.at(i) + bInt.number.at(i) + carry);
        final_sum.at(i) = sum % 10;
        carry = sum / 10;
        }
        
        if(carry == 1){
            final_sum.insert(final_sum.begin(), 1);
        }
        negative = true;
    }
    // else if just the top number is negative figure out which the the smaller value
    // and subtract the smaller value from the larger value. Calls the overloaded
    // subtraction operator in the process.
    else if(negative){
        if(isLessThan(bInt)){
            negative = false;
            return (bInt - *(this));   
        }
        else {//just changed this
            negative = true;
            bInt.negative = true;
            return (*(this) - bInt);  
        }
        
        
    }
    // else if just the bottom number is negative figure out which the the smaller value
    // and subtract the smaller value from the larger value. Calls the overloaded
    // subtraction operator in the process.
    else if(bInt.negative){
        if(isLessThan(bInt)){
            negative = true;
            return (bInt - *(this));  
        }
        else {
            negative = false;
            bInt.negative = false;
            return (*(this) - bInt);
        }
        
    }
    else {//means both are positive so you compute normally
         for(int i = number.size() - 1; i >= 0; i--){
            sum = (number.at(i) + bInt.number.at(i) + carry);
            final_sum.at(i) = sum % 10;
            carry = sum / 10;
         }
          if(carry == 1){
                final_sum.insert(final_sum.begin(), 1);
            }
    }
  // create a new bigInt by passing the final sum vector and and negative bool data memeber to 
  // represent if it is negative of not. Then return it.
  bigInt newBigInt(final_sum, negative);
  return newBigInt;
    
}

// helper function that helps to subtract the given bigInt from the bigInt that
// called this function. It stores the result of the operation in the given 
// vector. This function just simulates how one would subtract two numbers on
// paper. The bigger number is always on top before this function is even called
// and both the vectors have the same number of digits too which makes the process
// a lot easier.
void bigInt::sub(vector<int>& difference, bigInt& bInt){
    int carry_over = 0;
     for(int i = number.size() - 1; i >= 0; i--){
        if(number.at(i) < bInt.number.at(i)){
            if(carry_over == 0){
                difference.at(i) = (number.at(i) + 10) - bInt.number.at(i);
                carry_over = 1;
            }
            else {
                difference.at(i) = (number.at(i) + 9) - bInt.number.at(i);
                carry_over = 1;
            }
         }
         else {
             if(carry_over == 1){
                 if(number.at(i) == bInt.number.at(i)){
                     difference.at(i) = (number.at(i) + 9) - bInt.number.at(i);
                     carry_over = 1;
                 }
                 else {
                     difference.at(i) = (number.at(i) - 1) - bInt.number.at(i);
                     carry_over = 0;
                 }
                 
             }
             else {
                 difference.at(i) = number.at(i) - bInt.number.at(i);
             }
             
         }
    }
}

// this is the overloaded subtraction operator. It calculates the difference between
// the given bigInt and the bigInt that was to the left of the operator when called.
bigInt bigInt::operator-(bigInt& bInt){
    // pads 0s onto either vector until both the vectors have the same number of 
    // digits.
      while(number.size() != bInt.number.size()){
            if(number.size() > bInt.number.size()){
                bInt.number.insert(bInt.number.begin(), 0);
            }
            else {
                number.insert(number.begin(), 0);
            }
        }
        
    
    vector<int> difference(number.size());// vector that holds the difference btw the 2 vectors
    
    //if both numbers are negative then we figure out which one is smaller and
    // subtract the bigger number from the smaller number changing around the negative values
    // so that the final answer will have the proper sign.
    if(negative && bInt.negative){
          if(isLessThan(bInt)){
              negative = false;
              bInt.negative = false;
              return (bInt - *(this));  
          }
          else {
              negative = true;
              sub(difference, bInt);// actually calculates the difference
          }
    }
    // if the top number is negative then add the two numbers
    else if(negative){
        negative = true;
        bInt.negative = true;
         return (*(this) + bInt);
    }
    else if(bInt.negative){
        
        negative = false;
        bInt.negative = false;
        return (*(this) + bInt);
    }
    else {//means both are positive so you figure out which one is smaller and 
          //subtract the smaller from the bigger
        if(isLessThan(bInt)){
            negative = true;
            bInt.negative = true;
            return (bInt - *(this));  
        }
        else {
            sub(difference, bInt);
        }
        
    }
    
     bigInt newBigInt(difference, negative);// makes new bigInt representing difference and returns
     return newBigInt;
    
    
}

// overloaded multiplication operator that multiplies the 2 bigInts and 
// returns the product
bigInt bigInt::operator*(bigInt& bInt){
    // pads on zeros until both numbers have the same number of digits
    while(number.size() != bInt.number.size()){
            if(number.size() > bInt.number.size()){
                bInt.number.insert(bInt.number.begin(), 0);
            }
            else {
                number.insert(number.begin(), 0);
            }
        }
        
    int carry = 0;//carry over variable
    int a_product = 0;// product variable that hold product of each corresponding digit
    // this is a vector of a vector of ints, so a 2-D vector that holds all the numbers
    // for each row of the multiplication process. Meaning when you multiply 2 numbers that are
    // greater than one digit on paper, rows are formed and then you add all the rows together to get 
    // your product. So, each of those rows that are formed are stored a vector of ints in the 
    // nested vector. The outer vector whose elements store vectors, hold each of the rows so the
    // algorithm can actually iterate throught each row and add the rows together to acquire
    // the product
    vector< vector<int> > product_sums;
    if((negative && bInt.negative) || (!negative && !bInt.negative)){//if both positive or both negative
        negative = false;
        bInt.negative = false;
    }
    else if(negative || bInt.negative){
        negative = true;
        bInt.negative = true;
    }
    
    for(int i = number.size() - 1; i >= 0; i--){
        vector<int> a_sum(number.size());
        for(int j = number.size() - 1; j >= 0; j--){
            a_product = (bInt.number.at(i) * number.at(j)) + carry;
            a_sum.at(j) = a_product % 10;
            carry = a_product / 10;
        }
        
        if(carry != 0){
            a_sum.insert(a_sum.begin(), carry);
            carry = 0;
            a_product = 0;
        }
        // this if statement is logic that helps to calculate how many zeros gets padded onto the end of each
        // row of digits because when you add the rows together you want to pad on zeros to simulate
        // shifting each row over by one before actually adding them together
        if(i != (number.size() - 1)){
            int num_zeros = number.size() - (i + 1);
            for(int x = 0; x < num_zeros; x++){
                a_sum.push_back(0);
            }
            product_sums.push_back(a_sum);
        }
        else {
            product_sums.push_back(a_sum);
        }
    }
    bigInt newBigInt;
    // runs throught each row and adds them together. Does this by adding a generated bigInt
    // that is initialized with that row, and then added onto the previous row,
    // whose result is stored in newBigInt. After adding all the rows the newBigInt is returned
    for(int i = 0; i < product_sums.size(); i++){
        bigInt b_int(product_sums.at(i), negative); 
        newBigInt = newBigInt + b_int;
    }
    return newBigInt;
}

// Function is called by a bigInt and divides it by the given bigInt.
// It basically used a stringstream that takes in a string, which is what
// bigIntToValue() returns, the string of the value to be divided, and it converts
// it into the desired type, in this case a double. It does this by using the >> operator.
double bigInt::divideBigIntToDouble(bigInt& bInt){
    double num1, num2, quotient;
    stringstream convertor(bigIntToValue()); // this istringstream is a mechanism used to take in a string and convert to double
    convertor >> num1; // puts the converted value from string into double format, which is stored in variable num
    stringstream convertor2(bInt.bigIntToValue());// creates another one
    convertor2 >> num2;//stores in second variable;
    quotient = num1 / num2;// then simply divides and stores in final variable
    return quotient;// returns the result
}

// does what previous division function does except after calulating the result 
// it uses an extra stringstream to convert the result back into a string.
// Then it initializes a new bigInt with the number represented as a string
// and returns that bigInt
bigInt bigInt::divideBigInt(bigInt& bInt){
    long long num1, num2, quotient;
    string int_quotient = "";
    stringstream convertor(bigIntToValue()); // this stringstream is a mechanism used to take in a string and convert to double
    convertor >> num1;
    stringstream convertor2(bInt.bigIntToValue());
    convertor2 >> num2;
    quotient = num1 / num2;
    stringstream long_to_string_convertor;// extra string stream
    // this says give me whatever variable quotient hold and throw it into my stream
    long_to_string_convertor << quotient; 
    // then this says 
    int_quotient = long_to_string_convertor.str();
    bigInt b_int;
    b_int.setNum(int_quotient);
    return b_int;
   
}

//overrides normal cout
ostream& operator << (ostream& os, bigInt& bgInt){
  string str_num = ""; // 
  if(bgInt.negative){
    if(bgInt.bigIntToValue() == "0"){
      str_num = "0";
    }
    else {
      str_num = "-" + bgInt.bigIntToValue();
    }
    
  }
  else {
    str_num += bgInt.bigIntToValue();
  }
  os << str_num << endl;
  return os;
}

istream& operator >> (istream& is, bigInt& bgInt){
  string num;//a temp number to hold the input value
  is >> num;
  bgInt.setNum(num);//actually sets this input to the object bitset for it to store
  return is;
}