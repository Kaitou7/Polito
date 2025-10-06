#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int strsplit(const char* s, char delim, char*** out_tokens, size_t* out_count) {
    if (!s || !out_tokens || !out_count) return -1;

    // Count tokens: number of delimiters + 1, including empty between/ends
    size_t n_delim = 0;
    for (const char* p = s; *p; ++p) if (*p == delim) ++n_delim;
    size_t n_tok = n_delim + 1;

    char** tokens = (char**)calloc(n_tok, sizeof(char*));
    if (!tokens) return -2;

    size_t idx = 0;
    const char* start = s;
    for (const char* p = s; ; ++p) {
        if (*p == delim || *p == '\0') {
            size_t len = (size_t)(p - start);
            char* t = (char*)malloc(len + 1);
            if (!t) {
                // cleanup
                for (size_t i = 0; i < idx; ++i) free(tokens[i]);
                free(tokens);
                return -3;
            }
            if (len) memcpy(t, start, len);
            t[len] = '\0';
            tokens[idx++] = t;
            if (*p == '\0') break;
            start = p + 1;
        }
    }
    *out_tokens = tokens;
    *out_count = n_tok;
    return 0;
}

typedef struct node {
    int value;
    struct node* next;
} node;

void list_push_front(node** head, int value) {
    if (!head) return;
    node* n = (node*)malloc(sizeof *n);
    if (!n) return;
    n->value = value;
    n->next = *head;
    *head = n;
}

bool list_remove_first(node** head, int value) {
    if (!head) return false;
    node* cur = *head;
    node* prev = NULL;
    while (cur) {
        if (cur->value == value) {
            if (prev) prev->next = cur->next;
            else *head = cur->next;
            free(cur);
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

void list_free(node** head) {
    if (!head) return;
    node* cur = *head;
    while (cur) {
        node* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    *head = NULL;
}

int main(void) {
    // strsplit demos
    char** toks = NULL; size_t n = 0;
    if (strsplit("::a::", ':', &toks, &n) == 0) {
        printf("tokens=%zu\n", n);
        for (size_t i = 0; i < n; ++i) { printf("[%s]\n", toks[i]); free(toks[i]); }
        free(toks);
    }

    // list demos
    node* head = NULL;
    list_push_front(&head, 3);
    list_push_front(&head, 2);
    list_push_front(&head, 1);
    (void)list_remove_first(&head, 2);
    for (node* p = head; p; p = p->next) printf("%d ", p->value);
    puts("");
    list_free(&head);
    return 0;
}
