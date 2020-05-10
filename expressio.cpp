#include "expressio.hpp"
#include <list>
#include <iterator>
#include <algorithm>
#include <stack>
#include <queue>
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
  arbreBin<token> b;
  exp = arbreBin<token> (t, e.exp ,b);
}

expressio::expressio(const token &t, const expressio &e1, const expressio &e2){
  // Pre: t = TK és un token operador binari, e1 = E1, e2 = E2
  // Post: Crea una expressió formada per l'operador binari TK aplicat a les expressions E1 i E2
  exp = arbreBin<token> (t, e1.exp, e2.exp);
}

expressio:: expressio(const expressio &e){
  // Pre: e = E
  // Post: Crea una expressió a partir de l'expressió E (constructor per còpia)
  exp = e.exp;
}

expressio& expressio:: operator=(const expressio &e){
  // Pre: e = E
  // Post: Al p.i. se li ha assignat l'expressió E (operador assignació)
	if (this != &e) {
	    exp = e.exp;
	  }
	  return (*this);
}

expressio::~expressio(){
  // Pre: True
  // Post: S'ha destruït l'expressió del p.i. (destructora)
}

token expressio::arrel() const{
  // Pre: True
  // Post: Retorna el token de l'arrel del p.i.
  return exp.arrel();
}

expressio expressio::fe() const{
  // Pre: L'arrel del p.i. és un operador
  // Post: Retorna l'expressió de l'esquerra del p.i.	
  return this->fe();
}

expressio expressio::fd() const{
  // Pre: L'arrel del p.i. és un operador
  // Post: Retorna l'expressió de la dreta del p.i.
  return this->fd();
}

bool expressio::es_operand() const{
  // Pre: True
  // Post: Retorna si l'expressió del p.i. és un operand
  //   (o sigui que l'arbre binari que conté l'expressió és una fulla)
  if((exp.fe().arrel().es_enter() or exp.fe().arrel().es_boolea() or exp.fe().arrel().es_variable()) and (exp.fd().arrel().es_enter() or exp.fd().arrel().es_boolea() or exp.fd().arrel().es_variable())) return true;
  else return false;
}

list<token> expressio::operands() const{
  // Pre: True
  // Post: Retorna una llista dels tokens operands de l'expressió del p.i., d'esquerra a dreta
  list<token> op;
  return op;
}

void expressio::llegir_infixa(istream& is){
  // Pre: El canal is conté una expressió en notació infixa i sense errors.
  // Post: El p.i. conté l'expressió llegida del canal is.
  	stack<expressio> arb;
	stack<token> o;
	token s;
	while(is>>s){
		if(s=="("){
			o.push(s);
		}
			else if(s==")"){
				token aux(o.top());
				o.pop();
				while(aux!="("){
					if(aux.es_operador_binari()){
						expressio a1 = arb.top();
						arb.pop();
						expressio a2 = arb.top();
						arb.pop();
						expressio fin (aux, a2, a1);
						arb.push(fin);
					}
					else {
						expressio a1 = arb.top();
						arb.pop();
						expressio fin (aux, a1);
						arb.push(fin);
					}
					if(not o.empty()){
						aux=o.top();
						o.pop();
					}
				}
			}
			else if(s.es_enter() or s.es_boolea() or s.es_variable()){
				expressio a4(s);
				arb.push(a4);
			}
			else if(s.es_operador_unari() or s.es_operador_binari()){
				if(o.empty()){
					o.push(s);
				}
				else{
					pair<int, bool> res = s.prioritat();
					pair<int, bool> res1 = o.top().prioritat();
					while(((res.first < res1.first ) or (res.first<=res1.first and res.second)) and(not o.empty() and o.top()!="(")){
						token aux = o.top();
						o.pop();
						if(aux.es_operador_binari()){
							expressio a1 = arb.top();
							arb.pop();
							expressio a2 = arb.top();
							arb.pop();
							expressio fin (aux, a2, a1);
							arb.push(fin);
						}
						else {
							expressio a1 = arb.top();
							arb.pop();
							expressio fin (aux, a1);
							arb.push(fin);
						}
						if(not o.empty()) res1 = o.top().prioritat();
					}
					o.push(s);
				}
			}
	}
	
	
	while(not o.empty()){
		if(o.top().es_operador_binari()){
			expressio a1 = arb.top();
			arb.pop();
			expressio a2 = arb.top();
			arb.pop();
			expressio fin (o.top(), a2, a1);
			o.pop();
			arb.push(fin);
		}
		else {
			expressio a1 = arb.top();
			arb.pop();
			expressio fin (o.top(), a1);
			o.pop();
			arb.push(fin);
		}
	}
	*this = arb.top();
}

void expressio::llegir_postfixa(istream& is){
// Pre: El canal is conté una expressió en notació postfixa i sense errors.
// Post: El p.i. conté l'expressió llegida del canal is.
stack<arbreBin<token>> op;
token t;

while (is >> t){
	if(t.es_operador_binari() or t.es_operador_unari()){
	if (t.es_operador_unari()){
	arbreBin<token> e1 = op.top();
	arbreBin<token> e2;
	op.pop();
	arbreBin<token> aux(t, e1, e2);
	op.push(aux);
	}
	else{
	arbreBin<token> e1 = op.top();
	op.pop();
	arbreBin<token> e2 = op.top();
	op.pop();
	arbreBin<token> aux (t, e2, e1);
	op.push(aux);
	}
	}
	else{
	arbreBin<token> e1;
	arbreBin<token> e2;
	arbreBin<token> ope (t, e1, e2);
	op.push(ope);
	}
	}
	exp = op.top();
}


string expressio::infixa() const{
  // Pre: True
  // Post: Retorna un string que conté l'expressió del p.i. amb notació infixa
  //   amb el mínim nombre de parèntesis, cada element separat amb un espai
  	string s = " ERROR " ;
	return s;
}

string expressio::postfixa() const{
  // Pre: True
  // Post: Retorna un string que conté l'expressió del p.i. amb notació postfixa,
  //   cada element separat amb un espai
	arbreBin<token> aux = exp;
	stack<arbreBin<token>> auxiliar;
	stack<token> col1, col;
	string res;
	auxiliar.push(aux);
	aux=aux.fe();
	while(not aux.es_buit() or not auxiliar.empty()){
		while(not aux.es_buit()){
			auxiliar.push(aux);
			aux = aux.fe();
		}
		aux= auxiliar.top();
		auxiliar.pop();
		cout<<aux<<endl;
		col.push(aux.arrel());
		if(not aux.fd().es_buit()){
			aux = aux.fd();	
			auxiliar.push(aux);
		}
	}
	while (not col.empty()){
		col1.push(col.top());
		col.pop();
	}
	while (not col1.empty()){
		string j = col1.top().to_string();
		col1.pop();
		res = res+j+" ";
	}
	return res;
}

expressio expressio:: avalua_operador_unari(token op, expressio e){
  // Pre: op = OP és un operador unari, e = E
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre l'expressió E
  if (op.es_operador_unari()){
	token t(not e.fe().arrel().to_bool());
	expressio ae(t, e);
	return ae;
  }
  else{
    expressio ae(op, e);
    return ae;
  }
}

expressio expressio:: avalua_operador_boolea(token op, expressio e1, expressio e2){
  // Pre: op = OP és un operador binari booleà, e1 = E1, e2 = E2
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre les expressions E1 i E2
  token t1(false);
  expressio fa(t1);
  token t2(true);
  expressio tr(t2);
  if (op == "and"){
    if(e1.arrel().to_bool() and not(e2.arrel().to_bool())) return fa;
    else if(e2.arrel().to_bool() and not(e1.arrel().to_bool())) return fa;
    else if(e1.arrel().to_bool() and e2.arrel().to_bool()) return tr;
    else return fa;
  }
  else if (op == "or") {
    if(not(e1.arrel().to_bool()) and not(e2.arrel().to_bool())) return fa;
    else if(e1.arrel().to_bool() and not(e2.arrel().to_bool())) return tr;
    else if(e1.arrel().to_bool() and e2.arrel().to_bool()) return tr;
    else return tr;
  }
  else{
	expressio aux (op, e1, e2);
	return aux;
  }
}

expressio expressio:: avalua_operador_comparacio(token op, expressio e1, expressio e2){
  // Pre: op = OP és un operador binari de comparació, e1 = E1, e2 = E2
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre les expressions E1 i E2
   token t1(false);
  expressio fa(t1);
  token t2(true);
  expressio tr(t2);
  if ((e1.arrel().es_enter() and e2.arrel().es_enter()) or (e1.arrel().es_boolea() and e2.arrel().es_boolea())){
    if (op == "=="){
      if (e1.arrel() == e2.arrel()) return tr;
      else return fa;
    }
    else if (op == "!=") {
      if (e1.arrel() != e2.arrel()) return tr;
      else return fa;
    }
  }
  else{
	expressio aux (op, e1, e2);
	return aux;
  }
  expressio aux (op, e1, e2);
   return aux;
}

expressio expressio:: avalua_operador_aritmetic(token op, expressio e1, expressio e2){
  // Pre: op = OP és un operador binari aritmètic, e1 = E1, e2 = E2
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre les expressions E1 i E2
	int x;
	int y;
	int res;
	token t2(0);
	expressio zer(t2);
	token uno(1);
	expressio un(uno);
    if (not (e1.arrel().es_variable()) and e1.arrel().es_enter()){
      x = e1.arrel().to_int();
    }
    if (not(e2.arrel().es_variable()) and e1.arrel().es_enter()){
      y = e2.arrel().to_int();
    }
    if (op == "*"){
        if (x == 0 or y == 0) return zer;
        if (x == 1) return e2;
        if ( y == 1) return e1;
        else if(e1.arrel().es_enter() and e2.arrel().es_enter()){
          res = x*y;
	  token fi(res);
	  expressio alu(fi);
          return alu;
        }
    }
    if (op == "+"){
      if (x == 0) return e2;
      if (y == 0) return e1;
      else if(e1.arrel().es_enter() and e2.arrel().es_enter()){
          res = x+y;
	  token fi(res);
	  expressio alu(fi);
          return alu;
      }
    }
    if (op == "-"){
      if (x == 0) return e2;
      if (y == 0) return e1;
      else if(e1.arrel().es_enter() and e2.arrel().es_enter()){
          res = x-y;
	  token fi(res);
	  expressio alu(fi);
          return alu;
      }
    }
    if (op == "/"){
      if (x == 0) return zer;
      if (y == 1) return e1;
      else if(e1.arrel().es_enter() and e2.arrel().es_enter()){
         res = x/y;
	  token fi(res);
	  expressio alu(fi);
          return alu;
      }
    }
    if (op == "%"){
      if (x == 0) return zer;
      if (y == 1) return zer;
      else if(e1.arrel().es_enter() and e2.arrel().es_enter()){
          res = x%y;
	  token fi(res);
	  expressio alu(fi);
          return alu;
      }
    }
    if (op == "**"){
      if (x == 0) return zer;
      if (x == 1) return un;
      if (y == 0) return un;
      if (y == 1) return e1;
      else if(e1.arrel().es_enter() and e2.arrel().es_enter()){
      	  res = pow(x,y);
	  token fi(res);
	  expressio alu(fi);
          return alu;
      }
    }
  expressio aux ( op, e1, e2);
  return aux;
}

expressio expressio:: avalua() const{
  // Pre: True
  // Post: Retorna l'expressió resultant d'avaluar l'expressió del p.i. tot el que es pugui
	token aux1;
    expressio fin(aux1);
	token aux2;
    expressio e1(aux2);
	token aux3;
    expressio e2(aux3);
    if(not exp.es_buit()){
      if (not exp.fe().es_buit()){
        this->fe().avalua();
        if (exp.arrel().es_operador_unari()) e1 = avalua_operador_unari(exp.arrel(), this->fe());
        if ((exp.fe().arrel().es_enter() and exp.fd().arrel().es_enter()) or (exp.fe().arrel().es_variable() and exp.fd().arrel().es_variable())) e1.avalua_operador_aritmetic(exp.arrel(), this->fe(), this->fd());
	if ((exp.fe().arrel().es_variable() and exp.fd().arrel().es_enter()) or (exp.fe().arrel().es_enter() and exp.fd().arrel().es_variable())) e1.avalua_operador_aritmetic(exp.arrel(), this->fe(), this->fd());
        if (exp.fe().arrel().es_boolea() and exp.fd().arrel().es_boolea()) e1.avalua_operador_boolea(exp.arrel(), this->fe(), this->fd());
        if (exp.arrel() == "==" or exp.arrel() == "!=") e1.avalua_operador_comparacio(exp.arrel(), this->fe(), this->fd());
      }
      if (not exp.fd().es_buit()){
        this->fd().avalua();
        if (exp.arrel().es_operador_unari()) e2.avalua_operador_unari(exp.arrel(), this->fe());
        if ((exp.fe().arrel().es_enter() and exp.fd().arrel().es_enter()) or (exp.fe().arrel().es_variable() and exp.fd().arrel().es_variable())) e2.avalua_operador_aritmetic(exp.arrel(), this->fe(), this->fd());
	if ((exp.fe().arrel().es_variable() and exp.fd().arrel().es_enter()) or (exp.fe().arrel().es_enter() and exp.fd().arrel().es_variable())) e1.avalua_operador_aritmetic(exp.arrel(), this->fe(), this->fd());
        if (e2.arrel().es_boolea()) e2.avalua_operador_boolea(exp.arrel(), this->fe(), this->fd());
        if (e2.arrel() == "==" or e2.arrel() == "!=" ) e2.avalua_operador_comparacio(exp.arrel(), this->fe(), this->fd());
      }
      expressio fina(exp.arrel(), e1, e2);
      fin = fina;
  }
  return fin;
}

expressio expressio::expandeix(token t, const expressio &e) const{
  // Pre: t = TK és un token operand, e = E
  // Post: Retorna l'expressió resultant de canviar tots els tokens TK de l'expressió del p.i. per l'expressió E
expressio fin(t, e);
return fin;
}
