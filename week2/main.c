#include <stdio.h>
#include <stdlib.h>
#include "domain_ip.h"
int main(int argc, char *argv[]){
	if(argc==1){
		printf("Please input IP or host name\n");
		return 0;
	}
	else{
		char *input = argv[1];
		int check = ip_valid(input);
		printf("%d\n", check);
		if(check == 1) {
			get_info_ip_address(input);
			return 0;
		}else if(check == 2)
			get_ip(input);
		else{
			printf("IP khong hop le\n");
		}
	}
	return 0;
}