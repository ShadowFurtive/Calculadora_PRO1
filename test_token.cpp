#include <iostream>
#include <cstdlib>
#include "token.hpp"

using namespace std;

int main() {
  
  // Proves amb les operacions de 'token':
  // Crear tokens diferents i cridar a les consultores per comprovar si funcionen.

  token t1(3);
  cout << t1 << endl;
  cout << "És un operador unari: " << t1.es_operador_unari() << endl;
  cout << "És un operador binari: " << t1.es_operador_binari() << endl;
  cout << "És un operador commutatiu: " << t1.es_operador_commutatiu() << endl;
  cout << "És un valor booleà: " << t1.es_boolea() << endl;
  cout << "És un valor enter: " << t1.es_enter() << endl;
  cout << "És una variable: " << t1.es_variable() << endl;
  cout << "Valor enter: " << t1.to_int() << endl;
  cout << "Valor string: " << t1.to_string() << endl;
  cout << "Prioritat: " << t1.prioritat().first << " " << t1.prioritat().second << endl;
  cout << "=============================" << endl;

  token t2(true);
  cout << t2 << endl;
  cout << "És un operador unari: " << t2.es_operador_unari() << endl;
  cout << "És un operador binari: " << t2.es_operador_binari() << endl;
  cout << "És un operador commutatiu: " << t2.es_operador_commutatiu() << endl;
  cout << "És un valor booleà: " << t2.es_boolea() << endl;
  cout << "És un valor enter: " << t2.es_enter() << endl;
  cout << "És una variable: " << t2.es_variable() << endl;
  cout << "Valor booleà: " << t2.to_bool() << endl;
  cout << "Valor string: " << t2.to_string() << endl;
  cout << "Prioritat: " << t2.prioritat().first << " " << t2.prioritat().second << endl;
  cout << "=============================" << endl;

  token t3(false);
  cout << t3 << endl;
  cout << "És un operador unari: " << t3.es_operador_unari() << endl;
  cout << "És un operador binari: " << t3.es_operador_binari() << endl;
  cout << "És un operador commutatiu: " << t3.es_operador_commutatiu() << endl;
  cout << "És un valor booleà: " << t3.es_boolea() << endl;
  cout << "És un valor enter: " << t3.es_enter() << endl;
  cout << "És una variable: " << t3.es_variable() << endl;
  cout << "Valor booleà: " << t3.to_bool() << endl;
  cout << "Valor string: " << t3.to_string() << endl;
  cout << "Prioritat: " << t3.prioritat().first << " " << t3.prioritat().second << endl;
  cout << "=============================" << endl;

  string s4("x");
  token t4(s4);
  cout << t4 << endl;
  cout << "És un operador unari: " << t4.es_operador_unari() << endl;
  cout << "És un operador binari: " << t4.es_operador_binari() << endl;
  cout << "És un operador commutatiu: " << t4.es_operador_commutatiu() << endl;
  cout << "És un valor booleà: " << t4.es_boolea() << endl;
  cout << "És un valor enter: " << t4.es_enter() << endl;
  cout << "És una variable: " << t4.es_variable() << endl;
  cout << "Valor string: " << t4.to_string() << endl;
  cout << "Prioritat: " << t4.prioritat().first << " " << t4.prioritat().second << endl;
  cout << "=============================" << endl;

  string s5("x1");
  token t5(s5);
  cout << t5 << endl;
  cout << "És un operador unari: " << t5.es_operador_unari() << endl;
  cout << "És un operador binari: " << t5.es_operador_binari() << endl;
  cout << "És un operador commutatiu: " << t5.es_operador_commutatiu() << endl;
  cout << "És un valor booleà: " << t5.es_boolea() << endl;
  cout << "És un valor enter: " << t5.es_enter() << endl;
  cout << "És una variable: " << t5.es_variable() << endl;
  cout << "Valor string: " << t5.to_string() << endl;
  cout << "Prioritat: " << t5.prioritat().first << " " << t5.prioritat().second << endl;
  cout << "=============================" << endl;

  token t6(-459);
  cout << t6 << endl;
  cout << "És un operador unari: " << t6.es_operador_unari() << endl;
  cout << "És un operador binari: " << t6.es_operador_binari() << endl;
  cout << "És un operador commutatiu: " << t6.es_operador_commutatiu() << endl;
  cout << "És un valor booleà: " << t6.es_boolea() << endl;
  cout << "És un valor enter: " << t6.es_enter() << endl;
  cout << "És una variable: " << t6.es_variable() << endl;
  cout << "Valor string: " << t6.to_string() << endl;
  cout << "Prioritat: " << t6.prioritat().first << " " << t6.prioritat().second << endl;
  cout << "=============================" << endl;
  
  cout << t2 << " i " << t2 << " són iguals: " << (t2 == t2) << endl;
  cout << t2 << " i " << t3 << " són iguals: " << (t2 == t3) << endl;
  cout << t2 << " i " << t2 << " són diferents: " << (t2 != t2) << endl;
  cout << t2 << " i " << t3 << " són diferents: " << (t2 != t3) << endl;
  cout << "=============================" << endl;
  
  cout << t4 << " i x són iguals: " << (t4 == token("x")) << endl;
  cout << t4 << " i y són iguals: " << (t4 == token("y")) << endl;
  cout << t4 << " i x són diferents: " << (t4 != token("x")) << endl;
  cout << t4 << " i y són diferents: " << (t4 != token("y")) << endl;
  cout << "=============================" << endl;

  string s;
  bool primer = true;
  token tant;
  while (getline(cin, s)) {
    token t(s);
    cout << "TOKEN: " << t << endl;
    cout << "És un operador unari: " << t.es_operador_unari() << endl;
    cout << "És un operador binari: " << t.es_operador_binari() << endl;
    cout << "És un operador commutatiu: " << t.es_operador_commutatiu() << endl;
    cout << "És un valor booleà: " << t.es_boolea() << endl;
    cout << "És un valor enter: " << t.es_enter() << endl;
    cout << "És una variable: " << t.es_variable() << endl;
    cout << "Valor string: " << t.to_string() << endl;
    cout << "Prioritat: " << t.prioritat().first << " " << t.prioritat().second << endl;
    if (not primer) {
        cout << t << " i " << t << " són iguals: " << (t == t) << endl;
        cout << t << " i " << tant << " són iguals: " << (t == tant) << endl;
        cout << t << " i " << t << " són diferents: " << (t != t) << endl;
        cout << t << " i " << tant << " són diferents: " << (t != tant) << endl;
    }
    tant = t;
    primer = false;
    cout << "=============================" << endl;
  }
}
