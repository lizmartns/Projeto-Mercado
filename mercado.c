#include <stdio.h>

typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
} Carrinho;

// Struct Produto e Carrinho conforme o enunciado

void menu() {
    printf("\nMenu\n");
    printf("1. Cadastrar Produto.\n");
    printf("2. Listar Produtos.\n");
    printf("3. Comprar Produto\n");
    printf("4. Visualizar Carrinho.\n");
    printf("5. Fechar Pedido.\n");
    printf("6. Atualizar Produto.\n");  // Nova opção
    printf("7. Sair do Sistema.\n");
}

// Menu em formato de lista, que sera usado para as funcoes do codigo

int cadastrarProduto(Produto produtos[], int tamanhoProduto) {
    int i = 0;
    while (i < tamanhoProduto) {
        printf("\nCadastrar produto %d\n", i + 1);
        
        printf("\nDigite o codigo do produto: ");
        scanf("%d", &produtos[i].codigo);

        printf("Digite o nome do produto: ");
        scanf("%s", produtos[i].nome);

        printf("Digite o preço do produto: ");
        scanf("%f", &produtos[i].preco);

        i++; 
        
        // Loop com Whie para cadastrar os produtos sem ser infinitamente
        // O usuario pode sair, forma que encontramos de sair do loop
        
        char continuar;
        printf("Deseja cadastrar outro produto? (s/n): ");
        scanf(" %c", &continuar);  
        if (continuar == 'n') {
            break;
        }
    }
    // O usuario pode sair, caso ele digite 'n', saira do loop
    return i;
}

void listarProdutos(Produto produto[], int tamanhoProduto) {
    if (tamanhoProduto == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\nProdutos disponiveis:\n");
    for (int i = 0; i < tamanhoProduto; i++) {
        printf("%d | %s | R$ %.2f \n", produto[i].codigo, produto[i].nome, produto[i].preco);
    }
}

// Leitura e amostra dos produtos que estao disponiveis no mercado para compra

int comprarProduto(Produto produtos[], int tamanhoProduto, Carrinho carrinho[], int tamanhoCarrinho) {
    int codigoProduto;
    printf("\nDigite o codigo do produto para comprar: \n");
    scanf("%d", &codigoProduto);
// Procura um codigo informado anteriormente caso nao encontre ira retornar
// "Produto nao encontrado"
    int pos = pegarProdutoPorCodigo(produtos, tamanhoProduto, codigoProduto);
    if (pos == -1) {
        printf("Produto nao encontrado.\n");
        return tamanhoCarrinho;
    }
    
    int posCarrinho = temNoCarrinho(carrinho, tamanhoCarrinho, codigoProduto);
    if (posCarrinho != -1) {
        carrinho[posCarrinho].quantidade++;  
    } else {
        printf("\nProduto adicionado ao carrinho.\n");
        carrinho[tamanhoCarrinho].produto = produtos[pos];
        carrinho[tamanhoCarrinho].quantidade = 1;  
        tamanhoCarrinho++;  
    }
    
// Iniciamos as quantiades dos produtos com 1 e não com 0, porque 0 seria ele fora do carrinho
// Quantidade de produtos e somada a cada adicao 
    
    return tamanhoCarrinho;
}

void visualizarCarrinho(Carrinho carrinho[], int tamanhoCarrinho) {
    if (tamanhoCarrinho == 0) {
        printf("\nCarrinho vazio.\n");
        return;
    }
// Esse if so ira funcionar se o carrinho estiver vazio
    printf("\nItens no carrinho:\n");
    for (int i = 0; i < tamanhoCarrinho; i++) {
        printf("\nCodigo: %d | Nome: %s | Preco: R$ %.2f | Quantidade: %d\n", 
               carrinho[i].produto.codigo, carrinho[i].produto.nome, 
               carrinho[i].produto.preco, carrinho[i].quantidade);
    }
}

// Pequeno laco de repeticao com struct para mostrar os produtos do carrinho

void fecharPedido(Carrinho carrinho[], int tamanhoCarrinho) {
    float total = 0.0;
    printf("\nValor do Pedido:\n");
    for (int i = 0; i < tamanhoCarrinho; i++) {
       
        float subTotal = carrinho[i].produto.preco * carrinho[i].quantidade;
        printf("Produto: %s | Preco: R$ %.2f | Quantidade: %d | Total: R$ %.2f\n", 
               carrinho[i].produto.nome, carrinho[i].produto.preco, 
               carrinho[i].quantidade, subTotal);
        total += subTotal;
    }
    
// O subTotal e para calcular o valor caso aja mais de um item como 2 itens 4 
// Nessa situacao ele multiplica a quantidade pelo valor e depois retorna
    printf("\nTotal da compra: R$ %.2f\n", total);

    printf("Pedido fechado com sucesso! Carrinho esvaziado.\n");
    
    tamanhoCarrinho = 0;
// Zeramos o valor do carrinho apos a compra dos itens
}

int temNoCarrinho(Carrinho carrinho[], int tamanhoCarrinho, int codigo) {
    for (int i = 0; i < tamanhoCarrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            return i;  
        }
    }
    return -1; 
}
// Loop para verificar o que ja possuimos no carrinho

int pegarProdutoPorCodigo(Produto produtos[], int tamanhoProduto, int codigo) {
    for (int i = 0; i < tamanhoProduto; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1; 
    // Usamos o paramento de comparar os codigos dos produtos com o codigo
    // Que estamos buscando para selecionar e pegar ele
}
// Funcao para pegar os produtos pelo codigo

int atualizarProduto(Produto produtos[], int tamanhoProduto) {
    int codigoProduto;
    printf("\nDigite o codigo do produto que deseja atualizar: ");
    scanf("%d", &codigoProduto);

    int pos = pegarProdutoPorCodigo(produtos, tamanhoProduto, codigoProduto);
    if (pos == -1) {
        printf("Produto nao encontrado.\n");
        return tamanhoProduto;
    }
// Verificacao se estamos selecionando o produto correto
    printf("\nProduto encontrado: %s | R$ %.2f\n", produtos[pos].nome, produtos[pos].preco);

    printf("Digite o novo nome do produto: ");
    scanf("%s", produtos[pos].nome);
    
    printf("Digite o novo preço do produto: ");
    scanf("%f", &produtos[pos].preco);

    printf("Produto atualizado com sucesso!\n");
    return tamanhoProduto;
}
// Para alteracao buscamos pelo codigo e alteramos apenas o nome e o preco

int main() {
    Produto produto[50];
    Carrinho carrinho[50];
    int tamanhoProduto = 0;  
    int tamanhoCarrinho = 0;  
    int opcao;
    do {
        menu();  
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {  
            printf("Entrada invalida! Tente novamente.\n");
            continue;  
        }
        // Switch Case para rodar o nosso menu, criado la encima
        switch(opcao) {
            case 1: 
                tamanhoProduto = cadastrarProduto(produto, 50);
                break;
            case 2:
                listarProdutos(produto, tamanhoProduto);
                break;
            case 3:
                tamanhoCarrinho = comprarProduto(produto, tamanhoProduto, carrinho, tamanhoCarrinho);
                break;
            case 4:
                visualizarCarrinho(carrinho, tamanhoCarrinho);
                break;
            case 5:
                fecharPedido(carrinho, tamanhoCarrinho);
                break;
            case 6:  
                tamanhoProduto = atualizarProduto(produto, tamanhoProduto);
                break;
            case 7:
                printf("O sistema esta sendo encerrado!\n");
                break;
            default:
                printf("Opcao invalida! Por favor, tente novamente.\n");
        } 
    } while(opcao != 7);
// Caso escolha a opcao 7 o programa se encerra
    return 0;
}