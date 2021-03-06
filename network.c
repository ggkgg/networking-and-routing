#include<stdio.h>
#include<winsock2.h>

#include<time.h>
#include <string.h>
#include<stdlib.h>
#include <string.h>
#include <process.h>
#pragma comment(lib,"ws2_32.lib")

unsigned short _send_pingreq();
unsigned short _recieve_pingreq();
unsigned short _packet_queue(command, packet, mid, qos);
unsigned short _send_simple_command(command);
int recv_process();

int ping_ack();
int routetable();
//int USART_rec();
void rt_init();
void insert_rt_next();

void insert_rt_next_doublenew();
void insert_rt_next_doublenew_delete(int mid);
int searching_node(int mid);

unsigned short	CONNECT = 0x10;
unsigned short	CONNACK = 0x20;
unsigned short	PUBLISH = 0x30;
unsigned short	PUBACK = 0x40;
unsigned short	PUBREC = 0x50;
unsigned short	PUBREL = 0x60;
unsigned short	PUBCOMP = 0x70;
unsigned short	SUBSCRIBE = 0x80;
unsigned short	SUBACK = 0x90;
unsigned short	UNSUBSCRIBE = 0xA0;
unsigned short	UNSUBACK = 0xB0;
unsigned short	PINGREQ = 0xC0;//1100 0000 transfer to 192 in decimal unit
unsigned short	PINGRESP = 0xD0;
unsigned short	DISCONNECT = 0xE0;

unsigned short  MQTT_ERR_SUCCESS = 0;
unsigned short  MY_CHILD_HAS_NODE = 0;
unsigned short  MY_RT = 0xf0; //send myself route table
unsigned short  CHILD_RT_ERR = 1;
unsigned short  FOUND_MID;


char _out_packet[20] = { 0 };
char _current_out_packet[20] = { 0 };

struct messagestuff
{
	unsigned short  command;
	unsigned short  mid;
	unsigned short  did;
	unsigned short  qos;
	unsigned short  pos;
	unsigned short  to_process;
	unsigned short	packet;

};
struct messagestuff recmpkt;
struct messagestuff mpkt;

struct routestuff
{

	unsigned short  mid;
	unsigned short  forward_mid;
	unsigned short  layer;
	unsigned short  metric;
}rt;


typedef struct list
{
	int mid;
	struct list *child;//child
	struct list *next;//college
	struct list *prior;//college
	struct list *father;//college
}node;
node *head;
node *temp_next;
node *temp_child;
node *temp_prior;
node *temp_father;




void main(){

	struct A
	{
		int a;
		char b;
		int c;
		char d[];
	};
	struct A aa = { 2, 'k', 4, "hello" };

	char  buf[200] = { 0 };


	//memcpy(buf, &aa, sizeof(aa));

	sprintf_s(buf, 200, " all: %d%c%d%s\n", aa.a, aa.b, aa.c, aa.d);

	printf_s("Output:\n%s\ncharacter count =\n", buf);


	//all_init();
	_send_pingreq();
	//_recieve_pingreq();
	printf("hello\n");
	recv_process();

	routetable();
	//int lens = atoi(_current_out_packet);
	//int lenss = atoi(_out_packet);
	//printf("%d  and ", lens);




	//printf_s("Output:%scharacter count =\n", buff);
	//printf("%d  and buff ", sizeof(buff));
	//sprintf_s(buff, lens, " %u\n", PINGREQ);
	//printf_s("Output:%scharacter count =\n", buff);

	//printf("%s", _current_out_packet>>(lens-4));

	//printf("%d  and new buff ", sizeof(buff));

	//printf("ww%cww", _current_out_packet[2]);
	//printf("qqww%swwqq",_out_packet);
	//printf("%doo", lens);
	//printf("aa%d\n", lenss);
	//printf("end\n");

	printf("how many numbers\n");

	rt_init();
	insert_rt_next_doublenew(1);
	insert_rt_next_doublenew(2);
	insert_rt_next_doublenew(3);
	insert_rt_next_doublenew(4);
	insert_rt_next_doublenew(5);
	insert_rt_next_doublenew(6);
	insert_rt_next_doublenew(7);

	//	insert_rt_next_doublenew_delete(5);

	head = head->child;//transfer to the first child node and then printf head-next-mid
	searching_node(15);
	insert_rt_next_doublenew_delete(5);
	insert_rt_next_doublenew_delete(16);
	while (head != NULL)
	{
		printf("my mid is :  ");
		printf("%d\n", head->mid);
		printf("my father mid is :");
		printf("%d\n", head->father->mid);


		head = head->next;
	}
	printf("\n");


	printf("tocken!!!!!!!!!!!");
	char string1[] =
		"A string\tof ,,tokens and some  more tokens";

	char seps[] = ",";
	char seps1[] = "\t";
	char *token1 = NULL;

	char *next_token1 = NULL;


	printf("Tokens:\n");

	// Establish string and get the first token:
	token1 = strtok_s(string1, seps, &next_token1);
	printf("tocken1: %s\n", token1);
	token1 = strtok_s(token1, seps1, &next_token1);
	printf("tocken3: %s\n", token1);
	// While there are tokens in "string1" or "string2"
	while (token1 != NULL)
	{

		printf("tocken2:  %s\n", token1);
		token1 = strtok_s(NULL, seps1, &next_token1);


	}


	printf("tocken!!!!!!!!!!!\n\n\n");
	printf("new!!!!!!!!!!!\n");

	char we[] = { 'p', '2', '3' };
	int cc = atoi(we);
	char *me = we;
	printf("%c\n", *me);
	me++;
	printf("%c\n", *me);
	me++;
	printf("%c\n", *me);
	printf("%d\n", cc);

	printf("new!!!!!!!!!!!\n");




	getchar();
}



int send_my_rt(char * my_child_rt){
	char my_rt[] = { 0 };//数组初始化可以不确定大小吗？
	my_rt[0] = head->father->mid;
	my_rt[1] = head->mid;
	my_rt[2] = "#";
	my_rt[3] = head->mid;
	node * tmp_head = (node *)malloc(sizeof(struct list));
	tmp_head = head;
	int my_rt_num = 4;
	tmp_head = tmp_head->child;
	while (tmp_head != NULL)
	{
		my_rt[my_rt_num] = tmp_head->mid;
		my_rt_num++;

		tmp_head = tmp_head->next;
	}
	int my_child_rt_num = 0;
	char *my_rt_point = my_rt;
	char *my_child_rt_point = my_child_rt;


	if (MY_CHILD_HAS_NODE){

		my_rt_point = strcpy_s(my_rt_point, my_rt_num, my_child_rt_point);

	}

	_send_simple_command(MY_RT);



}

int read_my_child_rt(char * packet){   //use # to cut and build_my_child_rt to biuld whole node
	char seps[] = "#";
	char *token1 = NULL, *pNext = NULL;

	// Establish string and get the first token:
	token1 = strtok_s(packet, seps, pNext);
	build_my_child_rt(token1);

	while (token1 != NULL)
	{

		token1 = strtok_s(NULL, seps, pNext);

		build_my_child_rt(token1);

	}
}
int build_my_child_rt(char *packet){ //packet cannot have some string or else, only ok for num packet[]={'1','22','678'}

	if (atoi(*packet) == 102){
		packet++;
		while (*packet != NULL)
		{
			int tmp_id;
			tmp_id = atoi(*packet);
			insert_rt_next_doublenew(tmp_id);
			packet++;

		}
	}

	if (*packet != 102){
		int tmp_id;
		tmp_id = atoi(*packet);
		if (searching_node(tmp_id)){// must return a point to tmp_id

			/*
			add something to change the point to tmp_id
			void move_piont_to_build_rt(){node *head, node *tmp_id_point}
			*/
			packet++;
			while (*packet != NULL)
			{
				int tmp_id;
				tmp_id = atoi(*packet);
				insert_rt_next_doublenew(tmp_id);
				packet++;

			}
		}

		else {
			CHILD_RT_ERR = 1;
		}


	}

}


node * preordertraverse(node * tree, int mid){
	if (tree->mid == mid){
		FOUND_MID = 1;
		char *point_found_mid = tree;
		return point_found_mid;

	}

	if (tree == NULL)
		return;
	printf("%d", tree->mid);
	preordertraverse(tree->child, mid);
	preordertraverse(tree->next, mid);


}


int searching_node(int mid){// searching node only at its child level,
	printf("one");
	temp_next = head;
	int yc = 1;
	//head = head->child;
	//node * temp_delete = (node *)malloc(sizeof(struct list));//middle one
	while (temp_next->mid != mid){
		printf("two");
		if (temp_next != 0){
			printf("there");
			if (temp_next->next != 0){
				printf("four\n");
				temp_next = temp_next->next;

			}
			else{
				printf("out of storage node and cannot find it out \n");
				printf("the lost mid is : %d-------fail!!! \n", mid);
				yc = 0;
				break;
			}
		}
	}
	if (yc == 1){
		printf("get mid:  %d--------success!!\n", temp_next->mid);
		printf("its father is :  %d\n", temp_next->father->mid);

	}

	//temp_next->next = malloc(sizeof(struct list));
	//temp_next = temp_next->next;
	//temp_next->mid = 4;
	//temp_next->next = NULL;
	printf("five");


	return yc;


}


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
void insert_rt_next(){
	if (temp_next != 0){
		while (temp_next->next != 0){
			temp_next = temp_next->next;
		}
	}
	temp_next->next = malloc(sizeof(struct list));
	temp_next = temp_next->next;
	temp_next->mid = 4;
	temp_next->next = NULL;

}


void insert_rt_next_doublenew(int one){

	node * temp_insert = (node *)malloc(sizeof(struct list));//middle one

	if (head->child == 0){      //如果子节点为空

		temp_next->child = temp_insert;
		temp_insert->prior = temp_next;
		temp_insert->mid = one;
		temp_insert->next = NULL;
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
			temp_insert->father = temp_next->father;//same father node
			temp_next = temp_insert;
		}
	}

	//temp_next->next = malloc(sizeof(struct list));
	//temp_next = temp_next->next;
	//temp_next->mid = 4;
	//temp_next->next = NULL;




}
/*
void insert_rt_next_doublenew(int one){

node * temp_insert = (node *)malloc(sizeof(struct list));//middle one

if (temp_next != 0){
while (temp_next->next != 0){
temp_next = temp_next->next;
}
}
//temp_next->next = malloc(sizeof(struct list));
//temp_next = temp_next->next;
//temp_next->mid = 4;
//temp_next->next = NULL;

temp_next->next = temp_insert;
temp_insert->prior = temp_next;
temp_insert->mid = one;
temp_insert->next = NULL;
temp_insert->father = temp_next->father;//same father node
temp_next = temp_insert;



}

*/
void insert_rt_next_doublenew_delete(int mid){//deletenode
	printf("one");
	int ic = 1;
	temp_next = head;
	//node * temp_delete = (node *)malloc(sizeof(struct list));//middle one
	while (temp_next->mid != mid){
		printf("two");
		if (temp_next != 0){
			printf("there");
			if (temp_next->next != 0){
				printf("four\n");
				temp_next = temp_next->next;

			}
			else{
				printf("out of storage node and cannot delete it out \n");
				printf("the mid cannot delete is : %d-------fail!!! \n", mid);
				ic = 0;
				break;
			}
		}
	}

	//temp_next->next = malloc(sizeof(struct list));
	//temp_next = temp_next->next;
	//temp_next->mid = 4;
	//temp_next->next = NULL;
	printf("five\n");

	if (ic == 1){
		printf("delete node mid is :  %d----succes!!\n", temp_next->mid);
		temp_next->next->prior = temp_next->prior;
		temp_next->prior->next = temp_next->next;
	}



}






/*

int USART_rec(){
u16 t;
u16 len;
u16 times = 0;
while (1)
{
if (USART_RX_STA & 0x8000)
{
len = USART_RX_STA & 0x3FFF;//得到此次接收到的数据长度
printf("\r\n您发送的消息为:\r\n\r\n");
for (t = 0; t<len; t++)
{
USART1->DR = USART_RX_BUF[t];
while ((USART1->SR & 0X40) == 0);//等待发送结束
}
printf("\r\n\r\n");//插入换行
USART_RX_STA = 0;
int rc=1;
}
else
{
times++;
if (times % 5000 == 0)
{
printf("\r\n战舰STM32开发板 串口实验\r\n");
printf("正点原子@ALIENTEK\r\n\r\n");
}
if (times % 200 == 0)printf("请输入数据,以回车键结束\r\n");
if (times % 30 == 0)LED0 = !LED0;//闪烁LED,提示系统正在运行.
delay_ms(10);
int  rc=0;
}
}
return rc;
}

unsigned short _recieve_pingreq(){
if (USART_rec()){
printf("rec message");
}

}

void all_init(){
Stm32_Clock_Init(9);	//系统时钟设置
uart_init(72, 9600);	 	//串口初始化为9600
delay_init(72);	   	 	//延时初始化
LED_Init();		  		//初始化与LED连接的硬件接口
BEEP_Init();         	//初始化蜂鸣器端口
KEY_Init();         	//初始化与按键连接的硬件接口
}

*/




int recv_process(){

	char seps[] = " ,\t\n";
	char *token1 = NULL;

	char *next_token1 = NULL;


	printf("Tokens:\n");

	// Establish string and get the first token:
	token1 = strtok_s(_current_out_packet, seps, &next_token1);
	printf(" oo%soo", token1);
	int tokenx1 = atoi(token1);
	recmpkt.command = tokenx1;
	token1 = strtok_s(NULL, seps, &next_token1);
	int tokenx2 = atoi(token1);
	recmpkt.mid = tokenx2;
	printf(" %d\n", recmpkt.mid);

	// While there are tokens in "string1" or "string2"
	while (token1 != NULL)
	{
		// Get next token:

		printf(" %s\n", token1);
		token1 = strtok_s(NULL, seps, &next_token1);

	}

	unsigned short rc;
	if (recmpkt.command == PINGREQ){
		routetable();
		rc = ping_ack();

	}

	if (recmpkt.command == PINGRESP){
		//routetable_mult();
		rc = 0;


	}
	return rc;


}

int ping_ack(){

	unsigned short rc = _send_simple_command(PINGRESP);
	mpkt.did = rt.forward_mid;
	if (rc == MQTT_ERR_SUCCESS){
		unsigned short _ping_t = time(0);
	}
	return rc;

}




int routetable(){
	rt.mid = mpkt.mid;
	rt.forward_mid = recmpkt.mid;
	rt.layer = 1;
	rt.metric = 1;
	return 0;

}
//couple with ping——ack
unsigned short _send_pingreq(){
	//self._easy_log(MQTT_LOG_DEBUG, "Sending PINGREQ")
	unsigned short rc = _send_simple_command(PUBLISH);
	printf("%d", 11);
	if (rc == MQTT_ERR_SUCCESS){
		unsigned short _ping_t = time(0);
	}
	return rc;
}
unsigned short _send_simple_command(command){
	//For DISCONNECT, PINGREQ and PINGRESP
	//unsigned short remaining_length = 0;

	unsigned short packet = htons(command);
	printf("%d", 12);
	printf("%d", packet);
	//packet = struct.pack('!BB', command, remaining_length);
	//unsigned short packet = command;
	return _packet_queue(command, packet, 0, 0);
}

unsigned short _packet_queue(command, packet, mid, qos){

	mpkt.command = command;
	mpkt.mid = mid;
	mpkt.did = 0;
	mpkt.packet = packet;
	mpkt.qos = qos;
	mpkt.pos = 0;
	mpkt.to_process = sizeof(packet);


	//self._out_packet_mutex.acquire();
	sprintf_s(_out_packet, 20, "%u,%u,%u,%u,%u,%u,%u", mpkt.command, mpkt.mid, mpkt.did, mpkt.packet, mpkt.qos, mpkt.pos, mpkt.to_process);
	printf("%s\n", _out_packet);
	//	_out_packet.append(mpkt);  //插入队列
	//if self._current_out_packet_mutex.acquire(False){
	//if (_current_out_packet == 0 && sizeof(_out_packet) > 0)
	if (sizeof(_out_packet) > 0){
		for (int i = 0; i < sizeof(_out_packet); i++){
			_current_out_packet[i] = _out_packet[i];//把packet最后一位弹出给current-out-packet
		}
	}

	//	self._current_out_packet_mutex.release()
	//	}
	//self._out_packet_mutex.release()

	//Write a single byte to sockpairW (connected to sockpairR) to break
	//out of select() if in threaded mode.
	/*try:
	self._sockpairW.send(sockpair_data)
	except socket.error as err:
	if err.errno != EAGAIN:
	raise

	if not self._in_callback and self._thread is None:
	return self.loop_write()
	else:
	return MQTT_ERR_SUCCESS
	*/
	printf("%d\n", 13);
	printf("%s", _current_out_packet);
	return MQTT_ERR_SUCCESS;
}


