# LINE-FOLLOWING-IN-V-REP

*Functions : int lfr(), forward_wls(), left_turn_wls(), right_turn_wls(), Task_1_1
 some predefined functions provided by eYRC team namely forward(), right(), left(), stop(), ADC_conversion(), main() *Global Variables : NONE*/


#include "NS_Task_1_Sandbox.h"

/*
*
* Function Name: lfr
* Input: void
* Output: int
* Logic: Uses white line sensors to maintain motion on a line
* Example Call: n=lfr() //follows line from one node to next node and returns one on detection of node
*
*/

int lfr(void)//user defined function 
{
	int q = 10;// delay value 
	int w = 100, b = 210; //w indicates white sensor value so as b to black threshold values

	while (1)
	{
		int left_sensor = ADC_Conversion(1);// channel 1 value is assigned to left sensor
		int centre_sensor = ADC_Conversion(2);// channel 2 value is assigned to centre sensor
		int right_sensor = ADC_Conversion(3);// channel 3 value is assigned to right sensor

		_delay_ms(1);
		//following are conditions to follow line 
		if (left_sensor <= w && centre_sensor >= b && right_sensor <= w)
		{
			forward();
			_delay_ms(q);
		}
		if (left_sensor >= b && centre_sensor <= w && right_sensor <= w)
		{
			soft_left();
			_delay_ms(q);
		}
		if (left_sensor >= b && centre_sensor >= b && right_sensor <= w)
		{
			soft_left();
			_delay_ms(q);

		}
		if (left_sensor <= w && centre_sensor >= b && right_sensor >= b)
		{
			soft_right();
			_delay_ms(q);

		}
		if (left_sensor <= w && centre_sensor <= w && right_sensor >= b)
		{
			soft_right();
			_delay_ms(q);
		}

		if (left_sensor >= b && centre_sensor >= b && right_sensor >= b)
		{
			// following condition is used to stop the bot on node and move forward after detecting node a little bit
			while ((ADC_Conversion(1) <= 210) && (ADC_Conversion(3) <= 210) && (ADC_Conversion(2) == 210))
				forward();
			forward();
			while ((ADC_Conversion(1) >= 210) && (ADC_Conversion(3) >= 210));
			stop();
			return 1;// all the above condition is checked and the functions return TRUE on next node detection
		}
	}
}


/*
*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: forward_wls(2); //Goes forward by two nodes
*
*/
void forward_wls(unsigned char node)
{
	int n = lfr();
	_delay_ms(150);
	while ((ADC_Conversion(1) <= 210) && (ADC_Conversion(3) <= 210) && (ADC_Conversion(2) >= 210))
		forward();
	forward();
	while ((ADC_Conversion(1) >= 210) && (ADC_Conversion(3) >= 210));
	_delay_ms(20);
	stop();

}
//int node = 0;
//int path[11] = { 1,4,5,2,2,1,1,3,4,1,2 };

/*
*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls(); //Turns right until black line is encountered
*
*/
void left_turn_wls(void)
{
	left();
	_delay_ms(150);
	// below are condition to take left in different situation 
	while ((ADC_Conversion(1) <= 210) && (ADC_Conversion(3) <= 210) && (ADC_Conversion(2) >= 210));
	left();
	while (ADC_Conversion(1) <= 210);
	while (ADC_Conversion(2) <= 210);
	_delay_ms(60);
	stop();

}

/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wls(void)
{
	right();
	_delay_ms(150);
	while ((ADC_Conversion(1) <= 210) && (ADC_Conversion(3) <= 210) && (ADC_Conversion(2) >= 210));
	right();
	while (ADC_Conversion(3) <= 210);
	while (ADC_Conversion(2) <= 210);
	_delay_ms(30);
	stop();

}



/*
*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.1 logic
* Example Call: Task_1_1();
*/
void Task_1_1(void)


{

	stop();
	_delay_ms(10);
	forward_wls(1);
	//1
	right_turn_wls();
	forward_wls(1);
	//1.1
	lfr();
	//2
	left_turn_wls();
	forward_wls(1);
	//3
	forward_wls(1);
	_delay_ms(100);
	//4
	left();
	forward_wls(1);
	//5
	left();
	forward_wls(1);
	//6
	right_turn_wls();
	forward_wls(1);
	//7
	right_turn_wls();
	forward_wls(1);
	//8
	forward_wls(1);
	_delay_ms(100);
	//9
	left();
	while (ADC_Conversion(1) <= 210);
	while ((ADC_Conversion(2) <= 210));
	_delay_ms(100);
	forward_wls(1);
	//10
	right_turn_wls();
	forward_wls(1);
	//11
	left_turn_wls();
	forward_wls(1);
	stop();
	//forward();
	_delay_ms(2000);
}


/*
*
* Function Name: Task_1_2
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.2 lo
gic
* Example Call: Task_1_2();
*/
void Task_1_2(void)
{
	unsigned int red_pulse_count, green_pulse_count, blue_pulse_count, filter_clear_pulse_count;
	while (1)
	{
		filter_red();
		red_pulse_count = color_sensor_pulse_count;
		filter_green();
		green_pulse_count = color_sensor_pulse_count;
		filter_blue();
		blue_pulse_count = color_sensor_pulse_count;
		filter_clear();
		filter_clear_pulse_count = color_sensor_pulse_count;
		printf("\n%d    %d     %d    %d", red_pulse_count, green_pulse_count, blue_pulse_count, filter_clear_pulse_count);
		_delay_ms(1000);
	}

}
