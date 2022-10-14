
#include "Traffic_Light_app.h"

volatile uint8_t ss=10 , ss_p=10 , PP_SS = 0 , request = 0 , ext_rq =0;

void  main(void)
{
    //set leds pins as output
    SET_BIT(Traffic_signs_DDR,Car_G);
    SET_BIT(Traffic_signs_DDR,Car_R);
    SET_BIT(Traffic_signs_DDR,Car_Y);
    SET_BIT(Traffic_signs_DDR,PP_G);
    SET_BIT(Traffic_signs_DDR,PP_Y);
    SET_BIT(Traffic_signs_DDR,PP_R);
    
    //timer0 ISR callback for decoupling timer0 driver
    Timer0_CTC_isr_p = timer0_isr;
    
    //intialize interrupt0 to trigger on falling edge 
    INT1_init(0);   
    //intilization of sevensegments data pins and enable pins 
    SS_init();
    
    ENABLE_GLOBAL_INTTERUPT;
    ENABLE_INT0;

    //intialize timer0 in CTC mode , set timer0 isr to 8 ms
    Timer0_CTC_init(124,5); 
   
    traffic_state current_state = car_go;
    traffic_state previous_state = car_set;
    //dispach event
     Leds_state(current_state);

    while (1) 
    {
        if (request == 1 && ext_rq == 1)
        {
            //transition action 
            ss = 5;
            ss_p=ss;
            ext_rq =0;
            PP_SS = 1;
            //next state 
            current_state = car_set_pp_set;

            //dispach event
            Leds_state(current_state);

        }
        
        if(ss < ss_p)
        { 
            ss_p = ss;

            if(request == 0 && ss_p == 5)
            {
                //transition action 
               
                //next state 
                current_state = car_set;
            
            }
            else if(request == 0 && ss_p == 0)
            {
                //transition action 
                ss = 10;
                ss_p = ss;
                PP_SS = 0; //turn off pp seven seg if on

                //next state 
                if(previous_state == car_stop || previous_state == car_Stop_pp_go)
                {
                    current_state  = car_go;
                    previous_state = car_go;
                }
                else 
                {
                    current_state  = car_stop;
                    previous_state = car_stop;
                }

            }
            else if(request == 1 && ss_p == 0 )
            {
                //transition action 
                ss = 10;
                ss_p = ss;
               
                //next state 
                current_state = car_Stop_pp_go;
                
            }
            else if(request == 1 && ss_p == 5 )
            {
                //transition action 
                request = 0;
                PP_SS = 1;
                
                //next state 
                current_state = car_set_pp_set;
                previous_state = car_Stop_pp_go;
            }
            
            //dispach event
            Leds_state(current_state);
        }
    } 
}

void timer0_isr(void)
{
    static uint8_t count = 0;
    static uint8_t ss_select=0;

    if (count == 125)
    {
        if(ss>0)ss--;
        
        count=0;
    }
    else
    {
        count++;
    }
    
    if(ss_select > 3){ss_select =0;}

    if(PP_SS == 1)
    {
       switch (ss_select){
            case 0 : {SS_Single_DISPLAY(EN_C_1 , ss/10);ss_select++;}break;
            case 1 : {SS_Single_DISPLAY(EN_C_2 , ss%10);ss_select++;}break;
            case 2 : {SS_Single_DISPLAY(EN_PP_1, ss/10);ss_select++;}break;
            case 3 : {SS_Single_DISPLAY(EN_PP_2, ss%10);ss_select=0;}break;
        }
    }
    else
    {
       switch (ss_select){
            case 0 : {SS_Single_DISPLAY(EN_C_1 , ss/10);ss_select++;}break;
            case 1 : {SS_Single_DISPLAY(EN_C_2 , ss%10);ss_select=0;}break;
        }
    }

}


ISR(INT0_vect)
{
	request = 1;
    ext_rq =1;
}


void Leds_state(traffic_state state)
{   
    switch (state)
    {
        case car_go :
        {
            Traffic_signs_PORT = 0x00;
            SET_BIT(Traffic_signs_PORT,Car_G);

        } break;
        case car_stop :
        {
            Traffic_signs_PORT = 0x00;
            SET_BIT(Traffic_signs_PORT,Car_R);

        }break;
        case car_set : 
        {
            Traffic_signs_PORT = 0x00;
            SET_BIT(Traffic_signs_PORT,Car_Y);
  
        }break;
        case car_set_pp_set : 
        {
            Traffic_signs_PORT = 0x00;
            SET_BIT(Traffic_signs_PORT,Car_Y);
            SET_BIT(Traffic_signs_PORT,PP_Y);
            
           
        }break;
        case car_Stop_pp_go : 
        {
            Traffic_signs_PORT = 0x00;
            SET_BIT(Traffic_signs_PORT,Car_R);
            SET_BIT(Traffic_signs_PORT,PP_G);
           
        }break;
        default:
            break;
    }
}