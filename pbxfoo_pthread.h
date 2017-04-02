
#ifndef __PBXFOO__PTHREAD__H__
#define __PBXFOO__PTHREAD__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct pbxfoo{
	int	f_ref;
	pthread_mutex_t f_lock;
	char name[32];
	int score;
}pbxfoo_t;

struct pbxfoo *pbxfoo_alloc(void);
void pbxfoo_ref(struct pbxfoo *fp);
void pbxfoo_unref(struct pbxfoo *fp);
void pbxfoo_show(struct pbxfoo *fp);
void pbxfoo_destroy(struct pbxfoo *fp);


#endif
