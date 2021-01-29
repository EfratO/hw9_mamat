#include "port.h"
#include <cstdlib>
	
Port::Port(String pattern):Field(pattern){}
	bool Port::set_value(String val){
		size_t size;
		String *str;
		val.split("-",&str,&size);
	 
	 /*check if size is actally 2*/
	if (size == 2){
	    range[0]=str[0].trim().to_integer();
	    range[1]=str[1].trim().to_integer();
		if(range[0]< range[1]){ /*check if the range correct*/
		    delete[] str;
			return false;
		}
		delete[] str;
	    return true;
	}
	else{
		if(size !=0){
		delete[] str;
		}
		return false;
	}
 }
 
 
 
 bool Port::match_value(String val) const{
	int val_check = val.trim().to_integer();
    if((range[0]<=val_check) && (val_check<=range[1])){
	    return true;
	}
	return false;
 }