#define BUFFER_SIZE 120
#define INPUT_SIZE 15
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
/************************print func********************/

void PrintResult(MYSQL * a_mySql) {
	MYSQL_RES *result = NULL;
	unsigned int Number_of_Columns = 0;
	unsigned int Number_of_Rows = 0;
	MYSQL_FIELD *field = NULL;
	MYSQL_ROW row;
	result = mysql_store_result(a_mySql); //MYSQL_RES *result;
	if ((result == NULL ) && (mysql_errno(a_mySql) != 0)) {
		fprintf(stderr, "mysql_store_result failed errno: %d Msg: %s\n", mysql_errno(a_mySql), mysql_error(a_mySql)) ;
		mysql_close(a_mySql);
		exit(1);	
	}
	else {
		puts("mysql_store_result succeeded\n");
		getchar();
	}

	if (result == NULL) {
		puts("Result is NULL \n");
	} else {
		Number_of_Columns = mysql_num_fields(result); //unsigned int Number_of_Columns;
		Number_of_Rows = mysql_num_rows(result); //unsigned int Number_of_Rows;
		printf("Number_of_columns: %d Number_of_rows: %d\n", Number_of_Columns, Number_of_Rows);
		printf("|");
		for(int i = 0; i < Number_of_Columns; ++i) {
			field = mysql_fetch_field(result); //MYSQL_FIELD *field;
			printf("%16s |", field->name);
		}
		printf("\n");
		printf("-------------------------------------------------------------------------\n");
		for (int i = 0; i < Number_of_Rows; i++) {
			row = mysql_fetch_row(result); //MYSQL_ROW row;
			printf("|");
			for ( int j = 0; j< Number_of_Columns; ++j) {
				printf("%16s |", row[j]);
			}
			printf("\n");
		}
	}
}

void PrintResultWithoutTable(MYSQL * a_mySql) {
	MYSQL_RES *result = NULL;
	result = mysql_store_result(a_mySql); //MYSQL_RES *result;
	if ((result == NULL ) && (mysql_errno(a_mySql) != 0)) {
		fprintf(stderr, "mysql_store_result failed errno: %d Msg: %s\n", mysql_errno(a_mySql), mysql_error(a_mySql)) ;
		mysql_close(a_mySql);
		exit(1);	
	}
	else {
		puts("mysql_store_result succeeded\n");
		getchar();
	}	
}

/*****************finish print func******************************/



/***********************func******************************/
void AOwnersList(MYSQL * a_mySql) {
	int Retvali = 0;
	Retvali = mysql_query(a_mySql, "SELECT * FROM veterinar.owners"); 
	if (Retvali != 0) {
		fprintf(stderr, "mysql_query failed errno: %d Msg: %s\n", mysql_errno(a_mySql), mysql_error(a_mySql)) ;
		mysql_close(a_mySql);
		exit(1);	
	}
	else {
		puts("mysql_query succeeded\n");
	}
	PrintResult(a_mySql);
}

void BPetsList(MYSQL * a_mySql) {
	int Retvali = 0;
	Retvali = mysql_query(a_mySql, "SELECT pets.number_of_pet, pets.pet_name, pets.type_pet, pets.number_of_owner , owners.first_name FROM pets INNER JOIN owners WHERE pets.number_of_owner = owners.number_of_owner;"); 
	if (Retvali != 0) {
		fprintf(stderr, "mysql_query failed errno: %d Msg: %s\n", mysql_errno(a_mySql), mysql_error(a_mySql)) ;
		mysql_close(a_mySql);
		exit(1);	
	}
	else {
		puts("mysql_query succeeded\n");
	}
	PrintResult(a_mySql);
}

void SendToSqlAndPrintWithoutTable(MYSQL * a_mySql, char * a_string) {
	int Retvali = 0;
	Retvali = mysql_query(a_mySql,a_string); 
	if (Retvali != 0) {
		fprintf(stderr, "mysql_query failed errno: %d Msg: %s\n", mysql_errno(a_mySql), mysql_error(a_mySql)) ;
		mysql_close(a_mySql);
		exit(1);	
	}
	else {
		puts("mysql_query succeeded\n");
	}
	PrintResultWithoutTable(a_mySql);
}

void SendToSqlAndPrint(MYSQL * a_mySql, char * a_string) {
	int Retvali = 0;
	Retvali = mysql_query(a_mySql,a_string); 
	if (Retvali != 0) {
		fprintf(stderr, "mysql_query failed errno: %d Msg: %s\n", mysql_errno(a_mySql), mysql_error(a_mySql)) ;
		mysql_close(a_mySql);
		exit(1);	
	}
	else {
		puts("mysql_query succeeded\n");
	}
	PrintResult(a_mySql);
}


void CAddOwner(MYSQL * a_mySql) {
	char firstName[INPUT_SIZE], lastName[INPUT_SIZE], numberOfOwner[INPUT_SIZE]; 
	char string[BUFFER_SIZE] = "INSERT INTO veterinar.owners(number_of_owner,first_name, last_name) VALUES";
	printf("press first name:");
    scanf("%s", firstName);
    printf("press last name:");
    scanf("%s", lastName);
    printf("press number of owner:");
    scanf("%s", numberOfOwner);
	strcat(string, "(");
	strcat(string, numberOfOwner );
	strcat(string, ",");
	strcat(string, "'");
	strcat(string, firstName);
	strcat(string, "'");
	strcat(string, ",");
	strcat(string, "'");
	strcat(string, lastName);
	strcat(string, "'");
	strcat(string, ")");
	SendToSqlAndPrintWithoutTable(a_mySql, string);
}

void DAddPet(MYSQL * a_mySql) {
	char typePet[INPUT_SIZE], petName[INPUT_SIZE], numberOfPet[INPUT_SIZE], numberOfOwner[INPUT_SIZE]; 
	char string[BUFFER_SIZE] = "INSERT INTO veterinar.pets(number_of_pet,pet_name, type_pet, number_of_owner) VALUES";
	printf("press number pet:");
    scanf("%s", numberOfPet);
    printf("press pet name:");
    scanf("%s", petName);
	printf("press type pet:");
    scanf("%s", typePet);
    printf("press number of owner:");
	scanf("%s", numberOfOwner);
	strcat(string, "(");
	strcat(string, numberOfPet );
	strcat(string, ",");
	strcat(string, "'");
	strcat(string, petName);
	strcat(string, "'");
	strcat(string, ",");
	strcat(string, "'");
	strcat(string, typePet);
	strcat(string, "'");
	strcat(string, ",");
	strcat(string, numberOfOwner);
	strcat(string, ")");
	SendToSqlAndPrintWithoutTable(a_mySql, string);
}

void IUpdateOwner(MYSQL * a_mySql) {
	char firstName[INPUT_SIZE], lastName[INPUT_SIZE], numberOfOwner[INPUT_SIZE]; 
	char string[BUFFER_SIZE] = "UPDATE veterinar.owners set first_name =";
	printf("press first name new:");
    scanf("%s", firstName);
    printf("press last name new:");
    scanf("%s", lastName);
    printf("press number of owner:");
    scanf("%s", numberOfOwner);
	strcat(string, "'");
	strcat(string, firstName);
	strcat(string, "'");
	strcat(string, ",");
	strcat(string, " last_name =");
	strcat(string, "'");
	strcat(string, lastName);
	strcat(string, "'");
	strcat(string, "where number_of_owner = ");
	strcat(string, numberOfOwner);
	SendToSqlAndPrintWithoutTable(a_mySql, string);
}


void JUpdatePet(MYSQL * a_mySql) {
	char typePet[INPUT_SIZE], petName[INPUT_SIZE], numberOfPet[INPUT_SIZE]; 
	char string[BUFFER_SIZE] = "UPDATE veterinar.pets set pet_name =";
	printf("press number pet:");
    scanf("%s", numberOfPet);
    printf("press pet name new:");
    scanf("%s", petName);
	printf("press type pet new:");
    scanf("%s", typePet);

	strcat(string, "'");
	strcat(string, petName);
	strcat(string, "'");

	strcat(string, ", type_pet = ");
	strcat(string, "'");
	strcat(string, typePet);
	strcat(string, "'");
	strcat(string, "where number_of_pet = ");
	strcat(string, numberOfPet);
	SendToSqlAndPrintWithoutTable(a_mySql, string);
}

void GFindOwner(MYSQL * a_mySql) {
	char numberOfOwner[INPUT_SIZE]; 
	char string[BUFFER_SIZE] = "SELECT * from veterinar.owners WHERE number_of_owner =";
	printf("press number owner:");
    scanf("%s", numberOfOwner);
	strcat(string, numberOfOwner);
	SendToSqlAndPrint(a_mySql, string);
}

void HFindPet(MYSQL * a_mySql) {
	char numberOfPet[INPUT_SIZE]; 
	char string[BUFFER_SIZE] = "SELECT * from veterinar.pets WHERE number_of_pet =";
	printf("press number pet:");
    scanf("%s", numberOfPet);
	strcat(string, numberOfPet);
	SendToSqlAndPrint(a_mySql, string);
}

void EDeleteOwner(MYSQL * a_mySql) {
	char numberOfOwner[INPUT_SIZE]; 
	char string[BUFFER_SIZE] = "DELETE from veterinar.owners WHERE number_of_owner =";
	printf("press number owner you want delete:");
    scanf("%s", numberOfOwner);
	strcat(string, numberOfOwner);
	SendToSqlAndPrint(a_mySql, string);
}

void FDeleteOwnere(MYSQL * a_mySql) {
	char numberOfPet[INPUT_SIZE]; 
	char string[BUFFER_SIZE] = "DELETE from veterinar.pets WHERE number_of_pet =";
	printf("press number pet you want delete:");
    scanf("%s", numberOfPet);
	strcat(string, numberOfPet);
	SendToSqlAndPrint(a_mySql, string);
}

void KListOfOwnersAndTheirPetsOrderByNumberOfPets(MYSQL * a_mySql) {
	char numberOfOwner[INPUT_SIZE]; 
	char string[BUFFER_SIZE] = "SELECT * FROM owners JOIN pets ON owners.number_of_owner = pets.number_of_owner HAVING pets.number_of_owner =" ;
	printf("press number owner:");
    scanf("%s", numberOfOwner);
	strcat(string, numberOfOwner);
	SendToSqlAndPrint(a_mySql, string);
}
/**************************finish func*******************************/


/**********************************main*********************************/
int main ()
{
	MYSQL * MySql = NULL ;
	MYSQL * Retval = NULL;
	MYSQL_RES *result = NULL;
	char letter;
	int run = TRUE;
	puts("Starting program");
	MySql = mysql_init(NULL); // MYSQL * MySql ;
	if (MySql == NULL) {
      	fprintf(stderr, "error mysql_init failed\n"); 
		mysql_close(MySql);
  	} else {
		puts("mysql_init succeeded");
	}
	Retval = mysql_real_connect(MySql, "localhost", "magi", "1234", "veterinar", 0 ,NULL,0); //MYSQL * Retval;
  	if (Retval == NULL) {
		fprintf(stderr, "mysql_real_connect failed errno: %d Msg: %s\n", mysql_errno(MySql), mysql_error(MySql)) ;
		mysql_close(MySql);
		exit(1);	
	}
	else {
		puts("mysql_real_connect succeeded\n");
	}
	
	while (run) {
		printf("Choose from the list \n a. Owner’s list. \n b. Pet’s list (with the name of their owner). \n c. Add Owner. \n d. Add Pet. \n e. Delete Owner \n f. Delete Pet. \n g. Find Owner. \n h. Find Pet. \n i. Update Owner. \n j. Update Pet. \n k. list of owners and their pets ordered by number of pets. \n x. exit \n");
		printf("your choice\n");
		scanf("%c", &letter);
		getchar();
		switch (letter) {
		case 'a':
			AOwnersList(MySql);
			break;
		case 'b':
			BPetsList(MySql);
			break;
		case 'c':
			CAddOwner(MySql);
			break;
		case 'd':
			DAddPet(MySql);
			break;
		case 'e':
			EDeleteOwner(MySql); 
			break;
		case 'f':
			FDeleteOwnere(MySql);
			break;
		case 'g':
			GFindOwner(MySql);
			break;
		case 'h':
			HFindPet(MySql);
			break;
		case 'i':
			IUpdateOwner(MySql);
			break;
		case 'j':
			JUpdatePet(MySql);
			break;
		case 'k':
			KListOfOwnersAndTheirPetsOrderByNumberOfPets(MySql);
			break;
		case 'x':
			run = FALSE;
			break;	
		default:
			printf("Your choice is incorrect. Please choose again\n"); 
			break;
		}
	}


	mysql_free_result(result);
	mysql_close(MySql);
	puts("Press enter to terminate");
	/*getchar();*/
	return(0);
}