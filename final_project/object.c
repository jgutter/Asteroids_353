//author: Sadeq Hashemi
#include "Object.h"



//dynamically allocate an object list
Object_list* new_object_list(void){

	Object_list* obj_list;
	//time_t time_now;
	
	obj_list = malloc(sizeof(Object_list)); //allocates memory for the list
	
	
	if (obj_list == NULL)
        return NULL;	//returns NULL if allocation failed
	
	//shouldn't we also dynamically allocate the objects
	//obj_list->objects = malloc(MAX_OBJECTS * sizeof(Object));
	
	//time(&time_now);	//gets and stores current time
	//obj_list->time = time_now; 
	
	obj_list->last_free = 0; //sets the first empty 
	return obj_list; 
	
}	

void free_list(Object_list* object_list){ //free dynamically allocated object list

//free(object_list->objects); 
	
free(object_list);	

}

//add an object to object_list
bool add_object(Object_list* object_list, int8_t object_type, Vector pos, Vector vel, float lifetime){ 

	Object obj;
	//time_t time_now;
	
	if(object_type > 2)	return false; //checks if type is valid
	//adds the appropriate values to the struct
	
	obj.type = object_type; 
	obj.position = pos; 
	obj.velocity = vel; 
	obj.lifetime = lifetime; 
	
	//time(&time_now);
	//obj.time_created = time_now; 
	
	obj.alive = true; 
	
	object_list->objects[object_list->last_free] = obj; 
	
	return true; 
}

//draw objects in list to lcd screen; using draw_image function
void draw_objects(Object_list* object_list){
	
	int ind; 
	
	for(ind =0; ind < object_list->last_free; ind++){
		
		Object obj = object_list->objects[ind];
		
		switch(obj.type){
			
			case TYPE_SHIP:
				 //TODO
				break;
			
			case TYPE_ASTEROID:
				 //TODO
				break; 
			
			case TYPE_LASER:
				 //TODO
				break; 
		}
		
	}
	
}

