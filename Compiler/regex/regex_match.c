#include "regex_match.h"

CONSTRUCT_STRUCT(regex_match);

regex_match* init_regex_match()
{
	regex_match* rm_ptr = create_regex_match();
	return rm_ptr;
}
void free_regex_match(regex_match* rm_ptr)
{
	if (rm_ptr == NULL) return;
	destroy_regex_match(rm_ptr);
	rm_ptr = NULL;
}
