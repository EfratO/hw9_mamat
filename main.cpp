#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"
#include "input.h"
#include "string.h"

int main(int argc, char **argv){
    if (check_args(argc, argv)){
        return 1;
    }

    String law(argv[1]);
    size_t size;
    String *sub_str;
    law.split("=",&sub_str,&size);
    Field filter(sub_str[0]);
    if (filter.get_type()==IP){
        Ip ip(sub_str[0]);
        ip.set_value(sub_str[1]);
        parse_input(ip);
    }
    if (filter.get_type()==PORT){
        Port port (sub_str[0]);
        port.set_value(sub_str[1]);
        parse_input(port);
    }
    delete[] sub_str;
    return 0;
}	
		