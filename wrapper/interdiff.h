//#ifdef HAVE_CONFIG_H
#include "config.h"
//#endif

#ifdef HAVE_ALLOCA_H
# include <alloca.h>
#endif
#include <assert.h>
#ifdef HAVE_ERROR_H
# include <error.h>
#endif /* HAVE_ERROR_H */
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */
#include <getopt.h>
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */
#ifdef HAVE_SYS_WAIT_H
# include <sys/wait.h>
#endif /* HAVE_SYS_WAIT_H */

// https://github.com/espressif/esp-idf/issues/224
#include <sys/unistd.h>

/* This can be invoked as interdiff, combinediff, or flipdiff. */
static enum {
	mode_inter,
	mode_combine,
	mode_flip,
} mode;
static int flipdiff_inplace = 0;

struct file_list {
	char *file;
	long pos;
	struct file_list *next;
	struct file_list *tail;
};

struct lines {
	char *line;
	size_t length;
	unsigned long n;
	struct lines *next;
	struct lines *prev;
};

struct lines_info {
	char *unline;
	unsigned long first_offset;
	unsigned long min_context;
	struct lines *head;
	struct lines *tail;
};

static int human_readable = 1;
static char diff_opts[4];
static unsigned int max_context_real = 3, max_context = 3;
static int context_specified = 0;
static int ignore_components = 0;
static int unzip = 0;
static int no_revert_omitted = 0;
static int debug = 0;

static struct patlist *pat_drop_context = NULL;

static struct file_list *files_done = NULL;
static struct file_list *files_in_patch2 = NULL;

/* checks whether file needs processing and sets context */
static int
check_filename (const char *fn);

static void
add_to_list (struct file_list **list, const char *file, long pos);

static long
file_in_list (struct file_list *list, const char *file);

static void
free_list (struct file_list *list);

static void
insert_line_before (struct lines_info *lines,
		    struct lines *at, struct lines *make);

/* Returns 1 is there is a conflict. */
static int
add_line (struct lines_info *lines, const char *line, size_t length,
	  unsigned long n);

static void
merge_lines (struct lines_info *lines1, struct lines_info *lines2);

static void
free_lines (struct lines *list);

static void
clear_lines_info (struct lines_info *info);

static void
whitespace_damage (const char *which);

static struct lines *
create_orig (FILE *f, struct lines_info *file,
	     int reverted, int *clash);

static void
construct_unline (struct lines_info *file_info);

static int
write_file (struct lines_info *file_info, int fd);

static int
do_output_patch1_only (FILE *p1, FILE *out, int not_reverted);

static int
output_patch1_only (FILE *p1, FILE *out, int not_reverted);

static int
apply_patch (FILE *patch, const char *file, int reverted);

static int
trim_context (FILE *f /* positioned at start of @@ line */,
	      const char *unline /* drop this line */,
	      FILE *out /* where to send output */);

static int
output_delta (FILE *p1, FILE *p2, FILE *out);

static int
copy_residue (FILE *p2, FILE *out);

static int
index_patch2 (FILE *p2);

struct offset {
	unsigned long line;	/* line number after patch1, before patch2 */
	long offset;		/* offset modification */
};

static struct offset *
add_offset (unsigned long line, long offset,
	    struct offset *offsets, unsigned long *allocated,
	    unsigned long *num_offsets);

static void
free_offsets (struct offset *offsets);

static int
patch2_removes_line (unsigned long line,	/* line number after patch1 */
		     struct offset *offsets,
		     unsigned long num_offsets);

static long
offset_at_line (unsigned long line,	/* line number after patch1 */
		struct offset *offsets,
		unsigned long num_offsets);

static int
insert_line (struct lines_info *lines, const char *line, size_t length,
	     unsigned long n);

static void
remove_line (struct lines_info *lines, const char *line,
	     unsigned long n);

static int
take_diff (const char *f1, const char *f2, char *headers[2],
	   const char *unline, FILE *out);

static int
flipdiff (FILE *p1, FILE *p2, FILE *flip1, FILE *flip2);

static int
copy (FILE *from, FILE *to);

static int
no_patch (const char *f);

static int
interdiff (FILE *p1, FILE *p2, const char *patch1, const char *patch2);

static void
set_interdiff (void);

static void
set_combinediff (void);

static void
set_flipdiff (void);

static void
get_mode_from_name (const char *argv0);

int
execute (int argc, char *argv[]);
