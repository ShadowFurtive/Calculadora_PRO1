#include "calculadora.hpp"

/* La classe "calculadora" permet guardar expressions en les seves 26 memòries
   anomenades de la 'a' a la 'z' i avaluar expressions que usin expressions de
   les seves 26 memòries si fan menció a variables anomenades de la 'a' a la 'z' */


int calculadora::pos_vec(char c){
//Pre: True
//Post: En cas de que sigui una lletra de la 'a' a la 'z', retorna la seva posicio de memoria de [0..26]. Retorna 0 en cas de que no sigui una lletra.
    int x(c);
    if(x >= 97 and x <= 103){
        x = x%26;
        x = x-19;
        return x;
    }
    if(x >= 104 and x <= 122){
        x = x%26;
        x = x+7;
        return x;  
    }
    return 0;
}

expressio calculadora::char_to_exp(char c){
//Pre: True
//Post: Retorna una expressio creada apartir del caràcter c.
	string s(1, c);
	token t(s);
	expressio e(t);
	return e;
}

expressio calculadora::expandeix_padentro(list<token> &l, list<token>::iterator it, vector<bool> v, expressio e, vector<expressio> ve){
//Pre: l=L amb els operands de l'expressio, it=IT al principi de la llista, v=V amb 26 posicions i tot en false, e=E, ve=VE és la memoria.
// Post: Retorna l'expressió E expandint-la el màxim fent ús de les expressions guardades a VE. Si es detecta una circularitat retorna una expressió amb sola variable de nom   	"ERROR_expressions_circulars" 
	if(l.size() != 0 and it!=l.end()){
		token t;
		t = *it;
		string f = t.to_string();
		if((f[0] >= 97 and f[0] <= 122) and f.size()==1){
			int x = pos_vec(f[0]);
			expressio aux = ve[x];
			if(v[x] == false){
				e = e.expandeix(t, aux);
				v.insert(v.begin() + x, 1);
				l = e.operands();
				it = l.begin();
				e = expandeix_padentro(l, it, v, e, ve);
				/* HI: Guarda el resultat de la crida a e, expandint-la el màxim fent ús de les expressions guardades a VE. Quan hem accedit a una posició de la memoria, canvia el seu valor boolea en V a TRUE. Seguidament, e es la expressio E pero expandida amb la posició de memòria corresponent. El iterador IT torna a l'inici de la llista. Si es detecta una circularitat retorna una expressió amb sola variable de nom "ERROR_expressions_circulars" */
				//Fita: el nombre de false de V.
				return e;
			}		
			else{
				if(aux.arrel() != char_to_exp(f[0]).arrel()) {
					token err("ERROR_expressions_circulars");
					expressio we(err);
					return err;
				}
			}
		}
		it++;
		e = expandeix_padentro(l, it, v, e, ve);
		/* HI: Guarda el resultat de la crida a e, expandint-la el màxim fent ús de les expressiones guardades a VE. E es la expressio e pero expandida amb la posició de memòria corresponent i el iterador IT avança una posició. Si es detecta una circularitat retorna una expressió amb sola variable de nom "ERROR_expressions_circulars" */
		//FITA: El nombre d'elements que falten per que IT arribi a l.end().
	}
	return e;
}

calculadora::calculadora(){
// Pre: true
// Post: Crea una calculadora amb totes les memòries buides
	char a = 'a';
	expressio e = char_to_exp(a);
	for(int i = 0; i<26; i++){
		calcu.push_back(e);
		++a;
		e = char_to_exp(a);
	} 
}

calculadora::calculadora(const calculadora &c){
// Pre: c = C
// Post: Crea una calculadora a partir de la calculadora C (constructor per còpia)
	calcu = c.calcu;
}

calculadora& calculadora::operator=(const calculadora &c){
// Pre: c = C
// Post: Al p.i. se li ha assignat la calculadora C (operador assignació)
	if(this!=&c){
		calcu = c.calcu;
	}
	return *this;
}

calculadora::~calculadora(){
// Pre: True
// Post: S'ha destruït la calculadora del p.i. (destructora)

}

bool calculadora::es_buida(char v) const{
// Pre: v = V és un caràcter entre 'a' i 'z'
// Post: Indica si la memòria V conté una expressió formada per una única variable el nom de la qual és V
	int x = pos_vec(v);
	expressio s = calcu[x];
	if(s.arrel() == char_to_exp(v).arrel()) return true;
	else return false;
}

void calculadora::guarda(char v, const expressio &e){
// Pre: v = V és un caràcter entre 'a' i 'z', e = E
// Post: Guarda a la memòria V l'expressió E
	int x = pos_vec(v);
	calcu[x] = e;
}

void calculadora::elimina(char v){
// Pre: v = V és un caràcter entre 'a' i 'z'
// Post: Elimina l'expressió de la memòria V
	int x = pos_vec(v);
	calcu[x] = char_to_exp(v);
}

expressio calculadora::mostra(char v) const{
// Pre: v = V és un caràcter entre 'a' i 'z'
// Post: Retorna l'expressió de la memòria V sense avaluar-la
	int x = pos_vec(v);
	return calcu[x];
}

expressio calculadora::expandeix(char v) const{
// Pre: v = V és un caràcter entre 'a' i 'z'
// Post: Retorna l'expressió de la memòria V expandint-la
//       usant les memòries del p.i. tot el que es pugui
//       Si es detecta una circularitat retorna una expressió
//       amb sola variable de nom "ERROR_expressions_circulars"
	expressio e = this->mostra(v);
	list<token> l = e.operands();
	list<token>::iterator it = l.begin();
	vector<bool> b(26);
	e = expandeix_padentro(l, it, b, e, calcu);
	return e;
}

expressio calculadora::expandeix(const expressio &e) const{
// Pre: e = E
// Post: Retorna una expressió fruit d'expandir l'expressió E
//       usant les memòries del p.i. tot el que es pugui
//       Si es detecta una circularitat retorna una expressió
//       amb sola variable de nom "ERROR_expressions_circulars"
	list<token> l = e.operands();
	list<token>::iterator it = l.begin();;
	vector<bool> b(26);
	expressio j = expandeix_padentro(l, it, b, e, calcu);
	return j;
}

expressio calculadora::avalua(char v) const{
// Pre: v = V és un caràcter entre 'a' i 'z'
// Post: Retorna l'expressió de la memòria V expandint-la i avaluant-la
//       usant les memòries del p.i. tot el que es pugui
//       Si es detecta una circularitat retorna una expressió
//       amb sola variable de nom "ERROR_expressions_circulars"
	expressio e = this->expandeix(v);
	if(e.arrel() != "ERROR_expressions_circulars"){
		e = e.avalua();
		return e;
	}
	else return e;
}

expressio calculadora::avalua(const expressio &e) const{
// Pre: e = E
// Post: Retorna una expressió fruit d'expandir i avaluar l'expressió E
//       usant les memòries del p.i. tot el que es pugui
//       Si es detecta una circularitat retorna una expressió
//       amb sola variable de nom "ERROR_expressions_circulars"
	expressio f = this->expandeix(e);
	if(e.arrel() != "ERROR_expressions_circulars"){
		f = f.avalua();
		return f;
	}
	else return f;
}


















