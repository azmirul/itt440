#include<stdio.h>
#include<postgresql/libpq-fe.h>
#include<string>

int main()
{
	PGconn *conn;
	PGresult *res;
	int rec_count;
	int row;
	int col;

	if(PQstatus(conn) == CONNECTION_BAD)
	{
		puts("unable to connect to database");
		exit(0);
	}

	res = PQexec(conn, "select * from subject");

	if(PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		puts("not get any data");
		exit(0);
	}

	rec_count = PQntuples(res);

	printf("received %d records.\n", rec_count);
	puts("=======================");

	for(row=0; row<rec_count; row++)
	{
		for(col=0; col<2l col++)
		{
			printf("%\t", PQgetvalue(res, row, col));
		}
		puts("");
	}

	puts("=====================");

	PQclear(res);

	PQfinish(conn);

	return 0;
}
