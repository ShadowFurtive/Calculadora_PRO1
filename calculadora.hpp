#ifndef CALCULADORA_HPP
#define CALCULADORA_HPP

#include "expressio.hpp"
#include <vector>
using namespace std;

/* La classe "calculadora" permet guardar expressions en les seves 26 memòries
   anomenades de la 'a' a la 'z' i avaluar expressions que usin expressions de
   les seves 26 memòries si fan menció a variables anomenades de la 'a' a la 'z' */

class calculadora {
  public: 
  calculadora();
  // Pre: true
  // Post: Crea una calculadora amb totes les memòries buides

  calculadora(const calculadora &c);
  // Pre: c = C
  // Post: Crea una calculadora a partir de la calculadora C (constructor per còpia)

  calculadora& operator=(const calculadora &c);
  // Pre: c = C
  // Post: Al p.i. se li ha assignat la calculadora C (operador assignació)

  ~calculadora();
  // Pre: True
  // Post: S'ha destruït la calculadora del p.i. (destructora)

  bool es_buida(char v) const;
  // Pre: v = V és un caràcter entre 'a' i 'z'
  // Post: Indica si la memòria V conté una expressió formada per
  //       una única variable el nom de la qual és V

  void guarda(char v, const expressio &e);
  // Pre: v = V és un caràcter entre 'a' i 'z', e = E
  // Post: Guarda a la memòria V l'expressió E

  void elimina(char v);
  // Pre: v = V és un caràcter entre 'a' i 'z'
  // Post: Elimina l'expressió de la memòria V

  expressio mostra(char v) const;
  // Pre: v = V és un caràcter entre 'a' i 'z'
  // Post: Retorna l'expressió de la memòria V sense avaluar-la

  expressio expandeix(char v) const;
  // Pre: v = V és un caràcter entre 'a' i 'z'
  // Post: Retorna l'expressió de la memòria V expandint-la
  //       usant les memòries del p.i. tot el que es pugui
  //       Si es detecta una circularitat retorna una expressió
  //       amb sola variable de nom "ERROR_expressions_circulars"

  expressio expandeix(const expressio &e) const;
  // Pre: e = E
  // Post: Retorna una expressió fruit d'expandir l'expressió E
  //       usant les memòries del p.i. tot el que es pugui
  //       Si es detecta una circularitat retorna una expressió
  //       amb sola variable de nom "ERROR_expressions_circulars"

  expressio avalua(char v) const;
  // Pre: v = V és un caràcter entre 'a' i 'z'
  // Post: Retorna l'expressió de la memòria V expandint-la i avaluant-la
  //       usant les memòries del p.i. tot el que es pugui
  //       Si es detecta una circularitat retorna una expressió
  //       amb sola variable de nom "ERROR_expressions_circulars"

  expressio avalua(const expressio &e) const;
  // Pre: e = E
  // Post: Retorna una expressió fruit d'expandir i avaluar l'expressió E
  //       usant les memòries del p.i. tot el que es pugui
  //       Si es detecta una circularitat retorna una expressió
  //       amb sola variable de nom "ERROR_expressions_circulars"

  private:
    // Cal definir els atributs i mètodes privats dins del fitxer .rep 
    #include "calculadora.rep"
};

#endif
