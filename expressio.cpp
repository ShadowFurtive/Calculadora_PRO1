#include "expressio.hpp"
#include <list>
#include <iterator>
#include <algorithm>

expressio::expressio(const token &t){
  // Pre: t = TK és un token operand
  // Post: Crea una expressió formada per operand TK
  arbreBin<token> a;
  arbreBin<token> b;
  exp = arbreBin<token>(t,a,b);
}

expressio::expressio(const token &t, const expressio &e){
  // Pre: t = TK és un token operador unari, e = E
  // Post: Crea una expressió formada per l'operador unari TK aplicat a l'expressió E
  arbreBin<token> a = e.fe();
  arbreBin<token> b = e.fd();
  exp = arbreBin<token> (t,a,b);
}

expressio::expressio(const token &t, const expressio &e1, const expressio &e2){
  // Pre: t = TK és un token operador binari, e1 = E1, e2 = E2
  // Post: Crea una expressió formada per l'operador binari TK aplicat a les expressions E1 i E2
  exp = arbreBin<token> (t, e1, e2);
}

expressio:: expressio(const expressio &e){
  // Pre: e = E
  // Post: Crea una expressió a partir de l'expressió E (constructor per còpia)
  exp = e;
}

expressio::expressio& operator=(const expressio &e){
  // Pre: e = E
  // Post: Al p.i. se li ha assignat l'expressió E (operador assignació)
  if(this != &e){
    exp=e.exp;
  }
  return *this;
}

expressio::~expressio(){
  // Pre: True
  // Post: S'ha destruït l'expressió del p.i. (destructora)
}

expressio::token arrel() const{
  // Pre: True
  // Post: Retorna el token de l'arrel del p.i.
  return exp.arrel();
}

expressio::expressio fe() const{
  // Pre: L'arrel del p.i. és un operador
  // Post: Retorna l'expressió de l'esquerra del p.i.
  return exp.fe();
}

expressio::expressio fd() const{
  // Pre: L'arrel del p.i. és un operador
  // Post: Retorna l'expressió de la dreta del p.i.
  return exp.fd();
}

expressio::bool es_operand() const{
  // Pre: True
  // Post: Retorna si l'expressió del p.i. és un operand
  //   (o sigui que l'arbre binari que conté l'expressió és una fulla)
  if(exp.fe().es_buit() or exp.fd().es_buit())return true;
  else return false;
}

expressio::list<token> operands() const{
  // Pre: True
  // Post: Retorna una llista dels tokens operands de l'expressió del p.i., d'esquerra a dreta
  list<token> op;
  list<token>aux;
  if(this->es_operand()){
    token aux = exp.arrel();
    op = exp.fe().operands();
    aux = exp.fd().operands();
    copy(op.rbegin(), op.rend(), front_inserter(aux));
    op.insert(op.begin(), aux);
  }
  else return op;
  return op;
}

void expressio::llegir_infixa(istream& is){
  // Pre: El canal is conté una expressió en notació infixa i sense errors.
  // Post: El p.i. conté l'expressió llegida del canal is.
  vector<token> v;
  for(int i=0; i<v.size(); i++){
    v.pushback();
  }
}
