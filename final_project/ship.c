
#include "ship.h"

/* 
**  ship bitmaps for all angles of rotation
*/


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

Ship new_ship(Vector pos, Vector vel) { //create a new ship at a position with a velocity
	Ship ship;
	ship.position = pos;
	ship.velocity = vel;
	ship.angle = RESET_ANGLE;
	ship.invincibility = SHIP_INVINCIBILITY;
	return ship;
};

void accelerate_ship(Ship* ship) { //accelerate ship
	Vector vel;
	vel.y = (int) sin(PI * (ship->angle / 180));
	vel.x = (int) cos(PI * (ship->angle / 180));
	ship->velocity.x -= vel.x * ACCELERATION_CONST;
	if (fabs(ship->velocity.x) > MAX_SPEED) { //cap speed in x direction
		if (ship->velocity.x > 0)
			ship->velocity.x = MAX_SPEED;
		else
			ship->velocity.x = -MAX_SPEED;
	}
	ship->velocity.y += vel.y * ACCELERATION_CONST;
	if (fabs(ship->velocity.y) > MAX_SPEED) { //cap speed in y direction
		if (ship->velocity.y > 0 )
			ship->velocity.y = MAX_SPEED;
		else
			ship->velocity.y = -MAX_SPEED;
	}
};


void rotate_ship_left(Ship* ship) { //rotate ship left
	ship->angle = (ship->angle + ROTATE_INCR) % 360;
}; 

void rotate_ship_right(Ship* ship) { //rotate ship right
	ship->angle = (ship->angle - ROTATE_INCR) % 360;
}; 

void update_ship(Ship * ship) { //ship's movement does not include drag
	ship->position = add(ship->position, ship->velocity);
	if(ship->position.x > LCD_MAX_X)
		ship->position.x = LCD_MIN;
	else if(ship->position.x < LCD_MIN)
		ship->position.x = LCD_MAX_X;
	
	if(ship->position.y > LCD_MAX_Y)
		ship->position.y = LCD_MIN;
	else if (ship->position.y < LCD_MIN)
		ship->position.y = LCD_MAX_Y;
}

bool ship_asteroid_collision(Ship* ship, Asteroid_list * al) {
	uint16_t i;
	uint8_t ship_width = SHIP_WIDTH;
	uint8_t ship_height = SHIP_HEIGHT;
	uint8_t asteroid_width, asteroid_height;
	Vector collision;
	for (i = al->start_index; i < al->end_index; i++) {
		Asteroid asteroid = al->asteroids[i];
		if (asteroid.index < 0)
			continue;
		collision = sub(ship->position,asteroid.position);
		switch (asteroid.size) {
			case 0:
					asteroid_width = LARGE_ASTEROID_WIDTH;
					asteroid_height = LARGE_ASTEROID_HEIGHT;
			case 1:
					asteroid_width = MEDIUM_ASTEROID_WIDTH;
					asteroid_height = MEDIUM_ASTEROID_HEIGHT;
			case 2:
					asteroid_width = SMALL_ASTEROID_WIDTH;
					asteroid_height = SMALL_ASTEROID_HEIGHT;
		}
		if ((fabs(collision.x) <= (asteroid_width / 2) + (ship_width / 2)) && (fabs(collision.y) <= (asteroid_height / 2) + (ship_height / 2))) {
			return true;
		}
	}
	return false;
};

void draw_ship(Ship * ship) {
	uint8_t ship_indx = 0;
	//TODO: need a uniform bitmap array to access correct ship image via simple calculation of angle
	lcd_draw_image(ship->position.x,SHIP_WIDTH,ship->position.y,SHIP_HEIGHT, &shipBitmaps[ship_indx], SHIP_COLOR, BACKGROUND_COLOR);
};

