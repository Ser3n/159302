#include <algorithm>
#include "fuzzylogic.h"

/////////////////////////////////////////////////////////////////

//Initialise Fuzzy Rules

void initFuzzyRules(fuzzy_system_rec *fl) {
	
   const int
      // no_of_x_rules = 25,
      // no_of_theta_rules = 25;
      no_of_rules = 13;
   
   int i;
	
//---------------------------------------------------------------------------- 	
//Combined input X(Theta and Theta_dot)
//   
   for (i = 0;i < no_of_rules;i++) {
       // fl->rules[i].inp_index[0] = in_theta;
      //  fl->rules[i].inp_index[1] = in_theta_dot;
      fl->rules[i].inp_index[0] = in_x;
   }
      
   /* Regions for theta and theta_dot: */
   //sample only
   // fl->rules[0].inp_fuzzy_set[0] = in_nl;
   // fl->rules[0].inp_fuzzy_set[1] = in_nl;
   
	
	
//----------------------------------------------------------------------------   
//X vs. X_DOT
//
   // for (i = 0;i < no_of_x_rules;i++) {
   // 	  fl->rules[i + no_of_theta_rules].inp_index[0] = in_x;
   // 	  fl->rules[i + no_of_theta_rules].inp_index[1] = in_x_dot;
	// }
	  
	/* Regions for x and x_dot: */
   //sample only
   // fl->rules[25+0].inp_fuzzy_set[0] = in_nl;
   // fl->rules[25+0].inp_fuzzy_set[1] = in_nl;
   
   //and so on, and so forth...

   // fl->rules[25+24].out_fuzzy_set = out_nl;

   //Define rules based on Yamakawa
   //Each rule maps an input fuzzy set to an output fuzzy set

    fl->rules[0].inp_fuzzy_set[0] = in_nvl; fl->rules[0].out_fuzzy_set = out_pvl;//if X is Negatively Very Large, then force is Positively Very Large
    fl->rules[1].inp_fuzzy_set[0] = in_nl;  fl->rules[1].out_fuzzy_set = out_pl; //If X is Negatively large the the force is positively large
    fl->rules[2].inp_fuzzy_set[0] = in_nm;  fl->rules[2].out_fuzzy_set = out_pm;//if X is Negatively medium, then force is positively medium
    fl->rules[3].inp_fuzzy_set[0] = in_ns;  fl->rules[3].out_fuzzy_set = out_ps;//If X is negatively small then the force is positively small
    fl->rules[4].inp_fuzzy_set[0] = in_ze;  fl->rules[4].out_fuzzy_set = out_ze;//If x is 0 then force is 0
    fl->rules[5].inp_fuzzy_set[0] = in_ps;  fl->rules[5].out_fuzzy_set = out_ns;//if x is positively small then force is negatively small
    fl->rules[6].inp_fuzzy_set[0] = in_pm;  fl->rules[6].out_fuzzy_set = out_nm;// if x is positively medium then force is negatively medium
    fl->rules[7].inp_fuzzy_set[0] = in_pl;  fl->rules[7].out_fuzzy_set = out_nl;//if X is positively large then force is negatively large
    fl->rules[8].inp_fuzzy_set[0] = in_pvl; fl->rules[8].out_fuzzy_set = out_nvl;//if X is positively very large than the force is negatively very large
    fl->rules[9].inp_fuzzy_set[0] = in_nvm; fl->rules[9].out_fuzzy_set = out_pvm;//if X is negatively very medium then force is positively very medium
    fl->rules[10].inp_fuzzy_set[0] = in_pvm; fl->rules[10].out_fuzzy_set = out_nvm;//if X is positively very medium then force is negatively very medium
    fl->rules[11].inp_fuzzy_set[0] = in_nvs; fl->rules[11].out_fuzzy_set = out_pvs;// if X is negtively very small then force is positively very small
    fl->rules[12].inp_fuzzy_set[0] = in_pvs; fl->rules[12].out_fuzzy_set = out_nvs;// if X is positively ver small then force is negatively very small

      return;
}


void initMembershipFunctions(fuzzy_system_rec *fl) {
	
   /* The X membership functions */
   //Defined for the combined input x that represents the angle and angular velocity.
   //Each membership function is defined as a trapezoid with four points (a,b,c,d, and type)

    fl->inp_mem_fns[in_x][in_nvl] = init_trapz(-4, -4, -3, -2, left_trapezoid);    // Negative Very Large
    fl->inp_mem_fns[in_x][in_nl] = init_trapz(-3, -2, -2, -1, regular_trapezoid);  // Negative Large
    fl->inp_mem_fns[in_x][in_nm] = init_trapz(-2, -1, -1, -0.5, regular_trapezoid); // Negative Medium
    fl->inp_mem_fns[in_x][in_ns] = init_trapz(-1, -0.5, -0.5, 0, regular_trapezoid); // Negative Small
    fl->inp_mem_fns[in_x][in_ze] = init_trapz(-0.5, 0, 0, 0.5, regular_trapezoid);  // Zero
    fl->inp_mem_fns[in_x][in_ps] = init_trapz(0, 0.5, 0.5, 1, regular_trapezoid);   // Positive Small
    fl->inp_mem_fns[in_x][in_pm] = init_trapz(0.5, 1, 1, 2, regular_trapezoid);     // Positive Medium
    fl->inp_mem_fns[in_x][in_pl] = init_trapz(1, 2, 2, 3, regular_trapezoid);       // Positive Large
    fl->inp_mem_fns[in_x][in_pvl] = init_trapz(2, 3, 4, 4, right_trapezoid);        // Positive Very Large


   //Sample routines only, to give you an idea of what to do here
  	// fl->inp_mem_fns[in_x][in_neg] = init_trapz (0,0,-1.5,-0.5,left_trapezoid);
   //~ fl->inp_mem_fns[in_x][in_ze] = init_trapz (-1.5,-0.5,0.5,1.5,regular_trapezoid);
   //~ fl->inp_mem_fns[in_x][in_pos] = init_trapz (0.5,1.5,0,0,right_trapezoid);
	
   /* The X dot membership functions */
   //enter the appropriate membership function initialisations here 

   /* The theta membership functions */
   //enter the appropriate membership function initialisations here
  	
   /* The theta dot membership functions */
   //enter the appropriate membership function initialisations here
  	

	
	
   return;
}

void initFuzzySystem (fuzzy_system_rec *fl) {

   //Note: The settings of these parameters will depend upon your fuzzy system design
   fl->no_of_inputs = 1;  /* Combined input X */
   fl->no_of_rules = 13; //Reduced rules for simplicity and following Yamakawas approach
   fl->no_of_inp_regions = 9; //Number of input fuzzy sets
   fl->no_of_outputs = 9; //Number of output sets
	
   coefficient_A=1.0; //Angle coefficient
   coefficient_B=1.0; //Angular Velocit coefficient

   //removed for simplicity
   // coefficient_C=1.0;
   // coefficient_D=1.0;
	
	//Sample only
	// fl->output_values [out_nvl]=-95.0;
	// fl->output_values [out_nl] = -85.0;
   
   //Define the crisp output values for each set

   fl->output_values [out_nvl] = -100.0; //Negative Very Large
   fl->output_values [out_nl] = -75.0; //Negative Large
   fl->output_values [out_nm] = -50.0; //Negative Medium
   fl->output_values [out_ns] = -25.0; //Negative Small
   fl->output_values [out_ze] = 0.0; //Zero
   fl->output_values [out_ps] = 25.0; //Positive Small
   fl->output_values [out_pm] = 50.0; //Positive Medium
   fl->output_values [out_pl] = 75.0; //Positive Large
   fl->output_values [out_pvl] = 100.0; //Positive Very Large

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
   float m_values[MAX_NO_OF_INPUTS];
	
   
   for (i = 0;i < fz.no_of_rules;i++) {
      for (j = 0;j < fz.no_of_inputs;j++) {
	   variable_index = fz.rules[i].inp_index[j];
	   fuzzy_set = fz.rules[i].inp_fuzzy_set[j];
	   m_values[j] = trapz(inputs[variable_index],
	       fz.inp_mem_fns[variable_index][fuzzy_set]);
	   } /* end j  */
      
       weight = min_of (m_values,fz.no_of_inputs);
				
       sum1 += weight * fz.output_values[fz.rules[i].out_fuzzy_set];
       sum2 += weight;
   } /* end i  */
 
	
	if (fabs(sum2) < TOO_SMALL) {
      cout << "\r\nFLPRCS Error: Sum2 in fuzzy_system is 0.  Press key: " << endl;
      //~ getch();
      //~ exit(1);
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

