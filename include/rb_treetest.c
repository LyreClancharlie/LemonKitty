#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rb_tree.h"
//typedef int key_t;
//typedef int data_t;

//typedef enum color_t
//{
//	    RED = 0,
//		    BLACK = 1
//}color_t;

//typedef struct rb_node_t
//{
//	    struct rb_node_t *left, *right, *parent;
//		    key_t key;
//			    data_t data;
//				    color_t color;
//}rb_node_t;

/* forward declaration */
//extern rb_node_t* rb_insert(key_t key, data_t data, rb_node_t* root);
//extern rb_node_t* rb_search(key_t key, rb_node_t* root);
//extern rb_node_t* rb_erase(key_t key, rb_node_t* root);

int main()
{
	    int i, count = 900000;
	    key_t key;
	    rb_tree_node_t* root = NULL, *node = NULL;
				    
	   for (i = 1; i < count; ++i) {		
		   key = rand() % count;									
		   if ((root = rb_insert(key, i, root))) {			
			   printf("[i = %d] insert key %d success!\n", i, key);
	        } else {					
				printf("[i = %d] insert key %d error!\n", i, key);					
				exit(-1);																
			}
						
		   if ((node = rb_search(key, root))) {											
			   printf("[i = %d] search key %d success!\n", i, key);											
		   } else {					
			   printf("[i = %d] search key %d error!\n", i, key);				
			   exit(-1);																
		   }						
		   if (!(i % 10)) {						
			   if ((root = rb_erase(key, root))) {												
				   printf("[i = %d] erase key %d success\n", i, key);												
			   } else {					
				   printf("[i = %d] erase key %d error\n", i, key);					
			   }																
		   }				
	   }			
	   return 0;
}
