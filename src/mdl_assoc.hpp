#ifndef _H_MDL_ASSOC
#define _H_MDL_ASSOC

#include <gc/gc.h>

typedef struct mdl_assoc_t
{
    struct mdl_assoc_t *next;
    struct mdl_assoc_key_t *key;
    mdl_value_t *value;
    void *item_exists;
    void *indicator_exists;
} mdl_assoc_t;

typedef struct mdl_assoc_table_t
{
    int nbuckets;
    int size;
    GC_word last_clean;
    struct mdl_assoc_t *buckets[1];
} mdl_assoc_table_t;

typedef struct mdl_assoc_iterator_t
{
    mdl_assoc_table_t *table;
    int bucket;
    mdl_assoc_t *assoc;
} mdl_assoc_iterator_t;

inline int
mdl_assoc_table_size(mdl_assoc_table_t *table)
{
    return table->size;
}

inline bool 
mdl_assoc_iterator_at_end(const mdl_assoc_iterator_t *iter)
{
    return iter->assoc == NULL;
}

inline const mdl_assoc_key_t *mdl_assoc_iterator_get_key(mdl_assoc_iterator_t *iter)
{
    if (iter->assoc == NULL) return NULL;
    return (const mdl_assoc_key_t *)iter->assoc->key;
}

inline mdl_value_t *mdl_assoc_iterator_get_value(mdl_assoc_iterator_t *iter)
{
    if (iter->assoc == NULL) return NULL;
    return iter->assoc->value;
}

extern mdl_assoc_table_t *mdl_create_assoc_table();
extern bool mdl_assoc_clean(mdl_assoc_table_t *table);
extern void mdl_clear_assoc_table(mdl_assoc_table_t *table);
int mdl_swap_assoc_table(mdl_assoc_table_t *t1, mdl_assoc_table_t *t2);

extern bool mdl_add_assoc(mdl_assoc_table_t *table, mdl_assoc_key_t *inkey, mdl_value_t *value);
extern mdl_value_t *mdl_assoc_find_value(mdl_assoc_table_t *table, mdl_assoc_key_t *inkey);

extern mdl_value_t *mdl_delete_assoc(mdl_assoc_table_t *table, mdl_assoc_key_t *inkey);

// Iterator routines
extern mdl_assoc_iterator_t *mdl_assoc_iterator_first(mdl_assoc_table_t *table);
extern bool mdl_assoc_iterator_increment(mdl_assoc_iterator_t *iter);
extern bool mdl_assoc_iterator_delete(mdl_assoc_iterator_t *iter);

#endif // _H_MDL_ASSOC
