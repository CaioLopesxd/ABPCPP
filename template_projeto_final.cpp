#include <iostream>
#include <vector>
#include <string> 

using namespace std;

class ItemBiblioteca {
protected:
    int id, ano;
    string titulo;
    bool emprestado;

public:
	ItemBiblioteca(int id, string titulo, int ano) : id(id), titulo(titulo), ano(ano), emprestado(false) {};
	
    virtual void exibirDetalhes(){
        cout << "ID: " << id << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Ano: " << ano << endl;
        cout << "Emprestado: " << emprestado << endl;
    };
    int getId(){
        return id;
    };
    bool isEmprestado(){
        if(!emprestado){
            return false;
        }
        return true;
    };
    void emprestar(){
        if(emprestado){
            cout << "5";
            cout << "------------------------------" << endl;
            cout << "Item ja emprestado" << endl;
        }else{
            cout << "6";
            cout << "------------------------------" << endl;
            cout << "Item " << titulo << " emprestado" << endl;
            emprestado = true;
        }
    };
    void devolver(){
        if(emprestado){
            cout << "------------------------------" << endl;
            cout << "Item " << titulo << " devolvido" << endl;
            emprestado = false;
        }else{
            cout << "------------------------------" << endl;
            cout << "Item ja devolvido" << endl;
        }
    };
};

class Livro : public ItemBiblioteca {
protected:
	string autor;
	string genero;
	
public:
    Livro(int id, string titulo, int ano, string autor, string genero) : ItemBiblioteca(id, titulo, ano), autor(autor), genero(genero) {};      
    void exibirDetalhes() override{
        cout << "------------------------------" << endl;

        cout << "ID:         " << id << endl;
        cout << "Titulo:     " << titulo << endl;
        cout << "Ano:        " << ano << endl;
        cout << "Autor:      " << autor << endl;
        cout << "Genero:     " << genero << endl;
        cout << "Emprestado: " << emprestado << endl;
    };
};

class Usuario {
protected:
    int id, limiteEmprestimos, emprestimosAtuais;
    string nome;

public:
    Usuario(int id, string nome, int limiteEmprestimos) : id(id), nome(nome), limiteEmprestimos(limiteEmprestimos), emprestimosAtuais(0) {};
        
    virtual void exibirUsuario(){
        cout << "------------------------------" << endl;

        cout << "ID:                    " << id << endl;
        cout << "Nome:                  " << nome << endl;
        cout << "Limite de Emprestimos: " << limiteEmprestimos << endl;
        cout << "Emprestimos Atuais:    " << emprestimosAtuais << endl;
    };

    bool podeEmprestar(){
        if(emprestimosAtuais -1 <= limiteEmprestimos){
            return true;
        }
        return false;
    };
    void realizarEmprestimo(){
        if(podeEmprestar()){
            cout << "3";
            emprestimosAtuais++;
            cout << "------------------------------" << endl;
            cout << "Emprestimo realizado com sucesso!" << endl;
            limiteEmprestimos--;
        }else{
            cout << "4";
            cout << "------------------------------" << endl;
            cout << "Usuario atingiu o limite de emprestimos" << endl;
        }
    };
    void realizarDevolucao(){
        if(emprestimosAtuais > 0){
            emprestimosAtuais--;
            limiteEmprestimos++;
            cout << "------------------------------" << endl;
            cout << "Devolucao realizada com sucesso!" << endl;
            return;
        }else{
            cout << "------------------------------" << endl;
            cout << "Nenhum emprestimo para devolver!" << endl;
        }
    };
    int getId(){
        return id;
    };
};

class Aluno : public Usuario {
public:
    Aluno(int id, string nome) : Usuario(id, nome, 3) {
        cout << "------------------------------" << endl;
        cout << "Aluno cadastrado com sucesso!" << endl;
    };
};

class Professor : public Usuario {
public:
    Professor(int id, string nome) : Usuario(id, nome, 5) {
        cout << "------------------------------" << endl;
        cout << "Professor cadastrado com sucesso!" << endl;
    };
};

class Biblioteca {
    vector<Livro> livros;
    vector<Aluno> alunos;
    vector<Professor> professores;

public:
    void adicionarLivro(int id, string titulo, int ano, string autor, string genero){
        Livro livro(id, titulo, ano, autor, genero);
        livros.push_back(livro);

        cout << "------------------------------" << endl;
        cout << "Livro cadastrado com sucesso! - "<< endl << titulo << endl;
    };

    void listarLivros(){
        for(auto livro : livros){
            livro.exibirDetalhes();
        }
    };
    
    void adicionarUsuario(char tipo, int id, string nome){
        if(tipo == 'A'){
            Aluno aluno(id, nome);
            alunos.push_back(aluno);
        }else if(tipo == 'P'){
            Professor professor(id, nome);
            professores.push_back(professor);
        }
    };

    void listarUsuarios(){
        cout << "------------------------------" << endl;
        cout << "            Alunos            " << endl;
        for(auto aluno : alunos){
            aluno.exibirUsuario();
        }
        cout << "------------------------------" << endl;
        cout << "          Professores         " << endl;
        for(auto professor : professores){
            professor.exibirUsuario();
        }
    };

    void emprestarLivro(int idLivro, int idUsuario,char tipo){
        if (idLivro <= 0) {
            cout << "Livro não encontrado!" << endl;
            return;
        }

        cout << "1";
        if(tipo == 'A'){
            cout << "2";
            for (auto& aluno : alunos) {
                    if (aluno.getId() == idUsuario) {
                        if (livros[idLivro - 1].isEmprestado()) {
                        cout << "------------------------------" << endl;
                        cout << "O livro já está emprestado!" << endl;
                        return;
                    }
                    if (!aluno.podeEmprestar()) {
                        cout << "------------------------------" << endl;
                        cout << "Usuário atingiu o limite de empréstimos!" << endl;
                        return;
                    }

                    livros[idLivro - 1].emprestar();
                    aluno.realizarEmprestimo();
                    return;
                }
            }
        }else if(tipo == 'P'){
            cout << "3";
            for (auto& professor : professores) {
                if (professor.getId() == idUsuario) {
                    if (livros[idLivro - 1].isEmprestado()) {
                        cout << "------------------------------" << endl;
                        cout << "O livro já está emprestado!" << endl;
                        return;
                    }
                    if (!professor.podeEmprestar()) {
                        cout << "------------------------------" << endl;
                        cout << "Usuário atingiu o limite de empréstimos!" << endl;
                        return;
                    }

                    livros[idLivro - 1].emprestar();
                    professor.realizarEmprestimo();
                    return;
                }
            }
        }
    };

    void devolverLivro(int idLivro, int idUsuario,char tipo){
       if(tipo == 'A'){
            for(auto aluno : alunos){
                if(aluno.getId() == idUsuario){
                    aluno.realizarDevolucao();
                    livros[idLivro].devolver();
        
                }
            }
        }else if(tipo == 'P'){
            for(auto professor : professores){
                if(professor.getId() == idUsuario){
                    professor.realizarDevolucao();
                    livros[idLivro].devolver();
                }
            }
        }
    };

    void menu(){
        cout << "------------------------------" << endl;
        cout << "             Meunu            " << endl;
        cout << "------------------------------" << endl;
        cout << "1 - Adicionar Livro" << endl;
        cout << "2 - Listar Livros" << endl;
        cout << "3 - Adicionar Usuario" << endl;
        cout << "4 - Listar Usuarios" << endl;
        cout << "5 - Emprestar Livro" << endl;
        cout << "6 - Devolver Livro" << endl;
        cout << "0 - Sair" << endl;
        cout << "------------------------------" << endl;
    };
};

int main() {

    int idLivro = 5;
    int opcao;
    string titulo, autor, genero;
    int ano;
    string nome;
    char tipo;
    int idUsuario = 6;
    

    Biblioteca biblioteca;
    biblioteca.adicionarLivro(1, "O Senhor dos Anéis", 1954, "J.R.R. Tolkien", "Fantasia");
    biblioteca.adicionarLivro(2, "Harry Potter", 1997, "J.K. Rowling", "Fantasia");
    biblioteca.adicionarLivro(3, "O Pequeno Príncipe", 1943, "Antoine de Saint-Exupéry", "Infantil");
    biblioteca.adicionarLivro(4, "Dom Quixote", 1605, "Miguel de Cervantes", "Aventura");
    biblioteca.adicionarUsuario('P', 1,"Caio Lopes");
    biblioteca.adicionarUsuario('A', 2,"Gustavo");
    biblioteca.adicionarUsuario('A', 3,"Calebe");
    biblioteca.adicionarUsuario('P', 4,"Artur");
    biblioteca.adicionarUsuario('A', 5,"Jhoni");
	
    while (true) {
        biblioteca.menu();
        cout << "Digite a opção desejada: ";
        cin >> opcao;

        switch (opcao) {

            case 0:
                cout << "Saindo..." << endl;
                return 0;
                break;

            case 1:
                cout << "-=- Adicionar Livro -=-" << endl;

                cout << "Digite o Titulo do Livro: ";
                cin >> titulo;
                
                cout << "Digite o ano de lançamento do Livro: ";
                cin >> ano;

                cout << "Digite o Nome do Autor: ";
                cin >> autor;

                cout << "Digite o genero do Livro: ";
                cin >> genero;

                biblioteca.adicionarLivro(idLivro, titulo, ano, autor, genero);
                idLivro++;
                break;

            case 2:
                cout << "-=- Listagem de Livros -=-" << endl;
                biblioteca.listarLivros();
                break;

            case 3:
                cout << "-=- Adicionar Usuario -=-" << endl;
                cout << "Digite o Nome do Usuario: ";
                cin >> nome;
                cout << "Digite o Tipo do Usuario (A - Aluno, P - Professor): ";
                cin >> tipo;
                biblioteca.adicionarUsuario(tipo, idUsuario, nome);
                idUsuario++;
                break;
            case 4:
                cout << "-=- Listagem de Usuarios -=-" << endl;
                biblioteca.listarUsuarios();
                break;

            case 5:
                cout << "-=- Emprestar Livro -=-" << endl;
                cout << "Digite o ID do Livro: ";
                cin >> idLivro;
                cout << "Digite o ID do Usuario: ";
                cin >> idUsuario;
                cout << "Digite o Tipo do Usuario (A - Aluno, P - Professor): ";
                cin >> tipo;
                biblioteca.emprestarLivro(idLivro, idUsuario, tipo);
                break;

            case 6:
                cout << "-=- Devolver Livro -=-" << endl;
                cout << "Digite o ID do Livro: ";
                cin >> idLivro;
                cout << "Digite o ID do Usuario: ";
                cin >> idUsuario;
                cout << "Digite o Tipo do Usuario (A - Aluno, P - Professor): ";
                cin >> tipo;
                biblioteca.devolverLivro(idLivro, idUsuario, tipo);
                break;
            default:
                cout << "Opção inválida!" << endl;
                break;
        }
    }
	
    return 0;
}
