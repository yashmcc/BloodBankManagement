#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Bloodbank
{
	struct node
	{
		int ct ;
		string bgrp;
		string name;
		string id;
		node *left;
		node *right;
		node()
		{
			ct = 0;
		}
	};
	
	public:
		static int ct;
		Bloodbank();
		~Bloodbank();
		node *nullRecord, *root;
		void Insert_Record(string, string, string);
		void Delete_Record(string);
		void splay(string, node *&);
		bool contains(string);
		bool Is_Empty();
		void Make_Empty(node *&);
		void Display_Records(node *);
		void print(node *&);
		void rotate_with_left_child(node *&);
		void rotate_with_right_child(node *&);
		void search_key(string);
        void search_by_bgrp(const string &);
        void search_by_bgrp(node * n, const string &);
        bool bgrp_found( string &);
        bool bgrp_found(node * n, const string &);
};
