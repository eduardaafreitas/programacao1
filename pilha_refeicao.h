void inicializa_preparo();

struct refeicao* novo_ingrediente(char ingrediente);

void push(struct refeicao* novo, struct refeicao* topo, char ingrediente);

void pop(struct refeicao* topo);

void escreve_pilha(struct refeicao* topo);

void destroi_refeicao(struct refeicao* topo);