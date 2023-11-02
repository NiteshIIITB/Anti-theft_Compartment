//#include<stdio.h>

int main()
{

int light_sensor,buzzer,mask;
int touchsensor,buzzer_reg;





while (1)
{



			
//  asm code to read sensor value

	asm volatile(
		"andi %0, x30, 0x01\n\t"
		: "=r" (light_sensor)
		:
		: 
		);



//if condition logic
if (light_sensor)
	{
	mask=0xFFFFFFFD;
	
	
	
	buzzer_reg=1;
	
	asm volatile(
               
            "ori x30, x30,2"               
            :
            :
            :"x30"
            );
            
            asm volatile(
	    	"addi %0, x30, 0\n\t"
	    	:"=r"(buzzer)
	    	:
	    	:"x30"
	    	);
    	
    	
	

	}
else
	{
	
	mask=0xFFFFFFFD;
	
	buzzer_reg=0;
	
	
	asm volatile( 
            "and x30,x30, %0\n\t"     
            "ori x30, x30,0"            
            :
            :"r"(mask)
            :"x30"
        );
        asm volatile(
	    	"addi %0, x30, 0\n\t"
	    	:"=r"(buzzer)
	    	:
	    	:"x30"
	    	);
	 

	}
}	

return 0;
}

