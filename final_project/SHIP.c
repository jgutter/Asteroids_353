//NAME: SADEQ HASHEMI NEJAD
#include "ship.h"
#include <stdbool.h>

const uint8_t shipWidthPages[] = {3, 3, 3, 3, 3, 3, 3, 3, 3 };
const uint8_t shipHeightPixels[] = {20, 22, 23, 23, 23, 21, 20, 21, 21};

/* 
**  ship bitmaps for all angles of rotation
*/

/*  */

const uint8_t shipBitmaps[] =
{
	0x40, 0x00, 0x10, //  #                 #
	0x40, 0x00, 0x10, //  #                 #
	0x40, 0x00, 0x10, //  #                 #
	0x55, 0x55, 0x50, //  # # # # # # # # # #
	0x7F, 0xFF, 0xF0, //  ###################
	0x77, 0x77, 0x70, //  ### ### ### ### ###
	0x3F, 0xFF, 0xE0, //   ################# 
	0x18, 0x00, 0xC0, //    ##           ##  
	0x18, 0x00, 0xC0, //    ##           ##  
	0x1C, 0x01, 0xC0, //    ###         ###  
	0x0E, 0x03, 0x80, //     ###       ###   
	0x06, 0x03, 0x00, //      ##       ##    
	0x06, 0x02, 0x00, //      ##       #     
	0x07, 0x07, 0x00, //      ###     ###    
	0x03, 0x8E, 0x00, //       ###   ###     
	0x01, 0x8C, 0x00, //        ##   ##      
	0x00, 0x88, 0x00, //         #   #       
	0x01, 0xDC, 0x00, //        ### ###      
	0x00, 0xF8, 0x00, //         #####       
	0x00, 0x70, 0x00, //          ###  

	//3x22
	0x00, 0x00, 0x10, //                    # 
	0x00, 0x00, 0x30, //                   ## 
	0x00, 0x00, 0x10, //                    # 
	0x80, 0x00, 0x18, // #                  ##
	0xC0, 0x05, 0xF0, // ##           # ##### 
	0x80, 0xBF, 0xF0, // #       # ########## 
	0xD7, 0xF5, 0xF0, // ## # ####### # ##### 
	0xFA, 0x2F, 0xE0, // ##### #   # #######  
	0x77, 0xF4, 0x70, //  ### ####### #   ### 
	0x3E, 0x00, 0x60, //   #####          ##  
	0x1C, 0x00, 0xC0, //    ###          ##   
	0x0C, 0x00, 0xC0, //     ##          ##   
	0x0E, 0x01, 0xC0, //     ###        ###   
	0x0F, 0x00, 0x80, //     ####        #    
	0x07, 0x01, 0xC0, //      ###       ###   
	0x03, 0x81, 0x80, //       ###      ##    
	0x01, 0xC3, 0x80, //        ###    ###    
	0x00, 0xE3, 0x80, //         ###   ###    
	0x00, 0xF7, 0x00, //         #### ###     
	0x00, 0x33, 0x00, //           ##  ##     
	0x00, 0x7C, 0x00, //          #####       
	0x00, 0x08, 0x00, //             #        
	
	//3x23
	0x00, 0x00, 0x30, //                   ## 
	0x00, 0x00, 0x10, //                    # 
	0x00, 0x00, 0x18, //                    ##
	0x00, 0x00, 0x18, //                    ##
	0x00, 0x00, 0x78, //                  ####
	0x00, 0x01, 0xF8, //                ######
	0xC0, 0x0F, 0xB8, // ##          ##### ###
	0x40, 0x7D, 0xF0, //  #       ##### ##### 
	0x63, 0xEF, 0xB8, //  ##   ##### ##### ###
	0x7F, 0x7C, 0x30, //  ####### #####    ## 
	0x3F, 0xE0, 0x38, //   #########       ###
	0x1F, 0x00, 0x30, //    #####          ## 
	0x0E, 0x00, 0x30, //     ###           ## 
	0x07, 0x00, 0x30, //      ###          ## 
	0x03, 0xA0, 0x70, //       ### #      ### 
	0x01, 0xC0, 0x70, //        ###       ### 
	0x00, 0xF0, 0x60, //         ####     ##  
	0x00, 0x70, 0x70, //          ###     ### 
	0x00, 0x3C, 0xE0, //           ####  ###  
	0x00, 0x1E, 0x70, //            ####  ### 
	0x00, 0x0E, 0xE0, //             ### ###  
	0x00, 0x07, 0xC0, //              #####   
	0x00, 0x00, 0x80, //                 #    


//3x23
0x00, 0x00, 0xC0, //                 ##   
	0x00, 0x00, 0xC0, //                 ##   
	0x00, 0x00, 0x60, //                  ##  
	0x00, 0x00, 0x20, //                   #  
	0x00, 0x00, 0x70, //                  ### 
	0x00, 0x03, 0xE0, //               #####  
	0x00, 0x07, 0x70, //              ### ### 
	0x00, 0x0C, 0xE0, //             ##  ###  
	0x00, 0x7F, 0xF0, //          ########### 
	0x80, 0xEE, 0x20, // #       ### ###   #  
	0xC3, 0xFC, 0x70, // ##    ########   ### 
	0xCE, 0xE0, 0x20, // ##  ### ###       #  
	0x7D, 0xC0, 0x70, //  ##### ###       ### 
	0x3E, 0x00, 0x30, //   #####           ## 
	0x1F, 0x00, 0x70, //    #####         ### 
	0x0B, 0x80, 0x30, //     # ###         ## 
	0x07, 0xC0, 0x70, //      #####       ### 
	0x00, 0xE8, 0x38, //         ### #     ###
	0x00, 0x78, 0x30, //          ####     ## 
	0x00, 0x1E, 0x38, //            ####   ###
	0x00, 0x17, 0x30, //            # ###  ## 
	0x00, 0x03, 0xA0, //               ### #  
	0x00, 0x01, 0x40, //                # #   


//3x23
  0x00, 0x04, 0x00, //              #         
	0x00, 0x0E, 0x00, //             ###        
	0x00, 0x03, 0x00, //               ##       
	0x00, 0x01, 0x80, //                ##      
	0x00, 0x01, 0x80, //                ##      
	0x00, 0x03, 0xC0, //               ####     
	0x00, 0x07, 0xC0, //              #####     
	0x00, 0x0F, 0xE0, //             #######    
	0x00, 0x1F, 0x60, //            ##### ##    
	0x00, 0x3E, 0x60, //           #####  ##    
	0x00, 0x3C, 0x70, //           ####   ###   
	0x00, 0xE8, 0x38, //         ### #     ###  
	0x00, 0xD0, 0x30, //         ## #      ##   
	0x01, 0xB0, 0x18, //        ## ##       ##  
	0x03, 0x60, 0x1C, //       ## ##        ### 
	0xE2, 0xC0, 0x0E, // ###   # ##          ###
	0x65, 0x80, 0x0C, //  ##  # ##           ## 
	0x3F, 0xA0, 0x0E, //   ####### #         ###
	0x1F, 0xFC, 0x06, //    ###########       ##
	0x02, 0xFF, 0xC2, //       # ##########    #
	0x00, 0x0F, 0xF4, //             ######## # 
	0x00, 0x0A, 0xF8, //             # # #####  
	0x00, 0x00, 0x10, //                    #   

//3x21

	0x00, 0x70, 0x00, //          ###           
	0x00, 0x38, 0x00, //           ###          
	0x00, 0x1C, 0x00, //            ###         
	0x00, 0x0E, 0x00, //             ###        
	0x00, 0x1F, 0x00, //            #####       
	0x00, 0x1F, 0x00, //            #####       
	0x00, 0x17, 0x80, //            # ####      
	0x00, 0x2B, 0x80, //           # # ###      
	0x00, 0x7D, 0xC0, //          ##### ###     
	0x00, 0xF8, 0xE0, //         #####   ###    
	0x00, 0xF0, 0x60, //         ####     ##    
	0x00, 0xA0, 0x30, //         # #       ##   
	0x01, 0x60, 0x70, //        # ##      ###   
	0x03, 0x40, 0x18, //       ## #         ##  
	0x07, 0xC0, 0x1C, //      #####         ### 
	0x06, 0x80, 0x0E, //      ## #           ###
	0xC5, 0x80, 0x0C, // ##   # ##           ## 
	0xEF, 0xA8, 0x02, // ### ##### # #         #
	0x7F, 0xFF, 0xF4, //  ################### # 
	0x02, 0xAF, 0xF8, //       # # # #########  
	0x00, 0x01, 0x50, //                # # #   

	//3x20
	0x01, 0xE0, 0x00, //        ####            
	0x00, 0x70, 0x00, //          ###           
	0x00, 0x38, 0x00, //           ###          
	0x00, 0x3C, 0x00, //           ####         
	0x00, 0x3E, 0x00, //           #####        
	0x00, 0x7F, 0x00, //          #######       
	0x00, 0x7B, 0x80, //          #### ###      
	0x00, 0x51, 0xC0, //          # #   ###     
	0x00, 0xF0, 0xE0, //         ####    ###    
	0x00, 0xF0, 0x70, //         ####     ###   
	0x00, 0xA0, 0x78, //         # #      ####  
	0x01, 0x60, 0x1C, //        # ##        ### 
	0x01, 0xE0, 0x3E, //        ####       #####
	0x01, 0x40, 0x06, //        # #           ##
	0x03, 0xC0, 0x06, //       ####           ##
	0x02, 0xC0, 0x02, //       # ##            #
	0x02, 0x81, 0xFE, //       # #      ########
	0x47, 0xFF, 0xFC, //  #   ################# 
	0xFF, 0xFF, 0xA8, // ################# # #  
	0x1F, 0x50, 0x00, //    ##### # #           

	//3x21
	0x1F, 0x00, 0x00, //    #####              
	0x03, 0x80, 0x00, //       ###             
	0x01, 0xC0, 0x00, //        ###            
	0x01, 0xE0, 0x00, //        ####           
	0x01, 0xFC, 0x00, //        #######        
	0x02, 0xFC, 0x00, //       # ######        
	0x03, 0xDF, 0x00, //       #### #####      
	0x02, 0x87, 0x80, //       # #    ####     
	0x07, 0xC1, 0xF0, //      #####     #####  
	0x02, 0x80, 0xE0, //       # #       ###   
	0x07, 0x80, 0x78, //      ####        #### 
	0x07, 0x80, 0x38, //      ####         ### 
	0x05, 0x00, 0x0C, //      # #            ##
	0x05, 0x80, 0x28, //      # ##         # # 
	0x05, 0x00, 0xF0, //      # #        ####  
	0x0F, 0x0B, 0xF0, //     ####    # ######  
	0x0F, 0x7F, 0xD0, //     #### ######### #  
	0x0F, 0xFA, 0x00, //     ######### #       
	0x4F, 0xD0, 0x00, //  #  ###### #          
	0xFE, 0x00, 0x00, // #######               
	0x10, 0x00, 0x00, //    #                  


	//3x21
	0x50, 0x00, 0x00, //  # #                 
	0xAE, 0x00, 0x00, // # # ###              
	0x07, 0x00, 0x00, //      ###             
	0x0F, 0xE0, 0x00, //     #######          
	0x05, 0x70, 0x00, //      # # ###         
	0x0A, 0x3E, 0x00, //     # #   #####      
	0x05, 0x07, 0x00, //      # #     ###     
	0x0A, 0x03, 0xE0, //     # #       #####  
	0x05, 0x00, 0x70, //      # #         ### 
	0x0A, 0x00, 0x28, //     # #           # #
	0x05, 0x00, 0x10, //      # #           # 
	0x0A, 0x00, 0x28, //     # #           # #
	0x05, 0x00, 0x70, //      # #         ### 
	0x0A, 0x03, 0xE0, //     # #       #####  
	0x05, 0x07, 0x00, //      # #     ###     
	0x0A, 0x3E, 0x00, //     # #   #####      
	0x05, 0x70, 0x00, //      # # ###         
	0x0F, 0xE0, 0x00, //     #######          
	0x07, 0x00, 0x00, //      ###             
	0xAE, 0x00, 0x00, // # # ###              
	0x50, 0x00, 0x00, //  # #                 

	

	
	
	

};




/**********************************************************
* Function Name: 
**********************************************************
* Summary: 
*
*
* Returns:
*  Nothing
**********************************************************/
bool initialize_ship(ship* myShip, uint8_t angle, uint8_t Xpos, uint8_t Ypos, uint8_t Xvelocity, uint8_t Yvelocity){
	
	
	myShip->angle = angle;
	
	//checks for validity of X and Y coordinates
	if(Xpos < LCD_X_MIN || Xpos > LCD_X_MAX ||
					Ypos < LCD_Y_MIN || Ypos > LCD_Y_MAX) return false;
	
	myShip->Xpos = Xpos; 
	myShip->Ypos = Ypos; 
	
	myShip->Xvelocity = Xvelocity; 
	myShip->Yvelocity = Yvelocity; 
	
	myShip->isDead = 0;
}
/**********************************************************
* Function Name: lcd_print_ship
**********************************************************
* Summary: prints a string to the LCD screen at a specified
* XY location in specified foreground and background colors
* X will specify the number of characters across with X=0
* being the left most character position, and X=13 being
* the right most.  Y will specify the number of characters
* down the screen with Y=0 being the top of the screen and
* Y=19 being the bottom row of characters.  NOTE this is
* opposite of how columns and rows are specified for the
* IL9341.
* Returns:
*  Nothing
**********************************************************/
void lcd_print_ship(
    ship* myShip,
    uint16_t fg_color, 
    uint16_t bg_color
)
{
	int ind = 0; 
	uint16_t ship_width;
	uint16_t ship_height;
	uint8_t* img = (uint8_t*)shipBitmaps;
	
	uint8_t Xpos = myShip ->Xpos;
	uint8_t Ypos = myShip ->Ypos; 
	uint8_t angle = myShip->angle; 

	
	while(ind != angle){
		
	 img = (uint8_t*)(img + (shipWidthPages[ind] * shipHeightPixels[ind])); 
	
		ind++;
	}
	ship_width = shipWidthPages[angle]*8; 
	ship_height = shipHeightPixels[angle];
	

	lcd_draw_image( Xpos, ship_width, Ypos, ship_height,
					img, fg_color, bg_color);
	
	}
	
/**********************************************************
* Function Name: 
**********************************************************
* Summary: 
*
*
* Returns:
*  Nothing
**********************************************************/
void angle_increment(ship* myShip){
	uint8_t currAngle; 
	uint8_t newAngle;
	
	currAngle = myShip->angle; 
	
	newAngle = currAngle + 1; 
	if(newAngle > ANGLE_MAX) newAngle = ANGLE_MIN;
	
	myShip->angle = newAngle;
}

/**********************************************************
* Function Name: 
**********************************************************
* Summary: 
*
*
* Returns:
*  Nothing
**********************************************************/
void angle_decrement(ship* myShip){
	uint8_t currAngle; 
	uint8_t newAngle;
	
	currAngle = myShip->angle; 
	
	newAngle = currAngle - 1; 
	if(newAngle > ANGLE_MIN) newAngle = ANGLE_MAX;
	
	myShip->angle = newAngle;
}




