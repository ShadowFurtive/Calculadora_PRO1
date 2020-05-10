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
  	arbreBin<token> aux = exp.fe();
	 token t1(0);
	 expressio fin(t1);	
	 fin.exp = arbreBin<token>(aux.arrel(), aux.fe(), aux.fd());
	 return fin;
}

expressio expressio::fd() const{
  // Pre: L'arrel del p.i. és un operador
  // Post: Retorna l'expressió de la dreta del p.i.
	 arbreBin<token> aux = exp.fd();
	 token t1(0);
	 expressio fin(t1);	
	 fin.exp = arbreBin<token>(aux.arrel(), aux.fe(), aux.fd());
	 return fin;
}

bool expressio::es_operand() const{
  // Pre: True
  // Post: Retorna si l'expressió del p.i. és un operand
  //   (o sigui que l'arbre binari que conté l'expressió és una fulla)
  if(exp.arrel().es_enter() or exp.arrel().es_boolea() or exp.arrel().es_variable()) return true;
  else return false;
}

list<token> expressio::operands() const{
  // Pre: True
  // Post: Retorna una llista dels tokens operands de l'expressió del p.i., d'esquerra a dreta
    stack<arbreBin<token>> p;
    arbreBin<token> a = exp;
    p.push(a);
    list<token> l;
    list<token>::iterator it = l.begin();
    while (not p.empty()) {
        arbreBin<token> a1 = p.top();
        p.pop();
        if (not a1.es_buit()) {
            if (a1.fe().es_buit() and a1.fd().es_buit()) l.insert(it, a1.arrel()); 
            else { 
                if (not a1.fe().es_buit()) p.push(a1.fd());
                if (not a1.fd().es_buit()) p.push(a1.fe());
            }
        }
    }
    return l;
}

void expressio::llegir_infixa(istream& is){
  // Pre: El canal is conté una expressió en notació infixa i sense errors.
  // Post: El p.i. conté l'expressió llegida del canal is.
  	stack< arbreBin<token> > arb;
	stack<token> o;
	token s;
	while(is>>s){
		if(s=="("){
			o.push(s);
		}
			else if(s==")"){
				token aux=o.top();
				o.pop();
				while(aux!="("){
					if(aux.es_operador_binari()){
						arbreBin<token> a1 = arb.top();
						arb.pop();
						arbreBin<token> a2 = arb.top();
						arb.pop();
						arbreBin<token> fin (aux, a2, a1);
						arb.push(fin);
					}
					else {
						arbreBin<token> a1 = arb.top();
						arb.pop();
						arbreBin<token> a2 ;
						arbreBin<token> fin (aux, a1, a2);
						arb.push(fin);
					}
					if(not o.empty()){
						aux=o.top();
						o.pop();
					}
				}
			}
			else if(s.es_enter() or s.es_variable() or s.es_boolea()){
				arbreBin<token> a1;
				arbreBin<token> a2;
				arbreBin<token> a4(s, a1, a2);
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
							arbreBin<token> a1 = arb.top();
							arb.pop();
							arbreBin<token> a2 = arb.top();
							arb.pop();
							arbreBin<token> fin (aux, a2, a1);
							arb.push(fin);
						}
						else {
							arbreBin<token> a1 = arb.top();
							arb.pop();
							arbreBin<token> a2 ;
							arbreBin<token> fin (aux, a1, a2);
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
			arbreBin<token> a1 = arb.top();
			arb.pop();
			arbreBin<token> a2 = arb.top();
			arb.pop();
			arbreBin<token> fin (o.top(), a2, a1);
			o.pop();
			arb.push(fin);
		}
		else {
			arbreBin<token> a1 = arb.top();
			arb.pop();
			arbreBin<token> a2 ;
			arbreBin<token> fin (o.top(), a1, a2);
			o.pop();
			arb.push(fin);
		}
	}
	cout<<arb.top()<<endl;
	exp = arb.top();
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
	cout<<op.top();
	exp = op.top();
}


string expressio::infixa() const{
  // Pre: True
  // Post: Retorna un string que conté l'expressió del p.i. amb notació infixa
  //   amb el mínim nombre de parèntesis, cada element separat amb un espai
  	arbreBin<token> aux = exp;
	stack<arbreBin<token>> auxiliar, a1;
	stack<token> col1, col;
	string res;
	bool cert = false;
	while(not aux.es_buit() or not auxiliar.empty() or not a1.empty()){
		while(not aux.fe().es_buit()){
				cout<<1<<endl;
				pair<int, bool> res = aux.fe().arrel().prioritat();
				pair<int, bool> res1 = aux.arrel().prioritat();
					if((res.first < res1.first ) or ((res.first==res1.first and not aux.arrel().es_operador_commutatiu()) and not res1.second)){
						token aje = " ( ";
						col.push(aje);
						cert=true;
					}
				aux=aux.fe();
				while(not aux.es_buit()){
					a1.push(aux);
					if(not aux.fe().es_buit()){
					aux = aux.fe();
				}
				aux= a1.top();
				a1.pop();
				col.push(aux.arrel());
				aux = aux.fd();
				if(cert){
					token aje2 = " ) ";
					col.push(aje2);
				}
			}
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

string expressio::postfixa() const{
  // Pre: True
  // Post: Retorna un string que conté l'expressió del p.i. amb notació postfixa,
  //   cada element separat amb un espai
	arbreBin<token> aux = exp;
	stack<arbreBin<token>> auxiliar;
	stack<token> col1, col;
	string res;
	while(not aux.es_buit() or not auxiliar.empty()){
		while(not aux.es_buit()){
			auxiliar.push(aux);
			aux = aux.fe();
		}
		aux= auxiliar.top();
		auxiliar.pop();
		col.push(aux.arrel());
		aux = aux.fd();
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
	token t(not e.arrel().to_bool());
	expressio ae(t);
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
	if (op == "=="){
		if (e1.arrel() == e2.arrel()) return tr;
		else return fa;
	}
	else if (op == "!=") {
		if (e1.arrel() != e2.arrel()) return tr;
		else return fa;
	}
	expressio aux (op, e1, e2);
	return aux;
}

expressio expressio:: avalua_operador_aritmetic(token op, expressio e1, expressio e2){
  // Pre: op = OP és un operador binari aritmètic, e1 = E1, e2 = E2
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre les expressions E1 i E2
    cout<<"aloha"<<endl;
    token zero(0);
    expressio zer(zero);
    token uno(1);
    expressio un(uno);
    cout<<"hola"<<endl;
    if (op == "*"){
        if (e1.arrel() == "0" or e2.arrel() == "0") return zer;
        if (e1.arrel() == "1") return e2;
        if (e2.arrel() == "1") return e1;
        else if(e1.arrel().es_enter() and e2.arrel().es_enter()){
	  int x = e1.arrel().to_int();
	  int y = e2.arrel().to_int();
          int res = x*y;
	  token fi(res);
	  expressio alu(fi);
          return alu;
        }
    }
    if (op == "+"){
      if (e1.arrel() == "0") return e2;
      if (e2.arrel() == "0") return e1;
      else if(e1.arrel().es_enter() and e2.arrel().es_enter()){
          int x = e1.arrel().to_int();
	  int y = e2.arrel().to_int();
          int res = x+y;
	  token fi(res);
	  expressio alu(fi);
          return alu;
      }
    }
    if (op == "-"){
      if (e1.arrel() == "0") return e2;
      if (e2.arrel() == "0") return e1;
      else if(e1.arrel().es_enter() and e2.arrel().es_enter()){
          int x = e1.arrel().to_int();
	  int y = e2.arrel().to_int();
          int res = x-y;
	  token fi(res);
	  expressio alu(fi);
          return alu;
      }
    }
    if (op == "/"){
      if (e1.arrel() == "0") return zer;
      if (e2.arrel() == "1") return e1;
      else if(e1.arrel().es_enter() and e2.arrel().es_enter()){
		int x = e1.arrel().to_int();
		int y = e2.arrel().to_int();
		int res = x/y;
		token fi(res);
		expressio alu(fi);
		return alu;
      }
    }
    if (op == "%"){
      if (e1.arrel() == "0") return zer;
      if (e2.arrel() == "1") return zer;
      else if(e1.arrel().es_enter() and e2.arrel().es_enter()){
		int x = e1.arrel().to_int();
		int y = e2.arrel().to_int();
		int res = x*y;
		token fi(res);
		expressio alu(fi);
		return alu;
      }
    }
    if (op == "**"){
      if (e1.arrel() == "0") return zer;
      if (e1.arrel() == "1") return un;
      if (e2.arrel() == "0") return un;
      if (e2.arrel() == "1") return e1;
      else if(e1.arrel().es_enter() and e2.arrel().es_enter()){
		int x = e1.arrel().to_int();
		int y = e2.arrel().to_int();
		int res = pow(x,y);
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
	stack<expressio> pila_1;
	stack<expressio> pila_2;
	token aloha(0);
	expressio aux(aloha);
	pila_1.push(*this);
	while(not pila_1.empty()){
		aux = pila_1.top();
		pila_1.pop();
		if(not aux.fe().es_operand()){
			pila_1.push(aux.fe());
		}
		if(not aux.fd().es_operand()){
			pila_1.push(aux.fd());
		}
		pila_2.push(aux);
	}
	return aux;

}

expressio expressio::expandeix(token t, const expressio &e) const{
  // Pre: t = TK és un token operand, e = E
  // Post: Retorna l'expressió resultant de canviar tots els tokens TK de l'expressió del p.i. per l'expressió E
expressio fin(t, e);
return fin;
}
