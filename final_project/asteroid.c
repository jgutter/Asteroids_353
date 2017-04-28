//Author: SADEQ HASHEMI NEJAD
#include "asteroid.h"


const uint8_t asteroidWidthPages[] = {7, 7, 7, 4, 4, 4, 2, 2, 2};
const uint8_t asteroidHeightPixels[] = {50, 50, 49, 25, 25, 25, 13, 13, 13 };

/* 
**  ship bitmaps for all angles of rotation
*/

/*  */

const uint8_t asteroidBitmaps[] =
{
	//7x50
	0x00, 0x00, 0x00, 0x1F, 0xC0, 0x00, 0x00, //                            #######                
	0x00, 0x00, 0x00, 0xBE, 0xEA, 0x00, 0x00, //                         # ##### ### # #           
	0x00, 0x00, 0x00, 0xFC, 0x7E, 0x00, 0x00, //                         ######   ######           
	0x00, 0x00, 0x03, 0xC0, 0x07, 0xC0, 0x00, //                       ####           #####        
	0x00, 0x00, 0x07, 0xC0, 0x07, 0xC0, 0x00, //                      #####           #####        
	0x00, 0x00, 0x07, 0x00, 0x00, 0xC0, 0x00, //                      ###                ##        
	0x00, 0x07, 0xC7, 0x00, 0x00, 0x70, 0x00, //              #####   ###                 ###      
	0x00, 0x07, 0x86, 0x00, 0x00, 0x20, 0x00, //              ####    ##                   #       
	0x00, 0xFF, 0x7E, 0x00, 0x00, 0x7C, 0x00, //         ######## ######                  #####    
	0x02, 0xFA, 0x3A, 0x00, 0x00, 0x38, 0x00, //       # ##### #   ### #                   ###     
	0x03, 0xC0, 0x00, 0x00, 0x00, 0x1C, 0x00, //       ####                                 ###    
	0x0B, 0x80, 0x00, 0x00, 0x00, 0x0E, 0x00, //     # ###                                   ###   
	0x5F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, //  # #####                                   #####  
	0x38, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, //   ###                                        #### 
	0x78, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, //  ####                                        ###  
	0x20, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, //   #                                            ## 
	0xF0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // ####                                           #  
	0xE0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, // ###                                           ### 
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, // ##                                           ###  
	0x80, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, // #                                            ##   
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, // ##                                           ##   
	0x80, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, // #                                            ##   
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, // ##                                           ##   
	0x80, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, // #                                            ##   
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, // ##                                           ##   
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, // ##                                           ##   
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, // ##                                           ###  
	0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, // #                                             ### 
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // ##                                             #  
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, // ##                                             ###
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, // ##                                             ###
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // #                                               ##
	0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // #####                                           ##
	0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // #####                                           ##
	0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //    ##                                           ##
	0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //    ##                                           ##
	0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //    ###                                          ##
	0x0E, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, //     ###                                        ###
	0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, //      ###                                       ###
	0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, //      ###                                       ## 
	0x07, 0xC0, 0x00, 0x00, 0x7F, 0xFF, 0x00, //      #####                       ###############  
	0x03, 0xC0, 0x00, 0x00, 0x3F, 0xFF, 0x80, //       ####                        ############### 
	0x00, 0xF0, 0x00, 0x00, 0x70, 0x00, 0x00, //         ####                     ###              
	0x00, 0xF8, 0x00, 0x00, 0x20, 0x00, 0x00, //         #####                     #               
	0x00, 0x78, 0x00, 0x00, 0x70, 0x00, 0x00, //          ####                    ###              
	0x00, 0x1E, 0x00, 0x00, 0xE0, 0x00, 0x00, //            ####                 ###               
	0x00, 0x1F, 0x50, 0x00, 0xF0, 0x00, 0x00, //            ##### # #            ####              
	0x00, 0x07, 0xE0, 0x00, 0xC0, 0x00, 0x00, //              ######             ##                
	0x00, 0x07, 0x7F, 0xFF, 0xC0, 0x00, 0x00, //              ### #################                
	0x00, 0x00, 0x3F, 0xFF, 0xC0, 0x00, 0x00, //                   ################                

	//7x50
	0x00, 0x00, 0x1F, 0xFF, 0xFE, 0x00, 0x00, //                    ####################           
	0x00, 0x00, 0xBA, 0xFE, 0xFE, 0x80, 0x00, //                 # ### # ####### ####### #         
	0x00, 0x00, 0xF8, 0x00, 0xFF, 0xC0, 0x00, //                 #####           ##########        
	0x00, 0x07, 0x80, 0x00, 0x1E, 0xC0, 0x00, //              ####                  #### ##        
	0x00, 0x1F, 0x00, 0x00, 0x1E, 0xD0, 0x00, //            #####                   #### ## #      
	0x00, 0x0E, 0x00, 0x00, 0x00, 0xE0, 0x00, //             ###                         ###       
	0x00, 0x7C, 0x00, 0x00, 0x00, 0x78, 0x00, //          #####                           ####     
	0x00, 0x38, 0x00, 0x00, 0x00, 0x38, 0x00, //           ###                             ###     
	0x00, 0xF0, 0x00, 0x00, 0x00, 0x1E, 0x00, //         ####                               ####   
	0x00, 0xE0, 0x00, 0x00, 0x00, 0x0E, 0x00, //         ###                                 ###   
	0x00, 0xC0, 0x00, 0x00, 0x00, 0x07, 0x00, //         ##                                   ###  
	0x02, 0x80, 0x00, 0x00, 0x00, 0x03, 0x80, //       # #                                     ### 
	0x07, 0xC0, 0x00, 0x00, 0x00, 0x01, 0xC0, //      #####                                     ###
	0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //      ###                                        ##
	0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //      ###                                        ##
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //      ##                                         ##
	0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //    ####                                         ##
	0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //    ## #                                         ##
	0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //    ##                                           ##
	0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //    ##                                           ##
	0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //  # ##                                           ##
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //   #                                             ##
	0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //  ###                                            ##
	0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // ###                                             ##
	0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // ## #                                            ##
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // ##                                              ##
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // ##                                              ##
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // #                                               ##
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // ##                                              ##
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // ##                                              ##
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // ##                                              ##
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // #                                               ##
	0xFC, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, // ######                                         ###
	0xFE, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, // #######                                       ####
	0x07, 0xC0, 0x00, 0x00, 0x00, 0x01, 0x00, //      #####                                     #  
	0x03, 0xF8, 0x00, 0x00, 0x00, 0x03, 0x80, //       #######                                 ### 
	0x03, 0xF8, 0x00, 0x00, 0x00, 0x07, 0x00, //       #######                                ###  
	0x1F, 0x80, 0x00, 0x00, 0x0F, 0xFE, 0x00, //    ######                           ###########   
	0x1F, 0x00, 0x00, 0x00, 0x1F, 0xFE, 0x00, //    #####                           ############   
	0x18, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, //    ##                             ###             
	0x18, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, //    ##                            ###              
	0x18, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, //    ##                           ###               
	0x18, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, //    ##                          ###                
	0x1A, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, //    ## #                       ###                 
	0x1F, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, //    #####                       #                  
	0x0B, 0xF8, 0x00, 0x0E, 0x00, 0x00, 0x00, //     # #######               ###                   
	0x03, 0xFD, 0x50, 0x1E, 0x00, 0x00, 0x00, //       ######## # # #       ####                   
	0x00, 0x0F, 0xF8, 0x38, 0x00, 0x00, 0x00, //             #########     ###                     
	0x00, 0x17, 0x5F, 0xF0, 0x00, 0x00, 0x00, //            # ### # #########                      
	0x00, 0x00, 0x0F, 0xE0, 0x00, 0x00, 0x00, //                     #######                       
	
	//7x49
	0x00, 0x00, 0x00, 0x1F, 0xC0, 0x00, 0x00, //                            #######                
	0x00, 0x00, 0x2A, 0xBE, 0xEA, 0x00, 0x00, //                   # # # # ##### ### # #           
	0x00, 0x00, 0x7F, 0xFC, 0xFE, 0x00, 0x00, //                  #############  #######           
	0x00, 0x0F, 0x80, 0x00, 0x03, 0xC0, 0x00, //             #####                     ####        
	0x01, 0x5F, 0xC0, 0x00, 0x01, 0xD0, 0x00, //        # # #######                     ### #      
	0x03, 0xF8, 0x00, 0x00, 0x00, 0xE0, 0x00, //       #######                           ###       
	0x03, 0xD0, 0x00, 0x00, 0x00, 0x70, 0x00, //       #### #                             ###      
	0x03, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, //       ##                                  #       
	0x03, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, //       ##                                 #####    
	0x02, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, //       #                                   ###     
	0x04, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, //      #                                     ###    
	0x0E, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, //     ###                                     #     
	0x1C, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, //    ###                                     ###    
	0x18, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, //    ##                                       ###   
	0x58, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, //  # ##                                      #####  
	0x20, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, //   #                                          #### 
	0x78, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, //  ####                                        ###  
	0x38, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, //   ###                                         ### 
	0x18, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, //    ##                                          #  
	0x18, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, //    ##                                          ## 
	0x1F, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, //    #####                                       ###
	0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, //      ###                                       ###
	0x07, 0xC0, 0x00, 0x00, 0x00, 0x01, 0xC0, //      #####                                     ###
	0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0xC0, //       ###                                       ##
	0x01, 0x70, 0x00, 0x00, 0x00, 0x00, 0xC0, //        # ###                                    ##
	0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0xC0, //          ##                                     ##
	0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xC0, //         #####                                   ##
	0x02, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xC0, //       # ### #                                   ##
	0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC0, //       ####                                      ##
	0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0xC0, //      ####                                       ##
	0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //  # #####                                        ##
	0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, //   #####                                         ##
	0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // #### #                                          ##
	0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // ###                                             ##
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // ##                                              ##
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, // #                                               ##
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, // ##                                             ###
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, // ##                                             ## 
	0xD0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, // ## #                                         ###  
	0xE0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, // ###                                          #### 
	0x70, 0x01, 0xC0, 0x00, 0x00, 0x7F, 0x00, //  ###           ###                       #######  
	0x20, 0x03, 0xC0, 0x00, 0x02, 0x3E, 0x00, //   #           ####                    #   #####   
	0x70, 0x1F, 0xF0, 0x00, 0x07, 0xF0, 0x00, //  ###       #########                 #######      
	0x2A, 0xBA, 0xA8, 0x02, 0xAE, 0xA0, 0x00, //   # # # # ### # # # #         # # # ### # #       
	0x1F, 0xF8, 0x1E, 0x07, 0xFE, 0x00, 0x00, //    ##########      ####      ##########           
	0x08, 0x80, 0x0F, 0x0E, 0x80, 0x00, 0x00, //     #   #           ####    ### #                 
	0x00, 0x00, 0x07, 0x5E, 0x00, 0x00, 0x00, //                      ### # ####                   
	0x00, 0x00, 0x03, 0xF8, 0x00, 0x00, 0x00, //                       #######                     
	0x00, 0x00, 0x01, 0x50, 0x00, 0x00, 0x00, //                        # # #                      
	
	//4x25
	0x00, 0xBF, 0xF8, 0x00, //         # ###########    
	0x07, 0xFF, 0x0F, 0x00, //      ###########    #### 
	0x0E, 0x00, 0x03, 0x00, //     ###               ## 
	0x78, 0x00, 0x01, 0x00, //  ####                  # 
	0x20, 0x00, 0x01, 0x00, //   #                    # 
	0x60, 0x00, 0x07, 0x00, //  ##                  ### 
	0x60, 0x00, 0x0E, 0x00, //  ##                 ###  
	0x40, 0x00, 0x1C, 0x00, //  #                 ###   
	0xC0, 0x00, 0x1A, 0x00, // ##                 ## #  
	0xC0, 0x00, 0x3F, 0x80, // ##                #######
	0x80, 0x00, 0x20, 0x80, // #                 #     #
	0x80, 0x00, 0x00, 0x80, // #                       #
	0x80, 0x00, 0x00, 0x80, // #                       #
	0x80, 0x00, 0x00, 0x80, // #                       #
	0x80, 0x00, 0x00, 0x80, // #                       #
	0x80, 0x00, 0x00, 0x80, // #                       #
	0x80, 0x00, 0x00, 0x80, // #                       #
	0xC0, 0x00, 0x00, 0x80, // ##                      #
	0xC0, 0x00, 0x00, 0x80, // ##                      #
	0x60, 0x00, 0x01, 0x00, //  ##                    # 
	0x20, 0x00, 0x03, 0x00, //   #                   ## 
	0x70, 0x00, 0x03, 0x00, //  ###                  ## 
	0x38, 0x00, 0x0E, 0x00, //   ###               ###  
	0x1C, 0x00, 0x1C, 0x00, //    ###             ###   
	0x0B, 0xFF, 0xF8, 0x00, //     # ###############    

	//4x25
	0x01, 0xFF, 0xF8, 0x00, //        ##############    
	0x07, 0x80, 0x1F, 0x00, //      ####          ##### 
	0x0E, 0x00, 0x03, 0x80, //     ###               ###
	0x38, 0x00, 0x00, 0x80, //   ###                   #
	0x30, 0x00, 0x00, 0x80, //   ##                    #
	0x60, 0x00, 0x01, 0x80, //  ##                    ##
	0xC0, 0x00, 0x01, 0x80, // ##                     ##
	0xC0, 0x00, 0x01, 0x00, // ##                     # 
	0x80, 0x00, 0x0A, 0x00, // #                   # #  
	0x80, 0x00, 0x0F, 0x00, // #                   #### 
	0x80, 0x00, 0x0B, 0x80, // #                   # ###
	0x80, 0x00, 0x1F, 0x80, // #                  ######
	0x80, 0x00, 0x00, 0x80, // #                       #
	0x80, 0x00, 0x00, 0x80, // #                       #
	0x80, 0x00, 0x00, 0x80, // #                       #
	0xC0, 0x00, 0x00, 0x80, // ##                      #
	0xC0, 0x00, 0x00, 0x80, // ##                      #
	0x60, 0x00, 0x01, 0x80, //  ##                    ##
	0x20, 0x00, 0x01, 0x80, //   #                    ##
	0x30, 0x00, 0x01, 0x00, //   ##                   # 
	0x38, 0x00, 0x02, 0x00, //   ###                 #  
	0x1E, 0x00, 0x07, 0x00, //    ####              ### 
	0x03, 0x80, 0x0E, 0x00, //       ###           ###  
	0x05, 0xFF, 0x7C, 0x00, //      # ######### #####   
	0x00, 0x81, 0xE8, 0x00, //         #      #### #    
	
	//4x25
	0x00, 0xFF, 0x80, 0x00, //         #########        
	0x07, 0xC3, 0xF4, 0x00, //      #####    ###### #   
	0x0C, 0x00, 0x1E, 0x00, //     ##             ####  
	0x38, 0x00, 0x03, 0x00, //   ###                 ## 
	0x30, 0x00, 0x01, 0x00, //   ##                   # 
	0x60, 0x00, 0x01, 0x00, //  ##                    # 
	0x20, 0x00, 0x01, 0x00, //   #                    # 
	0x40, 0x00, 0x01, 0x80, //  #                     ##
	0xC0, 0x00, 0x01, 0x80, // ##                     ##
	0xC0, 0x00, 0x01, 0x80, // ##                     ##
	0xE8, 0x00, 0x01, 0x80, // ### #                  ##
	0x1C, 0x00, 0x01, 0x80, //    ###                 ##
	0xBA, 0x00, 0x00, 0x80, // # ### #                 #
	0xD0, 0x00, 0x01, 0x80, // ## #                   ##
	0x80, 0x00, 0x00, 0x80, // #                       #
	0x80, 0x00, 0x7F, 0x80, // #                ########
	0x80, 0x00, 0x7A, 0x80, // #                #### # #
	0xC0, 0x00, 0x70, 0x00, // ##               ###     
	0x60, 0x00, 0x3C, 0x00, //  ##               ####   
	0x70, 0x00, 0x17, 0x00, //  ###               # ### 
	0x3C, 0x00, 0x03, 0x00, //   ####                ## 
	0x17, 0x00, 0x01, 0x00, //    # ###               # 
	0x03, 0x80, 0x01, 0x80, //       ###              ##
	0x01, 0xE0, 0x0F, 0x80, //        ####         #####
	0x00, 0xBF, 0xF8, 0x00, //         # ###########    

	//2x13
	0x3F, 0xF0, //   ########## 
	0x20, 0x20, //   #       #  
	0x60, 0x30, //  ##       ## 
	0x40, 0x10, //  #         # 
	0xC0, 0x10, // ##         # 
	0x80, 0x18, // #          ##
	0x80, 0x18, // #          ##
	0x80, 0x08, // #           #
	0x80, 0x78, // #        ####
	0x80, 0xF8, // #       #####
	0x60, 0xD0, //  ##     ## # 
	0x38, 0x80, //   ###   #    
	0x5F, 0xC0, //  # #######   

	//2x13
	0x7F, 0x40, //  ####### #   
	0x63, 0xE0, //  ##   #####  
	0x40, 0x70, //  #       ### 
	0x80, 0x18, // #          ##
	0x80, 0x18, // #          ##
	0x80, 0x08, // #           #
	0x80, 0x08, // #           #
	0x80, 0x08, // #           #
	0x81, 0xC8, // #      ###  #
	0x81, 0xF8, // #      ######
	0x61, 0xF0, //  ##    ##### 
	0x21, 0x80, //   #    ##    
	0x5F, 0x80, //  # ######    

	//2x13
	0x1F, 0xF0, //    ######### 
	0x38, 0x30, //   ###     ## 
	0xF0, 0x10, // ####       # 
	0x80, 0x10, // #          # 
	0x80, 0x18, // #          ##
	0x80, 0x08, // #           #
	0x80, 0x08, // #           #
	0x80, 0x08, // #           #
	0xC0, 0x08, // ##          #
	0xC0, 0x08, // ##          #
	0x70, 0x30, //  ###      ## 
	0x38, 0x20, //   ###     #  
	0x1F, 0xC0, //    #######   

};

/**********************************************************
* Function Name: rand_gen
**********************************************************
* Summary: generate a random value between 0 and max_value
* 
* Returns: value generated
**********************************************************/
int16_t rand_gen(int16_t max_value){
	
	int16_t ret = rand() % (max_value+1); 
	
	return ret; 
}

/**********************************************************
* Function Name: initialize_asteroid
**********************************************************
* Summary: initializes asteroid with given size at a 
* random empty location.
*
* Returns: true if successful
**********************************************************/
bool initialize_asteroid(asteroid* myAsteroid, uint8_t size){
	uint16_t Xval;
	uint16_t Yval;
	uint8_t width;
	uint8_t height;
	int row, col;
	bool valid = true;
	uint8_t chk_vld;
	
	if((myAsteroid == NULL) || size>2) return false; 	//checks for validity of parameters
	
	//chooses the appropriate height and width based on one
	//of the three given sizes
	switch(size){
		case LARGE_AST: 
			width = LARGE_WIDTH;
			height = LARGE_HEIGHT; 
		
		case MED_AST:
			width = MED_WIDTH; 
			height = MED_HEIGHT;
		
		case SMALL_AST: 
			width = SMALL_WIDTH; 
			height = SMALL_HEIGHT;
	}
	//Generates a random X and Y coordinate, and checks
	//to see if that portion of the screen is empty
	//TODO check if location is empty
	do{
	 Xval = rand_gen(239);	//generates random X
	 Yval = rand_gen(319);	//generates random Y
	
	for(row= Xval; row <= Xval + width +; row++){
		for(col=Yval; col <= Yval +height; col++){
			chk_vld = screen_map[Xval][320/Yval];
			chk_vld>>(320%Yval);
			chk_vld = chk_vld & 0x01;
			
			if( ){}
		}
	}
	} while(); 
	
	myAsteroid->Xpos = Xval; 
	myAsteroid->Ypos = Yval; 
	myAsteroid->Xvelocity = CONST_X_VEL; 
	myAsteroid->Yvelocity = CONST_Y_VEL;
	myAsteroid->size = size; 
	
	return true; 
	
}
