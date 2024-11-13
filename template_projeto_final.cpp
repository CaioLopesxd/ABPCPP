#include <iostream>
#include <vector>

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
            cout << "Item ja emprestado" << endl;
        }else{
            cout << "Item" << titulo << "emprestado" << endl;
            emprestado = true;
        }
    };
    void devolver(){
        if(emprestado){
            cout << "Item" << titulo << "devolvido" << endl;
            emprestado = false;
        }else{
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
        cout << "ID: " << id << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Ano: " << ano << endl;
        cout << "Autor: " << autor << endl;
        cout << "Genero: " << genero << endl;
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
        cout << "ID: " << id << endl;
        cout << "Nome: " << nome << endl;
        cout << "Limite de Emprestimos: " << limiteEmprestimos << endl;
        cout << "Emprestimos Atuais: " << emprestimosAtuais << endl;
    };

    bool podeEmprestar(){
        if(emprestimosAtuais < limiteEmprestimos){
            return true;
        }
        return false;
    };
    void realizarEmprestimo(){
        if(podeEmprestar()){
            
        }else{
            cout << "Usuario atingiu o limite de emprestimos" << endl;
        }
    };
    void realizarDevolucao(){};
    int getId(){
        return id;
    };
};

class Aluno : public Usuario {
public:
    Aluno(int id, string nome) : Usuario(id, nome, 3) {};
};

class Professor : public Usuario {
public:
    Professor(int id, string nome) : Usuario(id, nome, 5) {};
};

class Biblioteca {
    vector<Livro> livros;
    vector<Aluno> alunos;
    vector<Professor> professores;

public:
    void adicionarLivro(int id,string titulo,int ano,string autor,string genero){
        Livro livro(id, titulo, ano, autor, genero);
        livros.push_back(livro);
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
        for(auto aluno : alunos){
            aluno.exibirUsuario();
        }
        for(auto professor : professores){
            professor.exibirUsuario();
        }
    };
    void emprestarLivro(int idLivro, int idUsuario,char tipo){
        if(tipo == 'A'){
            alunos[idUsuario].realizarEmprestimo();
        }else if(tipo == 'P'){
            professores[idUsuario].realizarEmprestimo();
        }
        livros[idLivro].emprestar();
    };
    void devolverLivro(int idLivro, int idUsuario,char tipo){
        if(tipo == 'A'){
            alunos[idUsuario].realizarDevolucao();
        }else if(tipo == 'P'){
            professores[idUsuario].realizarDevolucao();
        }
        livros[idLivro].devolver();
    };
    void menu(){
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

    Biblioteca biblioteca;
    int opcao;
	
    while (true) {
        biblioteca.menu();
        cout << "Digite a opção desejada: ";
        cin >> opcao;

        switch (opcao) {
            case 0:
                cout << "Saindo..." << endl;
                return 0;

            case 1:
                cout << "opção 1" << endl;
                break;

            case 2:
                cout << "opção 2" << endl;
                break;

            case 3:
                cout << "opção 3" << endl;
                break;

            case 4:
                cout << "opção 4" << endl;
                break;

            case 5:
                cout << "opção 5" << endl;
                break;

            case 6:
                cout << "opção 6" << endl;
                break;

            default:
                cout << "Opção inválida!" << endl;
                break;
        }
    }
	
    return 0;
}
