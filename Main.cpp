#include "stdafx.h"
#include "Database.h"
#include "ColumnTypes.h"
#include "Serializer.h"
using namespace std;

int main()
{
	Database db("NowaBaza");
	db.addTable(Table("Pracownicy"));
	db.addTable(Table("Studenci"));

	Table& studentsTable=db.getTable("Studenci");
	studentsTable.addColumn(Column("Imie",ColumnTypes::String));
	studentsTable.addColumn(Column("Nazwisko", ColumnTypes::String));
	studentsTable.addColumn(Column("Rok", ColumnTypes::Number));

	Row row1 = Row().addCell(Cell("Piotr")).addCell(Cell("Adamiak")).addCell(Cell("2"));
	Row row2 = Row().addCell(Cell("Michal")).addCell(Cell("Kowalski")).addCell(Cell("1"));
	studentsTable.addRow(row1);
	studentsTable.addRow(row2);

	Serializer::saveDatabase(db);

	
}

