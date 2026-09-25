#include "lexer.h"

#include "token.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void init(lexer_t* lexer, char* input)
{
    lexer->input   = input;
    lexer->pos     = 0;
    lexer->current = input[0];
}

static void advance(lexer_t* lexer)
{
    if (lexer->current != '\0') lexer->current = lexer->input[++lexer->pos];
}

static void skip_whitespaces(lexer_t* lexer)
{
    while (lexer->current && isspace((unsigned char)lexer->current)) advance(lexer);
}

static char* collect_word(lexer_t* lexer)
{
    size_t start = lexer->pos;

    while (lexer->current && !isspace((unsigned char)lexer->current)) advance(lexer);

    size_t len = lexer->pos - start;

    char* word = malloc(len + 1);
    if (!word) return NULL;

    memcpy(word, lexer->input + start, len);
    word[len] = '\0';

    return word;
}

lexer_status_t tokenize(token_t* tokens, char* input)
{
    lexer_t lexer;

    init(&lexer, input);

    while (lexer.current)
    {
        skip_whitespaces(&lexer);

        if (!lexer.current) break;

        char* word = collect_word(&lexer);
        if (!word)
        {
            tokens_free(tokens);
            return LEXER_MEMORY_ERROR;
        }

        token_t* token = token_new(TOKEN_WORD, word);
        if (!token)
        {
            free(word);
            tokens_free(tokens);
            return LEXER_MEMORY_ERROR;
        }

        token_append(&tokens, token);

        free(word);
    }

    return LEXER_OK;
}
