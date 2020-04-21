#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
using namespace std;

/* La classe "token" guarda un element (en anglès token) d'una expressió:
   Operadors: and, or, not, ==, !=, +, -­, *, /, %, **
   Operands: Números enters (tant positius com negatius), constants booleanes (T/F) i variables.*/

class token {
  public:
    token();
    // Pre: true
    // Post: Crea un token enter de valor 0

    token(int i);
    // Pre: i = I
    // Post: Crea un token a partir de l'enter I

    token(bool b);
    // Pre: b = B
    // Post: Crea un token a partir del booleà B

    token(string s);
    // Pre: s = S
    // Post: Crea un token a partir del string S (descriu un operador o un operand)

    token(const char s[]);
    // Pre: s = S
    // Post: Crea un token a partir del vector de caràcters S (descriu un operador o un operand)

    token(const token &t);
    // Pre: t = TK
    // Post: Crea un token a partir del token TK (constructor per còpia)

    token& operator=(const token &e);
    // Pre: t = TK
    // Post: Al p.i. se li ha assignat el token TK (operador assignació)

    ~token();
    // Pre: True
    // Post: S'ha destruït el token del p.i. (destructora)

    bool es_operador_unari() const;
    // Pre: true
    // Post: Indica si el p.i. és un operador unari

    bool es_operador_binari() const;
    // Pre: true
    // Post: Indica si el p.i. és un operador binari

    bool es_operador_commutatiu() const;
    // Pre: true
    // Post: Indica si el p.i. és un operador commutatiu

    bool es_boolea() const;
    // Pre: true
    // Post: Indica si el p.i. és una constant booleana 

    bool es_enter() const;
    // Pre: true
    // Post: Indica si el p.i. és una constant entera

    bool es_variable() const;
    // Pre: true
    // Post: Indica si el p.i. és una variable

    pair<int, bool> prioritat() const;
    // Pre: true
    // Post: Indica el nivell de prioritat a 'first' i si l'associativitat és d'esquerra a dreta a 'second' del p.i.
    //       Considerem que els operands tenen el màxim nivell de prioritat

    int to_int() const;
    // Pre: El p.i. és un token número enter
    // Post: Retorna el valor enter del p.i.

    bool to_bool() const;
    // Pre:  El p.i. és un token booleà
    // Post: Retorna el valor booleà true o false del p.i.

    string to_string() const;
    // Pre: true
    // Post: Retorna el valor del p.i. convertit en string

    bool operator==(const token &t) const;
    // Pre: t = TK
    // Post: Indica si el token del p.i. és igual al token TK

    bool operator!=(const token &t) const;
    // Pre: t = TK
    // Post: Indica si el token del p.i. és diferent al token TK

    friend istream& operator>>(istream& is, token &t);
    // Pre: El canal is conté un string amb un contingut d'un token TK
    // Post: t = TK

    friend ostream& operator<<(ostream& os, const token &t);
    // Pre: t = TK
    // Post: S'ha escrit al canal os el contingut del token TK

  private:
    // Cal definir els atributs i mètodes privats dins del fitxer .rep 
    #include "token.rep"
};

#endif
