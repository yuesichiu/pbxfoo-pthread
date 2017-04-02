/*
  *   This is a examples of pthread mutex and reference.
  *   Author : Yuesichiu<yuesichiu@126.com>
  *   Date    : 2017-04-02 10:31 
  */
#include "pbxfoo_pthread.h"
	
struct pbxfoo *pbxfoo_alloc(void)
{
	struct pbxfoo *fp = NULL;
	if((fp=(struct pbxfoo *)malloc(sizeof(struct pbxfoo))) != NULL){
		memset(fp, 0, sizeof(struct pbxfoo));
		fp->f_ref = 1;
		if(pthread_mutex_init(&fp->f_lock, NULL) != 0 ){
			free(fp);
			return NULL;
		}
	}

	return fp;
}


void pbxfoo_ref(struct pbxfoo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_ref++;
	pthread_mutex_unlock(&fp->f_lock);
}

void pbxfoo_unref(struct pbxfoo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_ref--;
	pthread_mutex_unlock(&fp->f_lock);
}

void pbxfoo_show(struct pbxfoo *fp)
{
	if(fp != NULL){
		fprintf(stderr, "Results :\n");
		fprintf(stderr, "f_count : %d\n", fp->f_ref);
		fprintf(stderr, "name : %s\n", fp->name);
		fprintf(stderr, "score : %d\n", fp->score);
	} else{
		fprintf(stderr, "pass a NULL pointer to %s\n", __func__);
	}
}

void pbxfoo_destroy(struct pbxfoo *fp)
{

#ifdef PBXFOO_DEBUG
	pbxfoo_show(fp);
#endif

	pthread_mutex_lock(&fp->f_lock);
	if(--fp->f_ref == 0) { /* last reference */
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}else{
		pthread_mutex_unlock(&fp->f_lock);
	}
}

void pbxfoo_maintest(struct pbxfoo *fp)
{
	if(fp != NULL){
		pbxfoo_ref(fp);
		snprintf(fp->name, 32, "Yuesichiu");
		fp->score = 98;
		pbxfoo_show(fp);
		pbxfoo_unref(fp);
		
	}

}

int main()
{
	int res = 0;
	struct pbxfoo *fp = pbxfoo_alloc();
	if(fp == NULL){
		return 0;
	}
	pbxfoo_maintest(fp);
	pbxfoo_destroy(fp);
	
	return 0;
}

