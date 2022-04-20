#include <stdio.h>
#include <stdlib.h>

enum TypeKind { TypeKind_Int, TypeKind_String };

struct Type {
    enum TypeKind kind;
    union {
        int value_int;
        char *value_str;
    };
};

struct Noh {
	struct Type data;
	struct Noh *prev; /* Ponteiro para o nó anterior */
	struct Noh *next; /* Ponteiro para o próximo nó */
} Noh;

struct Noh *criar_nodo(struct Type dado) {
	struct Noh *noh = malloc(sizeof(struct Noh));
	
	noh->data = dado;
	return noh;
}

typedef struct {
	struct Noh *first;
	struct Noh *last;
} LinkedList;

LinkedList *criar_le() {
	LinkedList *ll = malloc(sizeof(LinkedList));
	ll->first = NULL;
	ll->last = NULL;

	return ll;
}

void primeiro_valor_le(LinkedList *ll, struct Type head_value) {
	struct Noh *first_value = criar_nodo(head_value);
	first_value->prev = NULL;
	first_value->next = NULL;
	ll->first = first_value;
	ll->last = first_value;
}

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

void imprime_v(LinkedList *ll) {
	struct Noh *iterator = ll->first;

	while(iterator != NULL) {
		enum TypeKind type = iterator->data.kind;
		if(type == TypeKind_Int) printf("%d\n", iterator->data.value_int);
		else if(type == TypeKind_String) printf("%s\n", iterator->data.value_str);
		iterator = iterator->next;
	}
}