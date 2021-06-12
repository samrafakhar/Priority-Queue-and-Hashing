#pragma warning(disable:4996)
#include<iostream>
#include <algorithm>
#include <list>
#include <fstream>
#include <string>
#define TABLESIZE 1001
#define P 10003
#define A (rand() % P/2)
#define B (rand() % P/2)
using namespace std;

class User
{
	friend ostream& operator <<(ostream&, const User&);
private:
	int priority;
	int userID;
	char access;
	bool access_status;
public:
	User(int id = 0, int p = 0, char a = 0, bool i = false)
	{
		priority = p;
		access = a;
		userID = id;
		access_status = i;
	}

	User(const User& n)
	{
		priority = n.priority;
		access = n.access;
		userID = n.userID;
		access_status = n.access_status;
	}

	User& operator =(const User& n)
	{
		priority = n.priority;
		userID = n.userID;
		access_status = n.access_status;
		if (n.access == 'W' or n.access == 'R')
			access = n.access;
		else
			access = 0;
		return *this;
	}

	bool operator<(const User& obj)	//less than operator
	{
		if (priority < obj.priority)
			return true;
		return false;
	}

	bool operator>(const User& obj)	//less than operator
	{
		if (priority > obj.priority)
			return true;
		return false;
	}

	bool operator==(const User& obj)	//greater than operator
	{
		if (priority == obj.priority)
			return true;
		return false;
	}

	bool operator!=(const User& obj)	//greater than operator
	{
		if (priority != obj.priority)
			return true;
		return false;
	}

	void give_access()
	{
		access_status = true;
	}

	void deny_access()
	{
		access_status = true;
	}

	char access_type()
	{
		return access;
	}

	int get_id()
	{
		return userID;
	}

	int get_priority()
	{
		return priority;
	}
};

template <class T>
class MaxHeap
{
	friend ostream& operator <<(ostream&, const MaxHeap<User>&);
	friend class File;
	friend class User;
private:
	int cuurent_size;
	int max_size;
	T* data;
public:
	MaxHeap<User>& operator*()		//dereference cout data
	{
		return data;
	}

	MaxHeap(T* d = NULL, int cs = 0, int ms = 10)
	{
		cuurent_size = cs;
		max_size = ms;
		data = new T[max_size];
		if (d != nullptr)
		{
			for (int i = 0; i < max_size; i++)
			{
				data[i] = d[i];
			}
		}
	}

	MaxHeap& operator= (const MaxHeap<T>& m)
	{
		cuurent_size = m.cuurent_size;
		max_size = m.max_size;
		for (int i = 0; i < m.cuurent_size; i++)
		{
			data[i] = m.data[i];
		}
		return *this;
	}

	void insert(T& val)
	{
		if (cuurent_size < max_size)
		{
			data[cuurent_size] = val;
			cuurent_size++;
			reheapUp(0, cuurent_size - 1);
		}
		if (cuurent_size == max_size)
			resize();
	}

	void resize()
	{
		T* temp = new T[max_size];
		for (int i = 0; i < cuurent_size; i++)
			temp[i] = data[i];
		delete data;
		max_size = max_size * 2;
		data = new T[max_size];
		for (int i = 0; i < cuurent_size; i++)
			data[i] = temp[i];
	}

	void reheapUp(int root, int curr_index)
	{
		if (curr_index > root)
		{
			int parent = (curr_index - 1) / 2;
			if (data[parent] < data[curr_index])
			{
				User temp;
				temp = data[parent];
				data[parent] = data[curr_index];
				data[curr_index] = temp;

				reheapUp(root, parent);
			}
		}
	}

	void ReheapDown(int cnode, int last)
	{
		int max_child;
		int right_child;
		int left_child;

		left_child = cnode * 2 + 1;
		right_child = cnode * 2 + 2;

		if (left_child <= last)
		{
			if (left_child == last)
			{
				max_child = left_child;
			}
			else
			{
				if (data[left_child] < data[right_child])
					max_child = right_child;
				else
					max_child = left_child;
			}
			if (data[cnode] < data[max_child])
			{
				User temp;
				temp = data[cnode];
				data[cnode] = data[max_child];
				data[max_child] = temp;

				ReheapDown(max_child, last);
			}
		}
	}

	T delete_max(int root)
	{
		T el = data[root];
		data[root] = data[cuurent_size - 1];
		cuurent_size--;
		ReheapDown(root, cuurent_size);

		return el;
	}

	T remove(T root)
	{
		int i = 0;
		for (i = 0; i < cuurent_size; i++)
			if (data[i] == root)
				break;
		T el = data[i];
		data[i] = data[cuurent_size - 1];
		cuurent_size--;
		ReheapDown(0, cuurent_size);

		return el;
	}

	void BuildHeap(int n)
	{
		for (int i = n / 2; i >= 0; i--)
		{
			ReheapDown(i, n - 1);
		}
	}

	bool empty()
	{
		if (cuurent_size == 0)
			return true;
		return false;
	}

	T FindMax()
	{
		return data[0];
	}

	T FindMin()
	{
		T el = data[0];

		for (int i = 1; i < cuurent_size; ++i)
			if (data[i] < el)
				el = data[i];

		return el;
	}

	T min(T a, T b)
	{
		if (a < b)
			return a;
		else
			return b;
	}

	void print()
	{
		for (int i = 0; i < cuurent_size; i++)
			cout << data[i] << endl;
		cout << endl;
	}

	void Empty()
	{
		cuurent_size = 0;
	}

	int size()
	{
		return cuurent_size;
	}
};

template <class T>
class Hash
{
	friend class File;
	int TableSize;
	list<T>* table;
	int a;
	int b;
	int p;
public:
	Hash(int ts = 0)
	{
		a = A;
		b = B;
		p = P;
		TableSize = ts;
		table = new list<T>[TableSize];
	}

	bool insert(T& key)
	{
		if (Find(key) == false)
		{
			int index = Hash_Func(a, b, p, key);
			table[index].push_back(key);
			return true;
		}
		else
			return false;
	}

	void Delete(T key)
	{
		int index = Hash_Func(a, b, p, key);
		typename list <T> ::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			if (*i == key)
				break;
		}

		if (i != table[index].end())
			table[index].erase(i);
	}

	int Hash_Func(int a, int b, int p, T x)
	{
		return (((a * x) + b) % p) % TableSize;
	}

	void Print()
	{
		for (int i = 0; i < TableSize; i++)
		{
			if (table[i].begin() != table[i].end())
				cout << "H" << i + 1;
			typename list <T> ::iterator j;
			for (j = table[i].begin(); j != table[i].end(); j++)
			{
				cout << "\t--> " << *j;
			}
		}
	}

	int size()
	{
		return TableSize;
	}

	bool Find(T& key)
	{
		typename list <T> ::iterator j;
		int index = Hash_Func(a, b, p, key);
		j = find(table[index].begin(), table[index].end(), key);
		if (j == table[index].end())
			return false;
		else
			return true;
	}

};

class File
{
	friend ostream& operator <<(ostream&, const File&);
	template <class T> friend class Hash;
	friend class User;
private:
	int file_id;
	MaxHeap<User> heap;
	MaxHeap<User> currently_accessing;
public:
	File(User n, int fileid = 0)
	{
		file_id = fileid;
	}

	File& operator*(File& h)		//dereference cout data
	{
		return h;
	}

	File& operator= (const File& h)
	{
		file_id = h.file_id;
		heap = h.heap;
		currently_accessing = h.currently_accessing;
		return *this;
	}

	bool operator<(const File& obj)	//less than operator
	{
		if (file_id < obj.file_id)
			return true;
		return false;
	}

	bool operator>(const File& obj)	//less than operator
	{
		if (file_id > obj.file_id)
			return true;
		return false;
	}

	bool operator==(const File& obj)	//greater than operator
	{
		if (file_id == obj.file_id)
			return true;
		return false;
	}

	bool operator!=(const File& obj)	//greater than operator
	{
		if (file_id != obj.file_id)
			return true;
		return false;
	}

	void insert(File& f, Hash<File>& h, User& n)
	{
		h.insert(f);
		f.finst(f, n, h);
	}

	void finst(File& f, User& n, Hash<File>& h)
	{
		User null;
		int i = 0;
		int index = h.Hash_Func(h.a, h.b, h.p, f);

		if (n != null)
		{
			typename list <File> ::iterator it = find(h.table[index].begin(), h.table[index].end(), f);

			File fil = *it;
			fil.heap.insert(n);
			*it = fil;
		}
	}

	int getid()
	{
		return file_id;
	}

	void granting_access(Hash<File>& h)
	{
		for (int i = 0; i < h.TableSize; i++)
		{
			typename list <File> ::iterator j;
			for (j = h.table[i].begin(); j != h.table[i].end(); j++)
			{
				File temp = *j;
				User u_temp;

				for (int i = 0; i < temp.heap.size(); i++)
				{
					if (temp.heap.FindMax().access_type() == 'W')
					{
						u_temp = temp.heap.delete_max(0);
						u_temp.give_access();
						temp.currently_accessing.insert(u_temp);
					}
					else
					{
						while (temp.heap.FindMax().access_type() == 'R' && temp.heap.size() != 0)
						{
							u_temp = temp.heap.delete_max(0);
							u_temp.give_access();
							temp.currently_accessing.insert(u_temp);
							i++;
						}
					}
					*j = temp;
					break;
				}
			}
		}
	}

	void PrintInfo(Hash<File>& h)
	{
		for (int i = 0; i < h.TableSize; i++)
		{
			if (h.table[i].begin() != h.table[i].end())
				cout << "\nH" << i + 1;
			typename list <File> ::iterator j;
			for (j = h.table[i].begin(); j != h.table[i].end(); j++)
			{
				cout << "\t--> " << *j;
				File temp = *j;

				if (temp.currently_accessing.size() != 0)
				{
					cout << "\tAccess granted to ";
					for (int i = 0; i < temp.currently_accessing.size(); i++)
					{
						cout << "User " << temp.currently_accessing.data[i].get_id() << ", ";
					}
					if (temp.currently_accessing.FindMax().access_type() == 'R')
						cout << "to read." << endl;
					else
						cout << "to write." << endl;

					if (temp.heap.size() != 0)
					{
						cout << "\t\t\tNext user: User " << temp.heap.FindMax().get_id() << ", ";
						if (temp.heap.FindMax().access_type() == 'R')
							cout << "Read" << endl;
						else
							cout << "Write" << endl;
						cout << "\t\t\tWaiting: " << temp.heap.size() << endl << endl;
					}
					else
					{
						cout << "\t\t\tNext user: None\n";
						cout << "\t\t\tWaiting: None " << endl << endl;
					}
				}
				else
				{
					cout << "\tAccess granted to none.\n";
					cout << "\t\t\tNext user: None\n";
					cout << "\t\t\tWaiting: None " << endl << endl;
				}
				*j = temp;
			}
		}
	}

	void Delete_file(File& f, Hash<File>& h)
	{
		if (h.Find(f) == false)
			cout << "File not found!" << endl;
		else
		{
			int index = h.Hash_Func(h.a, h.b, h.p, f);
			typename list <File> ::iterator it = find(h.table[index].begin(), h.table[index].end(), f);

			File file = *it;

			if (file.currently_accessing.size() == 0)
			{
				h.Delete(file);
				cout << "File " << file.file_id << " has been removed successfully" << endl;
			}
			else
				cout << "Error deleting the file. Users are currently accessing File " << f.file_id << endl;
		}
	}

	void accessing(File& temp)
	{
		User u_temp;

		for (int i = 0; i < temp.heap.size(); i++)
		{
			if (temp.heap.FindMax().access_type() == 'W')
			{
				u_temp = temp.heap.delete_max(0);
				u_temp.give_access();
				temp.currently_accessing.insert(u_temp);
			}
			else
			{
				while (temp.heap.FindMax().access_type() == 'R' && temp.heap.size() != 0)
				{
					u_temp = temp.heap.delete_max(0);
					u_temp.give_access();
					temp.currently_accessing.insert(u_temp);
					i++;
				}
			}
			break;
		}
	}

	void release(File& f, Hash<File>& h, User u)
	{
		if (h.Find(f) == false)
		{
			cout << "File not found!";
			return;
		}
		else
		{
			int index = h.Hash_Func(h.a, h.b, h.p, f);
			typename list <File> ::iterator it = find(h.table[index].begin(), h.table[index].end(), f);

			File file = *it;
			User ret_user;

			for (int i = 0; i < file.currently_accessing.size(); i++)
			{
				if (file.currently_accessing.data[i].get_id() == u.get_id())
				{
					ret_user = file.currently_accessing.data[i];
					break;
				}
			}

			if (ret_user.get_id() == 0)
			{
				cout << "User " << u.get_id() << " is not accessing File " << f.file_id << endl;
				return;
			}
			else
			{
				file.currently_accessing.remove(ret_user);
				*it = file;
				if (file.currently_accessing.size() == 0)
				{
					file.accessing(file);
					*it = file;
				}
			}
		}
	}

	void high_priority(File& f, int& p, Hash<File>& h)
	{
		int index = h.Hash_Func(h.a, h.b, h.p, f);
		typename list <File> ::iterator it = find(h.table[index].begin(), h.table[index].end(), f);
		File fil = *it;

		p = fil.heap.FindMax().get_priority() + 1;
	}

	void low_priority(File& f, int& p, Hash<File>& h)
	{
		int index = h.Hash_Func(h.a, h.b, h.p, f);
		typename list <File> ::iterator it = find(h.table[index].begin(), h.table[index].end(), f);
		File fil = *it;

		p = fil.heap.FindMin().get_priority() - 1;
	}
};

int operator* (int& x, File f)
{
	return f.getid() * x;
}

ostream& operator <<(ostream& out, const File& obj)
{
	cout << "File " << obj.file_id << " ";
	return out;
}

ostream& operator <<(ostream& out, const MaxHeap<User>& obj)
{
	for (int i = 0; i < obj.cuurent_size; i++)
		cout << obj.data[i];
	return out;
}

ostream& operator <<(ostream& out, const User& obj)
{
	cout << "\t" << obj.userID << "\t" << obj.priority << "\t" << obj.access << endl;
	return out;
}

void Load(ifstream& fin, Hash<File> h)
{
	char buffer[200];
	fin.getline(buffer, 200);
	User n;
	File file(n, 0);

	char fi[180];
	char ui[180];
	char p[180];
	char a[180];
	int len = 0;
	int file_id;
	int user_id;
	int prior;
	char* acc = nullptr;

	while (!fin.eof())
	{
		fin.getline(buffer, 180);				//inputs a whole line
		strcpy(fi, strtok(buffer, ", "));		//tokenizes the line
		strcpy(ui, strtok(NULL, ", "));			//stores tokens in different variable
		strcpy(p, strtok(NULL, ", "));
		strcpy(a, strtok(NULL, "\n"));

		file_id = atoi(fi);
		user_id = atoi(ui);
		prior = atoi(p);

		len = strlen(a);
		acc = new char[len + 1];
		strcpy(acc, a);
		acc[len + 1] = '\0';

		User n(user_id, prior, acc[1], false);
		File f(n, file_id);
		f.insert(f, h, n);
	}
}

int  menu()
{
	int i = 1;
	int choice;
	cout << endl;
	cout << "--------------------------MENU--------------------------" << endl;
	cout << i++ << ". Request an access to a file by a user" << endl;
	cout << i++ << ". Delete a file" << endl;
	cout << i++ << ". Release a file by user" << endl;
	cout << i++ << ". Print current information" << endl;
	cout << i++ << ". Insert a file" << endl;
	cout << i++ << ". Exit" << endl;

	cout << "enter choice :\t";
	cin >> choice;
	cout << endl;
	return choice;
}

int main() {
	Hash<File> h(TABLESIZE);
	User u;
	File f(u, 0);

	string filename;
	cout << "enter the name of the data file: ";
	cin >> filename;
	ifstream fin(filename.c_str());

	if (fin)
	{
		Load(fin, h);
		f.granting_access(h);
		fin.close();
	}

	int choice;
	choice = menu();

	while (choice < 7)
	{
		if (choice == 1)
		{
			char acc;
			int id;
			char p;
			int priority;
			int file = 0;
			cout << "File to be accessed :\t";
			cin >> file;
			cout << "User ID :\t";
			cin >> id;
			cout << "Priority:\t";
			cin >> p;
			cout << "Access:\t";
			cin >> acc;

			File f(u, file);

			if (p == 'l' || p == 'L')
				f.low_priority(f, priority, h);
			if (p == 'h' || p == 'H')
				f.high_priority(f, priority, h);
			else
				priority = p - '0';

			if (acc == 'w' || acc == 'W')
				acc = 'W';
			else if (acc == 'r' || acc == 'R')
				acc = 'R';
			User u(id, priority, acc, false);

			File fil(u, file);

			if (h.Find(fil) == true)
			{
				f.finst(fil, u, h);
				f.accessing(fil);
			}
			else
				cout << "\nFile not found!" << endl;
		}
		if (choice == 2)
		{
			int file;
			cout << "File to be accessed :\t";
			cin >> file;
			User u;
			File f(u, file);
			f.Delete_file(f, h);
		}
		if (choice == 3)
		{
			int id;
			int file;
			cout << "File to be accessed :\t";
			cin >> file;
			cout << "User ID :\t";
			cin >> id;
			User u(id, 0, 0, false);
			File f(u, file);
			f.release(f, h, u);
		}
		if (choice == 4)
		{
			f.PrintInfo(h);
		}
		if (choice == 5)
		{
			int file;
			cout << "File ID :\t";
			cin >> file;
			User u;
			File f(u, file);
			h.insert(f);
		}
		if (choice == 6)
		{
			cout << "--------------------------Exiting----------------------";
			return 0;
		}
		choice = menu();
	}

	return 0;
}