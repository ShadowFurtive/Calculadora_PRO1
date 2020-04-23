#include "token.hpp"
#include "string"
#include <stdio.h>
#include <string.h>
//constructors

token::token(){
	valor="0";
}

token::token(int i){
	int temp;
	while(i/10!=0){
		temp=i%10;
		i= i/10;
		temp =temp + 48;
		valor = (char)temp + valor;
	}
	i=i+48;
	valor = (char)i + valor ;
}

token::token(bool b){
	if(b==true) valor="T";
	else valor="F";
}

token::token(string s){
	valor=s;
}

token::token(const char s[]){
	int aux=strlen(s);
	for (int i = 0; i < aux; i++) { 
	valor = valor + s[i]; 
	}  
}

token::token(const token &t){
	valor=t.valor;
}

token::~token(){
}

token& token:: operator=(const token &e){
	delete this;
	string *foo;
	foo = new string(e.valor);
	return foo;
		
}

bool token::es_operador_unari() const{
	if(valor=="not") return true;
	else return false;
}

bool token::es_operador_binari() const{
	if(valor=="and" or valor=="or") return true;
	else return false;
}

bool token::es_operador_commutatiu() const{
	if(valor=="+" or valor=="*") return true;
	else return false;
}

bool token::es_boolea() const{
	if(valor=="T" or valor=="F") return true;
	else return false;
}
bool token::es_enter() const{
	bool trobat = true;
	for(unsigned int i = 0; i<=valor.size() and trobat; ++i){
		if(valor[0]== '-') trobat = true;
			else if (valor[i]<48 and valor[i]>57) trobat = false;
			else trobat = false;
	}
	return trobat;
}
bool token::es_variable() const{
	if (not(this->es_enter() and this->es_boolea() and this->es_operador_unari() and this->es_operador_binari() and this->es_operador_commutatiu() and valor=="%" and valor=="**" and valor=="/" and 	valor=="==" and valor=="!=" and valor=="-")) return true;
	else return false;
}

pair<int, bool> token::prioritat() const{
    // Pre: true
    // Post: Indica el nivell de prioritat a 'first' i si l'associativitat és d'esquerra a dreta a 'second' del p.i.
    //       Considerem que els operands tenen el màxim nivell de prioritat
	pair<int, bool> res;
	if (this->es_operador_unari()){
		res.first=3;
		res.second=false;
		return res;
	}
	else if(this->es_operador_binari()){
		if (valor=="and"){
		res.first=2;
		res.second=true;
		return res;
		}
		else{
		res.first=1;
		res.second=true;
		return res;
		}
	}
	else if(valor=="==" or valor=="!="){
		res.first=4;
		res.second=true;
		return res;
	}
	else if(valor=="+" or valor=="-"){
		res.first=5;
		res.second=true;
		return res;
	}
	else if(valor=="*" or valor=="/" or valor=="%"){
		res.first=6;
		res.second=true;
		return res;
	}
	else if(valor=="**"){
		res.first=7;
		res.second=false;
		return res;
	}
	else{
		res.first=0;
		res.second=false;
		return res;
	}
}


int token::to_int() const{
	int numero;
	if(this->es_enter()){
		numero = stoi(valor);
		return numero;
	}
	return numero=0;
   
}

bool token::to_bool() const{
	if((valor=="T" or valor=="F") or (valor=="1" or valor=="0")) return true;
	else return false;
}

string token::to_string() const{
	return valor;
}

bool token::operator==(const token &t) const{
// Pre: t = TK
// Post: Indica si el token del p.i. és igual al token TK
if(valor==t.valor) return true;
else return false;
}

bool token::operator!=(const token &t) const{
// Pre: t = TK
// Post: Indica si el token del p.i. és diferent al token TK
if(valor!=t.valor) return true;
else return false;
}

istream& operator>>(istream& is, token &t){
// Pre: El canal is conté un string amb un contingut d'un token TK
// Post: t = TK
	is >> t.valor;
	return is;
}

ostream& operator<<(ostream& os, const token &t){
    // Pre: t = TK
    // Post: S'ha escrit al canal os el contingut del token TK
	os << t.valor;
	return os;
}


	



