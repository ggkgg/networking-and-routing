#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include <stdio.h>
#include "rt.h"


//#include <time.h>
#include <string.h>
#include "malloc.h"

#pragma comment(lib,"ws2_32.lib")


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
unsigned short	PINGREQ = 0xC0;
unsigned short	PINGRESP = 0xD0;
unsigned short	DISCONNECT = 0xE0;

unsigned short  MQTT_ERR_SUCCESS = 0;
unsigned short  USART_ERR_SUCCESS = 1;
unsigned short  USART_ERR_NOMESSAGE;
int rc;
int already_in_net=0;
int len_packet=0;
int usart_flag1=0;
int usart_flag2=0;


unsigned short  MY_CHILD_HAS_NODE = 0;
unsigned short  MY_RT = 0xf0; //send myself route table
unsigned short  CHILD_RT_ERR = 1;
unsigned short  FOUND_MID = 0;

char _out_packet[20] = { 0 };
char _current_out_packet[20] = { 0 };//��?�
char _usart_recv_packet1[200] ;
char _usart_recv_packet2[200] ;




//ALIENTEK????STM32?a�?�?�?�1
//?�?�?�?�  
//??�??�3??owww.openedv.com
//1??Y�DD?��?��????�D?T1???
int main(void)
{
	delay_init();	    	 //?��o��y3?�??�	  
	LED_Init();		  	//3?�??��?LED�??�?�2?t?�?�
	uart_init(9600);
  rt_init();

	while (1)
	{
		LED0 = 0;
		LED1 = 0;
		delay_ms(300);	 //?��300ms
		LED0 = 1;
		LED1 = 0;
		// _send_pingreq();
		_recieve_pingreq();



	
		printf("\n");

		//delay_ms(30000);	//?��300ms
	}
}
