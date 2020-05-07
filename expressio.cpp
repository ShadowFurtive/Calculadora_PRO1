#include "expressio.hpp"
#include <list>
#include <iterator>
#include <algorithm>
#include <stack>
#include <math.h>

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
  }
  else return op;
  return op;
}

void expressio::llegir_infixa(istream& is){
  // Pre: El canal is conté una expressió en notació infixa i sense errors.
  // Post: El p.i. conté l'expressió llegida del canal is.
  stack<token> op;
  stack<expressio> expre;
  token t;


  while (is>>t){
    if (t=="(") op.push(t);
    if (t!=")" and t.es_operand()) op.push(t);
    if (t.es_variable() or t.es_enter() or t.es_boolea()){
      expressio e1 (t);
      expre.push(e1);
    }
  }

}

void expressio::llegir_postfixa(istream& is){
// Pre: El canal is conté una expressió en notació postfixa i sense errors.
// Post: El p.i. conté l'expressió llegida del canal is.
stack<expressio> op;
token t;

while (is >> t){
    if (t.es_operand()){
      if (t.es_operador_unari()){
        expressio e1 = op.top();
        op.pop();
        expressio aux (t, e1);
        op.push(aux);
      }
      else{
        expressio e1 = op.top();
        op.pop();
        expressio e2 = op.top();
        op.pop();
        expressio aux (t, e2, e1);
        op.push(aux);
      }
    }
    else{
      expressio ope (t);
      op.push(ope);
    }
  }
  exp = aux;
}


string expressio::infixa() const{
  // Pre: True
  // Post: Retorna un string que conté l'expressió del p.i. amb notació infixa
  //   amb el mínim nombre de parèntesis, cada element separat amb un espai

}

string expressio::postfixa() const{
  // Pre: True
  // Post: Retorna un string que conté l'expressió del p.i. amb notació postfixa,
  //   cada element separat amb un espai
  stack<expressio> aux;
  queue<token> col;
  string res;

  while(exp.es_operand() or not aux.empty()){
    while(exp.es_operand()){
      aux.push(exp);
      exp = exp.fe();
    }
    exp = aux.top();
    aux.pop();
    col.push(exp.arrel());
    exp = exp.fd();
    while (not col.empty()){
      string j = col.front().to_string();
      res = res+j+32;
    }
  }
  return res;
}

static expressio::expressio avalua_operador_unari(token op, expressio e){
  // Pre: op = OP és un operador unari, e = E
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre l'expressió E
  if (op.es_operador_unari()) return not(e.arrel());
  else{
    expressio exp (op, e);
    return exp;
  }
}

static expressio::expressio avalua_operador_boolea(token op, expressio e1, expressio e2){
  // Pre: op = OP és un operador binari booleà, e1 = E1, e2 = E2
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre les expressions E1 i E2
  expressio exp (op);
  if (op.valor() == "and"){
    if(e1.arrel().to_bool() and not(e2.arrel().to_bool())) return exp (token t(false));
    else if(e2.arrel().to_bool() and not(e1.arrel().to_bool())) return exp(token t(false));
    else if(e1.arrel().to_bool() and e2.arrel().to_bool()) return exp (token t(true));
    else return exp (token t(false));
  }
  else if (op.valor() == "or") {
    if(not(e1.arrel().to_bool()) and not(e2.arrel().to_bool())) return exp (token t(false);
    else if(e1.arrel().to_bool() and not(e2.arrel().to_bool())) return exp (token t(true);
    else if(e1.arrel().to_bool() and e2.arrel().to_bool()) return exp (token t(true);
    else return exp (token t(true));
  }
  else return expressio aux (op, e1, e2);
}

static expressio::expressio avalua_operador_comparacio(token op, expressio e1, expressio e2){
  // Pre: op = OP és un operador binari de comparació, e1 = E1, e2 = E2
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre les expressions E1 i E2
  expressio exp (op);
  if ((e1.arrel().es_enter() and e2.arrel().es_enter()) or (e1.arrel().es_boolea() and e2.arrel().es_boolea())){
    if (op.valor() == "=="){
      if (e1.arrel() == e2.arrel()) return exp (token t(true));
      else return exp (token t(false));
    }
    else if (op.valor() == "!=") {
      if (e1.arrel() != e2.arrel()) return exp (token t(true));
      else return exp (token t(false));
    }
  }
  else return expressio aux (op, e1, e2);
}

static expressio::expressio avalua_operador_aritmetic(token op, expressio e1, expressio e2){
  // Pre: op = OP és un operador binari aritmètic, e1 = E1, e2 = E2
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre les expressions E1 i E2
  expressio exp (op);

    if (not (e1.arrel().es_variable())){
      int x = e1.arrel().to_int();
    }
    if (not(e2.arrel().es_variable())){
      int y = e2.arrel().to_int();
    }
    if (op.valor() == "*"){
        if (x == 0 or y == 0) return exp (token t(0));
        else if (x == 1) return e2;
        else if ( y == 1) return e1;
        else{
          int res = x*y;
          return exp (token t(res));
        }
    }
    if (op.valor() == "+"){
      if (x == 0) return e2;
      if (y == 0) return e1;
      else{
        int res = x+y;
        return exp (token t(res));
      }
    }
    if (op.valor() == "-"){
      if (x == 0) return e2;
      if (y == 0) return e1;
      else{
        int res = x-y;
        return exp (token t(res));
      }
    }
    if (op.valor() == "/"){
      if (x == 0) return exp (token t(0));
      if (y == 1) return e1;
      else{
        int res = x/y;
        return exp (token t(res));
      }
    }
    if (op.valor() == "%"){
      if (x == 0) return exp (token t(0));
      if (y == 1) return exp (token t(0));
      else{
        int res = x%y;
        return exp (token t(res));
      }
    }
    if (op.valor() == "**"){
      if (x == 0) return exp (token t(0));
      if (x == 1) return exp (token t(1));
      if (y == 0) return exp (token t(1));
      if (y == 1) return e1;
      else{
        int res = pow(x,y);
        return exp (token t(res));
      }
    }
  return expressio aux (op, e1, e2);
}

expressio::expressio avalua() const{
  // Pre: True
  // Post: Retorna l'expressió resultant d'avaluar l'expressió del p.i. tot el que es pugui
    expressio fin, e1, e2;
    if(not exp.es_buit()){
      if (not exp.fe().es_buit()){
        exp.fe().avalua();
        if (exp.arrel().es_operador_unari()){
          e1.avulua_operador_unari(exp.arrel(), exp.fe());
        }
        if ((exp.fe().es_enter() and exp.fd().es_enter()) or (exp.fe().es_variable() and exp.fd().es_variable())){
          e1.avalua_operador_aritmetic(exp.arrel(), exp.fe(), exp.fd());
          if (e1.es_boolea()){
            e1.avalua_operador_boolea(exp.arrel(), exp.fe(), exp.fd());
          }
          if (e1.arrel() == "==" or e1.arrel() == "!="){
            e1.avalua_operador_comparacio(exp.arrel(), exp.fe(), exp.fd());
          }
        }
      }
      if (not exp.fd().es_buit()){
        exp.fd().avalua();
        if (exp.arrel().es_operador_unari()){
          e2.avulua_operador_unari(exp.arrel(), exp.fe());
        }
        if ((exp.fe().es_enter() and exp.fd().es_enter()) or (exp.fe().es_variable() and exp.fd().es_variable())){
          e2.avalua_operador_aritmetic(exp.arrel(), exp.fe(), exp.fd());
          if (e2.es_boolea()){
            e2.avalua_operador_boolea(exp.arrel(), exp.fe(), exp.fd());
          }
          if (e2.arrel() == "==" or e2.arrel() == "!=" ){
            e2.avalua_operador_comparacio(exp.arrel(), exp.fe(), exp.fd());
          }
        }
      }
      fin(exp.arrel(), e1, e2);
  }
  return fin;
}

expressio expressio::expandeix(token t, const expressio &e) const{
  // Pre: t = TK és un token operand, e = E
  // Post: Retorna l'expressió resultant de canviar tots els tokens TK de l'expressió del p.i. per l'expressió E
exp = e;
return exp;
}
