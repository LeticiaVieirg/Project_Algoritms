#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 5 
#define MAX_USERS 4
#define MAX_NOTES 3

typedef struct{
    char email[80];
    char password[80];
} User;

typedef struct{
    char nome[100]; 
    char autor[100];
    float hora_totalotal, hora_lida; 
    float porc_hora, media, notaex;
} Book; //disciplina

User users[MAX_USERS] = {
    {"user1@mail.com", "livro1"},
    {"user2@mail.com", "livro2"},
    {"user3@mail.com", "livro3"},
    {"user4@mail.com", "livro4"},
    };

Book livros[MAX_USERS][MAX_BOOKS];
float nota[MAX_USERS][MAX_NOTES][MAX_BOOKS];
int currentUser = -1; 
int verifadm;


void enter(); 
void loginOuCad(); 
void cadUser(int g);
int verifLogin(char *email, char *password); 
int simbolo(char *string); 
int verifEmail(char *string);
int verifLivro(); 
void inserirLivro();
void registLivro(int i); 
void menuPrincipal();
void preListLivro();
void listaLivros(int atualLivro);  
void cadNotaLivro(int atualLivro); 
char* verMedia(int atualLivro); 
void menuAdm(); 

void enter(){ 
    printf("Aperte 'ENTER' para  dar continuidade\n");
    while (getchar() != '\n');     
    getchar(); 
    system("cls");
}  

void loginRequest() {
    char nomeUsuario[50];
    char senhaUsuario[50];
    int escolha;
    static int atual = 0;

    printf("***AGENDA - RELACAO DE LIVROS***");
    printf("Deseja fazer login ou cadastrar?");
    printf("[1] Para login. \n");
	printf("[2] para cadastrar. \n");
    scanf("%d", &escolha);

    switch (escolha){
    case 1:
        do {
            printf("De início, realizaremos seu login. ");
            printf("Informe o nome de usuario: ");
            scanf("%49s", nomeUsuario); 
            printf("Informe sua senha: ");
            scanf("%49s", senhaUsuario); 

            if (verifLogin(nomeUsuario, senhaUsuario)) {
                printf("Login bem-sucedido!\n");
                enter();
                if(verifadm != 1 && !verifLivro()){
                inserirLivro();
                }
                menuPrincipal();
            } else {
                printf("Detectamos algo de errado! \n")
                printf("Nome de usuario ou senha incorretos! \n");
            }
        } while((verifLogin(nomeUsuario,senhaUsuario)) == 0);
        break;

    case 2:
        if (atual <= MAX_USERS) {
            cadUser(atual);
            atual++;
            loginRequest();
        } else {
            printf("Numero maximo de usuarios cadastrados atingido. \n");
            printf("favor contate o administrador para resolver\n");
            loginRequest();
        }
        break;

    default:
        printf("Escolha invalida!!\n");
        loginRequest();
        break;
    }
}

void cadUser(int g) {
    char inputEmail[85];
    char inputPass[85];
    int cademail = 0;
    do {
        printf("***AGENDA - RELACAO DE LIVROS***\n");
        printf("Digite o email para realizar o cadastro: \n");
        scanf(" %99s", inputEmail);
        if (!simbolo(inputEmail) || strlen(inputEmail) > 80 || !verifEmail(inputEmail)) {
            printf("Verificamos que o email informado é inválido!. \n");
            printf("Informe-nos um email valido que contém o '@'\n");
            cademail = 0;
        } else {cademail = 1; };
    } while (cademail != 1);
    do {
        printf(" Informe-nos a senha: \n");
        scanf(" %99s", inputPass);
        if (strlen(inputPass) < 8 || strlen(inputPass) > 80) {
            printf("Senha invalida!\n")
            printf("Informe-nos uma senha válida - deve ter entre 8 e 80 caracteres.\n");
        }
    } while (strlen(inputPass) < 8 || strlen(inputPass) > 80);
    strcpy(users[g].email, inputEmail);
    strcpy(users[g].password, inputPass);
    enter();
}

int loginVerif(char *email, char *password){
    const char login_adm[] = "admana";
    const char password_adm[] = "anadm";
    for (int i = 0; i < MAX_USERS; i++)
    {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0)
        {
            currentUser = i; 
            return 1;        
        }
    }
    if (strcmp(email, login_adm) == 0 && strcmp(password, password_adm) == 0) {
        verifadm = 1;
        currentUser = MAX_USERS + 1;
        return 1;
    }
    return 0; 
}

int simbolo(char *string) {
    return strchr(string, '@') != NULL;  
   
}

int verifEmail(char *string) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(string,users[i].email)) {
            return 1;  
        } 
    }
    return 0;  
}

int verifLivro() {
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (strlen(livros[currentUser][i].nome) > 0) {
            return 1;   
        }
    }
    return 0;  
}

void inserirLivro() {     
    int h;
    do {
        printf("Vamos inserir os Livros!")
        printf("Lembre-se o máximo de livros é 5.\n");
        scanf("%d", &h);
        if (h < 1 || h > MAX_BOOKS
    ) {
                printf("Informe um numero entre 1 e 5.\n");
            }
        system("cls");
    } while (h < 1 || h > MAX_BOOKS);
    for (int i = 0; i < h; i++) {
        registLivro(i);
    }
}

void registLivro(int i) {
    printf("***AGENDA - RELACAO DE LIVROS***");
    printf("Numero da livros a ser registrada: %d\n", i + 1);
    printf("Digite o nome da disciplina n %d: ", i + 1);
    scanf(" %99[^\n]", livros[currentUser][i].nome); 
    printf("Digite o nome do autor: ");
    scanf(" %99[^\n]", livros[currentUser][i].autor); 
    printf("Digite a quantidade de horas totais do livro: ");
    scanf("%f", &livros[currentUser][i].hora_total);
    livros[currentUser][i].hora_total = (livros[currentUser][i].hora_total * 3) / 6;
    printf("Digite a quantidade de horas ja lidas: ");
    scanf("%f", &livros[currentUser][i].hora_lida);
    livros[currentUser][i].hora_lida = (livros[currentUser][i].hora_lida * 3) / 6;
    printf("O livro foi cadastrado com sucesso!\n");
    enter();
    //considerar meia hora de leitura
}

void menuPrincipal() {
    const int EXIT_CODE = 14323;  
    int m = 0;
    int r;
    while (m != EXIT_CODE) {
        printf("Lista de livross cadastradas: \n");
        for (int i = 0; i < 5; i++) {
            printf("%d - %s\n", i + 1, livros[currentUser][i].nome);
        }
        printf("Digite o numero do livros para obter mais detalhes.\n");
        printf("[7] Para realizar logoff. \n");
        printf("[8] Para adicionar livros. \n");
        printf("[9] Para sair\n");
        if (verifadm == 1) {
            printf("[1234] Para acessar o Menu Adm. \n");
        }
        scanf("%d", &r);
        if (r >= 1 && r <= 6) {
            r = r - 1;  // Ajuste do índice
            preListMat(r);
        } else {
            switch (r) {
                case 1234:
                    system("cls");
                    adminMenu();
                    break;

                case 9:
                    printf("Obrigado por utilizar o Programa!!\n");
                    printf("Finalizando...\n");
                    enter();
                    m = EXIT_CODE;
                    break;

                case 8:
                    printf("Digite qual livros deseja inserir ou modificar: \n");
                    scanf("%d", &r);
                    r--;
                    system("cls");
                    registLivro(r);
                    break;

                case 7:
                    printf("Fazendo logoff...\n");
                    enter();
                    verifadm = 0;
                    m = EXIT_CODE;
                    loginRequest();
                    break;

                default:
                    printf("Opcao invalida!!\n");
                    enter();
                    break;
            }
        }
    }
}

void registLivro(int atualLivro){
    int h;
    do{
        system("cls");
        listMat(atualLivro);
        printf("Selecione uma opcao \n");
        printf("[1] para inserir notas\n");
        printf("[2] para sair\n");
        scanf("%d", &h);
        switch (h){
        case 1:
            cadNotaLivro(atualLivro);
            break;
        case 2:
            enter();
            break;
        default:
            printf("Dado invalido!\n");
            enter();
            break;
        }
    } while (h != 2);  
}

void listMat(int atualLivro) {
    printf("Nome do livro: %s\n", livros[currentUser][atualLivro].nome);
    printf("Autor: %s\n", livros[currentUser][atualLivro].autor);
    printf("Horas totais de Leitura: %.2f\n", livros[currentUser][atualLivro].hora_total);
    printf("Horas lidas: %.2f\n", livros[currentUser][atualLivro].hora_lida);
    livros[currentUser][atualLivro].porc_hora = (livros[currentUser][atualLivro].hora_lida / livros[currentUser][atualLivro].hora_total) * 100;
    printf("Porcentagem de horas lidas: %.2f%%\n", livros[currentUser][atualLivro].porc_hora);
    printf("Media do livro: %.2f\n", livros[currentUser][atualLivro].media);
    if (nota[currentUser][0][atualLivro] && nota[currentUser][1][atualLivro] && nota[currentUser][2][atualLivro]) {
        printf("Voce esta %s\n", verMedia(atualLivro));
    }
}

void cadNotaLivro(int atualLivro) {
    int l = 0;
    do {
        system("cls"); 
        for (int i = 0; i < MAX_NOTES; i++) {
            printf("Nota %d: %.1f\n", i + 1, nota[currentUser][i][atualLivro]);
        }
        printf("Qual nota deseja inserir? \n");
        printf("[4] Para sair\n");
        scanf("%d", &l);
        if (l >= 1 && l < 4) {
            printf("Digite a nota do livro %d: ", l);
            scanf("%f", &nota[currentUser][l - 1][atualLivro]); 
            printf("Nota inserida: %.1f\n", nota[currentUser][l - 1][atualLivro]);
            livros[currentUser][atualLivro].media = (nota[currentUser][0][atualLivro] + nota[currentUser][1][atualLivro] + nota[currentUser][2][atualLivro]) / 3;
            printf("Media: %.1f\n", livros[currentUser][atualLivro].media);
            enter();
        } else if (l == 4) {
            enter();
            break;
        } else {
            printf("Digite uma opcao valida!\n");
            enter();
        }
    } while (l != 4);
}

char* verMedia(int atualLivro) {
    float currentMedia = livros[currentUser][atualLivro].media;
    if (currentMedia >= 8) {
        return "Livro muito bom!";
    }
    else if (currentMedia < 8) {
        return "Leitura rasoável!";
    }
}

void adminMenu() {
    int escolhaMenu;
    int escolhaUser; 
    const char nulo[] = "";
    printf("Codigo de administrador encontrado\n");
    do {
        printf("Qual acao deseja?\n");
        printf("[1] Cadastrar.\n");
        printf("[2] Excluir.\n");
        printf("[0] Sair\n");
        scanf("%d", &escolhaMenu);
        switch (escolhaMenu) {
        case 1:
            for (int i = 0; i < MAX_USERS; i++){
                printf("Usuario %d: %s\n", i + 1, users[i].email);
            }
            printf("Qual usuario deseja inserir ou modificar?\n");
            scanf("%d", &escolhaUser);
            printf("O email registrado: %s\n", users[escolhaUser-1].email);
            cadUser(escolhaUser - 1);
            printf("Usuario atualizado com sucesso!\n");
            printf("email do Usuario: %s\n", users[escolhaUser - 1].email);
            printf("A senha eh %s\n", users[escolhaUser - 1].password);
            enter();
            system("cls");  
            break;

        case 2:
            for (int i = 0; i < MAX_USERS; i++){
                printf("Usuario %d: %s\n", i + 1, users[i].email);
				}
            printf("Qual usuario deseja excluir?\n");
            scanf("%d", &escolhaUser);
            printf("Deletando o usuario %d, de email: %s\n",escolhaUser,users[escolhaUser - 1].email);
            strcpy(users[escolhaUser - 1].email,nulo);
            strcpy(users[escolhaUser - 1].password,nulo);
        	printf("Usuário deletado. \n");
            enter();
            adminMenu();

        case 0:
            break;

        default:
            printf("Informe uma opcao valida!\n");
            enter();
            break;
        }
    } while (escolhaMenu != 0);
}

int main() {
    loginRequest();
    return 0;
}
