#include "string.h"
#include <iostream>
#include <cstring>

String::String(){
    data = new char[1];
    data[0]='\0';
    length=0;
}

String::String(const String &str){
    length = str.length;
    data = new char [length+1];
    strncpy (data,str.data,length+1);
}

String::String(const char *str){
	if (str == NULL||*str == '\0'){
		length = 0;
        data = new char[1];
        data[0]='\0';
    }
	else{
        length = strlen(str);
        data = new char [length+1];
        strncpy (data,str,length+1);
    }
}

String::~String(){
    delete[] data;
}
   
String& String::operator=(const String &rhs){
    if (this==&rhs){ /* they are the same object */
        return *this;
    }
    char *old_data = data; 
    length = rhs.length;
    data = new char [length+1];
    strncpy (data,rhs.data,length+1);
    delete[] old_data;
    return *this;
}
    
String& String::operator=(const char *str){
    char *old_data = data;  
    if (str == NULL||*str == '\0'){
        length = 0;
        data = new char[1];
        data[0]='\0';
    }
    else{
        length = strlen(str);
        data = new char [length+1];
        strncpy (data,str,length+1);
    }
    delete[] old_data;
    return *this;
}
bool String::equals(const String &rhs) const{
    if (!strcmp(data,rhs.data)){ /* strings are equals */
        return true;
    }
    return false;
}
		
bool String::equals(const char *rhs) const{
    if (!rhs){
        return false;
    }
    if (!strcmp(data,rhs)){ /* strings are equals */
        return true;
    }
    return false;
}

/**
 * @brief check if char is delimiter
 * @param a is char we want to check
 * @param delimiters is string of delimiters
 * @return true if char is delimiter and false otherwise 
 */
bool char_is_delimiter (char a,const char *delimiters){
    while ((delimiters) && (*delimiters!='\0')){
        if (a == *delimiters){
            return true;
        }
        delimiters++;
    }
    return false;	
}
 
/**
 * @brief get num of substrings we need to create
 * @param delimiters is a string of delimiters
 * @param str is a original string 
 * @return num of substrings 
 */ 
size_t num_substrings (const char *delimiters,const char *str){
	size_t count=0;
	int start_sub_str=0;
    if (!strlen(str)){
        return count;
    }
    int i;
    for (i=0;i<(int)(strlen(str));i++){
        if(!char_is_delimiter (str[i],delimiters)){
            continue;
        }
		else{
            if (i==start_sub_str){ /*null substring*/
                start_sub_str++;
            }
		    else{
                count++;
                start_sub_str=i+1;/*next char*/
            }
        }
    }
    if (i!=start_sub_str){ /*last substring*/
        count++;
    }
	return count;
}  

void String::split(const char *delimiters, String **output, size_t *size)const{
    size_t count=0;
    int start_sub_str=0;
    *size = num_substrings(delimiters,data); 
    if (!output){
        return;
    }
	if (*size == 0){
        *output=NULL;
        return;
    }
	*output = new String [*size];
    char *str = new char [length+1];
    strncpy (str,data,length+1);
    int i;
    for (i=0;i<(int)length;i++){
        if(!char_is_delimiter (str[i],delimiters)){
            continue;
        }
		else{
            if (i==start_sub_str){ /*null substring*/
                start_sub_str++;
            }
		    else{
                str[i] = '\0';		
                (*output)[count] = &str[start_sub_str];
                count++;
                start_sub_str=i+1;/*next char*/
            }
        }
    }
    if (i!=start_sub_str){ /*last substring*/
        (*output)[count]= &str[start_sub_str];
    }
    delete[] str;
 
}  

String String::trim() const{
    String clean_str = data;
    if (clean_str.length==0){
        return clean_str;
    }
    size_t start = 0;
    size_t end = clean_str.length-1;
	while (clean_str.data[start]==' '){
        start++;
    }
    while (start<end && clean_str.data[end]==' '){
        end--;
    }
    if (end>=start){
        clean_str.data[end+1] ='\0'; /* new str without spaces */
        clean_str = &(clean_str.data[start]);
    }
	return clean_str;
}

int String::to_integer() const{
    return atoi((this->trim()).data);
}
