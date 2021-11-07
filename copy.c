#include <stdio.h>
#include <mysql/mysql.h>
int main ()
{
	MYSQL * MySql = NULL ;
	MYSQL * Retval = NULL;
	MYSQL_RES *result = NULL;
	int Retvali = 0;
	unsigned int Number_of_Columns = 0;
	unsigned int Number_of_Rows = 0;
	MYSQL_FIELD *field = NULL;
	MYSQL_ROW row;
	puts("Starting program");
	MySql = mysql_init(NULL); // MYSQL * MySql ;
	if (MySql == NULL) {
      	fprintf(stderr, "error mysql_init failed\n"); 
		mysql_close(MySql);
  	} else {
		puts("mysql_init succeeded");
	}
	Retval = mysql_real_connect(MySql, "localhost", "magi", "1234", "employees", 0 ,NULL,0); //MYSQL * Retval;
  	if (Retval == NULL) {
		fprintf(stderr, "mysql_real_connect failed errno: %d Msg: %s\n", mysql_errno(MySql), mysql_error(MySql)) ;
		mysql_close(MySql);
		exit(1);	
	}
	else {
		puts("mysql_real_connect succeeded\n");
	}
	Retvali = mysql_query(MySql, "SELECT * FROM employees.employees limit 20"); //int Retvali;
	if (Retvali != 0) {
		fprintf(stderr, "mysql_query failed errno: %d Msg: %s\n", mysql_errno(MySql), mysql_error(MySql)) ;
		mysql_close(MySql);
		exit(1);	
	}
	else {
		puts("mysql_query succeeded\n");
	}
	result = mysql_store_result(MySql); //MYSQL_RES *result;
	if ((result == NULL ) && (mysql_errno(MySql) != 0)) {
		fprintf(stderr, "mysql_store_result failed errno: %d Msg: %s\n", mysql_errno(MySql), mysql_error(MySql)) ;
		mysql_close(MySql);
		exit(1);	
	}
	else {
		puts("mysql_store_result succeeded\n");
	}

	if (result == NULL) {
		puts("Result is NULL \n");
	} else {
		Number_of_Columns = mysql_num_fields(result); //unsigned int Number_of_Columns;
		Number_of_Rows = mysql_num_rows(result); //unsigned int Number_of_Rows;
		printf("Number_of_columns: %d Number_of_rows: %d\n", Number_of_Columns, Number_of_Rows);
		printf(":");
		for(int i = 0; i < Number_of_Columns; ++i) {
			field = mysql_fetch_field(result); //MYSQL_FIELD *field;
			printf("%s :", field->name);
		}
		printf("\n");
		for (int i = 0; i < Number_of_Rows; i++) {
			row = mysql_fetch_row(result); //MYSQL_ROW row;
			printf(":");
			for ( int j = 0; j< Number_of_Columns; ++j) {
				printf("%s :", row[j]);
			}
			printf("\n");
		}
	}
	mysql_free_result(result);
	mysql_close(MySql);
	puts("Press enter to terminate");
	getchar();
	return(0);
}
/*



Retvali = mysql_query(MySql, "SELECT * FROM employees.employees limit 20"); //int Retvali;
	if (Retvali != 0) {
		fprintf(stderr, "mysql_query failed errno: %d Msg: %s\n", mysql_errno(MySql), mysql_error(MySql)) ;
		mysql_close(MySql);
		exit(1);	
	}
	else {
		puts("mysql_query succeeded\n");
	}
	result = mysql_store_result(MySql); //MYSQL_RES *result;
	if ((result == NULL ) && (mysql_errno(MySql) != 0)) {
		fprintf(stderr, "mysql_store_result failed errno: %d Msg: %s\n", mysql_errno(MySql), mysql_error(MySql)) ;
		mysql_close(MySql);
		exit(1);	
	}
	else {
		puts("mysql_store_result succeeded\n");
	}

	if (result == NULL) {
		puts("Result is NULL \n");
	} else {
		Number_of_Columns = mysql_num_fields(result); //unsigned int Number_of_Columns;
		Number_of_Rows = mysql_num_rows(result); //unsigned int Number_of_Rows;
		printf("Number_of_columns: %d Number_of_rows: %d\n", Number_of_Columns, Number_of_Rows);
		printf(":");
		for(int i = 0; i < Number_of_Columns; ++i) {
			field = mysql_fetch_field(result); //MYSQL_FIELD *field;
			printf("%s :", field->name);
		}
		printf("\n");
		for (int i = 0; i < Number_of_Rows; i++) {
			row = mysql_fetch_row(result); //MYSQL_ROW row;
			printf(":");
			for ( int j = 0; j< Number_of_Columns; ++j) {
				printf("%s :", row[j]);
			}
			printf("\n");
		}
	}



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
}






    */