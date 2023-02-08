#define X_Burguer 0;
#define X_Salada 1;
#define Combo_1 2;
#define Combo_2 3;
#define Vegetariano 4;
#define Vegano 5;

struct estacao{
	char simbolo;
	int lin, col;
	char ingrediente;
};

struct elem_mapa{ //mudar nome
	char simbolo;
	int lin, col;
};

struct locais{
	struct elem_mapa parede_lateral, parede_horizontal, lixeira, entrega, chapeiro;
	struct estacao hamburguer, pao_cima, pao_baixo, queijo, salada, fritas, refrigerante;
};

struct pedido{
	int cliente;
	int num_refeicao;
	struct pedido* prox;
	struct pedido* anterior;
};

struct refeicao{
	char ingrediente;
	struct refeicao* anterior;
};

char* cardapio[] = {  //define as refeicoes que serao util para checar o lanche e imprimi-lo na tela 
	[X_Burguer] = "pHQP";
	[X_Salada] = "pHSP";
	[Combo_1] = "pHQPFR";
	[Combo_2] = "pHSPFR";
	[Vegetariano] = "pQPFR";
	[Vegano] = "SFR";
};

int fila_vazia(struct pedido* comeco, struct pedido* fim);

struct pedido* cria_pedido(int* num_clientes);

void insere_fim(struct pedido* comeco, struct pedido* fim, int* num_clientes);

void retira_comeco(struct pedido* comeco);

struct refeicao* novo_ingrediente(char ingrediente);

void push(struct refeicao* topo, char ingrediente);

void pop(struct refeicao* topo);

void escreve_pilha(struct refeicao* topo);

void destroi_refeicao(struct refeicao* topo);

int verifica_pedido(struct refeicao* topo, struct pedido* comeco);

int imprime_pedidos(struct pedido* comeco);

int move_direita(struct refeicao* topo, struct refeicao* comeco, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais* elementos_mapa);

int move_esquerda(struct refeicao* topo, struct refeicao* comeco, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais* elementos_mapa);

int move_baixo(struct refeicao* topo, struct refeicao* comeco, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais* elementos_mapa);

int move_cima(struct refeicao* topo, struct refeicao* comeco, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais* elementos_mapa);