/* 
 * $Id$ 
 *
 * Copyright (C) 2000-2002 Regents of the University of California
 * See ./DISCLAIMER
 */

#ifndef _OPT_INCLUDED
#define _OPT_INCLUDED

#if	HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/types.h>	/* for uid_t */

#include "list.h"	/* for list_t */

#ifndef _BOOL_DEFINED
#define _BOOL_DEFINED
typedef enum {false, true} bool;
#endif

#define MAX_USERNAME	9
#define MAX_GENDATTR	64

#define RC_MAGIC	"XXRETCODE:"

#define RC_FAILED	254	/* -S exit value if any hosts fail to connect */

typedef enum { DSH, PCP } pers_t;
typedef enum { RCMD_BSD, RCMD_K4, RCMD_SSH, RCMD_QSHELL } rcmd_t;
typedef enum { ALLOC_UNSPEC, ALLOC_BLOCK, ALLOC_CYCLIC } alloc_t;
 
typedef struct {

	/* common options */
	char *progname;		/* argv[0] */
	pers_t personality;
	bool debug;		/* -d */
	bool info_only;		/* -q */
	bool allnodes;		/* -a */
	char gend_attr[MAX_GENDATTR];	/* -g */
	bool sdr_verify;	/* -v */
	bool sdr_global;	/* -G */
	bool altnames; 		/* -i */
	bool sigint_terminates;	/* -b */
	rcmd_t rcmd_type;
	list_t wcoll;		/* target node list (-w, WCOLL, or stdin) */
	list_t exclude;		/* exclusion node list (-x) */
	char *range_op;		/* range expansion operator (environment) */
	char luser[MAX_USERNAME];/* local username */	
	uid_t luid;		/* uid for above */
	char ruser[MAX_USERNAME];/* remote username (-l or default) */
	int fanout;		/* (-f, FANOUT, or default) */
	int connect_timeout;
	int command_timeout;
	int nprocs;		/* -n nprocs */

	/* DSH-specific options */
	bool separate_stderr;	/* -s */
	bool delete_nextpass;	/* -c */
	bool stdin_unavailable; /* set if stdin used for WCOLL */
	char *cmd;
	char *dshpath;		/* optional PATH command prepended to cmd */
	char *getstat;		/* optional echo $? appended to cmd */
	bool labels;		/* display host: before output */

	/* Qshell specific */
	alloc_t q_allocation;	/* -m block */

	/* PCP-specific options */
	bool preserve;		/* -p */
	bool recursive;		/* -r */
	list_t infile_names;	/* -I or pcp source spec */
	char *outfile_name;	/* pcp dest spec */
} opt_t;	

void opt_default(opt_t *);
void opt_env(opt_t *);
void opt_args(opt_t *, int, char **);
bool opt_verify(opt_t *);
void opt_list(opt_t *);
void opt_free(opt_t *);

#endif /* OPT_INCLUDED */