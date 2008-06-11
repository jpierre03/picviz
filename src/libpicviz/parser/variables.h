#ifndef _VARIABLES_H_
#define _VARIABLES_H_

enum type_t {
        EMPTY,
        TIMELINE,
        INTEGER,
        FLOAT,
        STRING
} type_t;

struct variables_t {
	struct llist_head list;
        type_t type;
	void *variable;
	void *value;
} variables_t;

#endif /* _VARIABLES_H_ */
