#include <bits/stdc++.h> 
using namespace std; 

// current state, current symbol, new symbol, direction, new state 
// ; comentário 
// l - left, r - right, * - stay 
// halt - para, halt-accept - aceita 
// Auxiliares: #, &, %, £, ¢, § 

struct T {
	string newsy;
	char d;
	string newst;
};

map<pair<string, string>, T> converter(fstream& input){ 
	map<pair<string, string>, T> funcao; 
    string from, read, write, to; char move; 
    
    while(true){ 
        if(!(input >> from >> read >> write >> move >> to)) break; 
		T aux;
		aux.newsy = write;
		aux.d = move;
		aux.newst = to;
        funcao[{from, read}] = aux;  
     } 
    return funcao; 
} 

void S_to_I(map<pair<string,string>, T> funcao){
    cout << "Traduzindo de Sipser para Duplamente Infinita" << endl; 
    for(auto &[key, t] : funcao) { 
        string from = key.first, to = t.newst, read = key.second, write = t.newsy;
        char move = t.d;
    }     
} 

void I_to_S(map<pair<string,string>, T> funcao){ 
	cout << "Traduzindo de Duplamente Infinita para Sipser" << endl;
    map<pair<string,string>, T> f;
    // Pré-processamento.
    f[{"0", "1"}] = {"&", 'r', "first_blank"}; 
    f[{"0", "0" }] = {"#", 'r', "first_blank" }; 
    
    f[{"first_blank", "*" }] = {"*", 'r', "first_blank" };
    f[{"first_blank", "_" }] = {"£", 'l', "next" };

    f[{"next", "_" }] = {"_", 'l', "next" };
    f[{"next", "%" }] = {"*", 'l', "next" };
    f[{"next", "0" }] = {"%", 'r', "next0"};
    f[{"next", "1" }] = {"%", 'r', "next1"};
    f[{"next", "&" }] = {"§", 'r', "next1"};
    f[{"next", "#" }] = {"§", 'r', "next0"};
    f[{"next",  "§"}] = {"*", 'r', "old0"};

    f[{"next0","*"}] = {"0", 'l', "next"};
    f[{"next0", "0"}] = {"*", 'l', "next0"};
    f[{"next0","£"}] = {"0", 'r', "next0"};
    f[{"next0", "_"}] = {"£", 'l', "next0"}; 
    f[{"next0", "§"}] = {"*", 'r', "old0"}; 
   
    f[{"next1", "*"}] = {"1", 'l', "next"};
    f[{"next1", "1"}] = {"*", 'l', "next1"};
    f[{"next1", "£"}] = {"1", 'r', "next1"};
    f[{"next1", "_"}] = {"£", 'l', "next1"}; 
    f[{"next1","§"}] = {"*", 'r', "old0"}; 
   
    string ant = "0"; int flagl = 0, flagr= 0;  
    for(auto &[key, t] : funcao) {  
        string from = key.first, to = t.newst, read = key.second, write = t.newsy; 
        char move = t.d;
        
        if(ant != from) { flagr = 0; flagl = 0;  }

        if(move == 'r') flagr = 1; 

        if(from == "0") from = "old0"; 
        if(to == "0") to = "old0"; 
      
        f[{from, read}] = {write, move, to};
        
        if(flagr == 1 and write == "_"){ 
            f[{from, "£"}] = {"%", 'r', from}; 
            f[{from, "_"}] = {"£", 'l', from}; 
            f[{from, "%"}] = {"_", 'l', to}; 
        } 
        
        ant = from; 
    }
    
    ant = "0"; 
    for(auto &[key, t] : f){ 
        string from = key.first, to = t.newst, read = key.second, write =     t.newsy;
        char move = t.d; 
       
        if(ant != from){ ant = from; cout << endl; }  
        cout << from << " " << read << " " << write << " " << move << " "     <<  to << endl;
         
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
