#ifndef EXPRESSIO_HPP
#define EXPRESSIO_HPP

#include <list>
#include "token.hpp"
#include "arbreBin.hpp"
using namespace std;

/* La classe "expressio" permet guardar i avaluar una expressió aritmètica o booleana */

class expressio {
  public: 
  expressio(const token &t);
  // Pre: t = TK és un token operand
  // Post: Crea una expressió formada per operand TK

  expressio(const token &t, const expressio &e);
  // Pre: t = TK és un token operador unari, e = E
  // Post: Crea una expressió formada per l'operador unari TK aplicat a l'expressió E

  expressio(const token &t, const expressio &e1, const expressio &e2);
  // Pre: t = TK és un token operador binari, e1 = E1, e2 = E2
  // Post: Crea una expressió formada per l'operador binari TK aplicat a les expressions E1 i E2

  expressio(const expressio &e);
  // Pre: e = E
  // Post: Crea una expressió a partir de l'expressió E (constructor per còpia)

  expressio& operator=(const expressio &e);
  // Pre: e = E
  // Post: Al p.i. se li ha assignat l'expressió E (operador assignació)

  ~expressio();
  // Pre: True
  // Post: S'ha destruït l'expressió del p.i. (destructora)

  token arrel() const;
  // Pre: True
  // Post: Retorna el token de l'arrel del p.i.

  expressio fe() const;
  // Pre: L'arrel del p.i. és un operador
  // Post: Retorna l'expressió de l'esquerra del p.i.

  expressio fd() const;
  // Pre: L'arrel del p.i. és un operador binari
  // Post: Retorna l'expressió de la dreta del p.i.

  bool es_operand() const;
  // Pre: True
  // Post: Retorna si l'expressió del p.i. és un operand
  //   (o sigui que l'arbre binari que conté l'expressió és una fulla)

  list<token> operands() const;
  // Pre: True
  // Post: Retorna una llista dels tokens operands de l'expressió del p.i., d'esquerra a dreta

  void llegir_infixa(istream& is);
  // Pre: El canal is conté una expressió en notació infixa i sense errors.
  // Post: El p.i. conté l'expressió llegida del canal is.

  void llegir_postfixa(istream& is);
  // Pre: El canal is conté una expressió en notació postfixa i sense errors.
  // Post: El p.i. conté l'expressió llegida del canal is.

  string infixa() const;
  // Pre: True
  // Post: Retorna un string que conté l'expressió del p.i. amb notació infixa
  //   amb el mínim nombre de parèntesis, cada element separat amb un espai

  string postfixa() const;
  // Pre: True
  // Post: Retorna un string que conté l'expressió del p.i. amb notació postfixa,
  //   cada element separat amb un espai

  static expressio avalua_operador_unari(token op, expressio e);
  // Pre: op = OP és un operador unari, e = E
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre l'expressió E

  static expressio avalua_operador_boolea(token op, expressio e1, expressio e2);
  // Pre: op = OP és un operador binari booleà, e1 = E1, e2 = E2
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre les expressions E1 i E2

  static expressio avalua_operador_comparacio(token op, expressio e1, expressio e2);
  // Pre: op = OP és un operador binari de comparació, e1 = E1, e2 = E2
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre les expressions E1 i E2

  static expressio avalua_operador_aritmetic(token op, expressio e1, expressio e2);
  // Pre: op = OP és un operador binari aritmètic, e1 = E1, e2 = E2
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre les expressions E1 i E2

  expressio avalua() const;
  // Pre: True
  // Post: Retorna l'expressió resultant d'avaluar l'expressió del p.i. tot el que es pugui

  expressio expandeix(token t, const expressio &e) const;
  // Pre: t = TK és un token operand, e = E
  // Post: Retorna l'expressió resultant de canviar tots els tokens TK de l'expressió del p.i. per l'expressió E

  private:
    // Cal definir els atributs i mètodes privats dins del fitxer .rep 
    #include "expressio.rep"
};

#endif
