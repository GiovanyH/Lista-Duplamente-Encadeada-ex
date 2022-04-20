# **Lista Duplamente Encadeada**

Implementação de uma Lista Duplamente Encadeada explicativa e com exemplos.
- [Implementação](#implementação)
- ~~[Manipulação-de-tipos](#Manipulação-de-tipos)~~
- ~~[Funções-específicas](#Funções-específicas)~~
- ~~[principal](#principal)~~

***

### Implementação

Implementação da Lista Duplamente Encadeada,  
Conjunto de definições e funções para o uso geral da lista.  

Criamos a estrutura do nó  
A estrutura da LinkedList que contém ponteiros  
para o primeiro e último nó  

Funções que alocam memoria e adicionam nós ao final da lista.  

- [Incluindo-headers](#Incluindo-headers)
- [Discriminated-Union](#Discriminated-Union)
- [Estrutura-de-nó](#Estrutura-de-nó)
- [Alocando-memoria](#Alocando-memoria)
- [LinkedList](#LinkedList)
- [Alocando-memoria-para-a-lista](#Alocando-memoria-para-a-lista)
- [Configurando-o-primeiro-valor](#Configurando-o-primeiro-valor)
- [Inserindo-no-final-da-Lista](#Inserindo-no-final-da-Lista)
- [Imprimindo-os-valores-da-lista](#Imprimindo-os-valores-da-lista)

> #### Incluindo-headers
> 
> `stdio.h` é um header com algumas funções de I/O / Input/Output / Entrada/Saída.  
> `stdlib.h` é um header que possui algumas funções de alocação memoria que utilizaremos, `malloc(...)` e `free(...)`.  
```c
#include <stdio.h>
#include <stdlib.h>
```

> #### Discriminated-Union
> 
> forma simples de checar o tipo de algo, por enquanto, temos os tipos `int` e `char*` / string.  
```c
enum TypeKind { TypeKind_Int, TypeKind_String };

struct Type {
    enum TypeKind kind;
    union {
        int value_int;
        char *value_str;
    };
};
```

> Usamos `enum` para definir os tipos  
>> Um enum é um conjunto de valores inteiros representados por identificadores  
>> `enum < nome > { < constante1 > , < constante2 > , · · · , < constanteN > , }`
```c
enum TypeKind { TypeKind_Int, TypeKind_String };
```

> Usamos `struct` para definir a estrutura `Type`  
>> Uma struct é uma variável especial que contém diversas outras variáveis normalmente de tipos diferentes.  
>> As variáveis internas contidas pela struct são denominadas membros da struct.  
```c
struct Type {
    ...
};
```

>> Uma Union é uma estrutura de dados em linguagem C que permite agrupar dados de tipos diferentes como um único objeto de dados. Unions são tipos de dados derivados, cujos membros compartilham o mesmo espaço de armazenamento.  
```c
struct Type {
    ...
    union {
        int value_int;
        char *value_str;
    };
};
```

> #### Estrutura-de-nó
> 
> Esse é o nosso nó, contém o dado, um ponteiro para o proximo e um ponteiro para o anterior.  
> <img alt="Noh" src=https://user-images.githubusercontent.com/56926698/163765999-1ccbb7e6-cc7e-4a82-95a2-abe9ddbd8e7f.png width="300" />

>> A utilização de ponteiros em linguagem C é uma das características que tornam a linguagem tão flexível e poderosa.  
>> Ponteiros ou apontadores, são variáveis que armazenam o endereço de memória de outras variáveis.  
>> Dizemos que um ponteiro “aponta” para uma varíável quando contém o endereço da mesma.  
>> Os ponteiros podem apontar para qualquer tipo de variável. Portanto temos ponteiros para int, float, double, etc.  

```c
struct Noh {
	struct Type data;
	struct Noh *prev; /* Ponteiro para o nó anterior */
	struct Noh *next; /* Ponteiro para o próximo nó */
} Noh;
```

> ### Alocando-memoria
>
> Criamos um nó, alocamos memória, o dado do nó recebe o dado passado como argumento e logo depois, retornamos o nó  
```c
struct Noh *criar_nodo(struct Type dado) {
	struct Noh *noh = malloc(sizeof(struct Noh));
	
	noh->data = dado;
	return noh;
}
```

> Criamos um ponteiro para `struct Noh`, `noh`, alocamos memória para ele usando `malloc(...)`  
>> A função  malloc  (o nome é uma abreviatura de *memory allocation*) aloca espaço para um bloco de bytes consecutivos na memória RAM (= *random access memory*) do computador e devolve o endereço desse bloco.  O número de bytes é especificado no argumento da função.
> Associamos `noh` ao ponteiro que `malloc(...)` retorna.  
```c
struct Noh *noh = malloc(sizeof(struct Noh));
```

> Definimos o `data`, que está dentro do `noh`, para o dado passado como argumento.  
> Para acessarmos algo dentro de um struct, utilizamos `.`, exemplo, `noh.data`.  
> Com o operador `->`, sendo `noh->data`, é a mesma coisa que `(*noh).data`,  
> Acontece que `noh` é um ponteiro, então temos que *desreferenciar* ele primeiro,  
```c
noh->data = dado;
```

> ### LinkedList
> 
> Criamos a estrutura da Lista Encadeada, o `typedef` é usado para não precisar especificar `struct` quando instanciamos,  
> fazemos apenas `LinkedList nome_da_lista;`. A estrutura contém ponteiros para Nós, declarados acima.  
> O primeiro ponteiro aponta para o que vai ser o primeiro nó, ou o nó "cabeça" da lista.  
> O segundo aponta para o último nó.  
```c
typedef struct {
	struct Noh *first;
	struct Noh *last;
} LinkedList;
```

> ### Alocando-memória-para-a-lista
>
> Função que retornará um ponteiro para LinkedList,  
> Criamos um ponteiro para LinkedList, alocamos memoria nele, definimos o primeiro nó (nó cabeça)  
> como `NULL` assim como o último, para evitar problemas de memoria, e depois retornamos esse ponteiro.  
```c
LinkedList *criar_le() {
	LinkedList *ll = malloc(sizeof(LinkedList));
	ll->first = NULL;
	ll->last = NULL;

	return ll;
}
```

> ### Configurando-o-primeiro-valor
> 
> O primeiro valor, ou nó cabeça, precisa ser configurado diferentemente dos outros  
> Já que ele não tem um "próximo" valor ainda, nem um anterior.  
```c
void primeiro_valor_le(LinkedList *ll, struct Type head_value) {
	struct Noh *first_value = criar_nodo(head_value);
	first_value->prev = NULL;
	first_value->next = NULL;
	ll->first = first_value;
	ll->last = first_value;
}
```

> Criamos um novo ponteiro para nó, ele recebe o valor retornado pela função `criar_nodo(...)`.  
```c
struct Noh *first_value = criar_nodo(head_value);
```

> Para evitar problemas de memória, definimos os valores do primeiro e último nó para `NULL`.  
```c
first_value->prev = NULL;
first_value->next = NULL;
```

> Como é nosso primeiro valor, ele será o primeiro e também o último nó da Lista.
```c
ll->first = first_value;
ll->last = first_value;
```

> ### Inserindo-no-final-da-Lista
> 
> Checa se for o primeiro da Lista, se sim, ele usa a função `primeiro_valor_le(...)` para inserir.
> Se não, insere normalmente

```c
void Inserir_le(LinkedList *ll, struct Type value) {
	if(ll->first == NULL) {
		primeiro_valor_le(ll, value);
		return;
	}
	struct Noh *new_node = criar_nodo(value);
	new_node->next = NULL;

	new_node->prev = ll->last;
	ll->last->next = new_node;
	ll->last = new_node;
}
```

> Checando se o primeiro valor da lista é `NULL`  
> se a condição for verdadeira, ele chama a função mostrada anteriormente `primeiro_valor_le(...)`  
> para inserir o primeiro, e depois retorna.  
```c
if(ll->first == NULL) {
	primeiro_valor_le(ll, value);
	return;
}
```

> Criando o primeiro valor, ele recebe o que a função `criar_nodo(...)` retorna  
> Definimos o próximo valor do nó como `NULL` para evitar problemas de memória.  
```c
struct Noh *new_node = criar_nodo(value);
new_node->next = NULL;
```

> Como estamos criando um novo nó, o último valor da lista, agora será o penúltimo, pois precisamos definir o nó que criamos como último.  
> Então o nó anterior ao novo nó, (`new_node->prev`) será o atual último nó da lista.  
```c
new_node->prev = ll->last;
```

> E claro, o nó posterior ao último nó da lista (`ll->last->next`), será o novo nó  
```c
ll->last->next = new_node;
```

> E agora, definimos o último nó como o novo nó  
```c
ll->last = new_node;
```

> ### Imprimindo-os-valores-da-lista
> Itera por toda a lista, diferencia os tipos para usar o `printf(...)`  

```c
void imprime_v(LinkedList *ll) {
	struct Noh *iterator = ll->first;

	while(iterator != NULL) {
		enum TypeKind type = iterator->data.kind;
		if(type == TypeKind_Int) printf("%d\n", iterator->data.value_int);
		else if(type == TypeKind_String) printf("%s\n", iterator->data.value_str);
		iterator = iterator->next;
	}
}
```
> Ponteiro para um nó, ele vai iterar por todos os nós, começando pelo primeiro  
```c
struct Noh *iterator = ll->first;
```

> Enquanto for diferente de `NULL`, executa o código, temos um `iterator = iterator->next;`  
> ele vai iterar até que seja `NULL`  
```c
while(iterator != NULL)
```

> Recebendo o tipo do valor atual  
```c
enum TypeKind type = iterator->data.kind;
```

> Checando se é `int` ou `char*` para usarmos `printf("%d\n")` ou `printf("%s\n")`  
```c
if(type == TypeKind_Int) printf("%d\n", iterator->data.value_int);
else if(type == TypeKind_String) printf("%s\n", iterator->data.value_str);
```
