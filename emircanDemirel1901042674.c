#include<Windows.h>
#include<stdio.h>
#include<conio.h> 
#include<string.h>
#include<stdlib.h>

HANDLE hComm;
char PortName[] = "\\\\.\\COM5";
BOOL Status;
DWORD dwEventMask;
char TempChar;
DWORD NoBytesRead;
char SerialBuffer[256];
char lpBuffer[6];

void sendData(char[]);
char receiveData();

int main(){
//Open Communication with SerialPort
	hComm = CreateFile(PortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	
	if(hComm == INVALID_HANDLE_VALUE){
		printf("ERROR! PORT %s CAN'T BE OPENED\n", PortName);
	}
	else{
		printf("PORT %s OPENED..\n",PortName);
	}
//Parameters
	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(hComm, &dcbSerialParams);
	if(Status == FALSE){
		printf("ERROR! GetCommState()\n");
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	
	Status = SetCommState(hComm, &dcbSerialParams);
	
	if(Status == FALSE){
		printf("ERROR! SETTING DCB STRUCTURE\n");
	}
	
	//Set Timeouts
	COMMTIMEOUTS timeouts = {0};
	timeouts.ReadIntervalTimeout = 80;
	timeouts.ReadTotalTimeoutConstant = 80;
	timeouts.ReadTotalTimeoutMultiplier = 20;
	timeouts.WriteTotalTimeoutConstant = 80;
	timeouts.WriteTotalTimeoutMultiplier = 20;
	
	if(SetCommTimeouts(hComm, &timeouts) == FALSE){
		printf("ERROR! SETTING TIMEOUTS\n");
	}
	
	
	printf("## WELCOME TO GTU ARDUINO LAB------------------------------##\n");
	printf("## STUDENT NAME: Emircan Demirel---------------------------##\n");
	printf("## PLEASE SELECT FROM THE FOLLOWING------------------------##\n");
	printf("## MENU :--------------------------------------------------##\n");
	printf("##(1) TURN ON LED ON ARDUINO-------------------------------##\n");
	printf("##(2) TURN OFF LED ON ARDUINO------------------------------##\n");
	printf("##(3) FLASH ARDUINO LED 3 TIMES----------------------------##\n");
	printf("##(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO##\n");
	printf("##(5) BUTTON COUNTER---------------------------------------##\n");
	printf("##(0) EXIT-------------------------------------------------##\n");
	printf("-------------------------------------------------------------\nPLEASE SELECT: ");
	
	while(lpBuffer[0] != '0'){
		fflush(stdin);
		scanf("%c",&lpBuffer[0]);
		
		if(lpBuffer[0] == '0'){
			printf("\n...Program Finished...\n");
		}
		else if(lpBuffer[0] == '1'){
			sendData(lpBuffer);
			printf("LED TURNED ON\n");
			printf("PLEASE SELECT: \n");
		}
		else if(lpBuffer[0] == '2'){
			sendData(lpBuffer);
			printf("LED TURNED OFF\n");
			printf("PLEASE SELECT: \n");
		}
		else if(lpBuffer[0] == '3'){
			sendData(lpBuffer);
			printf("LED FLASH X3\n");
			printf("PLEASE SELECT: \n");
		}
		else if(lpBuffer[0] == '4'){
			sendData(lpBuffer);
			char number[10];
			printf("Input a positive integer: ");
			scanf("%s", number);
			sendData(number);
			receiveData();
			printf("PLEASE SELECT: \n");
		}
		else if(lpBuffer[0] == '5'){
			sendData(lpBuffer);
			while(receiveData() != 'b'){
				if(receiveData() == 'b'){
					break;
				}
			}
			printf("PLEASE SELECT: \n");
		}
		else printf("INVALID OPERATION!!! TRY AGAIN");
	}
	CloseHandle(hComm);
	getch();
	return 0;
}
void sendData(char lpBuffer[]){
	
	DWORD dNoOFBytestoWrite;
	DWORD dNoOFBytesWritten = 0;
	dNoOFBytestoWrite = sizeof(lpBuffer);
	
	Status = WriteFile(hComm, lpBuffer, dNoOFBytestoWrite, &dNoOFBytesWritten, NULL);
	if(Status != TRUE){
		printf("ERROR! %d in Writing to SERIAL PORT", GetLastError());
	}
}
char receiveData(){
	int i=0;
	
	Status = SetCommMask(hComm, EV_RXCHAR);
	if(Status == FALSE){
		printf("ERROR! SETTING CommMask");
	}
	
	Status = WaitCommEvent(hComm, &dwEventMask, NULL);
	if (Status == FALSE){
		printf("ERROR! SETTING WaitCommEvent()");
	}
	
	else{
		do{
			Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
			SerialBuffer[i] = TempChar;
			i++;
		} while (NoBytesRead > 0);
	}
		int j=0;
		for(j = 0; j < i - 1;j++){
			printf("%c",SerialBuffer[j]);
		}
	if(SerialBuffer[0] == 'Q'){
		return 'b';
	}		
}



























