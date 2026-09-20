#ifndef TOKEN_H
#define TOKEN_H

typedef enum token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_APPEND,
    TOKEN_HEREDOC,

} token_type_t;

typedef struct token
{
    token_type_t  type;
    char*         value;
    struct token* next;
} token_t;

token_t* token_new(token_type_t type, const char* value);
void     token_append(token_t** head, token_t* new);
void     tokens_free(token_t* head);

#endif
