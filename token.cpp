#include "token.hpp"
#include "string"
//constructors

token::token(){
	valor="0"
}

token::token(int i){
	int temp;
	while(i/10!=0){
		temp=i%10;
		i= i/10;
		temp =temp + 48;
		num = (char)temp + num;
	}
	i=i+48;
	valor = (char)i + num ;
}

token::token(bool b){
	if(b==true) valor="T";
	else valor="F";
}

token::token(string s){
	valor=s;
}

token::token(const char s[]){
	valor(s);
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

token::bool es_operador_commutatiu(){
	if(valor=="+" or valor=="*") return true;
	else return false;
}

token::bool es_boolea() const{
	if(valor="T" or valor="F") return true;
	else return false;
}
token::bool es_enter() const{
	bool trobat = true;
	for(unsigned int i = 0; i<=numero.size() and trobat; ++i){
		if(numero[0]== '-') trobat = true;
			else if (numero[i]<48 and numero[i]>57) trobat = false;
			else trobat = false;
	}
	return trobat;
}
token::bool es_variable(){
	if (not(valor.es_enter() and valor.es_boolea() and valor.es_operador_unari()
	valor.es_operador_binari() and valor.es_operador_commutatiu() and valor=="%"
	and valor=="**" and valor=="/" and valor=="==" and valor=="!=" and valor=="-")) return true;
	else return false;
}
pair<int, bool> prioritat() const;
    // Pre: true
    // Post: Indica el nivell de prioritat a 'first' i si l'associativitat és d'esquerra a dreta a 'second' del p.i.
    //       Considerem que els operands tenen el màxim nivell de prioritat


token::int to_int() const{
	int numero;
	if(valor.es_enter()){
		numero = stoi(valor);
		return numero;
	}
	return numero=0;
   
}

token::bool to_bool() const{
	if((valor="T" or valor="F") or (valor="1" or valor="0")) return true;
	else return false;
}

token::string to_string() const{
	return valor;
}

token::bool operator==(const token &t) const{
// Pre: t = TK
// Post: Indica si el token del p.i. és igual al token TK
if((valor==t.valor) return true;
else return false;
}

token::bool operator!=(const token &t) const{
// Pre: t = TK
// Post: Indica si el token del p.i. és diferent al token TK
if(valor!=t.valor) return true;
else return false;
}

friend istream& operator>>(istream& is, token &t){
// Pre: El canal is conté un string amb un contingut d'un token TK
// Post: t = TK
	



