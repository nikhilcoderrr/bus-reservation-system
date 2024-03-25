//BUS RESERVATION SYSTEM 
//TESTED TO BE WORKING ON VS CODE LINUX(UBUNTU 23.10) with gcc compiler
//COMPILER-> gcc (Ubuntu 13.2.0-4ubuntu3) 13.2.0, 
//debugger-> GNU gdb (Ubuntu 14.0.50.20230907-0ubuntu1) 14.0.50.20230907-git
//MAKE SURE TO STORE THIS FILE INSIDE A FOLDER BEFOREHAND FOR THE REQUIRED FILES TO BE GENERATED 
//CGU GROUP1 538-543 
//3/12/2023
//--------------------BUS RESERVATION SYSTEM--------------------

#include<stdio.h>
#include<string.h>
#define MAX_BUSES 5
#define SEAT_BIN_FILE "SEATS.bin"                                
#define PASSENGERS_BINARY_FILE "passengers_data.bin"            
#define PASSENGERS_TEMP_FILE "passenders_data_tmp.bin"         


int main(){
    int desc = 0;
    int bus_number;
    int bus_found = 0;
    int cont;
    FILE *file_ptr;
    FILE *file_tmp_ptr;
    FILE *file_ptr2;
    int ticket_num = 0;
    int inp_ticket_num;
    int desc2;
    int bus_num;
    char chr;
    int a;
    int place;
    long int input_mobile_number;
    int ticket_found = 0;

    struct Buses{                        
        int Bus_num;
        char Bus_name[100];
        char Depart_time[6];
        char Arrival_time[6];
        char departure[100];
        char destination[100];
        int days;                               
        float fare;
    };

    struct Passenger{              
        int ticket_number;
        char passenger_name[200];
        int age;
        char Gender[100];
        char destination[100];
        char divyangjan[10];
        long int mobile_num;
        float fee;

    };
    int seat[MAX_BUSES] = {40,40,40,40,40};   
    int seat_from_file[MAX_BUSES];

    struct Buses *bus;               
    struct Passenger *passenger;    

    struct Buses buses[MAX_BUSES] = {{0,"laxmisangam travels","10:00","16:00","kochi","MUMBAI",2,400},
                                    {1,"omm buses","15:00","23:00","kochi","AGRA",3,200},              
                                    {2,"mukund travels","09:00","16:00","kochi","VISAKHAPATNAM",1,200},           
                                    {3,"merry holidays","18:00","22:00","kochi","HYDERABAD",1,100},              
                                    {4,"ragushyam travels","11:00","00:00","kochi","AMRITSAR",4,500}};              

    
    struct Passenger pasngr;    
    struct Passenger buff;        
    buff.ticket_number = 0;

    if(fopen(SEAT_BIN_FILE,"r+b")==NULL){
        file_ptr2 = fopen(SEAT_BIN_FILE,"w+b");
        printf("created SEATS.bin file\n");
        fclose(file_ptr2);
    }

    do{
        file_ptr2 = fopen(SEAT_BIN_FILE,"r+b");  
        if (fgetc(file_ptr2)==EOF){  
            printf("file empty...seats were reset\n");
            file_ptr2 = fopen(SEAT_BIN_FILE,"wb+");           
            printf("=============================================================\n");
            for (int a = 0;a<MAX_BUSES;a++){ 
                fwrite(&seat[a],sizeof(int),1,file_ptr2); 
                printf("bus %d seats->%d\n",a,seat[a]);
            }
            printf("==============================================================\n");
            fclose(file_ptr2);           
        }
        else{
        file_ptr2 = fopen(SEAT_BIN_FILE,"rb+");  
        printf("successfully read bus seat data\n");
        printf("===================================================================\n");
        for(int a=0;a<MAX_BUSES;a++){
            fread(&seat_from_file[a],sizeof(int),1,file_ptr2);
            printf("bus %d seats-> %d\n",a, seat_from_file[a]);
            seat[a]= seat_from_file[a];
        }
        printf("===================================================================\n");
        fclose(file_ptr2);
        }

        printf("===============WELCOME TO CGU'S BUS MANAGEMENT SYSTEM================\n"); 
        printf("PRESS 0 TO EXIT\n");
        printf("PRESS 1 FOR BUS ENQUIRY\n");
        printf("PRESS 2 FOR CHECKING RESERVATION\n");
        printf("PRESS 3 FOR TICKET BOOKING\n");
        printf("PRESS 4 FOR CANCELLATION OF BOOKING\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d",&desc);

        if (desc == 1){
            printf("========================BUS ENQUIRY============================\n");
            printf("ENTER THE BUS NUMBER YOU WANT TO ENQUIRE: ");
            scanf("%d",&bus_number);                         
            for(int a = 0 ;a<MAX_BUSES;a++){                 
                if (buses[a].Bus_num == bus_number){
                    bus = &buses[a];                       
                    bus_found = 1;                        
                }

            }
            if(bus_found){               
                printf("=====================BUS DETAILS===========================\n");     
                printf("BUS NUMBER -> %d\n",bus->Bus_num);
                printf("BUS NAME IS -> %s\n",bus->Bus_name);
                printf("BUS WILL DEPART IN -> %s HOURS\n",bus->Depart_time);
                printf("BUS WILL ARRIVE TO DESTINATION BY -> %s HOURS\n",bus->Arrival_time);
                printf("BUS WILL DEPART FROM -> %s\n",bus->departure);
                printf("BUS'S FINAL DESTINATION IS -> %s\n",bus->destination);
                printf("IT WILL TAKE -> %d DAYS\n",bus->days);
                printf("THE PRICE OF THE RIDE WILL BE-> %f\n",bus->fare);
                printf("============================================================\n");
                printf("PRESS 1 TO CONTINUE---->\n");
                scanf("%d",&cont);
                bus_found = 0;                              
            }
            else{
                printf("============================================================\n");
                printf("BUS NOT FOUND\n");
                printf("============================================================\n");
            }
        }
        
        else if(desc ==3){
            file_ptr = fopen(PASSENGERS_BINARY_FILE,"a+b"); 
            if (file_ptr == NULL){                      
                printf("unable to initialize or create file\n");
            }
            else{
                passenger = &pasngr;           
                printf("===============WELCOME TO RESERVATION SYSTEM===============\n");
                printf("PLEASE ENTER DESTINATION->\n");
                printf("ENTER 0 IF MUMBAI\n");
                printf("ENTER 1 IF AGRA\n");
                printf("ENTER 2 IF VISAKHAPATNAM\n");
                printf("ENTER 3 IF HYDERABAD\n");
                printf("ENTER 4 IF AMRITSAR\n");
                printf("ENTER YOUR CHOICE->\n");
                scanf("%d",&place);
                if(place == 0 && seat[0] != 0){  
                    strcpy(passenger -> destination,"MUMBAI"); 
                    bus = &buses[0];                       
                }
                else if(place == 1 && seat[1] != 0){
                    strcpy(passenger -> destination,"AGRA");
                    bus = &buses[1];
                }
                else if(place == 2 && seat[2] != 0){
                    strcpy(passenger -> destination,"VISAKHAPATNAM");
                    bus = &buses[2];
                }
                else if(place == 3 && seat[3] != 0){
                    strcpy(passenger-> destination,"HYDERABAD");
                    bus = &buses[3];
                }
                else if(place == 4 && seat[4] != 0){
                    strcpy(passenger -> destination,"AMRITSAR");
                    bus = &buses[4];
                }
                else{
                    printf("========================================================\n");
                    printf("SEATS ARE NOT AVAILABLE FOR THE PREFFERED JOURNEY\n");
                    printf("========================================================\n");
                    printf("ENTER 1 TO CONTINUE: ");
                    scanf("%d",&cont);
                    continue;
                }

                printf("PLEASE ENTER NAME-> ");          
                getchar();                              
                gets(passenger->passenger_name);       
                printf("PLEASE ENTER GENDER->\n");
                printf("PRESS 1 IF YOU ARE A MALE\n");
                printf("PRESS 2 IF YOU ARE A FEMALE\n");
                printf("PRESS 3 FOR OTHER\n");
                scanf("%d",&desc2);
                if (desc2 == 1){
                    strcpy(passenger->Gender,"MALE");
                    passenger->fee = bus->fare;
                }
                else if(desc2 == 2){
                    strcpy(passenger->Gender,"FEMALE");
                    printf("10percent DISCOUNT WILL BE APPLIED ON PAYMENT\n");
                    passenger->fee = bus->fare - (10.0/100.0)*(bus->fare); 
                }
                else{
                    strcpy(passenger->Gender,"OTHER");
                    passenger->fee = bus->fare;
                }
                printf("ENTER AGE->");
                scanf("%d",&passenger->age);
                if(passenger->age <= 5){
                    printf("CHILDREN BELOW 5 YEAR OF AGE CAN RIDE FOR FREE\n");
                    passenger->fee = 0.0;
                }

                printf("IS THE PERSON DIVYANGJAN?\n");
                printf("PRESS 1 FOR YES\n");
                printf("PRESS 2 FOR NO\n");
                scanf("%d",&desc2);
                if(desc2 == 1){
                    printf("DIVYANGJAN CAN RIDE FOR FREE\n");
                    strcpy(passenger -> divyangjan,"YES");
                    passenger -> fee = 0;
                }
                else{
                    strcpy(passenger -> divyangjan,"NO");
                    
                }

                printf("ENTER YOUR MOBILE NUMBER:\n");
                scanf("%ld",&passenger->mobile_num);

                while(fread(&buff,sizeof(struct Passenger),1,file_ptr)){
                    ticket_num = buff.ticket_number; 
                    
                }
                
                passenger->ticket_number = ticket_num + 1;
                printf("TICKET NUMBER IS %d\n",(passenger->ticket_number));   
                fwrite(passenger,sizeof(struct Passenger),1,file_ptr);  
                ticket_num = 0;                         
                fclose(file_ptr);

                printf("TOTAL FEE IS: %f\n",passenger->fee);
                seat[bus->Bus_num] = seat[bus->Bus_num]-1;  
                file_ptr2 = fopen(SEAT_BIN_FILE,"w+b");
                for (int a = 0;a<MAX_BUSES;a++){
                    fwrite(&seat[a],sizeof(int),1,file_ptr2);
                }
                fclose(file_ptr2);      
                printf("ENTER 1 TO CONTINUE....\n");
                scanf("%d",&cont); 
                
            }
        }

        else if(desc == 2){
            printf("===================CHECK YOUR RESERVATION=====================\n");
            printf("PLEASE ENTER YOUR TICKET NUMBER: ");
            scanf("%d",&inp_ticket_num);
            file_ptr = fopen(PASSENGERS_BINARY_FILE,"r+");
            if (file_ptr == NULL){
                printf("COULD NOT OPEN FILE\n");
            }
            else{
       
                while(fread(&buff,sizeof(struct Passenger),1,file_ptr)){
                    if(buff.ticket_number == inp_ticket_num){    
                        for(int a = 0;a<MAX_BUSES;a++){
                            if(strcmp(buses[a].destination,buff.destination)==0){
                                bus = &buses[a];
                                bus_found = 1;
                            }
                        }
                        printf("NAME: %s\n",buff.passenger_name);
                        printf("AGE: %d\n",buff.age);
                        printf("GENDER: %s\n",buff.Gender);
                        printf("DESTINATION: %s\n",buff.destination);
                        printf("DIVYANGJAN?: %s\n",buff.divyangjan);
                        printf("MOBILE NUMBER: %ld\n",buff.mobile_num);
                        printf("FEE: %f\n",buff.fee);
                        printf("BUS: %s\n",bus ->Bus_name);
                        printf("DEPART TIME: %s\n",bus->Depart_time);
                        printf("ARRIVAL TIME: %s\n",bus->Arrival_time);
                        printf("NUMBER OF DAYS NEEDED TO REACH DESTINATION: %d\n",bus->days);

                    }
                }
                if (! bus_found){
                    printf("TICKET NUMBER NOT IN FILE\n");
                }
                bus_found = 0;  

                fclose(file_ptr);
                printf("ENTER 1 TO CONTINUE....\n");
                scanf("%d",&cont);
            }
        }

        else if(desc == 4){
            printf("================CANCELLING YOUR RESERVATION===================\n");
            printf("PLEASE ENTER YOUR TICKET NUMBER: ");
            scanf("%d",&inp_ticket_num);
            printf("PLEASE ENTER YOUR MOBILE NUMBER: ");
            scanf("%ld",&input_mobile_number);
            file_ptr = fopen(PASSENGERS_BINARY_FILE,"r+b");
            file_tmp_ptr = fopen(PASSENGERS_TEMP_FILE,"a+b");
            if (file_tmp_ptr ==NULL || file_ptr == NULL){
                printf("FILE COULD NOT BE OPENED\n");
            }
            else{
                while(fread(&buff,sizeof(struct Passenger),1,file_ptr)){                  
                    if((buff.ticket_number == inp_ticket_num) && (buff.mobile_num == input_mobile_number)){
                        ticket_found = 1;
                        printf("REMOVED DATA SUCCESSFULLY\n");
                        for(int a = 0;a<MAX_BUSES;a++){
                           if (strcmp(buses[a].destination, buff.destination) == 0){
                            bus = &buses[a];
                            }
                        }
                        seat[bus->Bus_num] = seat[bus->Bus_num] + 1;
                    }

                    else{
                        fwrite(&buff,sizeof(struct Passenger),1,file_tmp_ptr);
                        }
                }

                if (! ticket_found){
                    printf("TICKET OR MOBILE NUMBER NOT FOUND OR LINKED!!!\n");
                }     
                ticket_found = 0;     

                file_ptr2 = fopen(SEAT_BIN_FILE,"w+b");
                for (int a = 0;a<MAX_BUSES;a++){
                    fwrite(&seat[a],sizeof(int),1,file_ptr2);
                }
                fclose(file_ptr2); 
                fclose(file_ptr);
                fclose(file_tmp_ptr);
                remove(PASSENGERS_BINARY_FILE);           
                rename(PASSENGERS_TEMP_FILE,PASSENGERS_BINARY_FILE); 
            }
            printf("PRESS 1 TO CONTINUE....\n");
            scanf("%d",&cont);


        }else if(desc != 0){
            printf("YOU ENTERD THE WRONG OPTION PLEASE RETRY\n");
            printf("ENTER 1 TO CONTINUE: ");
            scanf("%d",&cont);
        }

    }
    
    while (desc !=0);
    printf("BYE\n");
    return 0;
}
//--------------------------------EOF--------------------------------