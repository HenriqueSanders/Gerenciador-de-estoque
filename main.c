#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void main(){
    printf("\nGerenciador de estoque de materiais de obra... v1.0\n\n");
    int contador = -1;
    struct material produto[50];
    printf("Deseja iniciar o programa com estoque inicial para testes? (s ou n)\n");
    char option;
    option = getchar();
    fflush(stdin);
    if(option == 's' || option=='S'){
        char matriz[6][20] = {"Piso\n","Argamassa\n","Tinta preta\n","Tinta amarela\n","Saco de cimento\n","Tabuas de madeira\n"};
        for(int i = 0;i<6;i++){
            contador++;
            strcpy(produto[i].material,matriz[i]);
            produto[i].quantidade = (i+1)*10;
            produto[i].price = (i+1)*5;
        }
    }
    menu(contador,produto);
}

int menu(int contador,struct material *p){
    system("cls");
    char option;
    printf("\n|----- Gerenciador De Estoque -----|\n");
    printf("\nAperte 1 --- para mostrar o ESTOQUE COMPLETO");
    printf("\nAperte 2 --- para PESQUISAR no estoque");
    printf("\nAperte 3 --- para ADICIONAR produto ao estoque");
    printf("\nAperte 4 --- para REMOVER produto no estoque");
    printf("\nAperte 5 --- para ALTERAR produto do estoque");
    printf("\nAperte 0 --- para FECHAR o programa\n");
    option = getchar();
    switch (option){
        case '1': 
            mostrarEstoque(contador,p); 
        case '2': 
            pesquisarEstoque(contador,p); 
        case '3': 
            adicionarEstoque(contador,p); 
        case '4': 
            removerEstoque(contador,p); 
        case '5': 
            alterarEstoque(contador,p);
        case '0':
            exit(0);
        default: 
            menu(contador,p);
    }
}

void mostrarEstoque(int contador,struct material *p){
    system("cls");
    if(contador < 0){
        printf("\nEstoque vazio\n\n");
        system("pause");
        menu(contador,p);
    }
    for(int i=0;i<=contador;i++){
        mostrarProduto(i,p);
    }
    system("pause");
    menu(contador,p);
}

void pesquisarEstoque(int contador,struct material *p){
    system("cls");
    printf("Digite o nome do produto:");
    char pesquisa[30];
    fflush(stdin);
    fgets(pesquisa,30,stdin);
    toCase(pesquisa);
    int quantidade = 0;
    for(int i = 0;i<=contador;i++){
        int teste = 1;
        for(int j = 0;j<strlen(pesquisa)-1;j++){
            if(pesquisa[j]!=p[i].material[j]){
                teste = 0;
                break;
            }
        }
        if(teste==1){
            mostrarProduto(i,p);
            quantidade++;
        }
    }
    if(quantidade==0){
        printf("\nNenhum resultado para a busca\n\n");
    }else{
        printf("\n%d resultado(s) encontrado(s) na busca\n\n",quantidade);
    }
    char option;
    printf("Deseja fazer mais uma pesquisa? (s ou n)\n");
    option = getchar();
    if(option == 's' || option == 'S'){
        return pesquisarEstoque(contador,p); 
    }else{
        menu(contador,p);
    }
}

void adicionarEstoque(int contador,struct material *p){
    system("cls");
    contador++;
    printf("Digite o nome do material:");
    fflush(stdin);
    fgets(p[contador].material,30,stdin);
    toCase(p[contador].material);
    printf("Digite a quantidade do material:");
    scanf("%d%*c",&p[contador].quantidade);
    printf("Digite o preco do material:");
    scanf("%f%*c",&p[contador].price);
    printf("\nMaterial adicionado com sucesso no estoque\n\n");
    system("pause");
    menu(contador,p);
}

void removerEstoque(int contador,struct material *p){
    system("cls");
    if(contador==-1){
        mostrarEstoque(contador,p);
    }
    int id;
    printf("Digite o id do produto a ser retirado do estoque:");
    scanf("%d%*c",&id);
    if(!(id>=0 && id<=contador)){
        printf("\nProduto nao encontrado\n\n");
        system("pause");
        menu(contador,p);
    }
    mostrarProduto(id,p);
    printf("Tem certeza que deseja excluir este item do estoque? (s ou n)\n");
    char option;
    option = getchar();
    if(option == 's' || option == 'S'){
        int j = contador - id;
        for(int i = 0;i<=j;i++){
            p[id+i] = p[(id+i)+1];
        }
        printf("\nProduto retirado do estoque com sucesso\n\n");
        contador--;
    }else{
        printf("\nComando cancelado, voltando a tela inicial\n\n");
    }
    system("pause");
    menu(contador,p);
}

void alterarEstoque(int contador,struct material *p){
    system("cls");
    int id;
    printf("Digite o id do produto a ser alterado:");
    scanf("%d%*c",&id);
    if(!(id>=0 && id<=contador)){
        printf("\nProduto nao encontrado\n\n");
        system("pause");
        menu(contador,p);
    }else{
        mostrarProduto(id,p);
    }
    printf("Deseja mesmo alterar o produto? (s ou n)");
    char option = getchar();
    if(option == 'S' || option=='s'){
        char option;
        printf("Deseja alterar o nome? (s ou n)");
        fflush(stdin);
        option = getchar();
        if(option=='s' || option == 'S'){
            printf("\nAlterar o nome do produto:");
            fflush(stdin);
            fgets(p[id].material,30,stdin);
        }
        printf("Deseja alterar a quantidade do produto? (s ou n)");
        fflush(stdin);
        option = getchar();
        if(option=='s' || option == 'S'){
            printf("Alterar a quantidade do produto:");
            scanf("%d%*c",&p[id].quantidade);
        }
        printf("Deseja alterar o valor do produto? (s ou n)");
        fflush(stdin);
        option = getchar();
        if(option=='s' || option == 'S'){
            printf("Alterar o valor do produto:");
            scanf("%f",&p[id].price);
        }
        printf("\nProduto alterado com sucesso\n");
        mostrarProduto(id,p);
        system("pause");
        menu(contador,p);
    }else{
        menu(contador,p);
    }
    system("pause");
    menu(contador,p);
}

void toCase(char *p){
    for(int i = 0;i<strlen(p);i++){
        if(i==0){
            p[i] = toupper(p[i]);
        }else{
            p[i] = tolower(p[i]);
        }
    }
}

void mostrarProduto(int id,struct material *p){
    printf("\nID do pacote: %d\n",id);
    printf("Nome do material......... : %s",p[id].material);
    printf("Quantidade em estoque.... : %d\n",p[id].quantidade);
    printf("Preco por UNIDADE........ : R$ %.2f\n",p[id].price);
    printf("Valor total.............. : R$ %.2f\n\n",p[id].quantidade*p[id].price);
}