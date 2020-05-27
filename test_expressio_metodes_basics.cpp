using namespace std;
#include <iostream>

#include "expressio.hpp"

// Aquest programa només valida si funcionen els mètodes
// arrel(), fe(), fd(), es_operand()

int main() {
  expressio expr1(token(false));
  cout << "F. arrel() " << expr1.arrel() << endl;
  cout << "F. es_operand() " << expr1.es_operand() << endl;

  expressio expr2(token(-45));
  cout << "-45. arrel() " << expr2.arrel() << endl;
  cout << "-45. es_operand() " << expr2.es_operand() << endl;

  expressio expr3(token("x2"));
  cout << "x2. arrel() " << expr3.arrel() << endl;
  cout << "x2. es_operand() " << expr3.es_operand() << endl;

  expressio expr4(token("not"), expressio(token(true)));
  cout << "not T. arrel() " << expr4.arrel() << endl;
  cout << "not T. es_operand() " << expr4.es_operand() << endl;
  cout << "not T. fe() " << expr4.fe().arrel() << endl;

  expressio expr5(token("or"), expr1, expr3);
  cout << "F or x2. arrel() " << expr5.arrel() << endl;
  cout << "F or x2. es_operand() " << expr5.es_operand() << endl;
  cout << "F or x2. fe() " << expr5.fe().arrel() << endl;
  cout << "F or x2. fd() " << expr5.fd().arrel() << endl;

  expressio expr6(expr5);
  cout << "F or x2. arrel() " << expr6.arrel() << endl;
  cout << "F or x2. es_operand() " << expr6.es_operand() << endl;
  cout << "F or x2. fe() " << expr6.fe().arrel() << endl;
  cout << "F or x2. fd() " << expr6.fd().arrel() << endl;

  expr4 = expr5;
  cout << "F or x2. arrel() " << expr4.arrel() << endl;
  cout << "F or x2. es_operand() " << expr4.es_operand() << endl;
  cout << "F or x2. fe() " << expr4.fe().arrel() << endl;
  cout << "F or x2. fd() " << expr4.fd().arrel() << endl;

/*expressio expr(token(false));
  string tipus;
  string sortida; 
  while (cin >> tipus) { // Llegir format d'entrada
    if (tipus == "//") {
      string s;
      getline(cin, s); // Llegir la resta del comentari
      cout << "//" << s << endl;
    } else {
      if (tipus == "INFIXA")
        expr.llegir_infixa(cin);
      else if (tipus == "POSTFIXA") 
        expr.llegir_postfixa(cin);

      cout << expr.arrel() << endl;
      cout << expr.es_operand() << endl;
      if (not expr.es_operand()) {
        cout << expr.fe().arrel() << endl;
        if (expr.arrel().es_operador_binari())
          cout << expr.fd().arrel() << endl;
      }
      cout << "----------\n";
    }
  }*/
}
