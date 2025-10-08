#include <bits/stdc++.h> 
using namespace std; 

void S_to_I(fstream& input){
    cout << "Traduzindo de Sipser para Duplamente Infinita" << endl; 
    string line; 
    while(getline(input,line)) cout << line << endl; 

} 

void I_to_S(fstream& input){ 
    cout << "Traduzindo de Duplamente Infinita para Sipser" << endl;

}


int main(){ 
    fstream input; 
    input.open("MT1.in", ios::in); 

    if(!input) cout << "Erro ao ler a máquina de input." << endl; 
    else{ 
        string line; 
        getline(input,line); 
        if(line[1] == 'S') S_to_I(input); 
        else I_to_S(input); 
    } 
    
    input.close(); 
    return 0; 
} 
