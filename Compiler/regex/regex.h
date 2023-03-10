#pragma once

#include "collections/vector.h"
#include "collections/binary_tree.h"

// 正则表达式
#ifdef __cplusplus
extern "C" {
#endif

/* regex_comp() flags */
#define	REG_BASIC	0000
#define	REG_EXTENDED	0001
#define	REG_ICASE	0002
#define	REG_NOSUB	0004
#define	REG_NEWLINE	0010
#define	REG_NOSPEC	0020
#define	REG_PEND	0040
#define	REG_DUMP	0200

/* regex_error() flags */
#define	REG_NOMATCH	 1
#define	REG_BADPAT	 2
#define	REG_ECOLLATE	 3
#define	REG_ECTYPE	 4
#define	REG_EESCAPE	 5
#define	REG_ESUBREG	 6
#define	REG_EBRACK	 7
#define	REG_EPAREN	 8
#define	REG_EBRACE	 9
#define	REG_BADBR	10
#define	REG_ERANGE	11
#define	REG_ESPACE	12
#define	REG_BADRPT	13
#define	REG_EMPTY	14
#define	REG_ASSERT	15
#define	REG_INVARG	16
#define	REG_ATOI	255	/* convert name to number (!) */
#define	REG_ITOA	0400	/* convert number to name (!) */

/* regex_exec() flags */
#define	REG_NOTBOL	00001
#define	REG_NOTEOL	00002
#define	REG_STARTEND	00004
#define	REG_TRACE	00400	/* tracing of execution */
#define	REG_LARGE	01000	/* force large representation */
#define	REG_BACKR	02000	/* force use of backref code */


typedef struct regex
{
	int re_magic;
	size_t re_nsub;		/* number of parenthesized subexpressions */
	const char* re_endp;	/* end pointer for REG_PEND */
	struct regex_guts* re_g;	/* none of your business :-) */
}regex;

typedef struct regmatch
{
	size_t rm_so;
	size_t rm_eo;
} regmatch;

regex* init_regex();
size_t	regex_error(int errcode, const regex* preg,	char* errbuf, size_t errbuf_size);
int regex_comp(regex* preg, const char* regex, int cflags);
int regex_exec(const regex* preg, const char* expr, size_t nmatch, regmatch pmatch[], int eflags);

void free_regex(regex* re);

#ifdef __cplusplus
}

#endif