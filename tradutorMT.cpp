#include <bits/stdc++.h> 
using namespace std; 

// current state, current symbol, new symbol, direction, new state 
// ; comentário 
// l - left, r - right, * - stay 
// halt - para, halt-accept - aceita 
// Auxiliares: #, &, %, £, ¢, § 

string caminho = "inputs/MT1.in", saida = "output/traducao.out"; 

struct T {
	string newsy;
	char d;
	string newst;
};

map<pair<string, string>, T> converter(fstream& input){ 
	map<pair<string, string>, T> funcao; 
    string line, from, read, write, to; char move; 
   
    while(getline(input,line)){ 
        if(line[0] == ';' or line.empty()) continue;
        
        stringstream ss(line); 

        if(!(ss >> from >> read >> write >> move >> to)) continue; 
             
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
    f[{"0", "1"}] = {"§", 'r', "shift1"}; 
    f[{"0", "0" }] = {"§", 'r', "shift0"};

    f[{"shift0", "1"}] = {"0", 'r', "shift1"}; 
    f[{"shift0", "0"}] = {"0", 'r', "shift0"};
    f[{"shift0", "_"}] = {"0", 'r', "set£"};

    f[{"shift1", "0"}] = {"1", 'r', "shift0"};
    f[{"shift1", "1"}] = {"1", 'r', "shift1"};
    f[{"shift1", "_"}] = {"1", 'r', "set£"};

    f[{"set£", "_"}] = {"£", 'l', "reset"}; 

    f[{"reset", "*"}] = {"*", 'l', "reset"};
    f[{"reset", "§"}] = {"*", 'r', "old0"};
       
   
    string previous, new_state;  
    for(auto &[key, t] : funcao) {  
        string from = key.first, to = t.newst, read = key.second, write = t.newsy; 
        char move = t.d;
        
        if(from == "0") from = "old0"; 
        if(to == "0") to = "old0"; 
      
        f[{from, read}] = {write, move, to};
        
        if(move == 'r'){ 
            new_state = "aux";
            new_state +=from; 
            f[{to, "£"}] = {"*", 'r', new_state}; 
            f[{new_state, "_"}] = {"£", 'l', new_state}; 
            f[{new_state, "£"}] = {"_", '*', to}; 
        } 
        
        if(move == 'l'){ 
           new_state = "shift_"; 
           new_state += to;  
           f[{to, "§"}] = { "*", 'r', new_state } ;

           f[{new_state, "0"}] = {"_", 'r', new_state + "_0"};  
           f[{new_state, "1"}] = {"_", 'r', new_state + "_1"}; 
        
           f[{new_state + "_0", "1"}] = {"0", 'r', new_state + "_1"}; 
           f[{new_state + "_0", "0"}] = {"0", 'r', new_state + "_0"};
           f[{new_state + "_0", "_"}] = {"0", 'r', "to_" + to};
           f[{new_state + "_0", "£"}] = {"0", 'r', "set_£_" + to};
           

           f[{new_state + "_1", "0"}] = {"1", 'r', new_state + "_0"};
           f[{new_state + "_1", "1"}] = {"1", 'r', new_state + "_1"};
           f[{new_state + "_1", "_"}] = {"1", 'r', "to_" + to};
           f[{new_state + "_1", "£"}] = {"1", 'r', "set_£_" + to};

           f[{"set_£_" + to, "_"}] = {"£", 'l', "to_" + to};

           f[{"to_"+to, "£"}] = {"_", 'r', "set_£_"+to};
           f[{"to_" + to, "*"}] = {"*", 'l', "to_" + to};
           f[{"to_" + to, "§"}] = {"*", 'r', to};

        } 
 
    }
    
    previous = "0"; 
     
    ofstream output(saida); 
    
    for(auto &[key, t] : f){ 
        string from = key.first, to = t.newst, read = key.second, write =     t.newsy;
        char move = t.d; 
       
        if(previous != from){ previous = from; output << endl; }  
          output << from << " " << read << " " << write << " " << move << " "     <<  to << endl;
         
    } 
}


int main(){ 
    fstream input; 
    input.open(caminho, ios::in); 

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
