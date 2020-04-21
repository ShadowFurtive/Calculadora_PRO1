using namespace std;
#include <iostream>

#include "expressio.hpp"

int main() {
  expressio expr(false);
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

      expr = expr.avalua();

      cin >> sortida;  // Llegir format de sortida.
      if (sortida == "INFIXA")
        cout << expr.infixa() << endl;
      else if (sortida == "POSTFIXA")
        cout << expr.postfixa() << endl;
      else if (sortida == "OPERANDS") {
        list<token> l = expr.operands();
        for(list<token>::const_iterator it = l.begin(); it != l.end(); it++)
          cout << *it << " ";
        cout << endl;
      } else if (sortida == "EXPANDEIX") {
        // EXPANDEIX llegeix un token i una 2a expressió infixa,
        // canvia els tokens de la 1a expressió per la 2a expressió
        // i l'expressió resultant l'avalua i la mostra infixa
        token t;
        cin >> t;
        expressio expr2(false);
        expr2.llegir_infixa(cin);
        expr = expr.expandeix(t, expr2).avalua();
        cout << expr.infixa() << endl;
      }
    }
  }
}
