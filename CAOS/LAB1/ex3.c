#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef bool (*stage_fn)(int32_t* x, void* user);

typedef struct { int32_t k; } add_k_cfg;
typedef struct { int32_t lo, hi; } clamp_cfg;
typedef bool (*pred_fn)(int32_t);
typedef int32_t (*map_fn)(int32_t);
typedef struct { pred_fn p; map_fn f; } map_if_cfg;

bool run_pipeline(int32_t* x, stage_fn const* stages, void* const* users, size_t n_stages) {
    if (!x || !stages) return false;
    for (size_t i = 0; i < n_stages; ++i) {
        void* u = users ? users[i] : NULL;
        if (!stages[i](x, u)) return false;
    }
    return true;
}

bool stage_add_k(int32_t* x, void* user) {
    if (!x || !user) return false;
    const add_k_cfg* cfg = (const add_k_cfg*)user;
    *x += cfg->k;
    return true;
}

bool stage_clamp(int32_t* x, void* user) {
    if (!x || !user) return false;
    const clamp_cfg* cfg = (const clamp_cfg*)user;
    if (*x < cfg->lo) *x = cfg->lo;
    else if (*x > cfg->hi) *x = cfg->hi;
    return true;
}

bool stage_map_if(int32_t* x, void* user) {
    if (!x || !user) return false;
    const map_if_cfg* cfg = (const map_if_cfg*)user;
    if (cfg->p && cfg->p(*x) && cfg->f) *x = cfg->f(*x);
    return true;
}

// Example predicates/maps
static bool is_even(int32_t v){ return (v & 1) == 0; }
static bool is_negative(int32_t v){ return v < 0; }
static int32_t half(int32_t v){ return v/2; }
static int32_t square(int32_t v){ return v*v; }

int main(void) {
    add_k_cfg add7 = { .k = 7 };
    clamp_cfg clamp01 = { .lo = 0, .hi = 10 };
    map_if_cfg even_half = { .p = is_even, .f = half };

    stage_fn stages[] = { stage_add_k, stage_clamp, stage_map_if };
    void*    users[]  = { &add7,        &clamp01,     &even_half     };

    int32_t x = 5;
    bool ok = run_pipeline(&x, stages, users, 3);
    printf("ok=%s, x=%d\n", ok?"true":"false", x); // expected: 6
    // Early stop demo
    map_if_cfg neg_square = { .p = is_negative, .f = square };
    stage_fn stages2[] = { stage_clamp, stage_map_if };
    void* users2[] = { &clamp01, &neg_square };
    x = -3; // becomes 0 after clamp, map_if won't trigger; pipeline ok
    ok = run_pipeline(&x, stages2, users2, 2);
    printf("ok=%s, x=%d\n", ok?"true":"false", x);
    return 0;
}
