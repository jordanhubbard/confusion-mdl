enum
{
    SYMCLASS_OBJECT,
    SYMCLASS_PROPERTY,
    SYMCLASS_DICTWORD,
    SYMCLASS_VERB,
    SYMCLASS_FLAG, /* AKA attribute */
    SYMCLASS_GLOBAL_VAR,
    SYMCLASS_LOCAL_VAR,
    SYMCLASS_INT_CONSTANT,
    SYMCLASS_ADDR_CONSTANT,
    SYMCLASS_PADDR_CONSTANT,
};

enum
{
    SYMTYPE_FALSE  =   1,
    SYMTYPE_ATOM   =   2,
    SYMTYPE_FIX    =   4, /* integer */
    SYMTYPE_STRING =   8,
    SYMTYPE_ADV    =  16, /* Player character, I think */
    SYMTYPE_OBJECT =  32,
    SYMTYPE_HACK   =  64,
    SYMTYPE_VECTOR = 128,
    SYMTYPE_TABLE  = 256,
};

#define SYMTYPE_ANY ((SYMTYPE_TABLE << 1) - 1)

struct symtab_entry
{
    char *name;
    short symclass;
    int allowable_types;
    int intvalue;
    char *stringvalue;
};

#ifdef __cplusplus
    extern "C" {
#endif
	void add_compass_word(char *s);
	int is_compass_word(char *s);
	void yyerror(char *s);
#ifdef __cplusplus
    };
#endif
