// mediator
#include <iostream>
#include <string>

// Interface Mediador
class Mediador {
public:
    virtual void enviarMensagem( std::string mensagem, class Colega* colega) = 0;
};

class Colega {
protected:
    Mediador* mediador;

public:
    Colega(Mediador* med) : mediador(med) {}
    virtual void receberMensagem( std::string mensagem) = 0;
};


class Loja : public Colega {
public:
    Loja(Mediador* med) : Colega(med) {}

    void enviarMensagem( std::string mensagem) {
        mediador.enviarMensagem(mensagem);
    }

    void receberMensagem( std::string mensagem)  {
        std::cout << "Loja recebeu: " << mensagem << std::endl;
    }
};

class Cliente : public Colega {
public:
    Cliente(Mediador* med) : Colega(med) {}

    void enviarMensagem( std::string mensagem) {
        mediador.enviarMensagem(mensagem);
    }

    void receberMensagem( std::string mensagem)  {
        std::cout << mensagem << std::endl;
    }
};

class Fornecedor : public Colega {
public:
    Fornecedor(Mediador* med) : Colega(med) {}

    void enviarMensagem( std::string mensagem) {
        mediador.enviarMensagem(mensagem);
    }

    void receberMensagem( std::string mensagem)  {
        std::cout << mensagem << std::endl;
    }
};

class MediadorConcreto : public Mediador {
private:
    Loja* loja;
    Cliente* cliente;
    Fornecedor* fornecedor;

public:
    void definirLoja(Loja* loja) {
        this->loja = loja;
    }

    void definirCliente(Cliente* cliente) {
        this->cliente = cliente;
    }

    void definirFornecedor(Fornecedor* fornecedor) {
        this->fornecedor = fornecedor;
    }

    void enviarMensagem( std::string mensagem, Colega* colega)  {
        if (colega == loja) {
            cliente.receberMensagem(mensagem);
            fornecedor.receberMensagem(mensagem);
        } else if (colega == cliente) {
            loja.receberMensagem(mensagem);
        } else if (colega == fornecedor) {
            loja.receberMensagem(mensagem);
        }
    }
};

int main() {
    MediadorConcreto* mediador = new MediadorConcreto();

    Loja* loja = new Loja(mediador);
    Cliente* cliente = new Cliente(mediador);
    Fornecedor* fornecedor = new Fornecedor(mediador);

    mediador.definirLoja(loja);
    mediador.definirCliente(cliente);
    mediador.definirFornecedor(fornecedor);

    cliente.enviarMensagem("quero comprar  produto");
    loja.enviarMensagem("novo pedido  produto.");
    fornecedor.enviarMensagem("Produto enviado para a loja.");

    return 0;
}










//Chain of responsability
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

    std::string getNome() {
      return nome;
    }

    bool isValido() {
      return validade;
    }

    bool temDesconto() {
      return desconto;
    }
};

class Verificador {
private:
    Verificador* proximo;

public:
    void definirProximo(Verificador* proximo) {
        this->proximo = proximo;
    }

    virtual void verificar(Produto* produto) {
            proximo.verificar(produto);
    }
};

class VerificadorValidade : public Verificador {
public:
    void verificar(Produto* produto)  {
        if (produto.isValido()) {
            std::cout << "dentri da validade";
        } else {
            std::cout << "fora da validade";
        }
    }
};

class VerificadorDesconto : public Verificador {

public:
    void verificar(Produto* produto) {
        if (produto.temDesconto()) {
           std::cout << " desconto";
        } else {
            std::cout << "sem  desconto";
        }
    }
};

int main() {
    Produto produto1("Produto 1", true, false);
    Produto produto2("Produto 2", false, true);

    VerificadorValidade* verificadorValidade = new VerificadorValidade();
    VerificadorDesconto* verificadorDesconto = new VerificadorDesconto();

    verificadorValidade.definirProximo(verificadorDesconto);

    verificadorValidade.verificar(&produto1);
    verificadorValidade.verificar(&produto2);

    return 0;
}








//Command
#include <iostream>

class Luz {
public:
    void ligar() {
        std::cout << " luz  LIGADA" << std::endl;
    }

    void desligar() {
        std::cout << " luz  DESLIGADA" << std::endl;
    }
};

class ComandoLigarLuz {
private:
    Luz* luz;
public:
    ComandoLigarLuz(Luz* l) : luz(l) {}

    void executar() {
        luz.ligar();
    }
};

class ComandoDesligarLuz {
private:
    Luz* luz;
public:
    ComandoDesligarLuz(Luz* l) : luz(l) {}

    void executar() {
        luz.desligar();
    }
};

class ControleRemoto {
private:
    ComandoLigarLuz* comandoLigar;
    ComandoDesligarLuz* comandoDesligar;
public:
    void definirComandoLigar(ComandoLigarLuz* comando) {
        comandoLigar = comando;
    }

    void definirComandoDesligar(ComandoDesligarLuz* comando) {
        comandoDesligar = comando;
    }

    void apertarBotaoLigar() {
        comandoLigar.executar();
    }

    void apertarBotaoDesligar() {
        comandoDesligar.executar();
    }
};

int main() {
    Luz* luzSala = new Luz();

    ComandoLigarLuz* ligarLuz = new ComandoLigarLuz(luzSala);
    ComandoDesligarLuz* desligarLuz = new ComandoDesligarLuz(luzSala);

    ControleRemoto controle;
    controle.definirComandoLigar(ligarLuz);
    controle.definirComandoDesligar(desligarLuz);

    controle.apertarBotaoLigar();
    controle.apertarBotaoDesligar();



    return 0;
}








//state
#include <iostream>

class PortaAutomatica;

class Estado {
public:
    virtual ~Estado() = default;
    virtual void abrir(PortaAutomatica porta) = 0;
    virtual void fechar(PortaAutomatica porta) = 0;
    virtual void parar(PortaAutomatica porta) = 0;
};

class PortaAutomatica {
public:
    PortaAutomatica();
    void definirEstado(Estado* novoEstado) {
        this->estado = novoEstado;
    }
    void abrir() {
        this->estado->abrir();
    }
    void fechar() {
        this->estado->fechar();
    }
    void parar() {
        this->estado->parar();
    }
private:
    Estado* estado;
};

class EstadoAberto : public Estado {
public:
    void abrir(PortaAutomatica porta)  {
        std::cout << "A porta já está aberta." << std::endl;
    }
    void parar(PortaAutomatica porta)  {
        std::cout << "A porta está aberta" << std::endl;
    }
};

class EstadoFechado : public Estado {
public:
    void abrir(PortaAutomatica porta) ;
    void fechar(PortaAutomatica porta)  {
        std::cout << "A porta já esta fechada." << std::endl;
    }
    void parar(PortaAutomatica porta)  {
        std::cout << "A porta esta fechada e no pode ser parada." << std::endl;
    }
};

class EstadoMovendo : public Estado {
public:
    void abrir(PortaAutomatica porta)  {
        std::cout << "A porta está se movendo. Parando e abrindo a porta." << std::endl;
   
    }
    void fechar(PortaAutomatica porta)  {
        std::cout << "A porta está se movendo. Parando e fechando a porta." << std::endl;

    }
    void parar(PortaAutomatica porta)  {
        std::cout << "A porta parou de se mover." << std::endl;
    }
};

void EstadoAberto::fechar(PortaAutomatica porta) {
    std::cout << "Fechando a porta." << std::endl;
 
}

void EstadoFechado::abrir(PortaAutomatica porta) {
    std::cout << "Abrindo a porta." << std::endl;
  
}

PortaAutomatica::PortaAutomatica() {
    this->estado = new EstadoFechado();
}

int main() {
    PortaAutomatica* porta = new PortaAutomatica();
    PortaAutomatica* outraPorta = new PortaAutomatica();  

    porta->abrir();
    porta->fechar();
    porta->parar();
    porta->abrir();
    porta->parar();
    porta->fechar();
    porta->parar();

    outraPorta->abrir();
    outraPorta->fechar();
    return 0;
}









//Visitor
#include <iostream>

class CachorroQuente;
class Sorvete;

class Visitante {
public:
    virtual void visitarCachorroQuente(CachorroQuente* cachorroQuente) {}
    virtual void visitarSorvete(Sorvete* sorvete) {}
};

class Produto {
public:
    virtual void aceitar(Visitante* visitante) {}
};

class CachorroQuente : public Produto {
  private:
    double preco;
  
  public:
    CachorroQuente(double preco) {
        this->preco = preco;
    }
    double obterPreco() { 
      return preco; 
    }

    void aceitar(Visitante* visitante)  {
        visitante.visitarCachorroQuente();
    }
};

class Sorvete : public Produto {
  private:
    double preco;
  
  public:
    Sorvete(double preco) {
        this->preco = preco;
    }

    double obterPreco() {
      return preco; 
    }

    void aceitar(Visitante* visitante)  {
        visitante.visitarSorvete();
    }
};

class VisitantePreco : public Visitante {
public:
    void visitarCachorroQuente(CachorroQuente* cachorroQuente)  {
        std::cout << "Preço do Cachorro Quente: " << cachorroQuente.obterPreco() << std::endl;
    }

    void visitarSorvete(Sorvete* sorvete)  {
        std::cout << "Preç Sorvete: " << sorvete.obterPreco() << std::endl;
    }
};

int main() {
    CachorroQuente* cachorroQuente = new CachorroQuente(2.50);
    Sorvete* sorvete = new Sorvete(1.75);

    VisitantePreco* visitantePreco = new VisitantePreco();

    cachorroQuente.aceitar(visitantePreco);
    sorvete.aceitar(visitantePreco);
    return 0;
}













//Template method
#include <iostream>

class Bolo {
public:
    
    void FazerBolo() {
        PrepararIngredientes();
        MisturarIngredientes();
        Assar();
        AdicionarCobertura();
    }

protected:
    virtual void PrepararIngredientes() {
        std::cout << "Preparar ingredientes  para o bolo" << std::endl;
    }

    virtual void MisturarIngredientes() {
        std::cout << "Misturar ingredientes." << std::endl;
    }

    virtual void Assar() {
        std::cout << "Assar " << std::endl;
    }

    virtual void AdicionarCobertura() = 0; 
};

class BoloDeChocolate : public Bolo {
protected:
    void AdicionarCobertura()  {
        std::cout << "cobertura de chocolate" << std::endl;
    }
};

class BoloDeMorango : public Bolo {
protected:
    void AdicionarCobertura()  {
        std::cout << "cobertura de morango" << std::endl;
    }
};

int main() {
    Bolo* boloChocolate = new BoloDeChocolate();
    Bolo* boloMorango = new BoloDeMorango();

    std::cout << "Bolo de Chocolate:" << std::endl;
    boloChocolate.FazerBolo();

    std::cout << "Bolo de Morango:" << std::endl;
    boloMorango.FazerBolo();

    return 0;
}

















//memento
#include <iostream>
#include <vector>
#include <string>


class Memento {
private:
    std::string estado;

public:
    Memento( std::string estado) : estado(estado) {}
    std::string getEstado(){ 
      return estado; 
    }
};


class Editor {
private:
    std::string conteudo;

public:
    void setConteudo( std::string novoConteudo) { 
      conteudo = novoConteudo; 
    }

    std::string getConteudo()  {
      return conteudo; 
    }

    Memento salvar()  {
      return Memento(conteudo); 
    }

    void restaurar( Memento memento) {
      conteudo = memento.getEstado(); 
    }
};

// Classe Cuidador
class Cuidador {
private:
    std::vector<Memento> historico;
    Editor editor;

public:
    Cuidador(Editor editor) : editor(editor) {}
    void backup() {
      historico.push_back(editor.salvar()); 
    }

    void desfazer() {
        historico.pop_back();
    }
};

// Exemplo de uso
int main() {
    Editor* editor = new Editor();
    Cuidador* cuidador = new Cuidador(*editor);

    editor.setConteudo("Versão 1");
    cuidador.backup();
    std::cout << editor.getConteudo() << std::endl;


    return 0;
}












// iterator
#include <iostream>

class Iterador {

private:
    int* atual;

public:
    Iterador(int* inicio) {
        atual = inicio;
    }
    
    int valor() {
        return *atual;
    }

    void avancar() {
        ++atual;
    }

    bool diferente(Iterador outro) {
        return atual != outro.atual;
    }

};

class Colecao {
private:
    const int tamanho = 3;

    int dados[tamanho];

public:
    Colecao() {
        dados[0] = 1;
        dados[1] = 2;
        dados[2] = 3;
    }

    Iterador inicio() {
        return Iterador(dados);
    }

    Iterador fim() {
        return Iterador(dados + tamanho);
    }
};

int main() {
    Colecao colecao;
    for (int i = 0; i < colecao.tamanho(); ++i) {
      std::cout << colecao[i];
    }
    std::cout << std::endl;
    return 0;
}














//Composite
#include <iostream>
#include <vector>
#include <string>

class Decoracao {
public:
    virtual void exibir() const = 0;
};

class Balao : public Decoracao {
public:
    void exibir() {
        std::cout << "Balão" << std::endl;
    }
};

class Bandeirinha : public Decoracao {
public:
    void exibir(){
        std::cout << "Bandeirinha" << std::endl;
    }
};

class Luz : public Decoracao {
public:
    void exibir(){
        std::cout << "Luz" << std::endl;
    }
};

class PacoteDecoracao : public Decoracao {
private:
    std::vector<Decoracao*> decoracoes; 
public:
    void adicionar(Decoracao* decoracao) {
        decoracoes.push_back(decoracao);
    }

    void exibir(){
      for (int i = 0; i < decoracoes.size(); ++i) {
        decoracoes[i].exibir();
      }
    }
};

int main() {
    Balao* balao = new Balao();
    Bandeirinha* bandeirinha = new Bandeirinha();
    Luz* luz = new Luz();

    PacoteDecoracao* pacote = new PacoteDecoracao();
    pacote.adicionar(balao);
    pacote.adicionar(bandeirinha);
    pacote.adicionar(luz);

    pacote.exibir();  



    return 0;
}











// Decorator
#include <iostream>
#include <string>

class Cafe {
public:
    virtual std::string descricao() = 0;
    virtual double preco() = 0;
};

class CafeSimples : public Cafe {
public:
    std::string descricao() {
        return "Cafe Simples";
    }

    double preco() {
        return 5.0;
    }
};

class DecoradorCafe : public Cafe {
protected:
    Cafe* cafe;
public:

    DecoradorCafe(Cafe* c) {
        cafe = c;
    }
};

class Leite : public DecoradorCafe {
public:

    Leite(Cafe* c) : DecoradorCafe(c) {
        cafe = c;
    }

    std::string descricao() {
        return cafe.descricao() + ", Leite";
    }

    double preco() {
        return cafe.preco() + 1.5;
    }
};

class Acucar : public DecoradorCafe {
public:

    Acucar(Cafe* c) : DecoradorCafe(c) {
        cafe = c;
    }

    std::string descricao() {
        return cafe.descricao() + ", acuacar";
    }

    double preco() {
        return cafe.preco() + 0.5;
    }
};

class Chocolate : public DecoradorCafe {
public:
    Chocolate(Cafe* c) : DecoradorCafe(c) {
        cafe = c;
    }

    std::string descricao() {
        return cafe.descricao() + ", Chocolate";
    }

    double preco() {
        return cafe.preco() + 2.0;
    }
};

int main() {
    Cafe* meuCafe = new CafeSimples();

    meuCafe = new Leite(meuCafe);
    meuCafe = new Acucar(meuCafe);
    meuCafe = new Chocolate(meuCafe);

    std::cout << meuCafe.descricao() <<  meuCafe.preco() <<;

    return 0;
}













// adapter
#include <iostream>

class ProcessadorPagamento {
public:
    virtual void processarPagamento(double valor) = 0;
};

class PayPal {
public:
    void enviarPagamento(double valor) {
        std::cout << valor << std::endl;
    }
};

class Stripe {
public:
    void realizarPagamento(double valor) {
        std::cout << valor << std::endl;
    }
};

class Square {
public:
    void completarPagamento(double valor) {
        std::cout << valor << std::endl;
    }
};

class AdaptadorPayPal : public ProcessadorPagamento {
private:
    PayPal* payPal;
public:
    AdaptadorPayPal(PayPal* payPal) {
        this->payPal = payPal;
    }

    void processarPagamento(double valor)  {
        payPalenviarPagamento(valor);
    }
};

class AdaptadorStripe : public ProcessadorPagamento {
private:
    Stripe* stripe;
public:
    AdaptadorStripe(Stripe* stripe) {
        this->stripe = stripe;
    }

    void processarPagamento(double valor)  {
        striperealizarPagamento(valor);
    }
};

class AdaptadorSquare : public ProcessadorPagamento {
private:
    Square* square;
public:
    AdaptadorSquare(Square* square) {
        thissquare = square;
    }

    void processarPagamento(double valor)  {
        squarecompletarPagamento(valor);
    }
};

int main() {
    PayPal* paypal = new PayPal();
    Stripe* stripe = new Stripe();
    Square* square = new Square();

    ProcessadorPagamento* adaptadorPayPal = new AdaptadorPayPal(paypal);
    ProcessadorPagamento* adaptadorStripe = new AdaptadorStripe(stripe);
    ProcessadorPagamento* adaptadorSquare = new AdaptadorSquare(square);

    adaptadorPayPalprocessarPagamento(100.0);
    adaptadorStripeprocessarPagamento(200.0);
    adaptadorSquareprocessarPagamento(300.0);


    return 0;
}












//bridge
#include <iostream>
#include <string>

class Arma {
public:
    virtual void usarArma() = 0;
};

class Espada : public Arma {
public:
    void usarArma()  {
        std::cout << "espada.\n";
    }
};

class Laser : public Arma {
public:
    void usarArma()  {
        std::cout << " laser.\n";
    }
};

class Boneco {
protected:
    Arma* arma;

    Boneco(Arma* a) : arma(a) {}

public:
    virtual void atacar() = 0;
};

class SuperHeroi : public Boneco {
public:
    SuperHeroi(Arma* a) : Boneco(a) {}

    void atacar()  {
        std::cout << "Super heroi  ";
        arma.usarArma();
    }
};

class Vilao : public Boneco {
public:
    Vilao(Arma* a) : Boneco(a) {}

    void atacar()  {
        std::cout << "Vilao  ";
        arma.usarArma();
    }
};

int main() {
    Arma* espada = new Espada();
    Arma* laser = new Laser();

    Boneco* heroi = new SuperHeroi(espada);
    Boneco* vilao = new Vilao(laser);

    heroi.atacar();
    vilao.atacar();

    return 0;
}










// facade
#include <iostream>

class TV {
public:
    void ligar() {
        std::cout << "TV ligada." << std::endl;
    }

    void selecionarEntrada() {
        std::cout << "Entrada da TV selecionada para DVD." << std::endl;
    }
};

class ReprodutorDeDVD {
public:
    void ligar() {
        std::cout << "DVD ligado" << std::endl;
    }

    void reproduzir() {
        std::cout << " DVD iniciado" << std::endl;
    }
};

class SistemaDeSom {
public:
    void ligar() {
        std::cout << "Som ligado." << std::endl;
    }

    void ajustarVolume() {
        std::cout << "Volume ajustado " << std::endl;
    }
};

// Facade
class ControleRemoto {
private:
  TV* tv;
  ReprodutorDeDVD* reprodutorDeDVD;
  SistemaDeSom* sistemaDeSom;

public:
  ControleRemoto(TV* tv, ReprodutorDeDVD* reprodutorDeDVD, SistemaDeSom* sistemaDeSom) {
    this->tv = tv;
    this->reprodutorDeDVD = reprodutorDeDVD;
    this->sistemaDeSom = sistemaDeSom;
  }


    void assistirFilme() {
        tv.ligar();
        tv.selecionarEntrada();
        reprodutorDeDVD.ligar();
        reprodutorDeDVD.reproduzir();
        sistemaDeSom.ligar();
        sistemaDeSom.ajustarVolume();
    }
};

int main() {
    TV* tv = new TV();
    ReprodutorDeDVD* reprodutorDeDVD = new ReprodutorDeDVD();
    SistemaDeSom* sistemaDeSom = new SistemaDeSom();

    ControleRemoto controleRemoto(tv, reprodutorDeDVD, sistemaDeSom);
    controleRemoto.assistirFilme();


    return 0;
}












/// abstract factory
#include <iostream>
#include <string>

class Decoracao {
public:
    virtual std::string getDescricao()  {
      return "Decoração Genérica";
    }
};

class DecoracaoEspaco : public Decoracao {
public:
    std::string getDescricao()   {
        return "Decoração Espacial";
    }
};

class DecoracaoSelva : public Decoracao {
public:
    std::string getDescricao()   {
        return "Decoração da Selva";
    }
};

class Comida {
public:
    virtual std::string getDescricao()  {
      return "Comida base";
    }
};

class ComidaEspaco : public Comida {
public:
    std::string getDescricao()   {
        return "Comida Espacial";
    }
};

class ComidaSelva : public Comida {
public:
    std::string getDescricao()   {
        return "Comida Selva";
    }
};

class Entretenimento {
public:
    virtual std::string getDescricao()  {
      return "classe entretenimeno"; 
    }
};

class EntretenimentoEspaco : public Entretenimento {
public:
    std::string getDescricao()   {
        return "Espacial";
    }
};

class EntretenimentoSelva : public Entretenimento {
public:
    std::string getDescricao()   {
        return "Selva";
    }
};

class FestaFabrica {
public:
    virtual Decoracao* criarDecoracao()  {
      return  Decoracao();
    }

    virtual Comida* criarComida()  {
      return  Comida();
    }

    virtual Entretenimento* criarEntretenimento()  {
      return  Entretenimento();
    }
};

class FestaEspacoFabrica : public FestaFabrica {
public:
    Decoracao* criarDecoracao()   {
        return  DecoracaoEspaco();
    }
    Comida* criarComida()   {
        return  ComidaEspaco();
    }
    Entretenimento* criarEntretenimento()   {
        return  EntretenimentoEspaco();
    }
};

class FestaSelvaFabrica : public FestaFabrica {
public:
    Decoracao* criarDecoracao()   {
        return  DecoracaoSelva();
    }
    Comida* criarComida()   {
        return  ComidaSelva();
    }
    Entretenimento* criarEntretenimento()   {
        return  EntretenimentoSelva();
    }
};

void organizarFesta( FestaFabrica* fabrica) {
    Decoracao* decoracao = fabrica.criarDecoracao();
    Comida* comida = fabrica.criarComida();
    Entretenimento* entretenimento = fabrica.criarEntretenimento();

    std::cout << decoracao.getDescricao();
    std::cout << comida.getDescricao();
    std::cout << entretenimento.getDescricao();

}

int main() {
    FestaFabrica* festaEspaco = new FestaEspacofabrica();
    FestaFabrica* festaSelva = new FestaSelvafabrica();

    std::cout << "Festa no Espaço:";
    organizarFesta(festaEspaco);

    std::cout << "Festa na Selva:";
    organizarFesta(festaSelva);


    return 0;
}














//factory method
#include <iostream>

class Brinquedo {
public:
    virtual void exibir() = 0;
};

class Carro : public Brinquedo {
public:
    void exibir()  {
        std::cout << "carro de brinquedo." << std::endl;
    }
};

class Boneca : public Brinquedo {
public:
    void exibir()  {
        std::cout << "boneca." << std::endl;
    }
};

class QuebraCabeca : public Brinquedo {
public:
    void exibir()  {
        std::cout << "Eu sou um quebra-cabeça." << std::endl;
};

class FabricaDeBrinquedos {
public:
    virtual Brinquedo* criarBrinquedo() = 0;
};

class FabricaDeCarros : public FabricaDeBrinquedos {
public:
    Brinquedo* criarBrinquedo()  {
        return  Carro();
    }
};

class FabricaDeBonecas : public FabricaDeBrinquedos {
public:
    Brinquedo* criarBrinquedo()  {
        return  Boneca();
    }
};

class FabricaDeQuebraCabecas : public FabricaDeBrinquedos {
public:
    Brinquedo* criarBrinquedo()  {
        return  QuebraCabeca();
    }
};

int main() {
    FabricaDeBrinquedos* fabrica;
    
    fabrica = new FabricaDeCarros();
    Brinquedo* brinquedo1 = fabrica.criarBrinquedo();
    brinquedo1.exibir();
    
 
    
    return 0;
}














//builder
#include <iostream>
#include <string>

// Classe Produto
class Pizza {
public:
    std::string massa;
    std::string molho;
    std::string cobertura;

    void mostrarPizza() {
        std::cout  << massa << molho << cobertura << std::endl;
    }
};

// Interface Builder
class PizzaBuilder {
public:
    virtual ~PizzaBuilder() {}
    virtual void buildMassa() = 0;
    virtual void buildMolho() = 0;
    virtual void buildCobertura() = 0;
    virtual Pizza* getPizza() = 0;
};

// Concrete Builder para criacao da pizza marherita
class MargheritaPizzaBuilder : public PizzaBuilder {
private:
    Pizza* pizza;

public:
    MargheritaPizzaBuilder() {
        this->pizza = new Pizza();
    }

    void buildMassa()  {
        pizza->massa = "fina";
    }

    void buildMolho()  {
        pizza->molho = "tomate";
    }

    void buildCobertura()  {
        pizza->cobertura = "mozzarella";
    }

    Pizza* getPizza()  {
        return pizza;
    }
};

// Diretor
class Pizzaiolo {
private:
    PizzaBuilder* pizzaBuilder;

public:
    void setPizzaBuilder(PizzaBuilder* pizzaBuilder) {
        this->pizzaBuilder = pizzaBuilder;
    }

    Pizza* getPizza() {
        return pizzaBuilder->getPizza();
    }

    void construirPizza() {
        pizzaBuilder->buildMassa();
        pizzaBuilder->buildMolho();
        pizzaBuilder->buildCobertura();
    }
};

int main() {
    Pizzaiolo* pizzaiolo = new Pizzaiolo();
    MargheritaPizzaBuilder* margheritaPizzaBuilder = new MargheritaPizzaBuilder();

    pizzaiolo->setPizzaBuilder(margheritaPizzaBuilder);
    pizzaiolo->construirPizza();

    Pizza* pizza = pizzaiolo->getPizza();
    pizza->mostrarPizza();

    return 0;
}

















// Prototype
#include <iostream>
#include <string>

class prototipoApp {
public:
    virtual prototipoApp* clonar() = 0;
    virtual void personalizar(std::string nomeDoCliente,  std::string logotipo,  std::string cor) = 0;
    virtual void exibir() = 0;
};

class AplicativoMobile : public prototipoApp {
private:
    std::string nomeDoCliente;
    std::string logotipo;
    std::string cor;

public:
    AplicativoMobile() {
        nomeDoCliente = "cliente";
        logotipo = "Logotipo padrao";
        cor = "Cor padrao";
    }
    
    AplicativoMobile(AplicativoMobile outro) {
        nomeDoCliente = outro.nomeDoCliente;
        logotipo = outro.logotipo;
        cor = outro.cor;
    }

    prototipoApp* clonar() {
        return new AplicativoMobile();
    }

    void personalizar(std::string nomeDoCliente,  std::string logotipo, std::string cor) {
        this.nomeDoCliente = nomeDoCliente;
        this.logotipo = logotipo;
        this.cor = cor;
    }

    void exibir() {
        std::cout << nomeDoCliente << std::endl;
        std::cout << logotipo << std::endl;
        std::cout <<  cor << std::endl;
    }
};

int main() {
    PrototipoApp* prototipo = new AplicativoMobile();
    
    PrototipoApp* aplicativoCliente1 = prototipo.clonar();
    aplicativoCliente1.personalizar("Cliente 1", "Logotipo 1", "Azul");

    aplicativoCliente1.exibir();

    return 0;

  }



//flyweight
#include <iostream>
#include <string>
#include <unordered_map>

// Classe Flyweight simplificada
class CarroFlyweight {
  private:
  std::string modelo;
  std::string cor;

public:
  CarroFlyweight(std::string modelo, std::string cor){
    this->modelo = modelo;
    this->cor = cor;
  }

  void exibir() const {
    std::cout << modelo << cor << std::endl;
  }
};

// Fábrica Flyweight simplificada
class FabricaCarroFlyweight {
  private:
      static std::unordered_map<std::string, CarroFlyweight*> flyweights;

  public:
      static CarroFlyweight* obterCarroFlyweight( std::string modelo,  std::string cor) {
          std::string chave = modelo + cor;
          if (flyweights.find(chave) == flyweights.end()) {
              flyweights[chave] = new CarroFlyweight(modelo, cor);
          }
          return flyweights[chave];
      }


};

std::unordered_map<std::string, CarroFlyweight*> FabricaCarroFlyweight::flyweights;

class Carro {
  private:
      CarroFlyweight* flyweight;
      std::string placa;

  public:
      Carro( std::string modelo,  std::string cor, std::string placa) {
        this->flyweight = FabricaCarroFlyweight::obterCarroFlyweight(modelo, cor);
        this->placa = placa;
      }
      void exibir()  {
          flyweight->exibir();
          std::cout << "Placa: " << placa << std::endl;
      }


};

int main() {
    Carro carro1("Sedan", "Vermelho", "ABC-1234");
    Carro carro2("SUV", "Azul", "DEF-5678");
    Carro carro3("Sedan", "Vermelho", "GHI-9012");

    carro1.exibir();
    carro2.exibir();
    carro3.exibir();

    return 0;
}













// interpreter
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

class Expressao {
public:
    virtual int interpretar( std::unordered_map<std::string, int contexto) = 0;
    virtual ~Expressao() = default;
};

class ExpressaoTerminal : public Expressao {
    std::string variavel;
public:
    ExpressaoTerminal( std::string& var) : variavel(var) {}
    int interpretar( std::unordered_map<std::string, int>& contexto)  {
        return contexto.at(variavel);
    }
};

class ExpressaoAdicionar : public Expressao {
    Expressao* esquerda;
    Expressao* direita;
public:
    ExpressaoAdicionar(Expressao* e, Expressao* d) : esquerda(e), direita(d) {}
    int interpretar( std::unordered_map<std::string, int contexto)  {
        return esquerda.interpretar(contexto) + direita->interpretar(contexto);
    }
};

class ExpressaoSubtrair : public Expressao {
    Expressao* esquerda;
    Expressao* direita;
public:
    ExpressaoSubtrair(Expressao* e, Expressao* d) : esquerda(e), direita(d) {}
    int interpretar( std::unordered_map<std::string, int>& contexto)  {
        return esquerda.interpretar(contexto) - direita->interpretar(contexto);
    }
};

int main() {
    std::unordered_map<std::string, int> contexto = {{"x", 5}, {"y", 10}};

    Expressao* x = new ExpressaoTerminal("x");
    Expressao* y = new ExpressaoTerminal("y");

    Expressao* expressao1 = new ExpressaoAdicionar(x, y);
    Expressao* expressao2 = new ExpressaoSubtrair(y, x);

    std::cout << "x + y = " << expressao1.interpretar(contexto) << std::endl;
    std::cout << "y - x = " << expressao2.interpretar(contexto) << std::endl;

    delete x;
    delete y;
    delete expressao1;
    delete expressao2;

    return 0;
}
