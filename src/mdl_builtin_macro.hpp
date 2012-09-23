#include "macros.hpp"

#define MDL_BUILTIN(name, cname, stype, proc) do    \
{ \
    extern mdl_built_in_proc_t proc; \
    atom_t *atom_##cname; \
    mdl_value_builtin_##cname = mdl_new_mdl_value( );   \
    mdl_built_in_t bi = { proc };                 \
    mdl_value_builtin_##cname->pt = PRIMTYPE_WORD; \
    mdl_value_builtin_##cname->type = MDL_TYPE_##stype;              \
    mdl_value_builtin_##cname->v.w = built_in_table.size();                            \
    atom_##cname = mdl_create_atom_on_oblist(#name, mdl_value_root_oblist)->v.a; \
    bi.a = mdl_newatomval(atom_##cname); \
    bi.v = mdl_value_builtin_##cname; \
    built_in_table.push_back(bi); \
    mdl_set_gval(atom_##cname, mdl_value_builtin_##cname); \
} while (0);
