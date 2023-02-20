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

struct elem_mapa{ 
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

struct fila_clientes{ //ponteiros da fila
	struct pedido* fim;
	struct pedido* comeco;
};

struct ingredientes{ //struct dos ingredientes que compoem a pilha de ingredientes
	char ingrediente;
	struct ingredientes* anterior;
};

struct pilha{	//struct da pilha que compoe a ingredientes
	struct ingredientes* topo;
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

struct pedido* cria_pedido(int* num_clientes);

int fila_vazia(struct fila_clientes* fila);

void insere_fim(struct fila_clientes* fila, int* num_clientes);

struct fila_clientes* inicializa_fila(int* num_clientes);

void retira_comeco(struct fila_clientes* fila);

struct pilha* inicializa_pilha();

void push(struct pilha* refeicao, char ingrediente);

void pop(struct pilha* refeicao);

void destroi_refeicao(struct pilha* refeicao);

void imprime_refeicao(struct pilha* refeicao);

//int verifica_pedido(struct pilha* refeicao, struct fila_clientes* fila);

int verifica_direita(struct pilha* refeicao, struct fila_clientes* fila, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais elementos_mapa);

int verifica_esquerda(struct pilha* refeicao, struct fila_clientes* fila, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais elementos_mapa);

int verifica_baixo(struct pilha* refeicao, struct fila_clientes* fila, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais elementos_mapa);

int verifica_cima(struct pilha* refeicao, struct fila_clientes* fila, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais elementos_mapa);

void inicializa_elem_mapa(struct locais* elementos_mapa);

void pontuacao(int* pontos);

void imprime_tela(struct locais* elementos_mapa, struct pilha* refeicao, int* pontos);