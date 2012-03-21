#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lookup.h"




int isprint(int);
int isdigit(int);

struct node{
	unsigned int orig;
	unsigned int val;
	struct node *prev;
	struct node *next;
};

struct board{
	struct node head;
	struct node *grid;
	struct node tail;
	struct node *ptr;
};




void print_board(struct board *b){
	for(unsigned int n=0;n<81;++n){
		if(n!=0 && n%9==0)puts("");
		printf("%c",b->grid[n].val==0?'.':b->grid[n].val+'0');
	}
	puts("");
}


void link_board(struct board *b){
	struct node *prev=&(b->head);
	for(int n=0;n<81;++n){
		if(b->grid[n].orig==0){//blank
			b->grid[n].prev=prev;
			prev->next=&(b->grid[n]);
			prev=prev->next;
		}
	}
	prev->next=&(b->tail);
	b->tail.prev=prev;
	b->ptr=&(b->head);
}


void read_board(struct board *b,FILE *source){
	for(unsigned int n=0;n<81;++n){
		int d=fgetc(source);
		if(feof(source))break;
		if(!isprint(d)){--n;continue;}
		b->grid[n].val=(isdigit(d)?d-'0':0);
		b->grid[n].orig=('1'<=d && d<='9');
	}
	link_board(b);
}


int solve_board(struct board *b){

	if(b->ptr==&(b->head)){
		b->ptr=b->ptr->next;
	}else	if(b->ptr==&(b->tail)){
		b->ptr=b->ptr->prev;
	}

	for(int trip,*index,n;;){
		if(b->ptr==&(b->head))return 0;//walked off the head
		if(b->ptr==&(b->tail))return 1;//walked off the tail
		index=(int*)&lookup[b->ptr-b->grid];//cache this value for later use

		while(++(b->ptr->val)<=9){
			trip=1;

			for(n=0;n<20;++n){
				if(b->grid[*(index+n)].val==b->ptr->val){//found conflict
					trip=0;
					break;
				}
			}

			if(trip)break;//no conflicts were found

		}

		if(b->ptr->val==10){//couldn't find the next value
			b->ptr->val=0;
			b->ptr=b->ptr->prev;
		}else{
			b->ptr=b->ptr->next;
		}
	}

}


void create_board(struct board *b){
	b->grid=malloc(81*sizeof(struct node));
	for(unsigned int n=0;n<81;++n){
		b->grid[n].orig=0;
		b->grid[n].val=0;
		b->grid[n].prev=NULL;
		b->grid[n].next=NULL;
	}
	b->head.next=NULL;
	b->tail.prev=NULL;
	b->ptr=NULL;
}


void destroy_board(struct board *b){
	for(unsigned int n=0;n<81;++n){
		b->grid[n].prev=NULL;
		b->grid[n].next=NULL;
	}
	free(b->grid);
	b->grid=NULL;
	b->head.next=NULL;
	b->tail.prev=NULL;
	b->ptr=NULL;
}




int main(int argc,char **argv){

	FILE *source=stdin;
	int count=1;
	int all=0;

	if(argc>=2){
		if(!strcmp(argv[1],"--help")){
			printf("Usage: sudoku [COUNT|all] [FILE|-]\n");
			return 0;
		}
		if(strcmp(argv[argc-1],"-")){
			if((source=fopen(argv[argc-1],"r"))==NULL){
				fprintf(stderr,"sudoku: %s: No such file\n",argv[1]);
				return 0;
			}
		}
	}

	if(argc>=3){
		if(!strcmp(argv[argc-2],"all")){
			all=1;
		}else{
			count=atoi(argv[argc-2]);
		}
	}

	if(count){

		struct board b;
		create_board(&b);
		read_board(&b,source);
		fclose(source);

		if(solve_board(&b)){
			print_board(&b);
			--count;
			while(count || all){
				if(!solve_board(&b))break;
				puts("");
				print_board(&b);
				//getchar();
				--count;
			}

		}else{
			fprintf(stderr,"sudoku: puzzle is impossible to solve\n");
		}

		destroy_board(&b);
	}

	return 0;
}
