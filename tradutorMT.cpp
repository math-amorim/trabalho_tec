#include <bits/stdc++.h> 
using namespace std; 

// current state, current symbol, new symbol, direction, new state 
// ; comentário 
// l - left, r - right, * - stay 
// halt - para, halt-accept - aceita 
// Auxiliares: #, &, %, £, ¢, § 

map < pair<string, char>, tuple<char,char,string> > converter(fstream& input){ 
    map <pair<string, char>, tuple<char,char,string>> funcao; 

    string from, to; char read, write, move; 
    
    while(true){ 
        if(!(input >> from >> read >> write >> move >> to)) break; 
        
        funcao[{from, read}] = {write, move, to} ;  
     } 
    /*  
     for(auto &[key, t] : funcao) {
          string from = key.first, to = get<2>(t);
          char read = key.second, write = get<0>(t), move = get<1>(t);
          cout << from << " " << read << " " << write << " " << move << " " << to << endl;
      }
    */ 

    return funcao; 
} 

void S_to_I(map<pair<string,char>, tuple<char,char,string>> funcao){
    cout << "Traduzindo de Sipser para Duplamente Infinita" << endl; 
  
    for(auto &[key, t] : funcao) { 
        string from = key.first, to = get<2>(t);
        char read = key.second, write = get<0>(t), move = get<1>(t);

    }     
    // (estado, simbolo) -> (novo_estado, novo_simbolo, direcao)
   

} 

void I_to_S(map<pair<string,char>, tuple<char,char,string>> funcao){ 
    cout << "Traduzindo de Duplamente Infinita para Sipser" << endl;

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
