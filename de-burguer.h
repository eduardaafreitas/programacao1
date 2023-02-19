#define X_Burguer 0
#define X_Salada 1
#define Combo_1 2
#define Combo_2 3
#define Vegetariano 4
#define Vegano 5

#define Hamburguer 0
#define Pao_cima 1
#define Pao_baixo 2
#define Queijo 3
#define Salada 4
#define Fritas 5
#define Refrigerante 6

struct estacao{
	char simbolo[3];
	int lin, col[3];
	char ingrediente;
};

struct elem_mapa{ //mudar nome
	char simbolo;
	int lin, col;
};

struct locais{
	struct elem_mapa parede_direita, parede_baixo, lixeira, entrega, chapeiro;
	struct estacao hamburguer, pao_cima, pao_baixo, queijo, salada, fritas, refrigerante;
};

struct pedido{ //fila de pedidos
	int cliente;
	int num_refeicao;
	struct pedido* prox;
	struct pedido* anterior;
};

struct refeicao{ //pilha de refeicoes
	char ingrediente;
	struct refeicao* anterior;
};

/*char* ingrediente[] = { //define os ingredientes que serao utilizados para checar o lanche e imprimi-lo na tela
	[Hamburguer] = "H",
	[Pao_cima] = "P",
	[Pao_baixo] = "p",
	[Queijo] = "Q",
	[Salada] = "S",
	[Fritas] = "F",
	[Refrigerante] = "R"
};*/

/*char* cardapio[] = {  //define as refeicoes que serao util para checar o lanche e imprimi-lo na tela 
	[X_Burguer] = "pHQP",
	[X_Salada] = "pHSP",
	[Combo_1] = "pHQPFR",
	[Combo_2] = "pHSPFR",
	[Vegetariano] = "pQPFR",
	[Vegano] = "SFR"
};*/

void inicializa_ncurses();

void inicializa_fila(struct pedido* comeco, struct pedido* fim, int* num_clientes);

int fila_vazia(struct pedido* comeco, struct pedido* fim);

struct pedido* cria_pedido(int* num_clientes);

void insere_fim(struct pedido* comeco, struct pedido* fim, int* num_clientes);

void retira_comeco(struct pedido* comeco);

struct refeicao* novo_ingrediente(char ingrediente);

void push(struct refeicao* topo, char ingrediente);

void pop(struct refeicao* topo);

void destroi_refeicao(struct refeicao* topo);

int verifica_pedido(struct refeicao* topo, struct pedido* comeco);

int verifica_direita(struct refeicao* topo, struct pedido* comeco, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais elementos_mapa);

int verifica_esquerda(struct refeicao* topo, struct pedido* comeco, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais elementos_mapa);

int verifica_baixo(struct refeicao* topo, struct pedido* comeco, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais elementos_mapa);

int verifica_cima(struct refeicao* topo, struct pedido* comeco, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais elementos_mapa);

void inicializa_elem_mapa(struct locais* elementos_mapa);

void imprime_mapa();