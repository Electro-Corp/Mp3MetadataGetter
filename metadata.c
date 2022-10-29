#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <png.h>
int version = 0;
uint8_t buffer[1000];
int v = 0;
int main(int argv, char** args){
	if(args[2] == "-v")
		v = 1;
	FILE* fp = fopen(args[1], "r");
	if(fp == NULL){printf("File %s not found!\n",args[1]);exit(1);}
	fread(buffer,sizeof(buffer),1,fp);
	// print byte
	//for(int i = 0; i<100; i++)
    	//	printf("%u ", buffer[i]);
    	//printf("\n");
	if(buffer[0] == 73 && buffer[1] == 68 && buffer[2] == 51){
		printf("Attempting to read as ID3 File!\n");
		// Version Check
		printf("Version %u.%u\n",buffer[3],buffer[4]);
		// Find Header frame
		int offset = 0, i = 0;
		while(sizeof(buffer) > offset){
			if(buffer[offset] == 84 && buffer[offset+1] == 73 && buffer[offset+2] == 84 && buffer[offset+3] == 50)
				break;
			offset++;
		}
		if(offset != 0)
			if(v == 1){
				printf("Header found at offset %d, header ID found as %u %u %u %u, also known as ",offset,buffer[offset],buffer[offset+1],buffer[offset+2],buffer[offset+3]);
				putchar(buffer[offset]);
				putchar(buffer[offset+1]);
				putchar(buffer[offset+2]);
				putchar(buffer[offset+3]);
				printf("\n");
			}
			else 
				printf("");
		else
			printf("No header found!\n");
		// Parse header
		if(offset != 0){
			offset += 10; // get away from the header
			char* data = malloc(100);
			if(v == 1)
			printf("Reading song title from offset %d.\n",offset);
			if(offset == 0) offset++;
			while(buffer[offset++] != 0 || i == 0)
				data[i++] = buffer[offset];
			if(v == 1)
			printf("Final offset: %d, which is: %u\n",offset,buffer[offset]);
			printf("Song title: %s\n",data); // Song title
			
		}
		// Get Artist header
		offset = 0;
		i = 0;
		while(sizeof(buffer) > offset){
			if(buffer[offset] == 84 && buffer[offset+1] == 80 && buffer[offset+2] == 69 && buffer[offset+3] == 49)
				break;
			offset++;
		}
		if(offset != 0){
			offset += 10; // get away from the header
			char* data = malloc(100);
			
			if(offset == 0) offset++;
			while(buffer[offset++] != 0 || i == 0)
				data[i++] = buffer[offset];
			printf("Song artist: %s\n",data); // Song title
			
		}
		// Get album info (if it exists)
		offset = 0;
		i = 0;
		while(sizeof(buffer) > offset){
			if(buffer[offset] == 84 && buffer[offset+1] == 65 && buffer[offset+2] == 76 && buffer[offset+3] == 66)
				break;
			offset++;
		}
		if(offset != 0){
			offset += 10; // get away from the header
			char* data = malloc(100);
			
			if(offset == 0) offset++;
			while(buffer[offset++] != 0 || i == 0)
				data[i++] = buffer[offset];
			
			if(data)
				printf("Album: %s\n",data); // Song title
			
		}
		// Get release year
		offset = 0;
		i = 0;
		while(sizeof(buffer) > offset){
			//V4
			if(buffer[offset] == 84 && buffer[offset+1] == 68 && buffer[offset+2] == 82 && buffer[offset+3] == 67)
				break;
			//V3
			if(buffer[offset] == 84 && buffer[offset+1] == 89 && buffer[offset+2] == 69 && buffer[offset+3] == 82)
				break;
			offset++;
		}
		if(offset != 0){
			offset += 10; // get away from the header
			char* data = malloc(100);
			
			if(offset == 0) offset++;
			while(buffer[offset++] != 0 || i == 0)
				data[i++] = buffer[offset];
			if(data)
				printf("Release Year: %s\n",data); // Song title
			
		}
		// Output image
		FILE* image = fopen("out.jpg","wb");
		offset = 0;
		i = 0;
		while(sizeof(buffer) > offset){
			//V4
			if(buffer[offset] == 106 && buffer[offset+1] == 112 && buffer[offset+2] == 101 && buffer[offset+3] == 103)
				break;
			offset++;
		}
		if(offset != 0){
			offset += 7; // get away from the header
			char* data = malloc(1000);
			
			if(offset == 0) offset++;
			//while(buffer[offset] != 51 && buffer[offset + 1] != 68 && buffer[offset+2] != 73 || offset < sizeof(buffer) || i < sizeof(data))
				//data[i++] = buffer[offset++];
			//fwrite(data,sizeof(data),1,image);
			
		}
	}
	return 0;
}
