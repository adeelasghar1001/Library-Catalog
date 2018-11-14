#include <string>
using namespace std;

//Base Class=============================================================
class item{
public:
	item();
	void setTitle(string);
	void setID(int);
	void setStatus(int);
	
	string getTitle() const;
	int getID() const;
	int getStatus() const;

private:
	int id;
	string title;
	int status;
	string author;
};

//Book Class=============================================================
class book :public item{
public:
	book(string, string, int, int);
	string getAuthor() const;

private:
	string author;
};

//Journal Class=============================================================
class journal :public item{
public:
	journal::journal(string t, int v, int i, int s);
	int getJournal() const;

private:
	int volume;
};

//Magazine Class=============================================================
class magazine :public item{
public:
	magazine(string t, int i, int id, int s);
	int getMag() const;

private:
	int issue;
};


