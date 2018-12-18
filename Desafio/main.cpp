//
//  main.cpp
//  Desafio
//
//  Created by Renata da Silva Nunes on 15/12/2018.
//  Copyright © 2018 Renata da Silva Nunes. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

using namespace std;
typedef struct {
    int id, saldo, historico, soma_pontos, uso_pontos, expirado, avista, soma_avista, aprazo, soma_pontualidade, c, d, h, k, o, saldo_historico;
    double soma_aprazo;
    string b, e, f, g, i, j, l, m, n, p, q;
} Cliente;
Cliente cliente[10];

bool openFiles();
void getData();
void setClient(string nameFile, int indexColumn, int indexClient, string token);
void orderCliente();
void setHeaders();
void closeFiles();
void setData();
void showDate();

ifstream fileBonus;
ifstream fileClientes;
ofstream fileDados;

int main(int argc, const char * argv[]) {
    getData();
    return 0;
}

void getData(){
    if (openFiles()) {
        int indexColumn = 0;
        int indexLine = 0;
        int indexClient=0;
        int contChar = 0;
        string token;
        string lineBonus;
        string lineClientes;
        
        for (int i=0; i<2; i++) {
            if (i == 0) {
                string nameFile = "bonus";
                while (getline(fileBonus, lineBonus)) {
                    if (indexLine != 0) {
                        istringstream stream (lineBonus);
                        while (getline (stream, token, ';')) {
                            indexColumn++;
                            setClient(nameFile, indexColumn, indexClient, token);
                        }
                        indexColumn = 0;
                        indexClient++;
                    }
                    indexLine = 1;
                }
                orderCliente();
            }
            else{
                indexColumn = 0;
                indexClient=0;
                string lineClientes;
                string nameFile = "clientes";
                while (getline(fileClientes, lineClientes)) {
                    istringstream stream (lineClientes);
                    while (getline (stream, token, ';')) {
                        indexColumn++;
                        if (contChar != 0) {
                            if (token == "") {
                                token = "NaN";
                            }
                            setClient(nameFile, indexColumn-1, indexClient, token);
                        }
                        contChar = 1;
                    }
                    indexColumn = 0;
                    indexClient++;
                }
            }
        }
        showDate();
        closeFiles();
        setData();
    }
}

bool openFiles(){
    fileBonus.open("../../../files/bonus.txt");
    fileClientes.open("../../../files/clientes.txt");
//    fileDados.open("../../../files/DADOS.txt",ios::app);
    if ((fileBonus.is_open())&&(fileClientes.is_open())) {
        return true;
    }
    return false;
}

void closeFiles(){
    fileBonus.close();
    fileClientes.close();
}

void setClient(string nameFile, int indexColumn, int indexClient, string token){
    if (nameFile == "bonus") {
        if (indexColumn == 1){ cliente[indexClient].id = atoi(token.c_str()); return; }
        if (indexColumn == 2){ cliente[indexClient].saldo = atoi(token.c_str()); return; }
        if (indexColumn == 3){ cliente[indexClient].historico = atoi(token.c_str()); return; }
        if (indexColumn == 4){ cliente[indexClient].soma_pontos = atoi(token.c_str()); return; }
        if (indexColumn == 5){ cliente[indexClient].uso_pontos = atoi(token.c_str()); return; }
        if (indexColumn == 6){ cliente[indexClient].expirado = atoi(token.c_str()); return; }
        if (indexColumn == 7){ cliente[indexClient].avista = atoi(token.c_str()); return; }
        if (indexColumn == 8){ cliente[indexClient].soma_avista = atoi(token.c_str()); return; }
        if (indexColumn == 9){ cliente[indexClient].aprazo = atoi(token.c_str()); return; }
        if (indexColumn == 10){ cliente[indexClient].soma_aprazo = stod(token); return; }
        if (indexColumn == 11){ cliente[indexClient].soma_pontualidade = atoi(token.c_str()); return; }
    }
    else{
        if (indexColumn == 1){ cliente[indexClient].b = token; return; }
        if (indexColumn == 2){ cliente[indexClient].c = atoi(token.c_str()); return; }
        if (indexColumn == 3){ cliente[indexClient].d = atoi(token.c_str()); return; }
        if (indexColumn == 4){ cliente[indexClient].e = token; return; }
        if (indexColumn == 5){ cliente[indexClient].f = token.c_str(); return; }
        if (indexColumn == 6){ cliente[indexClient].g = token.c_str(); return; }
        if (indexColumn == 7){ cliente[indexClient].h = atoi(token.c_str()); return; }
        if (indexColumn == 8){ cliente[indexClient].i = token.c_str(); return; }
        if (indexColumn == 9){ cliente[indexClient].j = token.c_str(); return; }
        if (indexColumn == 10){ cliente[indexClient].k = atoi(token.c_str()); return; }
        if (indexColumn == 11){ cliente[indexClient].l = token; return; }
        if (indexColumn == 12){ cliente[indexClient].m = token; return; }
        if (indexColumn == 13){ cliente[indexClient].n = token; return; }
        if (indexColumn == 14){ cliente[indexClient].o = atoi(token.c_str()); return; }
        if (indexColumn == 15){ cliente[indexClient].p = token.c_str(); return; }
        if (indexColumn == 16){ cliente[indexClient].q = token; return; }
    }
}

void calcSaldoHistorico(){
    for (int i=0; i<10; i++) {
        cliente[i].saldo_historico = cliente[i].saldo + cliente[i].historico;
    }
}

void orderCliente(){
    Cliente clienteAUX;
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            if (cliente[i].id < cliente[j].id) {
                clienteAUX = cliente[i];
                cliente[i] = cliente[j];
                cliente[j] = clienteAUX;
            }
        }
    }
}

void setData(){
    fileDados.open("../../../files/DADOS.txt",ios::app);
    if (fileDados.is_open()) {
        string headFileClientes = "data_cadastro | num_cartao | classificacao | estado_civil | tem_filhos | limite_disponivel | medalhas | CNH | cartao_adicional | votos | renda_familiar | profissao | outros_cartoes | bonus_avaliacoes | sexo | q | saldo_historico";
        string headFileBonus = "cliente | saldo | historico | soma_pontos | uso_pontos | expirado | avista | soma_avista | aprazo | soma_aprazo | soma_pontualidade";
        string headComplete = headFileBonus + " " + headFileClientes;
        cout << headComplete << endl;
        fileDados << headComplete << "\n";
        
        calcSaldoHistorico();
        for (int i=0; i<10; i++) {
            fileDados << cliente[i].id << " | ";
            fileDados << cliente[i].saldo << " | ";
            fileDados << cliente[i].historico << " | ";
            fileDados << cliente[i].soma_pontos << " | ";
            fileDados << cliente[i].uso_pontos << " | ";
            fileDados << cliente[i].expirado << " | ";
            fileDados << cliente[i].avista << " | ";
            fileDados << cliente[i].soma_avista << " | ";
            fileDados << cliente[i].aprazo << " | ";
            fileDados << cliente[i].soma_aprazo << " | ";
            fileDados << cliente[i].soma_pontualidade << " | ";
            
            fileDados << cliente[i].b << " | ";
            fileDados << cliente[i].c << " | ";
            fileDados << cliente[i].d << " | ";
            fileDados << cliente[i].e << " | ";
            fileDados << cliente[i].f << " | ";
            fileDados << cliente[i].g << " | ";
            fileDados << cliente[i].h << " | ";
            fileDados << cliente[i].i << " | ";
            fileDados << cliente[i].j << " | ";
            fileDados << cliente[i].k << " | ";
            fileDados << cliente[i].l << " | ";
            fileDados << cliente[i].m << " | ";
            fileDados << cliente[i].n << " | ";
            fileDados << cliente[i].o << " | ";
            fileDados << cliente[i].p << " | ";
            fileDados << cliente[i].q << " | ";
            fileDados << cliente[i].saldo_historico << endl;
        }
    }
    fileDados.close();
}

void showDate(){
    for (int i=0; i<10; i++) {
        cout << "\nCliente: " << i << endl;
        cout << cliente[i].id << "\t";
        cout << cliente[i].saldo << " \t";
        cout << cliente[i].historico << "\t";
        cout << cliente[i].soma_pontos << "\t";
        cout << cliente[i].uso_pontos << "\t";
        cout << cliente[i].expirado << "\t";
        cout << cliente[i].avista << "\t";
        cout << cliente[i].soma_avista << "\t";
        cout << cliente[i].aprazo << "\t";
        cout << cliente[i].soma_aprazo << "\t";
        cout << cliente[i].soma_pontualidade << "\t";
        cout << cliente[i].b << "\t";
        cout << cliente[i].c << "\t";
        cout << cliente[i].d << "\t";
        cout << cliente[i].e << "\t";
        cout << cliente[i].f << "\t";
        cout << cliente[i].g << "\t";
        cout << cliente[i].h << "\t";
        cout << cliente[i].i << "\t";
        cout << cliente[i].j << "\t";
        cout << cliente[i].k << "\t";
        cout << cliente[i].l << "\t";
        cout << cliente[i].m << "\t";
        cout << cliente[i].n << "\t";
        cout << cliente[i].o << "\t";
        cout << cliente[i].p << "\t";
        cout << cliente[i].q << "\t";
        cout << cliente[i].saldo_historico << "\t" << endl;
    }
}


