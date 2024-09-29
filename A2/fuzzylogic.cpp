#include <algorithm>
#include "fuzzylogic.h"

/////////////////////////////////////////////////////////////////

//Initialise Fuzzy Rules

void initFuzzyRules(fuzzy_system_rec *fl) {
	
   const int
       no_of_x_rules = 25,
       no_of_theta_rules = 25;
       //no_of_rules = no_of_theta_rules + no_of_x_rules;
   
   int i;
	
 // Theta rules (pendulum angle)
    for (i = 0; i < no_of_theta_rules; i++) {
        fl->rules[i].inp_index[0] = in_theta; //Pendulum angle
        fl->rules[i].inp_index[1] = in_theta_dot; //Angular Velocity
    }
      
    // X rules (cart position)
    for (i = 0; i < no_of_x_rules; i++) {
        fl->rules[i + no_of_theta_rules].inp_index[0] = in_x; //Position
        fl->rules[i + no_of_theta_rules].inp_index[1] = in_x_dot; //Velocity
    }

    //Define output fuzzy sets based on Yamakawa's approach
    //The vectors define the output for each rule

        std::vector<int> famm_theta = {
        out_nvl, out_nvl, out_ns, out_ns, out_ze, out_nl,out_nl, out_ns, out_ze, out_ps, 
        out_ze, out_ns, out_nl,out_ps, out_pl, out_pl, out_ns, out_ze, out_ps, out_pvl,
        out_pvl, out_ze, out_pvl, out_pl, out_pl
    };   

  std::vector<int> famm_x = {
        out_pvl, out_pvl, out_ps, out_ps, out_ze, out_pl, out_pl, out_ps, out_ze, out_ns,
        out_ze, out_ps, out_pl, out_ns, out_nl, out_nl, out_ps, out_ze, out_ns, out_nvl, 
        out_nvl, out_ze, out_nvl, out_nl, out_nl

    };

    

    // Assign output fuzzy sets
    for (i = 0; i < no_of_theta_rules; i++) {
        fl->rules[i].out_fuzzy_set = famm_theta[i];
    }
    for (i = 0; i < no_of_x_rules; i++) {
        fl->rules[i + no_of_theta_rules].out_fuzzy_set = famm_x[i];
    }

    

   
    // Theta rules //Started with 26 but expanded to 50 to improve the system
    //Rules covering NL
    fl->rules[0].inp_fuzzy_set[0] = in_nl; fl->rules[0].inp_fuzzy_set[1] = in_nl; //If theta is NL and theta_dot is NL, then output is NVL
    fl->rules[1].inp_fuzzy_set[0] = in_nl; fl->rules[1].inp_fuzzy_set[1] = in_ns; //If theta is NL and theta_dot is NS, then output is NL
    fl->rules[2].inp_fuzzy_set[0] = in_nl; fl->rules[2].inp_fuzzy_set[1] = in_ze;//If theta is NL and theta_dot is ZE, then output is NS
    fl->rules[3].inp_fuzzy_set[0] = in_nl; fl->rules[3].inp_fuzzy_set[1] = in_ps; //If theta is NL and theta_dot is PS, then output is NS
    fl->rules[4].inp_fuzzy_set[0] = in_nl; fl->rules[4].inp_fuzzy_set[1] = in_pl; //If theta is NL and theta_dot is PL, then output is ZE
    
    //Rules covering ns
    fl->rules[5].inp_fuzzy_set[0] = in_ns; fl->rules[5].inp_fuzzy_set[1] = in_ns; //If theta is NS and theta_dot is NS, then output is NL
    fl->rules[6].inp_fuzzy_set[0] = in_ns; fl->rules[6].inp_fuzzy_set[1] = in_nl; //If theta is NS and theta_dot is NL, then output is NL
    fl->rules[7].inp_fuzzy_set[0] = in_ns; fl->rules[7].inp_fuzzy_set[1] = in_ze; //If theta is NS and theta_dot is NS, then output is NS
    fl->rules[8].inp_fuzzy_set[0] = in_ns; fl->rules[8].inp_fuzzy_set[1] = in_ps; //If theta is NS and theta_dot is ZE, then output is ZE
    fl->rules[9].inp_fuzzy_set[0] = in_ns; fl->rules[9].inp_fuzzy_set[1] = in_pl; //If theta is NS and theta_dot is ZE, then output is PS

    //Rules covering ZE
    fl->rules[10].inp_fuzzy_set[0] = in_ze; fl->rules[10].inp_fuzzy_set[1] = in_ze; //If theta is ZE and theta_dot is ZE, then output is ZE
    fl->rules[11].inp_fuzzy_set[0] = in_ze; fl->rules[11].inp_fuzzy_set[1] = in_nl; //If theta is ZE and theta_dot is NS, then output is NS
    fl->rules[12].inp_fuzzy_set[0] = in_ze; fl->rules[12].inp_fuzzy_set[1] = in_ns; //If theta is ZE and theta_dot is NL, then output is NL
    fl->rules[13].inp_fuzzy_set[0] = in_ze; fl->rules[13].inp_fuzzy_set[1] = in_ps; //If theta is ZE and theta_dot is PS, then output is PS
    fl->rules[14].inp_fuzzy_set[0] = in_ze; fl->rules[14].inp_fuzzy_set[1] = in_pl; //If theta is ZE and theta_dot is PL, then output is PL

    //Rules covering PS
    fl->rules[15].inp_fuzzy_set[0] = in_ps; fl->rules[15].inp_fuzzy_set[1] = in_ps; //If theta is PS and theta_dot is PS, then output is PL
    fl->rules[16].inp_fuzzy_set[0] = in_ps; fl->rules[16].inp_fuzzy_set[1] = in_nl; //If theta is PS and theta_dot is NL, then output is NS
    fl->rules[17].inp_fuzzy_set[0] = in_ps; fl->rules[17].inp_fuzzy_set[1] = in_ns; //If theta is PS and theta_dot is NS, then output is ZE
    fl->rules[18].inp_fuzzy_set[0] = in_ps; fl->rules[18].inp_fuzzy_set[1] = in_ze; //If theta is PS and theta_dot is ZE, then output is PS
    fl->rules[19].inp_fuzzy_set[0] = in_ps; fl->rules[19].inp_fuzzy_set[1] = in_pl; //If theta is PS and theta_dot is PL, then output is PVL

    //Rules covering PL
    fl->rules[20].inp_fuzzy_set[0] = in_pl; fl->rules[20].inp_fuzzy_set[1] = in_pl; //If theta is PL and theta_dot is PL, then output is PVL
    fl->rules[21].inp_fuzzy_set[0] = in_pl; fl->rules[21].inp_fuzzy_set[1] = in_nl; //If theta is PL and theta_dot is NL, then output is ZE
    fl->rules[22].inp_fuzzy_set[0] = in_pl; fl->rules[22].inp_fuzzy_set[1] = in_ns; //If theta is PL and theta_dot is NS, then output is PVL
    fl->rules[23].inp_fuzzy_set[0] = in_pl; fl->rules[23].inp_fuzzy_set[1] = in_ze; //If theta is PL and theta_dot is NL, then output is PL
    fl->rules[24].inp_fuzzy_set[0] = in_pl; fl->rules[24].inp_fuzzy_set[1] = in_ps; //If theta is PL and theta_dot is ZE, then output is PL

    // X rules
      //Rules covering NL
    fl->rules[25].inp_fuzzy_set[0] = in_nl; fl->rules[25].inp_fuzzy_set[1] = in_nl; //If theta is NL and theta_dot is NL, then output is PVL
    fl->rules[26].inp_fuzzy_set[0] = in_nl; fl->rules[26].inp_fuzzy_set[1] = in_ns; //If theta is NL and theta_dot is NS, then output is PL
    fl->rules[27].inp_fuzzy_set[0] = in_nl; fl->rules[27].inp_fuzzy_set[1] = in_ze;//If theta is NL and theta_dot is ZE, then output is PS
    fl->rules[28].inp_fuzzy_set[0] = in_nl; fl->rules[28].inp_fuzzy_set[1] = in_ps; //If theta is NL and theta_dot is PS, then output is PS
    fl->rules[29].inp_fuzzy_set[0] = in_nl; fl->rules[29].inp_fuzzy_set[1] = in_pl; //If theta is NL and theta_dot is PL, then output is ZE
    
    //Rules covering ns
    fl->rules[30].inp_fuzzy_set[0] = in_ns; fl->rules[30].inp_fuzzy_set[1] = in_ns; //If theta is NS and theta_dot is NS, then output is PL
    fl->rules[31].inp_fuzzy_set[0] = in_ns; fl->rules[31].inp_fuzzy_set[1] = in_nl; //If theta is NS and theta_dot is NL, then output is PL
    fl->rules[32].inp_fuzzy_set[0] = in_ns; fl->rules[32].inp_fuzzy_set[1] = in_ze; //If theta is NS and theta_dot is NS, then output is PS
    fl->rules[33].inp_fuzzy_set[0] = in_ns; fl->rules[33].inp_fuzzy_set[1] = in_ps; //If theta is NS and theta_dot is ZE, then output is ZE
    fl->rules[34].inp_fuzzy_set[0] = in_ns; fl->rules[34].inp_fuzzy_set[1] = in_pl; //If theta is NS and theta_dot is ZE, then output is NS

    //Rules covering ZE
    fl->rules[35].inp_fuzzy_set[0] = in_ze; fl->rules[35].inp_fuzzy_set[1] = in_ze; //If theta is ZE and theta_dot is ZE, then output is ZE
    fl->rules[36].inp_fuzzy_set[0] = in_ze; fl->rules[36].inp_fuzzy_set[1] = in_nl; //If theta is ZE and theta_dot is NS, then output is PS
    fl->rules[37].inp_fuzzy_set[0] = in_ze; fl->rules[37].inp_fuzzy_set[1] = in_ns; //If theta is ZE and theta_dot is NL, then output is PL
    fl->rules[38].inp_fuzzy_set[0] = in_ze; fl->rules[38].inp_fuzzy_set[1] = in_ps; //If theta is ZE and theta_dot is PS, then output is NS
    fl->rules[39].inp_fuzzy_set[0] = in_ze; fl->rules[39].inp_fuzzy_set[1] = in_pl; //If theta is ZE and theta_dot is PL, then output is NL

    //Rules covering PS
    fl->rules[40].inp_fuzzy_set[0] = in_ps; fl->rules[40].inp_fuzzy_set[1] = in_ps; //If theta is PS and theta_dot is PS, then output is NL
    fl->rules[41].inp_fuzzy_set[0] = in_ps; fl->rules[41].inp_fuzzy_set[1] = in_nl; //If theta is PS and theta_dot is NL, then output is PS
    fl->rules[42].inp_fuzzy_set[0] = in_ps; fl->rules[42].inp_fuzzy_set[1] = in_ns; //If theta is PS and theta_dot is NS, then output is ZE
    fl->rules[43].inp_fuzzy_set[0] = in_ps; fl->rules[43].inp_fuzzy_set[1] = in_ze; //If theta is PS and theta_dot is ZE, then output is NS
    fl->rules[44].inp_fuzzy_set[0] = in_ps; fl->rules[44].inp_fuzzy_set[1] = in_pl; //If theta is PS and theta_dot is PL, then output is NVL

    //Rules covering PL
    fl->rules[45].inp_fuzzy_set[0] = in_pl; fl->rules[45].inp_fuzzy_set[1] = in_pl; //If theta is PL and theta_dot is PL, then output is NVL
    fl->rules[46].inp_fuzzy_set[0] = in_pl; fl->rules[46].inp_fuzzy_set[1] = in_nl; //If theta is PL and theta_dot is NL, then output is ZE
    fl->rules[47].inp_fuzzy_set[0] = in_pl; fl->rules[47].inp_fuzzy_set[1] = in_ns; //If theta is PL and theta_dot is NS, then output is NVL
    fl->rules[48].inp_fuzzy_set[0] = in_pl; fl->rules[48].inp_fuzzy_set[1] = in_ze; //If theta is PL and theta_dot is NL, then output is NL
    fl->rules[49].inp_fuzzy_set[0] = in_pl; fl->rules[49].inp_fuzzy_set[1] = in_ps; //If theta is PL and theta_dot is ZE, then output is NL

      return;
}


void initMembershipFunctions(fuzzy_system_rec *fl) 
{
	
   /* The X membership functions */
   //Defined for the combined input x that represents the angle and angular velocity.
   //Each membership function is defined as a trapezoid with four points (a,b,c,d, and type)
   
    // For each input variable (x, x_dot, theta, theta_dot)
   for (int var = 0; var < 4; var++) {
        fl->inp_mem_fns[var][in_nl] = init_trapz(-2, -1, 0, 0, left_trapezoid);
        fl->inp_mem_fns[var][in_ns] = init_trapz(-1.5, -1, -.6, -0.1, regular_trapezoid);
        fl->inp_mem_fns[var][in_ze] = init_trapz(-0.6, -.1, .1, 0.6, regular_trapezoid);
        fl->inp_mem_fns[var][in_ps] = init_trapz(.1, .6, 1, 1.5, regular_trapezoid);
        fl->inp_mem_fns[var][in_pl] = init_trapz(0, 0, 1, 2, right_trapezoid);
    }
   

	
   return;
}

void initFuzzySystem (fuzzy_system_rec *fl) {

   //Note: The settings of these parameters will depend upon your fuzzy system design
   fl->no_of_inputs = 2;  /* Combined input X */
   fl->no_of_rules = 50; //Reduced rules for simplicity and following Yamakawas approach
   fl->no_of_inp_regions = 5; //Number of input fuzzy sets
   fl->no_of_outputs = 9; //Number of output sets
	
   coefficient_A=.2; //Angle coefficient
   coefficient_B=.4; //Angular Velocit coefficient
   coefficient_C=.1;
   coefficient_D=.3;
	
	//Sample only
	// fl->output_values [out_nvl]=-95.0;
	// fl->output_values [out_nl] = -85.0;
   
   //Define the crisp output values for each set

   fl->output_values [out_nvl] = -1200; //Negative Very Large
   fl->output_values [out_nl] = -500; //Negative Large
   fl->output_values [out_nm] = -125; //Negative Medium
   fl->output_values [out_ns] = -25; //Negative Small
   fl->output_values [out_ze] = 0.0; //Zero
   fl->output_values [out_ps] = 25; //Positive Small
   fl->output_values [out_pm] = 125; //Positive Medium
   fl->output_values [out_pl] = 500; //Positive Large
   fl->output_values [out_pvl] = 1200; //Positive Very Large

//Memory alloc for the rules
   fl->rules = (rule *) malloc ((size_t)(fl->no_of_rules*sizeof(rule)));

   //init rules and membership functions
   initFuzzyRules(fl);
   initMembershipFunctions(fl);
   return;
}

//////////////////////////////////////////////////////////////////////////////

trapezoid init_trapz (float x1,float x2,float x3,float x4, trapz_type typ) {
   
   trapezoid trz;
   trz.a = x1;
   trz.b = x2;
   trz.c = x3;
   trz.d = x4;
   trz.tp = typ;
   switch (trz.tp) {
      
      case regular_trapezoid:
             trz.l_slope = 1.0/(trz.b - trz.a);
             trz.r_slope = 1.0/(trz.c - trz.d);
             break;
    
      case left_trapezoid: //2024, corrected version - to match variables used in the lectures - (c, d) instead of (a,b)
             trz.r_slope = 1.0/(trz.c - trz.d);
             trz.l_slope = 0.0;
             break;
    
      case right_trapezoid:
             trz.l_slope = 1.0/(trz.b - trz.a);
             trz.r_slope = 0.0;
             break;
   }  /* end switch  */
   
   return trz;
}  /* end function */

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
float trapz (float x, trapezoid trz) {
   switch (trz.tp) {
       
      case left_trapezoid: //2024, corrected version - to match variables used in the lectures - (c, d) instead of (a,b)
             if (x <= trz.c)
                return 1.0;
             if (x >= trz.d)
                return 0.0;
             /* c < x < d */
             return trz.r_slope * (x - trz.d);
     
     
      case right_trapezoid:
             if (x <= trz.a)
                return 0.0;
             if (x >= trz.b)
                return 1.0;
             /* a < x < b */
             return trz.l_slope * (x - trz.a);
     
      case regular_trapezoid:
             if ((x <= trz.a) || (x >= trz.d))
                return 0.0;
             if ((x >= trz.b) && (x <= trz.c))
                return 1.0;
             if ((x >= trz.a) && (x <= trz.b))
                return trz.l_slope * (x - trz.a);
             if ((x >= trz.c) && (x <= trz.d))
                return  trz.r_slope * (x - trz.d);
                
     }  /* End switch  */
     
   return 0.0;  /* should not get to this point */
}  /* End function */

//////////////////////////////////////////////////////////////////////////////
float min_of(float values[],int no_of_inps) {
   int i;
   float val;
   val = values [0];
   for (i = 1;i < no_of_inps;i++) {
       if (values[i] < val)
	  val = values [i];
   }
   return val;
}



//////////////////////////////////////////////////////////////////////////////
float fuzzy_system (float inputs[],fuzzy_system_rec fz) {
   int i,j;
   short variable_index,fuzzy_set;
   float sum1 = 0.0,sum2 = 0.0,weight;
   float m_values[MAX_NO_OF_INPUTS] = {0.0};
	
   
   for (i = 0;i < fz.no_of_rules;i++) {
      for (j = 0;j < fz.no_of_inputs;j++) {
	   variable_index = fz.rules[i].inp_index[j];
	   fuzzy_set = fz.rules[i].inp_fuzzy_set[j];
	   m_values[j] = trapz(inputs[variable_index],
	       fz.inp_mem_fns[variable_index][fuzzy_set]);

         //  // Debug print
         //    cout << "Rule " << i << ", Input " << j << ": " << m_values[j] << endl;

	   } /* end j  */
      
      
       weight = min_of (m_values,fz.no_of_inputs);
				
       sum1 += weight * fz.output_values[fz.rules[i].out_fuzzy_set];
       sum2 += weight;

      //   // Debug print
      //   cout << "Rule " << i << " weight: " << weight << endl;
   } /* end i  */
 
	
	if (fabs(sum2) < TOO_SMALL) {
      cout << "\r\nFLPRCS Error: Sum2 in fuzzy_system is 0.  Press key: " << endl;
      //getch();
      exit(1);
      return 0.0;
   }
   
   return (sum1/sum2);
}  /* end fuzzy_system  */

//////////////////////////////////////////////////////////////////////////////
void free_fuzzy_rules (fuzzy_system_rec *fz) {
   if (fz->allocated){
	   free (fz->rules);
	}
	
   fz->allocated = false;
   return;
}

