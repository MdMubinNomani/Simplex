#include <iostream>
using namespace std;
int main() {
string name = "John doe";
int age = 56;
int age_married = 30;
string partner_name = "Jane Doe";
bool Married = true;
int years_married = age - age_married;
if (Married) {
cout << name;
cout << " has been married to ";
cout << partner_name;
cout << " for ";
cout << years_married;
cout << " years.\n";
}
else {
cout << name;
cout << " has not married yet.\n";
}
return 0;
}