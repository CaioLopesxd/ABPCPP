#include <iostream>
#include <vector>
#include <string> 


using namespace std;

class ItemBiblioteca {
protected:
    int id, ano;
    string titulo;
    bool emprestado;
    int idUsuarioEmprestimo; 

public:
    ItemBiblioteca(int id, string titulo, int ano) : id(id), ano(ano), titulo(titulo), emprestado(false), idUsuarioEmprestimo(-1) {};
    
    virtual void exibirDetalhes(){
        cout << "ID: " << id << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Ano: " << ano << endl;
        cout << "Emprestado: ";
        if(emprestado){ 
            cout << "Sim" << endl;
        }else{
            cout << "Nao" << endl;
        }
    };
    int getId(){
        return id;
    };
    bool isEmprestado(){
        return emprestado;
    };
    void emprestar(int idUsuario){
        if(emprestado){
            cout << "------------------------------" << endl;
            cout << "Item ja emprestado" << endl;
        }else{
            cout << "------------------------------" << endl;
            cout << "Item " << titulo << " emprestado" << endl;
            emprestado = true;
            idUsuarioEmprestimo = idUsuario; 
        }
    };
    void devolver(int idUsuario){
        if(emprestado && idUsuarioEmprestimo == idUsuario){
            cout << "------------------------------" << endl;
            cout << "Item " << titulo << " devolvido" << endl;
            emprestado = false;
            idUsuarioEmprestimo = -1; 
        }else if(!emprestado){
            cout << "------------------------------" << endl;
            cout << "Item ja devolvido" << endl;
        }else{
            cout << "------------------------------" << endl;
            cout << "Erro: Este livro foi emprestado por outro usuario" << endl;
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
        cout << "Emprestado: ";
        if(emprestado){ 
            cout << "Sim" << endl;
        }else{
            cout << "Nao" << endl;
        }
    };
};

class Usuario {
protected:
    int id, limiteEmprestimos, emprestimosAtuais;
    string nome;

public:
    Usuario(int id, string nome, int limiteEmprestimos) : id(id), limiteEmprestimos(limiteEmprestimos), emprestimosAtuais(0), nome(nome) {};
    
    virtual void exibirUsuario(){
        cout << "------------------------------" << endl;
        cout << "ID:                    " << id << endl;
        cout << "Nome:                  " << nome << endl;
        cout << "Limite de Emprestimos: " << limiteEmprestimos << endl;
        cout << "Emprestimos Atuais:    " << emprestimosAtuais << endl;
    };

    bool podeEmprestar(){
        return limiteEmprestimos > 0;
    };
    void realizarEmprestimo(){
        if(podeEmprestar()){
            emprestimosAtuais++;
            limiteEmprestimos--;
            cout << "------------------------------" << endl;
            cout << "Emprestimo realizado com sucesso!" << endl;
        }else{
            cout << "------------------------------" << endl;
            cout << "Limite de emprestimos atingido!" << endl;
        }
        
    };
    void realizarDevolucao(){
       if(emprestimosAtuais > 0){
            emprestimosAtuais--;
            limiteEmprestimos++;
            cout << "------------------------------" << endl;
            cout << "Devolucao realizada com sucesso!" << endl;
        }else{
            cout << "------------------------------" << endl;
            cout << "Erro: Nao ha emprestimos para devolver!" << endl;
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

    void emprestarLivro(int idLivro, int idUsuario){
        if (idLivro <= 0) {
            cout << "Livro nao encontrado!" << endl;
            return;
        }

        if (idUsuario <= 0) {
            cout << "Usuario nao encontrado!" << endl;
            return;
        }

        for(auto& livro : livros){
            if(livro.getId() == idLivro){
                if(livro.isEmprestado()){
                    cout << "------------------------------" << endl;
                    cout << "      Livro ja emprestado      " << endl;
                    return;
                }
            }
        }

        for(auto& aluno : alunos){
                if(aluno.getId() == idUsuario){
                    
                    if(aluno.podeEmprestar()){
                    aluno.realizarEmprestimo();
                    livros[idLivro - 1].emprestar(idUsuario);
                    cout << "--------------------------------" << endl;
                    cout << "Emprestimo realizado com sucesso!" << endl;
                    break;
                    }else{
                        cout << "--------------------------------" << endl;
                        cout << "Limite de emprestimos atingido!" << endl;
                        break;
                    }
                    
                }
        }
        for(auto& professor : professores){
                if(professor.getId() == idUsuario){
                    if(professor.podeEmprestar()){
                        professor.realizarEmprestimo();
                        livros[idLivro - 1].emprestar(idUsuario);
                        cout << "--------------------------------" << endl;
                        cout << "Emprestimo realizado com sucesso!" << endl;
                    break;
                    }else{
                        cout << "--------------------------------" << endl;
                        cout << "Limite de emprestimos atingido!" << endl;
                        break;

                    }
                }
        }
    
    };

    void devolverLivro(int idLivro, int idUsuario){
        if (idLivro <= 0) {
            cout << "Livro nao encontrado!" << endl;
            return;
        }

        if (idUsuario <= 0) {
            cout << "Usuario nao encontrado!" << endl;
            return;
        }

        for(auto& aluno : alunos){
            if(aluno.getId() == idUsuario){
                if(!livros[idLivro - 1].isEmprestado()){
                    cout << "------------------------------" << endl;
                    cout << "      Livro ja Devolvido      " << endl;
                    return;
                } else {
                    aluno.realizarDevolucao();
                    livros[idLivro - 1].devolver(idUsuario);
                    cout << "------------------------------" << endl;
                    cout << "Devolucao realizada com sucesso!" << endl;
                    return;
                }                    
            }
        }

        for(auto& professor : professores){
            if(professor.getId() == idUsuario){
                if(!livros[idLivro - 1].isEmprestado()){
                    cout << "------------------------------" << endl;
                    cout << "      Livro ja Devolvido      " << endl;
                    return;
                } else {
                    professor.realizarDevolucao();
                    livros[idLivro - 1].devolver(idUsuario);
                    cout << "------------------------------" << endl;
                    cout << "Devolucao realizada com sucesso!" << endl;
                    return;
                }                    
            }
        }
        


    };

    void menu(){
        cout << "------------------------------" << endl;
        cout << "             Menu             " << endl;
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

    int idLivro = 11;
    int opcao;
    string titulo, autor, genero;
    int ano;
    string nome;
    char tipo;
    int idUsuario = 5;
    

    Biblioteca biblioteca;
    biblioteca.adicionarLivro(1, "O Senhor dos Aneis", 1954, "J.R.R. Tolkien", "Fantasia");
    biblioteca.adicionarLivro(2, "Harry Potter", 1997, "J.K. Rowling", "Fantasia");
    biblioteca.adicionarLivro(3, "O Pequeno Principe", 1943, "Antoine de Saint-Exupery", "Infantil");
    biblioteca.adicionarLivro(4, "Dom Quixote", 1605, "Miguel de Cervantes", "Aventura");
    biblioteca.adicionarLivro(5, "A Arte da Guerra", 500, "Sun Tzu", "Filosofia");
    biblioteca.adicionarLivro(6, "A Metamorfose", 1915, "Franz Kafka", "Ficcao");
    biblioteca.adicionarLivro(7, "O Processo", 1925, "Franz Kafka", "Ficcao");
    biblioteca.adicionarLivro(8, "O Principe", 1532, "Nicolau Maquiavel", "Filosofia");
    biblioteca.adicionarLivro(9, "O Hobbit", 1937, "J.R.R. Tolkien", "Fantasia");
    biblioteca.adicionarLivro(10, "A Divina Comedia", 1320, "Dante Alighieri", "epico");
    biblioteca.adicionarUsuario('A', 1, "Joao");
    biblioteca.adicionarUsuario('A', 2, "Maria");
    biblioteca.adicionarUsuario('P', 3, "Jose");
    biblioteca.adicionarUsuario('P', 4, "Ana");
    system("cls");
    
    while (true) {
        biblioteca.menu();
        cout << "Digite a opcao desejada: ";
        cin >> opcao;

        switch (opcao) {

            case 0:
                cout << "Saindo..." << endl;
                return 0;
                break;

            case 1:
                system("cls");
                cout << "-=- Adicionar Livro -=-" << endl;

                cout << "Digite o Titulo do Livro: ";
                cin.ignore();
                getline(cin, titulo);
                
                cout << "Digite o ano de lancamento do Livro: ";
                cin >> ano;

                cout << "Digite o Autor do Livro: ";
                cin.ignore();
                getline(cin, autor);

                cout << "Digite o genero do Livro: ";
                getline(cin, genero);

                biblioteca.adicionarLivro(idLivro, titulo, ano, autor, genero);
                idLivro++;
                break;

            case 2:
                cout << "-=- Listagem de Livros -=-" << endl;
                biblioteca.listarLivros();
                break;

            case 3:
                system("cls");
                cout << "-=- Adicionar Usuario -=-" << endl;
                cout << "Digite o Nome do Usuario: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Digite o Tipo do Usuario (A - Aluno, P - Professor): ";
                cin >> tipo;
                
                biblioteca.adicionarUsuario(toupper(tipo), idUsuario, nome);
                idUsuario++;
                break;

            case 4:
                cout << "-=- Listagem de Usuarios -=-" << endl;
                biblioteca.listarUsuarios();
                break;

            case 5:
                system("cls");
                cout << "-=- Emprestar Livro -=-" << endl;
                cout << "Digite o ID do Livro: ";
                cin >> idLivro;
                cout << "Digite o ID do Usuario: ";
                cin >> idUsuario;
                biblioteca.emprestarLivro(idLivro, idUsuario);
                break;

            case 6:
                system("cls");
                cout << "-=- Devolver Livro -=-" << endl;
                cout << "Digite o ID do Livro: ";
                cin >> idLivro;
                cout << "Digite o ID do Usuario: ";
                cin >> idUsuario;
                biblioteca.devolverLivro(idLivro, idUsuario);
                break;

            default:
                cout << "Opcao invalida!" << endl;
                break;
        }
    }
    
    return 0;
}
