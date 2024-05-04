#include <iostream>
#include <fstream> // Para manipulacao de arquivos
#include <iomanip> // Para formatar CPF

using namespace std;

// Estrutura para armazenar informações do funcionário
struct Funcionario {
    string nome, cpf, dataNascimento, endereco, bairro, dataAdmissao, setor, cargo, beneficios;
    int idade;
    float salario;
};

// Funcao para cadastrar um novo funcionario
void cadastrarFuncionario() {
    Funcionario novoFuncionario;

    cout << "\nDigite o CPF: ";
    getline(cin, novoFuncionario.cpf);
    
    cout << "Digite o nome: ";
    getline(cin, novoFuncionario.nome);

    cout << "Digite a data de nascimento (DD/MM/AAAA): ";
    getline(cin, novoFuncionario.dataNascimento);

    cout << "Digite a idade: ";
    cin >> novoFuncionario.idade;
    cin.ignore(); // Limpar o buffer
    cout << "Digite o endereco: ";
    getline(cin, novoFuncionario.endereco);

    cout << "Digite o bairro: ";
    getline(cin, novoFuncionario.bairro);

    cout << "Digite a data de admissao (DD/MM/AAAA): ";
    getline(cin, novoFuncionario.dataAdmissao);

    cout << "Digite o setor: ";
    getline(cin, novoFuncionario.setor);

    cout << "Digite o cargo: ";
    getline(cin, novoFuncionario.cargo);

    cout << "Digite o salario: ";
    cin >> novoFuncionario.salario;
    cin.ignore(); // Limpar o buffer

    cout << "Digite os beneficios: ";
    getline(cin, novoFuncionario.beneficios);

    // Abre o arquivo para escrita
    ofstream arquivo("SWCADASTRO.txt", ios::app); // Abre o arquivo em modo de adicao

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo SWCADASTRO.txt para escrita." << endl;
        return;
    }

    // Escreve as informacoes no arquivo
    arquivo << "===== Novo Funcionario =====\n";
    arquivo << "CPF: " << novoFuncionario.cpf << endl;
    arquivo << "Nome: " << novoFuncionario.nome << endl;
    arquivo << "Data de Nascimento: " << novoFuncionario.dataNascimento << endl;
    arquivo << "Idade: " << novoFuncionario.idade << endl;
    arquivo << "Endereco: " << novoFuncionario.endereco << endl;
    arquivo << "Bairro: " << novoFuncionario.bairro << endl;
    arquivo << "Data de Admissao: " << novoFuncionario.dataAdmissao << endl;
    arquivo << "Setor: " << novoFuncionario.setor << endl;
    arquivo << "Cargo: " << novoFuncionario.cargo << endl;
    arquivo << "Salario: " << novoFuncionario.salario << endl;
    arquivo << "Beneficios: " << novoFuncionario.beneficios << endl;

    // Fecha o arquivo
    arquivo.close();

    cout << "\nAs Informacoes foram gravadas no arquivo SWCADASTRO.txt" << endl;
}

// Funcao para visualizar os funcionarios cadastrados
void visualizarFuncionarios() {
    ifstream arquivo("SWCADASTRO.txt");

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo SWCADASTRO.txt para leitura." << endl;
        return;
    }

    string linha;
    cout << "\n====== Funcionarios Cadastrados ======\n";
    while (getline(arquivo, linha)) {
        cout << linha << endl;
    }

    // Fecha o arquivo
    arquivo.close();
}

// Funcao para pesquisar funcionario por CPF
void pesquisarPorCPF() {
    string cpfBusca;
    cout << "\nDigite o CPF do funcionario que deseja pesquisar: ";
    getline(cin, cpfBusca);

    ifstream arquivo("SWCADASTRO.txt");

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo SWCADASTRO.txt para leitura." << endl;
        return;
    }

    string linha;
    bool encontrado = false;
    while (getline(arquivo, linha)) {
        if (linha.find("CPF: " + cpfBusca) != string::npos) {
            encontrado = true;
            cout << "\nFuncionario encontrado:\n";
            // Mostra todas as linhas com as informações do funcionário
            for (int i = 0; i < 11; ++i) {
                cout << linha << endl;
                getline(arquivo, linha);
            }
            break;
        }
    }

    // Fecha o arquivo
    arquivo.close();

    if (!encontrado) {
        cout << "\nFuncionario nao encontrado." << endl;
    }
}

// Funcao para excluir um funcionario por CPF
void excluirFuncionario() {
    string cpfBusca;
    cout << "\nDigite o CPF do funcionario que deseja excluir: ";
    getline(cin, cpfBusca);

    ifstream arquivoEntrada("SWCADASTRO.txt");
    ofstream arquivoTemp("temp.txt");

    // Verifica se os arquivos foram abertos corretamente
    if (!arquivoEntrada.is_open() || !arquivoTemp.is_open()) {
        cout << "Erro ao abrir o arquivo SWCADASTRO.txt para leitura ou ao criar o arquivo temporario." << endl;
        return;
    }

    string linha;
    bool encontrado = false;
    while (getline(arquivoEntrada, linha)) {
        if (linha.find("CPF: " + cpfBusca) != string::npos) {
            encontrado = true;
            // Pula as linhas do funcionario a ser excluido
            for (int i = 0; i < 11; ++i) {
                getline(arquivoEntrada, linha);
            }
        } else {
            arquivoTemp << linha << endl;
        }
    }

    // Fecha os arquivos
    arquivoEntrada.close();
    arquivoTemp.close();

    // Remove o arquivo original e renomeia o temporario
    if (encontrado) {
        remove("SWCADASTRO.txt");
        rename("temp.txt", "SWCADASTRO.txt");
        cout << "\nFuncionario excluido com sucesso!" << endl;
    } else {
        cout << "\nFuncionario nao encontrado." << endl;
    }
}

int main() {
    string usuario = "rh"; // Nome de usuário
    string senha = "123"; // Senha

    // Variáveis para armazenar a entrada do usuário
    string inputUsuario;
    string inputSenha;

    // Solicitação de login
    cout << "Por favor, realize o login para continuar.\n";
    cout << "Usuario: ";
    getline(cin, inputUsuario);

    cout << "Senha: ";
    getline(cin, inputSenha);

    // Verificação de login
    if (inputUsuario == usuario && inputSenha == senha) {
        cout << "Login bem-sucedido!\n";
        
        cout << "Bem-vindo ao sistema de cadastro de funcionarios!\n";

        int opcao;
        do {
            cout << "\n=== Menu ===" << endl;
            cout << "1. Cadastrar novo funcionario" << endl;
            cout << "2. Visualizar funcionarios cadastrados" << endl;
            cout << "3. Pesquisar funcionario por CPF" << endl;
            cout << "4. Excluir funcionario por CPF" << endl;
            cout << "5. Sair" << endl;
            cout << "Escolha uma opcao: ";
            cin >> opcao;
            cin.ignore(); // Limpar o buffer

            switch (opcao) {
                case 1:
                    cadastrarFuncionario();
                    break;
                case 2:
                    visualizarFuncionarios();
                    break;
                case 3:
                    pesquisarPorCPF();
                    break;
                case 4:
                    excluirFuncionario();
                    break;
                case 5:
                    cout << "Encerrando o programa." << endl;
                    break;
                default:
                    cout << "Opcao invalida. Tente novamente." << endl;
            }
        } while (opcao != 5);
    } else {
        cout << "Login ou senha incorretos. Encerrando o programa." << endl;
    }

    return 0;
}
