int receive_from_all_links(char *buf,int *len){
	
	int res;
	fd_set set;
	while(1){
		FD_ZERO(&set);

		for(int i = 0;i < routerinterfaces; i++)
			FD_SET(interfaces[routerinterfaces], &set);

		res = select(interfaces[routerinterfaces - 1] + 1,&set,NULL,NULL,NULL);

		for(int i; i<routerinterfaces; i++){
			if(FD_ISSET(interfaces[i],&set)){
				receivemsg(interface[i], buf, len);
				return i;
			}
		}
	}
}

void receivemsg()
int main(){
	
	int interface;
	char packet[MAXLEN];
	int packet_len;


	while(1){

		interface = receive_from_all_links(packet, &packet_len);

		struct ether_header *ehdr = (struct ether_header *) packet;
		struct iphdr *ip = (struct iphdr *) (packet + sizeof(struct ether_header));
	}
}