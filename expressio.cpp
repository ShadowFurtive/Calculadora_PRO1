#include "expressio.hpp"
#include <list>
#include <stack>
#include <math.h>

/* La classe "expressio" permet guardar i avaluar una expressió aritmètica o booleana */

expressio::expressio(const token &t){
  // Pre: t = TK és un token operand
  // Post: Crea una expressió formada per operand TK
	arbreBin<token> a, b;
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
	if (this != &e) exp = e.exp;
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
		if (not a1.arrel().es_operador_unari() and not a1.fe().es_buit()) p.push(a1.fd());
		if (a1.arrel().es_operador_unari() and a1.fd().es_buit()) p.push(a1.fe());
		if (not a1.fd().es_buit()) p.push(a1.fe());
	    }
	}
	}
	return l;
}

void expressio::llegir_infixa(istream& is){
  // Pre: El canal is conté una expressió en notació infixa i sense errors.
  // Post: El p.i. conté l'expressió llegida del canal is.
  	stack<arbreBin<token> > arb;
	stack<token> o;
	token s;
	while(is>>s and s!="->"){
		if(s=="(") o.push(s);
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
						arbreBin<token> a1 = arb.top(), a2;
						arb.pop();
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
				arbreBin<token> a1, a2;
				arbreBin<token> a4(s, a1, a2);
				arb.push(a4);
			}
			else if(s.es_operador_unari() or s.es_operador_binari()){
				if(o.empty()) o.push(s);
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
							arbreBin<token> a1 = arb.top(), a2;
							arb.pop();
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
			arbreBin<token> a1 = arb.top(), a2;
			arb.pop();
			arbreBin<token> fin (o.top(), a1, a2);
			o.pop();
			arb.push(fin);
		}
	}
	exp = arb.top();
}

void expressio::llegir_postfixa(istream& is){
// Pre: El canal is conté una expressió en notació postfixa i sense errors.
// Post: El p.i. conté l'expressió llegida del canal is.
stack<arbreBin<token>> op;
token t;

	while (is >> t and t!="->"){
		if(t.es_operador_binari() or t.es_operador_unari()){
			if (t.es_operador_unari()){
				arbreBin<token> e1 = op.top(), e2;
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
			arbreBin<token> e1, e2;
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
	token z(0);
	expressio aux(z);
	aux.exp = exp; 
	string s="";
  	if(not aux.es_operand()){
		if(aux.arrel().es_operador_unari()) s = aux.arrel().to_string() + " " + s;
		if(not aux.fe().es_operand()){
			pair<int, bool> res = aux.arrel().prioritat();
			pair<int, bool> res1 = aux.fe().arrel().prioritat();
			if((res1.first < res.first ) or ((res.first==res1.first) and not aux.arrel().es_operador_commutatiu() and not res.second)){
				s = s + "( ";
				s = s + aux.fe().infixa();
				  /* HI: Retorna un string que conté l'expressió del fil esquerre de aux amb notació infixa
 				   amb el mínim nombre de parèntesis, cada element separat amb un espai */
				  /* FITA: El nº de elemenets restants en el subarbre esquerre */
				s = s + " )";
			}
			else s = s + aux.fe().infixa();
			/* HI: Retorna un string que conté l'expressió del fil esquerre de aux amb notació infixa
			   amb el mínim nombre de parèntesis, cada element separat amb un espai */
			  /* FITA: El nº de elemenets restants en el subarbre esquerre */
		}
		else s = s + aux.fe().arrel().to_string();
		if(not  aux.arrel().es_operador_unari()){
			s = s + " " +  aux.arrel().to_string() + " ";
			if(not aux.arrel().es_operador_unari()){
				if(not aux.fd().es_operand()){
					pair<int, bool> res = aux.arrel().prioritat();
					pair<int, bool> res1 = aux.fd().arrel().prioritat();
					if((res1.first < res.first ) or ((res.first==res1.first) and not aux.arrel().es_operador_commutatiu() and res.second)){
						s = s + "( ";
						s = s + aux.fd().infixa();
						/* HI: Retorna un string que conté l'expressió del fil dret de aux amb notació infixa
		 				   amb el mínim nombre de parèntesis, cada element separat amb un espai */
						/* FITA: El nº de elemenets restants en el subarbre dret */
						s = s + " )";
					}
					else s = s + aux.fd().infixa();
					/* HI: Retorna un string que conté l'expressió del fil dret de aux amb notació infixa
	 				   amb el mínim nombre de parèntesis, cada element separat amb un espai */
					  /* FITA: El nº de elemenets restants en el subarbre dret */
					
				}
				else s = s + aux.fd().arrel().to_string();
			}
		}
	}
	else s = s + aux.arrel().to_string();
	return s;
}

string expressio::postfixa() const{
  // Pre: True
  // Post: Retorna un string que conté l'expressió del p.i. amb notació postfixa,
  //   cada element separat amb un espai
	string res;
	stack<arbreBin<token>> s1, s2;
	arbreBin<token> arb(exp);
	s1.push(arb);
	while (not s1.empty()){
		arb = s1.top();
		s1.pop();
		if(not arb.fe().es_buit()) s1.push(arb.fe());
		if(not arb.arrel().es_operador_unari()){
    			if(not arb.fd().es_buit()) s1.push(arb.fd());
    		}
		s2.push(arb);
	}
	while (not s2.empty()){
		res = res+s2.top().arrel().to_string()+" ";
		s2.pop();
	}
	return res;
}


expressio expressio:: avalua_operador_unari(token op, expressio e){
  // Pre: op = OP és un operador unari, e = E
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre l'expressió E
	if (e.arrel().es_boolea()){ 
		bool b = e.arrel().to_bool();
		b = not(b);
		token t(b);
		expressio fi(b);
		return fi;
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
		if(e1.arrel()=="F" or e2.arrel()=="F") return fa;
		else if(e1.arrel()=="T" and not e2.arrel().es_boolea()) return e2;
		else if(e2.arrel()=="T" and not e1.arrel().es_boolea()) return e1;
		else if(e1.arrel().es_boolea() and e2.arrel().es_boolea()){
			bool a = e1.arrel().to_bool();
			bool b = e2.arrel().to_bool();
			if(a and b) return tr;
			else return fa;
		}	
	}
	else if (op == "or") {
		if(e1.arrel()=="T" or e1.arrel()=="T") return tr;
		else if(e1.arrel()=="F" and not e2.arrel().es_boolea()) return e2;
		else if(e2.arrel()=="F" and not e1.arrel().es_boolea()) return e1;
		else if(e1.arrel().es_boolea() and e2.arrel().es_boolea()){
			bool a = e1.arrel().to_bool();
			bool b = e2.arrel().to_bool();
			if(a or b) return tr;
			else return fa;
		}
	}
	expressio aux (op, e1, e2);
	return aux;
}

expressio expressio:: avalua_operador_comparacio(token op, expressio e1, expressio e2){
  // Pre: op = OP és un operador binari de comparació, e1 = E1, e2 = E2
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre les expressions E1 i E2
	token t1(false);
	expressio fa(t1);
	token t2(true);
	expressio tr(t2);
	if (op == "=="){
		if(e1.arrel().es_boolea() and e2.arrel().es_boolea()){
			if (e1.arrel() == e2.arrel()) return tr;
			else return fa;
		}
		if(e1.arrel().es_enter() and e2.arrel().es_enter()){
			if (e1.arrel() == e2.arrel()) return tr;
			else return fa;
		}
		if(e1.arrel().es_variable() and e2.arrel().es_variable()){
			if (e1.arrel() == e2.arrel()) return tr;
		}
	}
	else if (op == "!=") {
		if(e1.arrel().es_boolea() and e2.arrel().es_boolea()){
			if (e1.arrel() != e2.arrel()) return tr;
			else return fa;
		}
		if(e1.arrel().es_enter() and e2.arrel().es_enter()){
			if (e1.arrel() != e2.arrel()) return tr;
			else return fa;
		}
		if(e1.arrel().es_variable() and e2.arrel().es_variable()){
			if (e1.arrel() == e2.arrel()) return fa;
		}
	}
	expressio aux (op, e1, e2);
	return aux;
}

expressio expressio:: avalua_operador_aritmetic(token op, expressio e1, expressio e2){
  // Pre: op = OP és un operador binari aritmètic, e1 = E1, e2 = E2
  // Post: Retorna l'expressió resultat d'avaluar l'operador OP sobre les expressions E1 i E2
	token zero(0);
	expressio zer(zero);
	token uno(1);
	expressio un(uno);
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
	token z(0);
	expressio aux(z);
	aux.exp = exp;
	if(not aux.es_operand()){
			expressio A1(z);
			expressio A2(z);
			if(not aux.fe().es_operand()) A1 = aux.fe().avalua();
			//HI: Guarda a A1 l'expressió resultant d'avaluar el fil esquerre de l'expressió de aux tot el que es pugui.
			//FITA: el nº de nodes restants del subarbre esquerre.
			else A1 = aux.fe();
			if(not aux.arrel().es_operador_unari()){
				if(not aux.fd().es_operand()) A2 = aux.fd().avalua();
			//HI: Guarda a A2 l'expressió resultant d'avaluar el fil dret de l'expressió de aux tot el que es pugui
			//FITA: el nº de nodes restants del subarbre dret.
				else A2 = aux.fd();
			}
			if(A1.es_operand() and aux.arrel().es_operador_unari()){
				aux = avalua_operador_unari(aux.arrel(), A1);
				return aux;
			}
			if((A2.es_operand() or A1.es_operand()) and aux.arrel().es_operador_binari()){
				aux = avalua_operador_boolea(aux.arrel(), A1, A2);
				if(aux.arrel().es_operador_binari()) aux = avalua_operador_comparacio(aux.arrel(), aux.fe(), aux.fd());
				if(aux.arrel().es_operador_binari()) aux = avalua_operador_aritmetic(aux.arrel(), aux.fe(), aux.fd());
				return aux;
			}
			expressio amp(aux.arrel(), A1, A2);
			return amp;
	}
	return aux;

}

expressio expressio::expandeix(token t, const expressio &e) const{
  // Pre: t = TK és un token operand, e = E
  // Post: Retorna l'expressió resultant de canviar tots els tokens TK de l'expressió del p.i. per l'expressió E
	token z(0);
	expressio aux(z);
	aux.exp = exp;
	if(not aux.es_operand()){
		expressio A1(z);
		expressio A2(z);
		A1 = aux.fe().expandeix(t, e);
		//HI: Guarda a A1 l'expressió resultant de canviar tots els tokens TK de l'expressió del fil esquerre de aux per l'expressió E
		//FITA: el nº de nodes restants del subarbre esquerre.
		if(not aux.arrel().es_operador_unari()) A2 = aux.fd().expandeix(t, e);
		//HI: Guarda a A2 l'expressió resultant de canviar tots els tokens TK de l'expressió del fil dret de aux per l'expressió E
		//FITA: el nº de nodes restants del subarbre dret.
		expressio amp(aux.arrel(), A1, A2);
		return amp;
	}
	else if(aux.arrel()==t) return e;
	return aux;

}
			


	


































