//Hans Joseph R. Legaspi | 2nd - Year BSCS | VSU Baybay |

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

typedef struct _studentRecord{
    char* StudentID;
    char* Surname;
    char* FirstName;
    char* BirthDate;
    char* Gender;
} * STUDENT;

STUDENT createStudent(char* stID, char* sur, char* fir, char* bd, char* gen){
    STUDENT temp = malloc(5*sizeof(struct _studentRecord));
    temp->StudentID = malloc(10*sizeof(char));
    temp->Surname = malloc(51*sizeof(char));
    temp->FirstName = malloc(51*sizeof(char));
    temp->BirthDate = malloc(10*sizeof(char));
    temp->Gender = malloc(6*sizeof(char));

    strcpy(temp->StudentID, stID);
    strcpy(temp->Surname, sur);
    strcpy(temp->FirstName, fir);
    strcpy(temp->BirthDate, bd);
    strcpy(temp->Gender, gen);

    return temp;
}

STUDENT changeStudent(STUDENT student, char* nstID, char* nsur, char* nfir, char* nbd, char* ngen){
    free(student);

    student = malloc(5*sizeof(struct _studentRecord));
    student->StudentID = malloc(10*sizeof(char));
    student->Surname = malloc(51*sizeof(char));
    student->FirstName = malloc(51*sizeof(char));
    student->BirthDate = malloc(10*sizeof(char));
    student->Gender = malloc(6*sizeof(char));

    strcpy(student->StudentID, nstID);
    strcpy(student->Surname, nsur);
    strcpy(student->FirstName, nfir);
    strcpy(student->BirthDate, nbd);
    strcpy(student->Gender, ngen);

    return student;
}

void createFile(char** fileRecord);
void openFile(char** fileRecord);
void deleteFile(char** fileRecord);
void allocateFileRecord(char** fileRecord);
void renameFile(char** fileRecord);
void saveFile(char** fileRecord);
void captl(char* n, int size);
void line();
void add(STUDENT* student);
void edit(STUDENT* student);
void manageData();
void s0rt(STUDENT* student);
void save(STUDENT* student);
void delet3(STUDENT* student, int* testFile);
int allocateStudent(STUDENT* student);
void birthMonthNameSort(STUDENT* student, int n);
void birthYearNameSort(STUDENT* student, int n);
void firstNameSort(STUDENT* student, int n);
void surnameSort(STUDENT* student, int n);
void studentIDsort(STUDENT* student, int n);
int filter(char* filterNMCtrl, char* filterCharCtrl);

char folder[7] = "!Files\\";
char fileName[100] = "sampleFile";
char fileTemp[100] = "sampleFile";
char extension[5] = ".txt";
int fileRecNum = 0;
int ctrl = 0;
int saveRecord = 0;
int createCtr = 0;

int main(){
	system("cls");
    strcpy(fileName, folder);
    strcat(fileName, fileTemp);
	strcat(fileName, extension);
	char** fileRecord = malloc(100*sizeof(char*));
	allocateFileRecord(fileRecord);
	int ext = 0;
	while(ext == 0){
		printf("Active File: [ %s ]\n", fileTemp);
		printf("[1]Create File   [2]Open existing File   [3]Delete File   [4]Rename File   [5]Manage Data  [6]Exit\n");
		char cn = getch();
		switch(toupper(cn)){
			case '1' : createFile(fileRecord);
				break;
			case '2' : openFile(fileRecord);
				break;
			case '3' : deleteFile(fileRecord);
				break;
			case '4' : renameFile(fileRecord);
				break;
			case '5' : printf("\n");
                manageData();
                break;
			case '6' : ext = 1;
				free(fileRecord);
				break;
			default : system("cls");
                printf("Please select properly!\n\n");
				break;
		}
	}

	return 0;
}

void allocateFileRecord(char** fileRecord){
	fileRecNum = 0;
	FILE * fileAllocate = fopen("!Files\\(FileRecord)!@#!unique.txt", "r");
	while(!feof(fileAllocate)){
		fileRecord[fileRecNum] = malloc(100*sizeof(char));
		char* temp = malloc(100*sizeof(char));
		fgets(temp, 100, fileAllocate);
		char* temp2 = strtok(temp, "\n");
		strcpy(fileRecord[fileRecNum], temp2);
		fileRecNum++;
	}
	fclose(fileAllocate);
}

void createFile(char** fileRecord){
	char* tempName = malloc(100*sizeof(char));
	printf("\n(choose carefully, once finished, you can't edit this.)\n");
    printf("Name of file (Only letters are allowed) : ");
    if(createCtr == 0){
        scanf("%[^\n]", tempName);
        createCtr = 1;
    }else{
        char tempCF;
        scanf("%c", &tempCF);
        scanf("%[^\n]", tempName);
    }
	for(int i = 0; i < fileRecNum; i++){
		if(strcmp(tempName, fileRecord[i]) == 0){
			system("cls");
			printf("\nThe file already exist!\n\n");
			free(tempName);
			return;
		}
	}
    strcpy(fileName, folder);
    strcat(fileName, tempName);
    strcpy(fileTemp, tempName);
	free(tempName);
	FILE * fileCreate = fopen("!Files\\(FileRecord)!@#!unique.txt", "a");
	fprintf(fileCreate, "\n%s", fileTemp);
	fclose(fileCreate);

	strcat(fileName, extension);
	FILE * createFile = fopen(fileName, "w");
	fclose(createFile);
	allocateFileRecord(fileRecord);
	system("cls");
	printf("\nSuccessfully created the file.\n\n");
}

void openFile(char** fileRecord){
	printf("\nFILE(S)\n");
	printf("------------------------------\n");
	for(int i = 0; i < fileRecNum; i++){
		printf("[%d] %s\n", (i+1), fileRecord[i]);
	}
	printf("\n------------------------------\n");
	int nF;
	checkInput:
        printf("\nSelect file number you want to open: ");
        while(scanf("%d",&nF) != 1)
        {
            printf("\nPlease select properly!\n");
            printf("\nSelect file number you want to open: ");
            while(getchar() != '\n');
        }
    if(nF <= 0 || nF > fileRecNum){
        printf("\nPlease select properly!\n");
        goto checkInput;
    }
    strcpy(fileName, folder);
    strcat(fileName, fileRecord[nF-1]);
    strcpy(fileTemp, fileRecord[nF-1]);
    strcat(fileName, extension);
    system("cls");
    printf("\nSuccessfully opened the file.\n\n");
}
void deleteFile(char** fileRecord){
	printf("\nFILE(S)\n");
	printf("------------------------------\n");
	for(int i = 0; i < fileRecNum; i++){
		printf("[%d] %s\n", (i+1), fileRecord[i]);
	}
	printf("\n------------------------------\n");

	int nF;
	checkInput:
        printf("\nSelect file number you want to delete: ");
        while(scanf("%d",&nF) != 1)
        {
            printf("\nPlease select properly!\n");
            printf("\nSelect file number you want to delete: ");
            while(getchar() != '\n');
        }
    if(nF <= 0 || nF > fileRecNum){
        printf("\nPlease select properly!\n");
        goto checkInput;
    }else if(nF == 1){
    	system("cls");
    	printf("\nThis file is restricted and can't be deleted!\n\n");
        return;
    }
    int conTemp = 0;
    printf("\nAre you sure you want to delete this file? [ Y | N ]\n");
    char confirmation = getch();
    while(conTemp == 0){
    	switch(toupper(confirmation)){
    		case 'Y' : conTemp = 1;
    			break;
    		case 'N' : system("cls");
    			printf("\nFile deletion canceled.\n\n");
    			return;
    			break;
    		default : printf("Please select properly!\n");
    			break;
    	}
    }

    char removeTemp[100];
    strcpy(removeTemp, fileRecord[nF-1]);
    if(strcmp(removeTemp, fileTemp) == 0){
    	strcpy(fileTemp, fileRecord[0]);
        strcpy(fileName, folder);
    	strcat(fileName, fileTemp);
    	strcat(fileName, extension);
    }
    char* tempR = malloc(100*sizeof(char));
    strcpy(tempR, removeTemp);
    strcpy(removeTemp, folder);
    strcat(removeTemp, tempR);
    strcat(removeTemp, extension);
    remove(removeTemp);
    free(tempR);

    int i = nF-1;
    if(i == (fileRecNum-1)){
    	fileRecord[i] = NULL;
    	fileRecNum--;
    }else{
    	while(i < (fileRecNum-1)){
	        fileRecord[i] = fileRecord[i+1];
	        i++;
	    }
	    fileRecord[i] = NULL;
    	fileRecNum--;
    }

    saveFile(fileRecord);
    system("cls");
    printf("\nSuccessfully deleted the file.\n\n");
}
void renameFile(char** fileRecord){
	printf("\nFILE(S)\n");
	printf("------------------------------\n");
	for(int i = 0; i < fileRecNum; i++){
		printf("[%d] %s\n", (i+1), fileRecord[i]);
	}
	printf("\n------------------------------\n");

	int nRF;
	checkInput:
        printf("\nSelect file number you want to rename: ");
        while(scanf("%d",&nRF) != 1)
        {
            printf("\nPlease select properly!\n");
            printf("\nSelect file number you want to rename: ");
            while(getchar() != '\n');
        }
    if(nRF <= 0 || nRF > fileRecNum){
        printf("\nPlease select properly!\n");
        goto checkInput;
    }else if(nRF == 1){
        system("cls");
        printf("\nThis file is restricted and can't be renamed!\n\n");
        return;
    }
    char* nFile = malloc(100*sizeof(char));
    char* currentFile = malloc(100*sizeof(char));
    char* newFile = malloc(100*sizeof(char));
    char renameTemp;
    printf("%-14s%-23s%s\n", " ", "Current", "New");
    printf("%-12s:%-23s: ", "Name of file: ", fileRecord[nRF-1]);
    scanf("%c", &renameTemp);
    scanf("%[^\n]", nFile);

    char* tempRR = malloc(100*sizeof(char));
    char* tempRR2 = malloc(100*sizeof(char));
    strcpy(tempRR, fileRecord[nRF-1]);
    strcpy(currentFile, folder);
    strcat(currentFile, tempRR);
    strcat(currentFile, extension);

    strcpy(tempRR2, nFile);
    strcpy(newFile, folder);
    strcat(newFile, tempRR2);
    strcat(newFile, extension);

    rename(currentFile, newFile);

    free(tempRR);
    free(tempRR2);

    if(strcmp(fileRecord[nRF-1], fileTemp) == 0){
    	strcpy(fileRecord[nRF-1], nFile);
    	strcpy(fileTemp, fileRecord[nRF-1]);
        strcpy(fileName, folder);
    	strcat(fileName, fileTemp);
    	strcat(fileName, extension);
    }else{
    	strcpy(fileRecord[nRF-1], nFile);
    }
    free(nFile);
    free(currentFile);
    free(newFile);
    saveFile(fileRecord);
    system("cls");
    printf("\nSuccessfully edited the file\n\n");
}

void saveFile(char** fileRecord){
	FILE * fileRecordSave = fopen("!Files\\(FileRecord)!@#!unique.txt", "w");

    int ncnc = 0;
    while(ncnc < fileRecNum){
        if(ncnc == (fileRecNum-1)){
            fprintf(fileRecordSave, "%s", fileRecord[ncnc]);
            ncnc++;
        }else{
            fprintf(fileRecordSave, "%s\n", fileRecord[ncnc]);
            ncnc++;
        }
    }
    fclose(fileRecordSave);
}

int allocateStudent(STUDENT* student){
    ctrl = 0;
    FILE * fileTemp = fopen(fileName, "r");
    fseek(fileTemp, 0L, SEEK_END);
    int fileCheck = ftell(fileTemp);
    if(fileCheck == 0){
        fclose(fileTemp);
        return 0;
    }
    fclose(fileTemp);
    FILE * fileAllocate = fopen(fileName, "r");
    while(!feof(fileAllocate)){
        char* stdID = malloc(10*sizeof(char));
        char* sur = malloc(100*sizeof(char));
        char* fir = malloc(100*sizeof(char));
        char* bd = malloc(10*sizeof(char));
        char* gen = malloc(10*sizeof(char));

        char* temp = malloc(200*sizeof(char));
        fgets(temp, 200, fileAllocate);
        char* temp2 = strtok(temp, "\t");
        strcpy(stdID, temp2);
        temp2 = strtok(NULL, "\t");
        strcpy(sur, temp2);
        temp2 = strtok(NULL, "\t");
        strcpy(fir, temp2);
        temp2 = strtok(NULL, "\t");
        strcpy(bd, temp2);
        temp2 = strtok(NULL, "\n");
        strcpy(gen, temp2);

        student[ctrl] = createStudent(stdID, sur, fir, bd, gen);

        ctrl++;

        free(stdID);
        free(sur);
        free(fir);
        free(bd);
        free(gen);
        free(temp);
    }
    fclose(fileAllocate);
    return 1;
}

void manageData(){
	system("cls");
    STUDENT* student = malloc(100*sizeof(struct _studentRecord));
    int testFile = allocateStudent(student);
    int ext1 = 0;
    int filterNum = 0;
    char* filterNMCtrl = malloc(10*sizeof(char));
    char filterCharCtrl = ' ';
    while(ext1 == 0){
    	int tempNumfilter = 0;
        printf("Active File: [%s]\n", fileTemp);
        line();
        printf("Rec\tStud-ID\t\tSurname\t\tFirstName\t\tB-Date\t\tSex\n");
        printf("   \t    \t\t     \t\t    \t\t\t(MM/DD/YYYY)\n");
        line();

        if(filterNum == 0){
        	if(testFile == 0){
	            printf("No Data to show!\n");
	        }else{
	            for(int i = 0; i < ctrl; i++){
	                printf("%d\t%-16s%-16s%-23s%-17s%-5s\n", (i+1), student[i]->StudentID,
		                                                student[i]->Surname,
		                                                student[i]->FirstName,
		                                                student[i]->BirthDate,
		                                                student[i]->Gender);
	            }
	        }
        }else if(filterNum == 1){
            for(int i = 0; i < ctrl; i++){
                char surTemp[100];
                strcpy(surTemp, student[i]->Surname);
                if(surTemp[0] == filterCharCtrl){
                    tempNumfilter = 1;
                }
            }
            if(tempNumfilter == 0){
                printf("No Data to show!\n");
            }else{
                char surTemp[100];
                for(int i = 0; i < ctrl; i++){
                    strcpy(surTemp, student[i]->Surname);
                    if(surTemp[0] == filterCharCtrl){
                         printf("%d\t%-16s%-16s%-23s%-17s%-5s\n", (i+1), student[i]->StudentID,
                                                                    student[i]->Surname,
                                                                    student[i]->FirstName,
                                                                    student[i]->BirthDate,
                                                                    student[i]->Gender);
                    }

                }
            }

        }else if(filterNum == 2){
            for(int i = 0; i < ctrl; i++){
                char surTemp[100];
                strcpy(surTemp, student[i]->FirstName);
                if(surTemp[0] == filterCharCtrl){
                    tempNumfilter = 1;
                }
            }
            if(tempNumfilter == 0){
                printf("No Data to show!\n");
            }else{
                char surTemp[100];
                for(int i = 0; i < ctrl; i++){
                    strcpy(surTemp, student[i]->FirstName);
                    if(surTemp[0] == filterCharCtrl){
                         printf("%d\t%-16s%-16s%-23s%-17s%-5s\n", (i+1), student[i]->StudentID,
                                                                    student[i]->Surname,
                                                                    student[i]->FirstName,
                                                                    student[i]->BirthDate,
                                                                    student[i]->Gender);
                    }

                }
            }
            
        }else if(filterNum == 3){
            char* surTemp = malloc(10*sizeof(char));
            for(int i = 0; i < ctrl; i++){
                surTemp = student[i]->BirthDate;
                char* yearTemp = malloc(5*sizeof(char));
                *yearTemp = surTemp[6];
                *(yearTemp+1) = surTemp[7];
                *(yearTemp+2) = surTemp[8];
                *(yearTemp+3) = surTemp[9];
                if(strcmp(yearTemp, filterNMCtrl) == 0){
                    printf("%d\t%-16s%-16s%-23s%-17s%-5s\n", (i+1), student[i]->StudentID,
                                                                    student[i]->Surname,
                                                                    student[i]->FirstName,
                                                                    student[i]->BirthDate,
                                                                    student[i]->Gender);
                    tempNumfilter = 1;
                }
                free(yearTemp);
            }
            if(tempNumfilter == 0){
                printf("No Data to show!\n");
            }
            free(surTemp);
            
        }else if(filterNum == 4){
            char* surTemp = malloc(10*sizeof(char));
            for(int i = 0; i < ctrl; i++){
                surTemp = student[i]->BirthDate;
                char* monthTemp = malloc(3*sizeof(char));
                *monthTemp = surTemp[0];
                *(monthTemp+1) = surTemp[1];
                if(strcmp(monthTemp, filterNMCtrl) == 0){
                    printf("%d\t%-16s%-16s%-23s%-17s%-5s\n", (i+1), student[i]->StudentID,
                                                                    student[i]->Surname,
                                                                    student[i]->FirstName,
                                                                    student[i]->BirthDate,
                                                                    student[i]->Gender);
                    tempNumfilter = 1;
                }
                free(monthTemp);
            }
            if(tempNumfilter == 0){
                printf("No Data to show!\n");
            }
            free(surTemp);
            
        }
        else if(filterNum == 5){
        	char* tempFilter = "MALE";
        	for(int i = 0; i < ctrl; i++){
        		if(strcmp(student[i]->Gender, tempFilter) == 0){
        			tempNumfilter = 1;
        		}
        	}
        	if(tempNumfilter == 0){
        		printf("No Data to show!\n");
        	}else{
	            for(int i = 0; i < ctrl; i++){
	            	if(strcmp(student[i]->Gender, tempFilter) == 0){
	            		 printf("%d\t%-16s%-16s%-23s%-17s%-5s\n", (i+1), student[i]->StudentID,
					                                                student[i]->Surname,
					                                                student[i]->FirstName,
					                                                student[i]->BirthDate,
					                                                student[i]->Gender);
	            	}

	            }
	        }
            free(tempFilter);
        }else if(filterNum == 6){
        	char* tempFilter = "FEMALE";
        	for(int i = 0; i < ctrl; i++){
        		if(strcmp(student[i]->Gender, tempFilter) == 0){
        			tempNumfilter = 1;
        		}
        	}
        	if(tempNumfilter == 0){
        		printf("No Data to show!\n");
        	}else{
	            for(int i = 0; i < ctrl; i++){
	            	if(strcmp(student[i]->Gender, tempFilter) == 0){
	            		 printf("%d\t%-16s%-16s%-23s%-17s%-5s\n", (i+1), student[i]->StudentID,
					                                                student[i]->Surname,
					                                                student[i]->FirstName,
					                                                student[i]->BirthDate,
					                                                student[i]->Gender);
	            	}

	            }
	        }
            free(tempFilter);
        }else if(filterNum == 7){
        	char* tempFilter = "MALE";
        	char* tempFilter2 = "FEMALE";
        	for(int i = 0; i < ctrl; i++){
        		if((strcmp(student[i]->Gender, tempFilter) != 0) && (strcmp(student[i]->Gender, tempFilter2) != 0)){
        			tempNumfilter = 1;
        		}
        	}
        	if(tempNumfilter == 0){
        		printf("No Data to show!\n");
        	}else{
	            for(int i = 0; i < ctrl; i++){
	            	if((strcmp(student[i]->Gender, tempFilter) != 0) && (strcmp(student[i]->Gender, tempFilter2) != 0)){
	            		 printf("%d\t%-16s%-16s%-23s%-17s%-5s\n", (i+1), student[i]->StudentID,
					                                                student[i]->Surname,
					                                                student[i]->FirstName,
					                                                student[i]->BirthDate,
					                                                student[i]->Gender);
	            	}

	            }
	        }
            free(tempFilter);
            free(tempFilter2);
        }

        line();
        printf("[A]Add  [E]Edit  [D]Delete  [S]Sort  [F]Filter  [V]Save [X]Exit\n");
        char ctr2 = getch();
        switch(toupper(ctr2)){
            case 'A': printf("\n");
            	if(filterNum != 0){
            		system("cls");
            		printf("\nYou must filter the gender to all before adding.\n\n");
            	}else{
            		add(student);
	                saveRecord = 1;
	                testFile = 1;
            	}
                break;
            case 'E': printf("\n");
            	if(filterNum != 0){
            		system("cls");
            		printf("\nYou must filter the gender to all before editing.\n\n");
            	}else{
            		edit(student);
                	saveRecord = 1;
            	}
                break;
            case 'D': printf("\n");
            	if(filterNum != 0){
            		system("cls");
            		printf("\nYou must filter the gender to all before deleting.\n\n");
            	}else{
            		delet3(student, &testFile);
                	saveRecord = 1;
            	}
                break;
            case 'S': printf("\n");
                s0rt(student);
                saveRecord = 1;
                break;
            case 'F': printf("\n");
                filterNum = filter(filterNMCtrl, &filterCharCtrl);
                break;
            case 'V': printf("\n");
            	if(filterNum != 0){
            		system("cls");
            		printf("\nYou must filter the gender to all before saving.\n\n");
            	}else{
            		save(student);
                	saveRecord = 0;
            	}
                break;
            case 'X':
                if(saveRecord == 1){
                    printf("\nAre you sure to quit without saving the file?[Y/N]\n");
                    int ynTemp = 0;
                    while(ynTemp == 0){
                        char ctr3 = getch();
                        switch(toupper(ctr3)){
                            case 'Y' : ext1 = 1;
                                free(student);
                                ynTemp = 1;
                                saveRecord = 0;
                                free(filterNMCtrl);
                                break;
                            case 'N' : ext1 = 0;
                                ynTemp = 1;
                                break;
                            default : printf("Please select properly!\n");
                                break;
                        }
                    }
                    system("cls");
                }else{
                    ext1 = 1;
                    free(filterNMCtrl);
                    free(student);
                    system("cls");
                }
                printf("\n");
                break;
            default: system("cls");
                printf("\nPlease select properly!\n\n");
                break;
        }
    }
}
int filter(char* filterNMCtrl, char* filterCharCtrl){
    int filterNum = 0;
    int filCtrlNum = 0;
    while(filCtrlNum == 0){
        printf("[A]All  [S]Surname  [F]Firstname [Y]Birth Year  [M]Birth Month  [G]Gender\n");
        while(filCtrlNum == 0){
            char filCtrlCh = getch();
            switch(toupper(filCtrlCh)){
                case 'A': filterNum = 0;
                    filCtrlNum = 1;
                    break;
                case 'S': printf("\n");
                    printf("What first letter of the surname that you only want to show: ");
                    char charFilter1 = getch();
                    charFilter1 = charFilter1-32;
                    *filterCharCtrl = charFilter1;
                    filterNum = 1;
                    filCtrlNum = 1;
                    break;
                case 'F': printf("\n");
                    printf("What first letter of the firstname that you only want to show: ");
                    char charFilter2 = getch();
                    charFilter2 = charFilter2-32;
                    *filterCharCtrl = charFilter2;
                    filterNum = 2;
                    filCtrlNum = 1;
                    break;
                case 'Y': printf("\n");
                    char* charFilter11 = malloc(5*sizeof(char));
                    printf("Year : ");
                    scanf("%s", charFilter11);
                    captl(charFilter11, 5);
                    strcpy(filterNMCtrl, charFilter11);
                    free(charFilter11);
                    filterNum = 3;
                    filCtrlNum = 1;
                    break;
                case 'M': printf("\n");
                    char* charFilter12 = malloc(5*sizeof(char));
                    printf("Month (in numerical | e.g January = 01 , February = 02, October = 10): ");
                    scanf("%s", charFilter12);
                    captl(charFilter12, 5);
                    strcpy(filterNMCtrl, charFilter12);
                    free(charFilter12);
                    filterNum = 4;
                    filCtrlNum = 1;
                    break;
                case 'G': printf("\n");
                    int filChTemp = 0;
                    printf("[1]Male  [2]Female [3]Others\n\n");
                    while(filChTemp == 0){
                        char filCh = getch();
                        switch(toupper(filCh)){
                             case '1': filterNum = 5;
                                filChTemp = 1;
                                break;
                            case '2': filterNum = 6;
                                filChTemp = 1;
                                break;
                            case '3': filterNum = 7;
                                filChTemp = 1;
                                break;
                            default : printf("Please select properly!\n");
                                break;
                        }
                    }
                    filCtrlNum = 1;
                    break;
                default : printf("Please select properly!\n");
                    break;
            }
        }
    }
    system("cls");
    return filterNum;
}
void add(STUDENT* student){
    char temp;
    char* stdID = malloc(10*sizeof(char));
    char* sur = malloc(100*sizeof(char));
    char* fir = malloc(100*sizeof(char));
    char* bd = malloc(10*sizeof(char));
    char* gen = malloc(15*sizeof(char));

    checkAddInput:
        printf("\nInsert Information:\n\n");
        printf("%-14s%-36s%s\n", "", "\tFormat", "Information");
        printf("%-12s:%-36s: ", "Student ID", " [ ##-#-##### ]  (eg. 12-3-45678)");
        scanf("%s", stdID);
    
    for(int i = 0; i < ctrl; i++){
        if(strcmp(stdID, student[i]->StudentID) == 0){
            printf("\nThe Student ID already exist!.\n\n");
            goto checkAddInput;
        }
    }

    printf("%-12s:%-36s: ", "Surname", " [ Must Contain Letters ]");
    scanf("%c", &temp);
    scanf("%[^\n]s", sur);

    printf("%-12s:%-36s: ", "First Name", " [ Must Contain Letters ]");
    scanf("%c", &temp);
    scanf("%[^\n]s", fir);

    printf("%-12s:%-36s: ", "Birth Date", " [ MM/DD/YYYY ]  (eg. 01/23/4567)");
    scanf("%s", bd);

    printf("%-12s:%-36s: ", "Gender", " [ Male | Female | Others ]");
    scanf("%s", gen);

    captl(sur, 100);
    captl(fir, 100);
    captl(gen, 15);

    student[ctrl] = createStudent(stdID, sur, fir, bd, gen);

    ctrl++;

    free(stdID);
    free(sur);
    free(fir);
    free(bd);
    free(gen);
    system("cls");
    printf("Successfully Added\n\n");
}
void captl(char* n, int size){
    for (int i = 0; i < size; i++) {
      if(n[i] >= 'a' && n[i] <= 'z') {
         n[i] = n[i] -32;
      }
   }
}
void edit(STUDENT* student){

    int n;

    checkInput:
        printf("\nEnter Record number to Edit: ");
        while(scanf("%d",&n) != 1)
        {
            printf("\nPlease enter an integer!\n");
            printf("\nEnter Record number to Edit: ");
            while(getchar() != '\n');
        }
    if(n <= 0 || n > ctrl){
        printf("\nPlease select properly!\n");
        goto checkInput;
    }

    char temp;

    char* nstdID = malloc(10*sizeof(char));
    char* nsur = malloc(100*sizeof(char));
    char* nfir = malloc(100*sizeof(char));
    char* nbd = malloc(10*sizeof(char));
    char* ngen = malloc(10*sizeof(char));

    checkEditInput:
        printf("Rec:[%d]\n", n);
        printf("%-14s%-23s%s\n", " ", "Current", "New");
        printf("%-12s:%-23s: ", "Student ID", student[n-1]->StudentID);
        scanf("%s", nstdID);
    
    for(int i = 0; i < ctrl; i++){
        if(i == n-1){
            continue;
        }
        if(strcmp(nstdID, student[i]->StudentID) == 0){
            printf("\nThe Student ID already exist!.\n\n");
            goto checkEditInput;
        }
    }

    printf("%-12s:%-23s: ", "Surname", student[n-1]->Surname);
    scanf("%c", &temp);
    scanf("%[^\n]s", nsur);

    printf("%-12s:%-23s: ", "First Name", student[n-1]->FirstName);
    scanf("%c", &temp);
    scanf("%[^\n]s", nfir);

    printf("%-12s:%-23s: ", "Birth Date", student[n-1]->BirthDate);
    scanf("%s", nbd);

    char* tempGender = student[n-1]->Gender;
    if(toupper(tempGender[0]) == 'M'){
        printf("%-12s:%-23s: ", "Gender", "Male");
        scanf("%s", ngen);
    }else if(toupper(tempGender[0]) == 'F'){
        printf("%-12s:%-23s: ", "Gender", "Female");
        scanf("%s", ngen);
    }else{
    	printf("%-12s:%-23s: ", "Gender", "Others");
        scanf("%s", ngen);
    }

    free(student[n-1]->StudentID);
    free(student[n-1]->Surname);
    free(student[n-1]->FirstName);
    free(student[n-1]->BirthDate);
    free(student[n-1]->Gender);

    captl(nsur, 100);
    captl(nfir, 100);
    captl(ngen, 15);

    student[n-1] = changeStudent(student[n-1], nstdID, nsur, nfir, nbd, ngen);

    free(nstdID);
    free(nsur);
    free(nfir);
    free(nbd);
    free(ngen);
    system("cls");
    printf("Successfully Edited\n\n");
}
void delet3(STUDENT* student, int* testFile){
    int nTemp;
    checkInput:
        printf("\nEnter Record number to Delete: ");
        while(scanf("%d",&nTemp) != 1)
        {
            printf("\nPlease enter an integer!\n");
            printf("\nEnter Record number to Delete: ");
            while(getchar() != '\n');
        }
    if(nTemp <= 0 || nTemp > ctrl){
        printf("\nPlease select properly!\n");
        goto checkInput;
    }
    int i = nTemp-1;
    while(i < ctrl-1){
        student[i] = student[i+1];
        i++;
    }
    student[i] = NULL;
    ctrl--;
    system("cls");
    printf("\nSuccessfully deleted the record.\n\n");
    if(ctrl == 0){
        *testFile = 0;
    }
}
void s0rt(STUDENT* student){
    int extC = 0;
    printf("\n[1]Surname Ascending\t\t\t[7]Birthdate(Month) Ascending\n");
    printf("[2]Surname Descending\t\t\t[8]Birthdate(Month) Descending\n");
    printf("[3]FirstName Ascending\t\t\t[9]Student-ID Ascending\n");
    printf("[4]FirstName Descending\t\t\t[0]Student-ID Descending\n");
    printf("[5]Birthdate(Year) Ascending\n");
    printf("[6]Birthdate(Year) Descending\n\n");

    while(extC == 0){
        char sortSelect = getch();
        switch(toupper(sortSelect)){
            case '1' : surnameSort(student, 0);
                extC = 1;
                break;
            case '2' : surnameSort(student, 1);
                extC = 1;
                break;
            case '3' : firstNameSort(student, 0);
                extC = 1;
                break;
            case '4' : firstNameSort(student, 1);
                extC = 1;
                break;
            case '5' : birthYearNameSort(student, 0);
                extC = 1;
                break;
            case '6' : birthYearNameSort(student, 1);
                extC = 1;
                break;
            case '7' : birthMonthNameSort(student, 0);
                extC = 1;
                break;
            case '8' : birthMonthNameSort(student, 1);
                extC = 1;
                break;
            case '9' : studentIDsort(student, 0);
                extC = 1;
                break;
            case '0' : studentIDsort(student, 1);
                extC = 1;
                break;
            default : printf("\nPlease select properly!\n");
                break;

        }
    }
    system("cls");
}
void surnameSort(STUDENT* student, int n){
    int size = ctrl;
    if(n == 0){
        for(int i=0; i<size; i++){
            for(int j=0; j<size-1-i; j++){
                if(strcmp(student[j]->Surname, student[j+1]->Surname) > 0){
                    STUDENT temp = createStudent(student[j]->StudentID, student[j]->Surname, student[j]->FirstName, student[j]->BirthDate, student[j]->Gender);
                    student[j] = changeStudent(student[j], student[j+1]->StudentID, student[j+1]->Surname, student[j+1]->FirstName, student[j+1]->BirthDate, student[j+1]->Gender);
                    student[j+1] = changeStudent(student[j+1], temp->StudentID, temp->Surname, temp->FirstName, temp->BirthDate, temp->Gender);
                }
            }
        }
    }else{
        for(int i=0; i<size; i++){
            for(int j=0; j<size-1-i; j++){
                if(strcmp(student[j]->Surname, student[j+1]->Surname) < 0){
                    STUDENT temp = createStudent(student[j]->StudentID, student[j]->Surname, student[j]->FirstName, student[j]->BirthDate, student[j]->Gender);
                    student[j] = changeStudent(student[j], student[j+1]->StudentID, student[j+1]->Surname, student[j+1]->FirstName, student[j+1]->BirthDate, student[j+1]->Gender);
                    student[j+1] = changeStudent(student[j+1], temp->StudentID, temp->Surname, temp->FirstName, temp->BirthDate, temp->Gender);
                }
            }
        }
    }
}
void firstNameSort(STUDENT* student, int n){
    int size = ctrl;
    if(n == 0){
        for(int i=0; i<size; i++){
            for(int j=0; j<size-1-i; j++){
                if(strcmp(student[j]->FirstName, student[j+1]->FirstName) > 0){
                    STUDENT temp = createStudent(student[j]->StudentID, student[j]->Surname, student[j]->FirstName, student[j]->BirthDate, student[j]->Gender);
                    student[j] = changeStudent(student[j], student[j+1]->StudentID, student[j+1]->Surname, student[j+1]->FirstName, student[j+1]->BirthDate, student[j+1]->Gender);
                    student[j+1] = changeStudent(student[j+1], temp->StudentID, temp->Surname, temp->FirstName, temp->BirthDate, temp->Gender);
                }
            }
        }
    }else{
        for(int i=0; i<size; i++){
            for(int j=0; j<size-1-i; j++){
                if(strcmp(student[j]->FirstName, student[j+1]->FirstName) < 0){
                    STUDENT temp = createStudent(student[j]->StudentID, student[j]->Surname, student[j]->FirstName, student[j]->BirthDate, student[j]->Gender);
                    student[j] = changeStudent(student[j], student[j+1]->StudentID, student[j+1]->Surname, student[j+1]->FirstName, student[j+1]->BirthDate, student[j+1]->Gender);
                    student[j+1] = changeStudent(student[j+1], temp->StudentID, temp->Surname, temp->FirstName, temp->BirthDate, temp->Gender);
                }
            }
        }
    }
}
void birthYearNameSort(STUDENT* student, int n){
    char* temp1 = malloc(10*sizeof(char));
    char* temp2 = malloc(10*sizeof(char));
    char tempCtr1[8];
    char tempCtr2[8];
    int size = ctrl;
    if(n == 0){
        for(int i=0; i<size; i++){
            for(int j=0; j<size-1-i; j++){
                temp1 = student[j]->BirthDate;
                temp2 = student[j+1]->BirthDate;
                tempCtr1[0] = *(temp1+6);
                tempCtr1[1] = *(temp1+7);
                tempCtr1[2] = *(temp1+8);
                tempCtr1[3] = *(temp1+9);
                tempCtr1[4] = *temp1;
                tempCtr1[5] = *(temp1+1);
                tempCtr1[6] = *(temp1+3);
                tempCtr1[7] = *(temp1+4);
                tempCtr2[0] = *(temp2+6);
                tempCtr2[1] = *(temp2+7);
                tempCtr2[2] = *(temp2+8);
                tempCtr2[3] = *(temp2+9);
                tempCtr2[4] = *temp2;
                tempCtr2[5] = *(temp2+1);
                tempCtr2[6] = *(temp2+3);
                tempCtr2[7] = *(temp2+4);
                if(strcmp(tempCtr1, tempCtr2) > 0){
                    STUDENT temp = createStudent(student[j]->StudentID, student[j]->Surname, student[j]->FirstName, student[j]->BirthDate, student[j]->Gender);
                    student[j] = changeStudent(student[j], student[j+1]->StudentID, student[j+1]->Surname, student[j+1]->FirstName, student[j+1]->BirthDate, student[j+1]->Gender);
                    student[j+1] = changeStudent(student[j+1], temp->StudentID, temp->Surname, temp->FirstName, temp->BirthDate, temp->Gender);
                }
            }
        }
    }else{
        for(int i=0; i<size; i++){
            for(int j=0; j<size-1-i; j++){
                temp1 = student[j]->BirthDate;
                temp2 = student[j+1]->BirthDate;
                tempCtr1[0] = *(temp1+6);
                tempCtr1[1] = *(temp1+7);
                tempCtr1[2] = *(temp1+8);
                tempCtr1[3] = *(temp1+9);
                tempCtr1[4] = *temp1;
                tempCtr1[5] = *(temp1+1);
                tempCtr1[6] = *(temp1+3);
                tempCtr1[7] = *(temp1+4);
                tempCtr2[0] = *(temp2+6);
                tempCtr2[1] = *(temp2+7);
                tempCtr2[2] = *(temp2+8);
                tempCtr2[3] = *(temp2+9);
                tempCtr2[4] = *temp2;
                tempCtr2[5] = *(temp2+1);
                tempCtr2[6] = *(temp2+3);
                tempCtr2[7] = *(temp2+4);
                if(strcmp(tempCtr1, tempCtr2) < 0){
                    STUDENT temp = createStudent(student[j]->StudentID, student[j]->Surname, student[j]->FirstName, student[j]->BirthDate, student[j]->Gender);
                    student[j] = changeStudent(student[j], student[j+1]->StudentID, student[j+1]->Surname, student[j+1]->FirstName, student[j+1]->BirthDate, student[j+1]->Gender);
                    student[j+1] = changeStudent(student[j+1], temp->StudentID, temp->Surname, temp->FirstName, temp->BirthDate, temp->Gender);
                }
            }
        }
    }
    free(temp1);
    free(temp2);
}
void birthMonthNameSort(STUDENT* student, int n){
    char* temp1 = malloc(10*sizeof(char));
    char* temp2 = malloc(10*sizeof(char));
    char tempCtr1[5];
    char tempCtr2[5];
    int size = ctrl;
    if(n == 0){
        for(int i=0; i<size; i++){
            for(int j=0; j<size-1-i; j++){
                temp1 = student[j]->BirthDate;
                temp2 = student[j+1]->BirthDate;
                tempCtr1[0] = *temp1;
                tempCtr1[1] = *(temp1+1);
                tempCtr1[2] = *(temp1+2);
                tempCtr1[3] = *(temp1+3);
                tempCtr1[4] = *(temp1+4);
                tempCtr2[0] = *temp2;
                tempCtr2[1] = *(temp2+1);
                tempCtr2[2] = *(temp2+2);
                tempCtr2[3] = *(temp2+3);
                tempCtr2[4] = *(temp2+4);
                if(strcmp(tempCtr1, tempCtr2) > 0){
                    STUDENT temp = createStudent(student[j]->StudentID, student[j]->Surname, student[j]->FirstName, student[j]->BirthDate, student[j]->Gender);
                    student[j] = changeStudent(student[j], student[j+1]->StudentID, student[j+1]->Surname, student[j+1]->FirstName, student[j+1]->BirthDate, student[j+1]->Gender);
                    student[j+1] = changeStudent(student[j+1], temp->StudentID, temp->Surname, temp->FirstName, temp->BirthDate, temp->Gender);
                }
            }
        }
    }else{
        for(int i=0; i<size; i++){
            for(int j=0; j<size-1-i; j++){
                temp1 = student[j]->BirthDate;
                temp2 = student[j+1]->BirthDate;
                tempCtr1[0] = *temp1;
                tempCtr1[1] = *(temp1+1);
                tempCtr1[2] = *(temp1+2);
                tempCtr1[3] = *(temp1+3);
                tempCtr1[4] = *(temp1+4);
                tempCtr2[0] = *temp2;
                tempCtr2[1] = *(temp2+1);
                tempCtr2[2] = *(temp2+2);
                tempCtr2[3] = *(temp2+3);
                tempCtr2[4] = *(temp2+4);
                if(strcmp(tempCtr1, tempCtr2) < 0){
                    STUDENT temp = createStudent(student[j]->StudentID, student[j]->Surname, student[j]->FirstName, student[j]->BirthDate, student[j]->Gender);
                    student[j] = changeStudent(student[j], student[j+1]->StudentID, student[j+1]->Surname, student[j+1]->FirstName, student[j+1]->BirthDate, student[j+1]->Gender);
                    student[j+1] = changeStudent(student[j+1], temp->StudentID, temp->Surname, temp->FirstName, temp->BirthDate, temp->Gender);
                }
            }
        }
    }
    free(temp1);
    free(temp2);
}
void studentIDsort(STUDENT* student, int n){
    int size = ctrl;
    if(n == 0){
        for(int i=0; i<size; i++){
            for(int j=0; j<size-1-i; j++){
                if(strcmp(student[j]->StudentID, student[j+1]->StudentID) > 0){
                    STUDENT temp = createStudent(student[j]->StudentID, student[j]->Surname, student[j]->FirstName, student[j]->BirthDate, student[j]->Gender);
                    student[j] = changeStudent(student[j], student[j+1]->StudentID, student[j+1]->Surname, student[j+1]->FirstName, student[j+1]->BirthDate, student[j+1]->Gender);
                    student[j+1] = changeStudent(student[j+1], temp->StudentID, temp->Surname, temp->FirstName, temp->BirthDate, temp->Gender);
                }
            }
        }
    }else{
        for(int i=0; i<size; i++){
            for(int j=0; j<size-1-i; j++){
                if(strcmp(student[j]->StudentID, student[j+1]->StudentID) < 0){
                    STUDENT temp = createStudent(student[j]->StudentID, student[j]->Surname, student[j]->FirstName, student[j]->BirthDate, student[j]->Gender);
                    student[j] = changeStudent(student[j], student[j+1]->StudentID, student[j+1]->Surname, student[j+1]->FirstName, student[j+1]->BirthDate, student[j+1]->Gender);
                    student[j+1] = changeStudent(student[j+1], temp->StudentID, temp->Surname, temp->FirstName, temp->BirthDate, temp->Gender);
                }
            }
        }
    }
}
void save(STUDENT* student){
    FILE * fileSave;
    fileSave = fopen(fileName, "w");

    int nCtr = 0;
    while(nCtr < ctrl){
        if(nCtr == (ctrl-1)){
            fprintf(fileSave, "%s\t%s\t%s\t%s\t%s", student[nCtr]->StudentID,
                                                    student[nCtr]->Surname,
                                                    student[nCtr]->FirstName,
                                                    student[nCtr]->BirthDate,
                                                    student[nCtr]->Gender);
            nCtr++;
        }else{
            fprintf(fileSave, "%s\t%s\t%s\t%s\t%s\n", student[nCtr]->StudentID,
                                                    student[nCtr]->Surname,
                                                    student[nCtr]->FirstName,
                                                    student[nCtr]->BirthDate,
                                                    student[nCtr]->Gender);
            nCtr++;
        }
    }

    fclose(fileSave);
    system("cls");
    printf("File saved successfully\n\n");
}

void line(){
    int i = 0;
    while(i < 90){
        printf("-");
        i++;
    }
    printf("\n");
}
