#include "ip.h"
#include <cstring>
#include <iostream>

 Ip::Ip(String pattern): Field(pattern){}

 bool Ip::set_value(String val){
    size_t size;
	String *str;
	int mask;
	
    val.split("/",&str,&size);
	if (size == 2){
	    mask=str[1].trim().to_integer();
		if ((mask > 32) || (mask < 0)){
			delete[] str;
		    return false;
		}	
	}
	 else{
		 if(size !=0){
		 delete[] str;
		 }
		 return false;
	 }
    
    String *ip_str;
    str[0].split(".",&ip_str,&size);
    delete[] str;

	 
	 /*check if size is actally 4*/
    int ip_num;
	int ip_bit=0; 
	if (size == SEGMENTS){
		for (size_t i=0;i<size;i++){
			ip_num=ip_str[i].trim().to_integer();
			if ((ip_num>255) || (ip_num<0)){
				delete[] ip_str;
				return false;
			}	
            ip_bit= (ip_num<< (24 - (8 * i)))|ip_bit;
		}
		/*considering the mask*/
		unsigned int mask_bit= 0xFFFFFFFF;
		if (mask==32){
		    mask_bit= 0x00000000;
		}
		else{
		    mask_bit=mask_bit >> mask;   	
		}
        high=ip_bit | (mask_bit);
        low=ip_bit & (~mask_bit);	
		delete[] ip_str;
	    return true;
	}
	else{
		if(size !=0){
            delete[] ip_str;
		}
		return false;
	}
}
 
 
bool Ip::match_value(String val) const{
	size_t size;
	String *val_check = &val;
	val.split(".",&val_check,&size);
	
	 
	 /*check if size is actally 4*/
	unsigned int ip_bit=0;
	int ip_num; 
	if (size == SEGMENTS){
		for (int i=0;i<(int)size;i++){
			ip_num =val_check[i].trim().to_integer();
			if ((ip_num>255) || (ip_num<0)){
				delete[] val_check;
				return false;
			}
            ip_bit= (ip_num << (24 - (8 * i)))|ip_bit;
			}				
		}
	else{
	    delete[] val_check;
	    return true;
    }
			
	delete[] val_check;	
    if((low<=ip_bit) && (ip_bit<=high)){
	    return true;
	}
	return false;
}