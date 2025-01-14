#include "stdafx.h"
#include "ColumnTypes.h"
#include "Database.h"
#include <iostream>
#include "FileSystem.h"
#include "SelectHelper.h"
#include "DeleteHelper.h"
using namespace std;

Database db;
int getInput();
void displayMainMenu();
void displayDatabaseMenu();
void displayTablesMenu();
void displayTableMenu(Table& table);
void displayNewTableMenu(Table& table);

void displayAddTableDialog();
void displayAddRowDialog(Table& table);
bool displayCreateDatabaseDialog();
bool displayLoadDatabaseDialog();
void enterQueryDialog();
void enterRemoveQueryDialog();



void displayTable(Table& table, int numberOfRows = INT_MAX);
void saveChanges();
void displayAddColumnDialog(Table& table);
void displayRemoveColumnDialog(Table& table);


int main() {
	displayMainMenu();
	//db=FileSystem::restore("BazaTestowa.xml");
	//auto result=SelectHelper::Select(&db, "SELECT Imie, Nazwisko, Ocena WHERE Imie=Michal Studenci");
	//displayTable(*result);

	//| Imie(String) | Nazwisko(String) | Ocena(Number)|
	//	|Michal | Korniak | 5|
	//	|Tadeusz | Wozniak | 1|
	//	|Adam | Wasacz | 5|
	//	|Pawel | Kowal | 4 |

	//Database db = FileSystem::restore("NowaBazaX.xml");
	//Table pracTab = *db.getTable("Pracownicy");
	//auto table = SelectHelper::Select(&db, "SELECT column1,column2 FROM Pracownicy WHERE column1>1 STDEC column1 END");
	//displayTable(*table);
	//displayTable(pracTab);

	//Database db("NowaBazaX");
	//db.addTable(Table("Pracownicy"));
	//Table*  pracownicyTable = db.getTable("Pracownicy");
	//auto col4 = Column("column1", ColumnTypes::Number);
	//auto col5 = Column("column2", ColumnTypes::String);
	//pracownicyTable->addColumn(col4);
	//pracownicyTable->addColumn(col5);
	//auto& pracColumns = pracownicyTable->getColumns();
	//Row row3 = Row().addCell(Cell("10", &pracColumns[0])).addCell(Cell("NULL_10", &pracColumns[1]));
	//Row row4 = Row().addCell(Cell("3", &pracColumns[0])).addCell(Cell("NULL_3", &pracColumns[1]));
	//Row row5 = Row().addCell(Cell("0", &pracColumns[0])).addCell(Cell("0", &pracColumns[1]));
	//Row row6 = Row().addCell(Cell("1", &pracColumns[0])).addCell(Cell("0", &pracColumns[1]));
	//Row row7 = Row().addCell(Cell("2", &pracColumns[0])).addCell(Cell("0", &pracColumns[1]));
	//pracownicyTable->addRow(row3);
	//pracownicyTable->addRow(row4);
	//pracownicyTable->addRow(row5);
	//pracownicyTable->addRow(row6);	pracownicyTable->addRow(row7);
	//FileSystem::save(db);
	//Database dbLoaded = FileSystem::restore("NowaBazaX.xml");
	
}

void displayMainMenu() {

	int choice = 0;

	do {
		system("cls");

		cout << "Main Menu\n";
		cout << "Please make your selection\n";
		cout << "1 - Create Database\n";
		cout << "2 - Load Database\n";
		cout << "3 - Quit\n";
		cout << "Selection: ";

		choice = getInput();
		switch (choice) {
		case 1:
			if(displayCreateDatabaseDialog())
				displayDatabaseMenu();
			break;
		case 2:
			if(displayLoadDatabaseDialog())
				displayDatabaseMenu();
			break;
		case 3:
			break;

		default:
			break;
		}
	}
	while (choice != 3);

}

void displayDatabaseMenu() {
	bool close = false;
	do {
		system("cls");

		cout << "Database Menu\n";
		cout << "Database: " << db.getName() << endl;
		cout << "Please make your selection\n";
		cout << "1 - Show Tables\n";
		cout << "2 - Add Table\n";
		cout << "3 - Enter Select Query\n";
		cout << "4 - Enter Remove Query\n";
		cout << "5 - Save Changes\n";
		cout << "6 - Back To Main Menu\n";
		cout << "Selection: ";
		int choice = 0;
		choice = getInput();
		switch (choice) {
		case 1:
			displayTablesMenu();
			break;
		case 2:
			displayAddTableDialog();
			break;
		case 3:
			enterQueryDialog();
			break;
		case 4:
			enterRemoveQueryDialog();
			break;
		case 5:
			saveChanges();
			break;
		case 6:
			close = true;
			break;
		default:
			break;
		}
	}
	while (!close);

}

void displayTablesMenu() {
	do {
		system("cls");
		cout << "Database: " << db.getName() << endl;
		cout << "Tables:\n\n";
		int i = 0;
		for (auto& table : db.getTables()) {
			cout << table.getName() << " (" << table.getRows().size() << " records)" << endl;
		}
		cout << endl;
		cout << "Enter name of table if you want to display table menu." << endl;
		cout << "Enter \"q\" if you want to return to previous menu." << endl;
		cout << "Selection: ";
		string choice;
		getline(cin, choice);
		if (choice == "q")
			return;
		for (auto& table : db.getTables()) {
			if (choice == table.getName()) {
				displayTableMenu(table);
				break;
			}
		}
	}
	while (true);
}

void displayTableMenu(Table& table) {

	bool close = false;
	do {
		system("cls");
		cout << "Table name: " << table.getName() << endl;
		cout << "Number of records: " << table.getRows().size() << endl;
		cout << "Please make your selection\n";
		cout << "1 - Show Records\n";
		cout << "2 - Add Record\n";
		cout << "3 - Back To Previous Menu\n";
		cout << "Selection: ";
		int choice = 0;
		choice = getInput();
		switch (choice) {
		case 1:
			system("cls");
			displayTable(table);
			system("pause");
			break;
		case 2:
			displayAddRowDialog(table);
			break;
		case 3:
			close = true;
			break;
		default:
			break;
		}
	}
	while (!close);
}

void displayNewTableMenu(Table& table) {

	int choice = 0;
	bool close = false;
	do {
		system("cls");
		cout << "Welcome to the Column Managment Menu" << endl;
		cout << "Database: " << db.getName() << endl;
		cout << "Table: " << table.getName() << endl;
		cout << "Please make your selection\n";
		cout << "1 - Add Column\n";
		cout << "2 - Remove Column\n";
		cout << "3 - Back To Previous Menu\n";
		cout << "Selection: ";
		choice = getInput();
		switch (choice) {
		case 1:
			displayAddColumnDialog(table);
			break;
		case 2:
			displayRemoveColumnDialog(table);
			break;
		case 3:
			close = true;
			break;
		default:
			break;
		}
	}
	while (!close);
}

bool displayCreateDatabaseDialog() {
	system("cls");
	while (true) {
		cout << "Enter name for your database: ";
		string name;
		getline(cin, name);
		try {
			db = Database(name);
			return true;
		}
		catch (runtime_error error) {
			cout << "Database with this name already exists" << endl;
			cout << "Try again" << endl;
		}
	}
}

bool displayLoadDatabaseDialog() {
	system("cls");
	int i = 0;
	auto dbNames = FileSystem::getAllDbNames();
	if(dbNames.size()==0) {
		cout << "No databases in system."<<endl;
		system("pause");
		return false;
	}
	for (auto db :dbNames ) {
		cout << ++i << " - " << db << endl;
	}

	bool loaded = false;
	while (!loaded) {
		cout << "Enter name of database that you want to load (q to back): ";
		string name;
		getline(cin, name);
		if (name == "q")
			return false;
		bool found = false;
		for (auto db : dbNames) {
			if (db == name) {
				found = true;
				break;
			}
		}
		if (found != true) {
			cout << "Database with this name doesn't exists" << endl;
			cout << "Try again" << endl;
			continue;
		}
		db = FileSystem::restore(name + ".xml");
		loaded = true;
	}
	return true;

}

void displayAddTableDialog() {
	bool addedTable = false;
	system("cls");
	cout << "Enter name of new table." << endl;
	cout << "Enter \"q\" if you want to return to previous menu." << endl;
	do {
		cout << "Name: ";
		string name;
		getline(cin, name);
		if (name == "q")
			return;
		try { db.addTable(Table(name)); }
		catch (runtime_error ex) {
			cout << "Table with this name already exists in database" << endl;
			cout << "Try again." << endl;
			continue;
		}

		displayNewTableMenu(*db.getTable(name));
		addedTable = true;
	}
	while (!addedTable);


}

void displayAddRowDialog(Table& table) {
	system("cls");
	cout << "Enter values" << endl;
	Row newRow;
	for (auto& column : table.getColumns()) {
		bool done = true;
		do {
			cout << column.getName() << " (" << column.getType() << "): ";
			string value;
			getline(cin, value);
			try {
				Cell cell(value, &column);
				newRow.addCell(cell);
			}
			catch (runtime_error error) {
				done = false;
				cout << error.what() << endl;
				cout << "Try again!" << endl;
			}

		} while (!done);
	}
	table.addRow(newRow);
	cout << "Added!" << endl;
	system("pause");
}

void displayAddColumnDialog(Table& table) {

	system("cls");

	const ColumnType* type = NULL;
	bool validType;


	cout << "Choose type\n";
	cout << "1 - Number\n";
	cout << "2 - String\n";

	do {
		validType = true;
		cout << "Selection: ";
		int selection = getInput();
		switch (selection) {
		case 1:
			type = &ColumnTypes::Number;
			break;
		case 2:
			type = &ColumnTypes::String;
			break;
		default:
			cout << "Wrong selection." << endl;
			cout << "Try again." << endl;
			validType = false;
		}
	}
	while (!validType);

	string name;
	bool validName = false;
	while (!validName) {
		cout << "Enter name for column: ";
		getline(cin, name);
		try {
			Column column(name, *type);
			table.addColumn(column);
			validName = true;
		}
		catch (runtime_error error) {
			cout << "Column with this name already exists." << endl;
			cout << "Try again." << endl;
		}
	}
}

void displayRemoveColumnDialog(Table& table) {
	system("cls");
	int i = 0;
	for (auto column : table.getColumns()) {
		cout << ++i << " - " << column.getName() << " (" << column.getType() << ")" << endl;
		
	}
	cout << endl;

	cout << "Enter name of column that you want to remove: ";
	string name;
	getline(cin, name);
	bool found = false;
	int index = -1;
	for (auto column :table.getColumns()) {
		index++;
		if (column.getName() == name) {
			found = true;
			break;
		}
	}
	if (found != true) {
		cout << "Column with this name doesn't exist." << endl;
		system("pause");
	}
	else {
		table.getColumns().erase(table.getColumns().begin()+index);
		cout << "Column deleted!" << endl;
		system("pause");
	}

}

void displayTable(Table& table, int numberOfRows) {
	for (auto& column : table.getColumns()) {
		cout << "|";
		cout << column.getName() << "(" << column.getType() << ")";
	}
	if (table.getColumns().size() != 0)
		cout << "|";
	cout << endl;
	int i = 0;
	for (auto rows : table.getRows()) {
		if (i++ < numberOfRows) {
			cout << "|";
			for (auto cell : rows.getCells())
				cout << cell.getValue() << "|";
		}
		cout << endl;
	}
	cout << endl;
	cout.width();
}

void enterQueryDialog() {
	system("cls");
	cout << "Enter query:" << endl;
	string query;
	getline(cin, query);
	try {
		auto result = SelectHelper::Select(&db, query);
		displayTable(*result);
	}
	catch(exception ex) {
		cout << "Wrong query."<<endl;
	}
	system("pause");
}
void enterRemoveQueryDialog() {
	system("cls");
	cout << "Enter remove query:" << endl;
	string query;
	getline(cin, query);
	try {
		DeleteHelper::Delete(&db, query);
		cout << "Removed" << endl;
	}
	catch (exception ex) {
		cout << "Wrong query."<<endl;
	}
	
	system("pause");
}
void saveChanges() { FileSystem::save(db); }

int getInput() {
	int choice;
	cin >> choice;
	cin.get();
	return choice;
}
