#include<stdio.h>
#include<math.h>
#include<string.h>
#include "declar.h"
#define engine_temp_enable E		//if the engine_temp_enable any thing but E the engine temperature code will not be included.
struct state{char engine_state[5];	//structure of the required outputs/inputs.
char AC[5];
int vehicle_speed;
float room_temp;
char engine_cooler[5];
float engine_temp;};
struct state vehicle_state={"on","off",0,25,"off",125};
int main()
{	setbuf(stdout,NULL);
void set();
char op[20];
while(1)
{
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	scanf("%s",op);
	while(strlen(op)!=1)				//to make sure the user only enter one char
	{
		printf("invalid input,try again:");
		scanf("%s",op);
	}
	switch(*op)									//switch case to choose the required operation
	{
	case 'a':printf("Turn on the vehicle engine\n\n"); //first operation turn on the engine and call function set()
	set();printf("Turn off the vehicle engine\n\n");
	strcpy(vehicle_state.engine_state,"off");
	continue;
	case 'b':printf("Turn off the vehicle engine\n\n");
	strcpy(vehicle_state.engine_state,"off");
	continue;
	case 'c':printf("Quit the system\n\n");		//terminate the program
	return 0;
	default:
		printf("invalid input,please choose one of the following\n");
		continue;

	}

}
return 0;
}
void display(){				//display all the statues of the vehicle
	if(vehicle_state.vehicle_speed==30)
		check2();
	printf("the engine state is %s\n",vehicle_state.engine_state);
	printf("the AC is %s\n",vehicle_state.AC);
	printf("the vehicle speed is %d KM/H\n",vehicle_state.vehicle_speed);
	printf("the room temperature is %.2f °c\n",vehicle_state.room_temp);
#if engine_temp_enable==E
	printf("the engine temperature controller is %s\n",vehicle_state.engine_cooler);
	printf("the engine temperature is %.2f °c\n\n",vehicle_state.engine_temp);
#endif
}
void set()						//takes the input from the user based on his choice
{
	char op[20];
	while(1){
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
#if engine_temp_enable==E
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
#endif
	scanf("%s",op);
	while(strlen(op)!=1)
	{
		printf("invalid input,try again:");
		scanf("%s",op);
	}
	switch(*op)
	{
	case 'a':strcpy(vehicle_state.engine_state,"off");
	return;
	case 'b':set_color();
	continue;
	case 'c':set_room_temp();
	continue;
#if engine_temp_enable==E
	case 'd':set_engine_temp();
	continue;
#endif
	default :printf("invalid input,please choose one of the following:\n");
	continue;
	}
	}
}
void set_color()		//takes the color of traffic light
{
	char color[10];
	while(1){
	printf("enter the traffic light color:");
	scanf("%s",color);
	while(strlen(color)!=1)
	{
		printf("invalid input,try again:");
		scanf("%s",color);
	}
	switch(*color)
	{
	case 'g':
	case 'G':vehicle_state.vehicle_speed=100;display();return;
	case 'o':
	case 'O':vehicle_state.vehicle_speed=30;display();return; //modify the speed and calling check 2
	case 'r':
	case 'R':vehicle_state.vehicle_speed=0;display();return;
	default:printf("invalid input,try again:\n");
	continue;
	}
	}
}


void set_room_temp()			//takes the room temperature
{
	char temp[20];			 //to apply the user to enter a float and prevent entering a character take the input as array of chars and check them one by one
	float temp_val=0;		//variable to assign the float value of the input array of character in it
	printf("enter the room temperature:");
	while(1){
	scanf("%s",temp);
	if(check(temp))			//calling function check
	{
		int dot_pos=-1;    //if the user enter a float ,to know the position of the dot
		int dotcount=0;			//dot counter to make sure the user only puts one dot
		for(int j=0;temp[j]!='\0';j++)
		{		if(temp[j]==46)			//46 is the ASCII code of '.'
				{
				dot_pos=j;
				dotcount++;
				}
		if(dotcount>1)
		{	printf("invalid input,try again:");
					continue;
		}
		}

		if(dot_pos==-1)				//if the dot_pos=-1 then we have integer we convert it easily by the following loop
			for(int i=0;temp[i]!='\0';i++)
			{
				temp_val=10*temp_val+temp[i]-48;

			}
		else
			temp_val=convert_float_array(temp,dot_pos);  //if dot_pos not =-1 then we have a float and we call the function convert_float_array
	}
	else
	{
		printf("invalid input,try again:");
		continue;
	}
	if(vehicle_state.vehicle_speed==30)			//to apply special conditions when the speed is 30km/h
		{vehicle_state.room_temp=temp_val;
		display();return;}
	if(temp_val<10||temp_val>30)
	{
		strcpy(vehicle_state.AC,"on");
		vehicle_state.room_temp=20;
		display();
	}
	else
	{
		strcpy(vehicle_state.AC,"off");
		vehicle_state.room_temp=temp_val;
		display();
	}
	return;
	}

}
void set_engine_temp()   //the same as room temperature put different variables names
{
	int check(char arr[]);
	char engine_temp[20];
	float engine_temp_val=0;
	printf("enter the engine temperature:");
	while(1){
	scanf("%s",engine_temp);
	if(check(engine_temp))
	{
		int dot_pos=-1;
		int dotcount=0;
		for(int j=0;engine_temp[j]!='\0';j++)
		{
			if(engine_temp[j]==46)
				{dot_pos=j;
				dotcount++;
				}
			if(dotcount>1)
			{
				printf("invalid input,try again:");
						continue;
			}
		}
		if(dot_pos==-1)
			for(int i=0;engine_temp[i]!='\0';i++)
			{
				engine_temp_val=10*engine_temp_val+engine_temp[i]-48;

			}
		else
			engine_temp_val=convert_float_array(engine_temp,dot_pos);
	}
	else
	{
		printf("invalid input,try again:");
		continue;
	}
	if(vehicle_state.vehicle_speed==30)			//to apply special conditions when the speed is 30km/h
			{vehicle_state.engine_temp=engine_temp_val;
			display();return;}
	if(engine_temp_val<100||engine_temp_val>150)
	{
		strcpy(vehicle_state.engine_cooler,"on");
		vehicle_state.engine_temp=125;
		display();

	}
	else
	{
		strcpy(vehicle_state.engine_cooler,"off");
		vehicle_state.engine_temp=engine_temp_val;
		display();
	}
	return;
	}
}
int check(char arr[])			//checks that the array has no chars, just numbers or dots
{
	for(int i=0;arr[i]!='\0';i++)
	{
		if(!((arr[i]>=48&&arr[i]<=57)||arr[i]==46))
		{
			return 0;
		}
	}
	return 1;
}
void check2()							//if the speed is 30km/h and AC or engine cooler is off the function turns it on and change the temperature
{
	if(!strcmp(vehicle_state.AC,"off"))
	{

		strcpy(vehicle_state.AC,"on");
	}
	vehicle_state.room_temp=(5/4.0)*vehicle_state.room_temp+1;
	if(!strcmp(vehicle_state.engine_cooler,"off"))
	{

		strcpy(vehicle_state.engine_cooler,"on");
	}
	vehicle_state.engine_temp=(5/4.0)*vehicle_state.engine_temp+1;
}
float convert_float_array(char arr[],int dot_pos)		//converts array of chars(all are numbers and one dot) to a float value
{
	int counter=10;
	float value=0;
	for(int i=0;i<dot_pos;i++)
	{
		value=10*value+arr[i]-48;
	}
	for(int j=dot_pos+1;arr[j]!='\0';j++)
	{
		value=value+(arr[j]-48)/(float)(counter);
		counter=counter*10;
	}
	return value;
}
