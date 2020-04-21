using namespace std;
#include <iostream>
#include <sstream>

#include "calculadora.hpp"

void processa_linea(calculadora &c, string lin) {
// Pre: c = C, lin = LIN no conté comentaris
// Post: S'ha processat les accions de la línia LIN sobre la calculador C
  istringstream ss(lin);
  string primer;
  if (ss >> primer) { // La línia té un 1er element
    if (primer.size() == 1 and primer[0] >= 'a' and primer[0] <= 'z') {
      // La línea comença amb un caràcter que identifica una memòria de la calculadora
      char mem = primer[0];
      string segon;
      if (ss >> segon) { // La línia té un 2on element
        if (segon == "<<") { // Eliminem expressió de la memòria
          c.elimina(mem);
          cout << c.mostra(mem).infixa() << endl;
        }
        else if (segon == ">>") { // Mostrem l'expressió de la memòria
          cout << c.mostra(mem).infixa() << endl;
        }
        else if (segon == ">>>") { // Expandim l'expressió de la memòria
          cout << c.expandeix(mem).infixa() << endl;
        }
        else if (segon == "=") { // Guardem expressió a la memòria
          expressio e(false);
          e.llegir_infixa(ss);
          c.guarda(mem, e);
          cout << c.mostra(mem).infixa() << endl;
        }
        else { // No és cap cas especial, llavors la
          // línea és una expressió: La llegim i l'avaluem
          istringstream ss2(lin);
          expressio e(false);
          e.llegir_infixa(ss2);
          cout << c.avalua(e).infixa() << endl;          
        }
      } else { // La línia no té un 2on element: Avaluem la mèmòria
        cout << c.avalua(mem).infixa() << endl;
      }
    } else {
      // La línea és una expressió: La llegim i l'avaluem
      istringstream ss2(lin);
      expressio e(false);
      e.llegir_infixa(ss2);
      cout << c.avalua(e).infixa() << endl;
    }
  }
}


int main() {
  calculadora c;
  string lin; 
  while (getline(cin, lin)) { // Llegir línia d'entrada
    if (lin.find("//") == string::npos)
      processa_linea(c, lin); // No conté un comentari
    else
      cout << lin << endl; // Mostrem el comentari
  }
}
