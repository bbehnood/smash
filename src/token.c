#include "token.h"

#include <stdlib.h>
#include <string.h>

token_t* token_new(token_type_t type, const char* value)
{
    token_t* token = malloc(sizeof(token_t));
    if (!token) return NULL;

    token->type = type;
    token->next = NULL;

    if (value)
        token->value = strdup(value);
    else
        token->value = NULL;

    return token;
}

void token_append(token_t** head, token_t* new)
{
    if (!*head)
    {
        *head = new;
        return;
    }

    token_t* tmp = *head;

    while (tmp->next) tmp = tmp->next;

    tmp->next = new;
}

void tokens_free(token_t* head)
{
    token_t* tmp;

    while (head)
    {
        tmp = head->next;

        free(head->value);
        free(head);

        head = tmp;
    }
}
