#ifndef OPEN_LIB_H
#define OPEN_LIB_H

void *open_so_lib ( char *name ) __attribute__((nonnull, warn_unused_result));

void *get_symbol ( void *handle, char *name ) __attribute__((nonnull, warn_unused_result));

void close_so_lib ( void *handle ) __attribute__((nonnull));

void prepend_env ( char *name, char *val ) __attribute__((nonnull));

#endif

