

#include <iostream>
#include <string>

class Produto {
private:
    std::string nome;
    bool validade;
    bool desconto;

public:
    Produto(std::string nome, bool validade, bool desconto) {
        this->nome = nome;
        this->validade = validade;
        this->desconto = desconto;
    }

    std::string pegaNome() {
      return nome;
    }

    bool taValido() {
      return validade;
    }

    bool temDesconto() {
      return desconto;
    }
};

class Verificador {
private:
    Verificador* proximo;
// testando comentario em java
public:
    void definirProximo(Verificador* proximo) {
        this->proximo = proximo;
    }

    virtual void verificar(Produto* produto) {
            proximo->verificar(produto);
    }
};

class VerificadorValidade : public Verificador {
public:
    void verificar(Produto* produto)  {
        if (produto->taValido()) {
            std::cout << "dentro da  validade";
        } else {
            std::cout << "fora  validade";
        }
        
    }
};

class VerificadorDesconto : public Verificador {

public:
    void verificar(Produto* produto) {
        if (produto->temDesconto()) {
           std::cout << " desconto";
        } else {
            std::cout << "sem  desconto";
        }
    }
};

int main() {
    Produto produto1("Produto 1", true, false);

    VerificadorValidade* verificadorValidade = new VerificadorValidade();
    VerificadorDesconto* verificadorDesconto = new VerificadorDesconto();

    verificadorValidade->definirProximo(verificadorDesconto);

    verificadorValidade->verificar(&produto1);

    return 0;
}


