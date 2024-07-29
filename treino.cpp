#include <iostream>
#include <memory>
#include <string>

// Componente principal
class Bebida {
public:
    virtual std::string obterDescricao() const = 0;
    virtual double custo() const = 0;
    virtual ~Bebida() = default;
};

// Implementação concreta do componente principal
class Cafe : public Bebida {
public:
    std::string obterDescricao() const override {
        return "Café";
    }

    double custo() const override {
        return 5.0;
    }
};

// Classe base para incrementar a funcionalidade
class Incremento : public Bebida {
protected:
    std::unique_ptr<Bebida> bebida;
public:
    Incremento(std::unique_ptr<Bebida> b) : bebida(std::move(b)) {}

    std::string obterDescricao() const override {
        return bebida->obterDescricao();
    }

    double custo() const override {
        return bebida->custo();
    }
};

// Implementação concreta do incremento
class Leite : public Incremento {
public:
    Leite(std::unique_ptr<Bebida> b) : Incremento(std::move(b)) {}

    std::string obterDescricao() const override {
        return bebida->obterDescricao() + ", Leite";
    }

    double custo() const override {
        return bebida->custo() + 1.0;
    }
};

// Implementação concreta do incremento
class Chocolate : public Incremento {
public:
    Chocolate(std::unique_ptr<Bebida> b) : Incremento(std::move(b)) {}

    std::string obterDescricao() const override {
        return bebida->obterDescricao() + ", Chocolate";
    }

    double custo() const override {
        return bebida->custo() + 2.0;
    }
};

int main() {
    // Criação de um café simples
    std::unique_ptr<Bebida> bebida = std::make_unique<Cafe>();
    std::cout << bebida->obterDescricao() << " custa " << bebida->custo() << " reais.\n";

    // Adicionando leite ao café
    bebida = std::make_unique<Leite>(std::move(bebida));
    std::cout << bebida->obterDescricao() << " custa " << bebida->custo() << " reais.\n";

    // Adicionando chocolate ao café com leite
    bebida = std::make_unique<Chocolate>(std::move(bebida));
    std::cout << bebida->obterDescricao() << " custa " << bebida->custo() << " reais.\n";

    return 0;
}

