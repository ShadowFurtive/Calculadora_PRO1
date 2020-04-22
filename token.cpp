#include "token.hpp"
#include "string"
//constructors

token::token(){
	numero=0;
}

token::token(int i){
	numero=i;
}

token::token(bool b){
	booler=b;
}

token::token(string s){
	valor=s
}

token::token(const char s[]){
	strcpy(valor, s);
}

token::token(const token &t){
	valor=t.valor;
}

token::token& operator=(const token &e){
	valor=e.valor;
}

token::~token(){
}

token::bool es_operador_unari() const{
	if(valor="not") return true;
	else return false;
}

token::bool es_operador_binari() const{
	if(valor="and" or valor="or") return true;
	else return false;
}

token::bool es_boolea() const{
	if(valor="T" or valor="F") return true;
	else return false;
}
token::bool es_enter() const{
	try{
	int i = stoi(valor);
	}
	catch(invalid_argument const &e){
		return false;
	}
	catch(out_of_range const &e){
		return false;
	}
	return true;
}

pair<int, bool> prioritat() const;
    // Pre: true
    // Post: Indica el nivell de prioritat a 'first' i si l'associativitat és d'esquerra a dreta a 'second' del p.i.
    //       Considerem que els operands tenen el màxim nivell de prioritat


token::int to_int() const{
   	try{
	int i = stoi(valor);
	}
	catch(invalid_argument const &e){
		cout<<"No es un número"<<endl;
	}
	catch(out_of_range const &e){
		cout<<"Fora de rang"<<endl;
	}
	return i;
}

token::bool to_bool() const{
	if(valor="T") return true;
	else return false;
}



























