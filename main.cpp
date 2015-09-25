#include <iostream>
#include <cstdlib>
#include <string>
#include "bigInt.h"
using namespace std;

//Naveen Paramesh, Zachary Zaloga, Carly Longo, Nick Hoffman



void displayMenu(int& choice){
  cout << "Pick the number of the operation you want to do:" << endl;
  cout << "1. Addition" << endl;
  cout << "2. Subtraction" << endl;
  cout << "3. Multiplication" << endl;
  cout << "4. Division" << endl;
  cout << "5. Exit Program" << endl;
  cin >> choice;
  return;
}

void receiveInput(bigInt& number1, bigInt& number2){
  cout << "Please enter in an integer value: ";
  cin >> number1;
  cout << "Please enter in another integer value: ";
  cin >> number2;
}


int main(){
  
  int choice = 0;
  
  bigInt int1;
  bigInt int2;
  
  while(choice != 5){
    displayMenu(choice);
    switch(choice){
      case 1:
       {
        receiveInput(int1, int2);
        cout << "\nThe addition of these two numbers is: " << endl;
        bigInt sum = int1 + int2;
        cout << sum << endl;
        int1.number.resize(0);
        int2.number.resize(0);
        break;
       }
      case 2:
      {
        receiveInput(int1, int2);
        cout <<"\nThe  difference of these two numbers is: ";
        bigInt difference = int1 - int2;
        cout << difference << endl;
        int1.number.resize(0);
        int2.number.resize(0);
      }
        break;
      case 3:
      {
        receiveInput(int1, int2);
        cout <<"\nThe  product of these two numbers is: ";
        bigInt product = int1 * int2;
        cout << product << endl;  
        int1.number.resize(0);
        int2.number.resize(0);
        
      }
    
        break;
      case 4:
      {
        receiveInput(int1, int2);
        cout <<"\nThe  double represented quotient of these two numbers is: ";
        double doub_quotient = int1.divideBigIntToDouble(int2);
        cout << doub_quotient << endl;
        cout <<"\nThe  integer represented quotient of these two numbers is: ";
        bigInt quotient = int1.divideBigInt(int2);
        cout << quotient << endl;
        int1.number.resize(0);
        int2.number.resize(0);
        
      }
    
        break;
      case 5:
      
        break;
      default:
        cout << "That's not a valid choice, please choose again!" << endl;
        break;
    }
    
  }
  

  return 0;
}
