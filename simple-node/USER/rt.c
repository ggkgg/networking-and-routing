#include "rt.h"

node *will_after_found_id;
extern unsigned short  FOUND_MID;



//make my own rt into my_rt[], then _send_simple_command(MY_RT);
int send_my_rt(char * my_child_rt){
	char my_rt[300] = { 0 };//数组初始化可以不确定大小吗？
	node * tmp_head ;
	char *my_rt_point;
	char *my_child_rt_point;
	int my_child_rt_num ;
	
	
	 tmp_head = malloc(sizeof(struct list));
	 my_child_rt_num = 0;
	 my_rt_point = my_rt;
	 my_child_rt_point = my_child_rt;
	
	sprintf(my_rt, "%u,%u#%u", head->father->mid,head->mid,head->mid);
	
	tmp_head = head;
	tmp_head = tmp_head->child;


	while (tmp_head != NULL) // add child
	{
		sprintf(my_rt, "%s,%u",my_rt,tmp_head->mid);
		tmp_head = tmp_head->next;
	}

	sprintf(my_rt, "%s#",my_rt);


	if (MY_CHILD_HAS_NODE){  //MY_CHILD_HAS_NODE set in  
		my_rt_point = strcat(my_rt_point,  my_child_rt_point); // add child-child's child  
		//and the point my_rt_point point to the begining 
	}

	_send_simple_command(MY_RT,102,101);// 

	//todo
	/*
	_send_simple_command(MY_RT,my_rt_point);//
    */

}


/*
when got child_rt, to build own rt:
1. read_my_child_rt(char * packet)  //cut use #
2. build_my_child_rt(token1);

*/

int read_my_child_rt(char * packet){   //use # to cut and build_my_child_rt to biuld whole node
	char seps[] = "#";
	char *token1 = NULL;

	// Establish string and get the first token:
	token1 = strtok(packet, seps);
	build_my_child_rt(token1);

	while (token1 != NULL)
	{

		token1 = strtok(NULL, seps);
			if (token1 != NULL){
					build_my_child_rt(token1);
		
					}
	
	}
}


int build_my_child_rt(char *packet){ //packet cannot have some string or else, only ok for num packet[]={'1','22','678'}
		char seps[] = ",";
	  char *token1 = NULL;

	// Establish string and get the first token:
	token1 = strtok(packet, seps);
	if(atoi(token1)==102){
				while (token1 != NULL)
			{

					token1 = strtok(NULL, seps);

						insert_rt_next_doublenew(head, atoi(token1));

			}
	}
	//build_my_child_rt(token1);

	if(atoi(token1)!=102){
			node *try_found_id = (node *)malloc(sizeof(struct list));
		node *found_id = (node *)malloc(sizeof(struct list));
		found_id = will_after_found_id;
		try_found_id->mid=atoi(token1);
			preordertraverse(head, try_found_id);
		
		if(FOUND_MID==1){
					while (token1 != NULL)
			{

					token1 = strtok(NULL, seps);
						if (token1 != NULL){
			               insert_rt_next_doublenew(found_id, atoi(token1));
							}
						

			}
		
		
		}
		else {   // IF NOT FIND ID
			CHILD_RT_ERR = 1;
		}
				
	}
	
	/*

	if (atoi(*packet) == 102){
		packet++;
		while (*packet != NULL)
		{
			int tmp_id;
			tmp_id = atoi(*packet);
			insert_rt_next_doublenew(packet, tmp_id);    //insert from packet:should packet->child then insert
			packet++;

		}
	}

	if (*packet != 102){
		int tmp_id;
		tmp_id = atoi(*packet);
		
		node *after_found_id = (node *)malloc(sizeof(struct list));
		preordertraverse(head, tmp_id);

		if (FOUND_MID){// must return a point to tmp_id

			
			//add something to change the point to tmp_id
		//	void move_piont_to_build_rt(){node *head, node *tmp_id_point}
			
			packet++;
			while (*packet != NULL)
			{
				int tmp_id;
				tmp_id = atoi(*packet);
				insert_rt_next_doublenew(after_found_id, tmp_id);//inset from the after_found_id
				packet++;

			}
		}

		else {
			CHILD_RT_ERR = 1;
		}

	}
*/
}


//searvh preoder

node * preordertraverse(node * tree, node *id){
	

	if (tree != NULL){
		if (tree->mid != 0){

			printf("tree_mid->%d\n", tree->mid);

			if (tree->mid == id->mid){
				FOUND_MID = 1;
				will_after_found_id = malloc(sizeof(struct list));
				will_after_found_id = tree;
				//printf("after_found_id->%d\n", will_after_found_id->mid);
				//printf("after_found_id->next%d\n", will_after_found_id->next->mid);
				//printf("after_found_id%d\n", will_after_found_id);
				//printf("FOUND_MID:%d\n", FOUND_MID);
				return 	will_after_found_id ;

			}


		}


	}
	if (tree == NULL)
		return 0;
	printf("tree::%d\n", tree->mid);
	preordertraverse(tree->child, id);
	preordertraverse(tree->next, id);


}



//as we got node * preordertraverse(node * tree, int mid)
//which return the point of mid 


void rt_init(){

	head = malloc(sizeof(struct list));
	head->mid = 101;
	head->next = NULL;
	head->father = NULL;
	head->prior = NULL;
	head->child = NULL;



	temp_next = malloc(sizeof(struct list));
	temp_next = head;
	temp_child = malloc(sizeof(struct list));
	temp_child = head;

}


void insert_rt_next_doublenew(node * head, int one){

	node * temp_insert = (node *)malloc(sizeof(struct list));//middle one

	if (head->child == 0){      //如果子节点为空

		temp_next->child = temp_insert;
		temp_insert->prior = temp_next;
		temp_insert->mid = one;
		temp_insert->next = NULL;
		temp_insert->child = NULL;
		temp_insert->father = head;//same father node
		temp_next = temp_insert;

	}
	else{
		if (temp_next != 0){
			while (temp_next->next != 0){
				temp_next = temp_next->next;
			}
			temp_next->next = temp_insert;
			temp_insert->prior = temp_next;
			temp_insert->mid = one;
			temp_insert->next = NULL;
			temp_insert->child= NULL;
			temp_insert->father = temp_next->father;//same father node
			temp_next = temp_insert;
		}
	}






}


void insert_rt_next_doublenew_delete(node * tree ,int delete_id){//delete node

	node *found_id ;
	node *will_found_id ;
	
	FOUND_MID = 0;
	found_id= malloc(sizeof(struct list));
	will_found_id =malloc(sizeof(struct list));
	
	will_found_id->mid = delete_id;
	printf("deltet_head_mid->%d\n", tree->mid);
	preordertraverse(tree, will_found_id);
	printf("id\n");
	printf("id%d\n", will_after_found_id->mid);
	found_id = will_after_found_id;
	//printf("balal%d\n", preordertraverse(tree, will_found_id));
	printf("found_id->%d\n", found_id->next->mid);
	printf("FOUND_MID:%d\n", FOUND_MID);

	



	if (FOUND_MID == 1){
		
		found_id->next->prior = found_id->prior;
		printf("found_id->%d\n", found_id->next->prior->mid);
		found_id->prior->next = found_id->next;
		//found_id->father->child = NULL;  cause every child was point to father and if delete,it will affact
		if (found_id->child != NULL){
			found_id->child->father->next->prior = found_id->child->father->prior;
			found_id->child->father->prior->next = found_id->child->father->next;
			found_id->child = NULL;

		}
		
	}



}


