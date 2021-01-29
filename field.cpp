#include "field.h"
#include "ip.h"
#include "port.h"
#include <iostream>
#include <cstring>

Field::Field(String pattern){
    this->pattern = pattern.trim();
    if((this->pattern).equals("src-ip")||(this->pattern).equals("dst-ip")){
            this->type = IP;
    }
	else{
        if((this->pattern).equals("src-port")||
        (this->pattern).equals("dst-port")){
            this->type = PORT;
        }
        else{
            this->type = GENERIC;
        }
    }
}

Field::Field(String pattern, field_type type){
    this->pattern = pattern.trim();
    this->type = type;
}
 
Field::~Field(){
}
 
field_type Field::get_type() const{
    return type;
}

bool Field::set_value(String val){
    if(type == PORT){
        return ((Port*)this)->set_value(val);
	}
    if(type == IP){
	    return ((Ip*)this)->set_value(val);
    }
	return false; /*type is GENERIC */
}

bool Field::match_value(String val) const{
    if(type == PORT){
        return ((Port*)this)->match_value(val);
	}
    if(type == IP){
	    return ((Ip*)this)->match_value(val);
    }
	return false; /* type is GENERIC */
}

bool Field::match(String packet){
    size_t size=0;
    String *sub_str;
	packet.split(",=",&sub_str,&size);
    for (int i=0;i<(int)size;i++){
        if (pattern.equals(sub_str[i].trim())){
            if (i+1<(int)size && match_value(sub_str[i+1].trim())){
                delete[] sub_str;                
				return true;
            }
            delete[] sub_str;
            return false;
        }
    }
    delete[] sub_str;
    return false;
}