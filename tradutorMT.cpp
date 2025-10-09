#include <bits/stdc++.h> 
using namespace std; 

// current state, current symbol, new symbol, direction, new state 
// ; comentário 
// l - left, r - right, * - stay 
// halt - para, halt-accept - aceita 
// Auxiliares: #, &, %, £, ¢, § 

struct T {
	char newsy;
	char d;
	string newst;
};

map<pair<string, char>, T> converter(fstream& input){ 
	map<pair<string, char>, T> funcao; 
    string from, to; char read, write, move; 
    
    while(true){ 
        if(!(input >> from >> read >> write >> move >> to)) break; 
		T aux;
		aux.newsy = write;
		aux.d = move;
		aux.newst = to;
        funcao[{from, read}] = aux;  
     } 
    /* for(auto &[key, t] : funcao) {
          string from = key.first, to = get<2>(t);
          char read = key.second, write = get<0>(t), move = get<1>(t);
          cout << from << " " << read << " " << write << " " << move << " " << to << endl;
    } */ 
    return funcao; 
} 

void S_to_I(map<pair<string,char>, T> funcao){
    cout << "Traduzindo de Sipser para Duplamente Infinita" << endl; 
    for(auto &[key, t] : funcao) { 
        string from = key.first, to = t.newst;
        char read = key.second, write = t.newsy, move = t.d;

    }     
} 

void I_to_S(map<pair<string,char>, T> funcao){ 
	cout << "Traduzindo de Duplamente Infinita para Sipser" << endl;
	for(auto &[key, t] : funcao) { 
		string from = key.first, to = t.newst; 
		char read = key.second, write = t.newsy, move = t.d; 
	}
}


int main(){ 
    fstream input; 
    input.open("MT1.in", ios::in); 

    if(!input) cout << "Erro ao ler a máquina de input." << endl; 
    else{ 
        string line; 
        getline(input,line); 
        if(line[1] == 'S') S_to_I(converter(input)); 
        else I_to_S(converter(input)); 
    } 
    input.close(); 
    return 0; 
} 
