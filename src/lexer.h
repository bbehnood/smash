#ifndef LEXER_H
#define LEXER_H

#include "token.h"

#include <stddef.h>

typedef struct lexer
{
    const char* input;
    size_t      pos;
    char        current;
} lexer_t;

typedef enum lexer_status
{
    LEXER_OK,
    LEXER_MEMORY_ERROR,
} lexer_status_t;

lexer_status_t tokenize(token_t* tokens, char* input);

#endif
