#ifndef INI_H
#define INI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/* Typedef for handler function pointer */
typedef int (*ini_handler)(void* user, const char* section, const char* name, const char* value);

/* Parse given INI-style file. May have [section]s, name=value pairs
   (whitespace stripped), and comments starting with ';' (semicolon). Section
   is "" if name=value pair parsed before any section heading. name=value
   pairs under [section] override those without. Returns 0 on success, line
   number of first error on parse error (doesn't stop on first error), -1 on
   file open error, or -2 on memory allocation error (only when INI_USE_STACK
   is zero). */
int ini_parse(const char* filename, ini_handler handler, void* user);

/* Same as ini_parse(), but takes a FILE* instead of filename. This doesn't
   close the file when it's finished -- the caller must do that. */
int ini_parse_file(FILE* file, ini_handler handler, void* user);

/* Nonzero to allow multi-line value parsing, zero to disallow. */
extern int ini_allow_multiline;

/* Nonzero to allow a UTF-8 BOM sequence (0xEF 0xBB 0xBF) at the start of
   the file. */
extern int ini_allow_bom;

/* Nonzero to allow inline comments (with ';' or '#') at the end of a name=value
   line. */
extern int ini_allow_inline_comments;

/* Nonzero to use stack for line buffer, zero to use heap (malloc/free). */
extern int ini_use_stack;

/* Maximum line length for any line in INI file. */
#define INI_MAX_LINE 200

#ifdef __cplusplus
}
#endif

#endif /* INI_H */