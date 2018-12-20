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
    int id, saldo, historico, soma_pontos, uso_pontos, expirado, avista, soma_avista, aprazo, soma_pontualidade, num_cartao, classificacao, medalhas, votos, bonus_avaliacoes, saldo_historico;
    double soma_aprazo;
    string data_cadastro, estado_civil, tem_filhos, limite_disponivel, CNH, cartao_adicional, renda_familiar, profissao, outros_cartoes, sexo, num_solicitacao_cartao;
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
        if (indexColumn == 1){ cliente[indexClient].data_cadastro = token; return; }
        if (indexColumn == 2){ cliente[indexClient].num_cartao = atoi(token.c_str()); return; }
        if (indexColumn == 3){ cliente[indexClient].classificacao = atoi(token.c_str()); return; }
        if (indexColumn == 4){ cliente[indexClient].estado_civil = token; return; }
        if (indexColumn == 5){ cliente[indexClient].tem_filhos = token.c_str(); return; }
        if (indexColumn == 6){ cliente[indexClient].limite_disponivel = token.c_str(); return; }
        if (indexColumn == 7){ cliente[indexClient].medalhas = atoi(token.c_str()); return; }
        if (indexColumn == 8){ cliente[indexClient].CNH = token.c_str(); return; }
        if (indexColumn == 9){ cliente[indexClient].cartao_adicional = token.c_str(); return; }
        if (indexColumn == 10){ cliente[indexClient].votos = atoi(token.c_str()); return; }
        if (indexColumn == 11){ cliente[indexClient].renda_familiar = token; return; }
        if (indexColumn == 12){ cliente[indexClient].profissao = token; return; }
        if (indexColumn == 13){ cliente[indexClient].outros_cartoes = token; return; }
        if (indexColumn == 14){ cliente[indexClient].bonus_avaliacoes = atoi(token.c_str()); return; }
        if (indexColumn == 15){ cliente[indexClient].sexo = token.c_str(); return; }
        if (indexColumn == 16){ cliente[indexClient].num_solicitacao_cartao = token; return; }
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
        string headFileClientes = "data_cadastro | num_cartao | classificacao | estado_civil | tem_filhos | limite_disponivel | medalhas | CNH | cartao_adicional | votos | renda_familiar | profissao | outros_cartoes | bonus_avaliacoes | sexo | num_solicitacao_cartao | saldo_historico";
        string headFileBonus = "cliente | saldo | historico | soma_pontos | uso_pontos | expirado | avista | soma_avista | aprazo | soma_aprazo | soma_pontualidade | ";
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
            fileDados << cliente[i].data_cadastro << " | ";
            fileDados << cliente[i].num_cartao << " | ";
            fileDados << cliente[i].classificacao << " | ";
            fileDados << cliente[i].estado_civil << " | ";
            fileDados << cliente[i].tem_filhos << " | ";
            fileDados << cliente[i].limite_disponivel << " | ";
            fileDados << cliente[i].medalhas << " | ";
            fileDados << cliente[i].CNH << " | ";
            fileDados << cliente[i].cartao_adicional << " | ";
            fileDados << cliente[i].votos << " | ";
            fileDados << cliente[i].renda_familiar << " | ";
            fileDados << cliente[i].profissao << " | ";
            fileDados << cliente[i].outros_cartoes << " | ";
            fileDados << cliente[i].bonus_avaliacoes << " | ";
            fileDados << cliente[i].sexo << " | ";
            fileDados << cliente[i].num_solicitacao_cartao << " | ";
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
        cout << cliente[i].data_cadastro << "\t";
        cout << cliente[i].num_cartao << "\t";
        cout << cliente[i].classificacao << "\t";
        cout << cliente[i].estado_civil << "\t";
        cout << cliente[i].tem_filhos << "\t";
        cout << cliente[i].limite_disponivel << "\t";
        cout << cliente[i].medalhas << "\t";
        cout << cliente[i].CNH << "\t";
        cout << cliente[i].cartao_adicional << "\t";
        cout << cliente[i].votos << "\t";
        cout << cliente[i].renda_familiar << "\t";
        cout << cliente[i].profissao << "\t";
        cout << cliente[i].outros_cartoes << "\t";
        cout << cliente[i].bonus_avaliacoes << "\t";
        cout << cliente[i].sexo << "\t";
        cout << cliente[i].num_solicitacao_cartao << "\t";
        cout << cliente[i].saldo_historico << "\t" << endl;
    }
}


