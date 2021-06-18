#include <iostream>
#include <iomanip>
#include <stack>
#include <vector>
#include <string>
#include <cstdio>
#include <bits/stdc++.h>
#include "bloodbankdec.h"
using namespace std;

Bloodbank ::Bloodbank()
{
	nullRecord = new node;
	nullRecord->left = nullRecord->right = nullRecord;
	root = nullRecord;
}

Bloodbank ::~Bloodbank()
{
	Make_Empty(root);
	delete root;
}

void Bloodbank ::Insert_Record(string id, string name, string bgrp)
{
	node *newRecord = new node;
	newRecord->left = newRecord->right = nullRecord;
	newRecord->id = id;
	newRecord->name = name;
    newRecord->bgrp = bgrp;
	if (root == nullRecord)
		root = newRecord;

	else
	{
		splay(id, root);
		if (id < root->id)
		{
			newRecord->left = root->left;
			newRecord->right = root;
			root->left = nullRecord;
			root = newRecord;
		}

		else if (id > root->id)
		{
			newRecord->right = root->right;
			newRecord->left = root;
			root->right = nullRecord;
			root = newRecord;
		}

		else
			return;
	}
	cout << "\nEntry has been inserted!!\n";
}

void Bloodbank ::splay(string id, node *&t)
{
	node header;
	header.left = header.right = nullRecord;
	node *leftTreeMax, *rightTreeMin;
	leftTreeMax = rightTreeMin = &header;
	nullRecord->id = id;
	while (1)
	{
		if (id < t->id)
		{
			if (id < t->left->id)
				rotate_with_left_child(t);

			if (t->left == nullRecord)
				break;

			rightTreeMin->left = t;
			rightTreeMin = t;
			t = t->left;
		}

		else if (id > t->id)
		{
			if (id > t->right->id)
				rotate_with_right_child(t);

			if (t->right == nullRecord)
				break;

			leftTreeMax->right = t;
			leftTreeMax = t;
			t = t->right;
		}

		else
			break;
	}
	leftTreeMax->right = t->left;
	rightTreeMin->left = t->right;
	t->left = header.right;
	t->right = header.left;
}

void Bloodbank ::rotate_with_left_child(node *&k2)
{
	node *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2 = k1;
}

void Bloodbank ::rotate_with_right_child(node *&k2)
{
	node *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2 = k1;
}

void Bloodbank ::Delete_Record(string id)
{
	node *newTree = NULL;
	if (!contains(id))
	{
		cout << id << " is not present!!\n\n";
		return;
	}

	if (root->right == nullRecord)
		newTree = root->left;

	else
	{
		newTree = root->right;
		splay(id, newTree);
		newTree->left = root->left;
	}
	delete root;
	root = newTree;
}

bool Bloodbank ::contains(string id)
{
	splay(id, root);
	return root->id == id;
}

bool Bloodbank ::Is_Empty()
{
	return root == nullRecord;
}

void Bloodbank ::Make_Empty(node *&t)
{
	while (t != nullRecord)
		Delete_Record(t->id);
}

int Bloodbank::ct = 0;

void Bloodbank ::Display_Records(node *t)
{
	if (t == NULL)
	{
		cout << "\nNo donors!!\n";
		return;
	}
	cout << "\n********************************************\n";
	cout << "Name\t\tID\t\tBlood group" << endl;
	cout << "********************************************\n";
	print(t);
	cout << "********************************************\n";
}

void Bloodbank ::print(node *&t) //Preorder traversal
{
	if (t != t->left)
	{
		cout << t->name << "\t\t" << t->id << "\t\t" << t->bgrp << endl;
		//printf("%-24s %s\n", t->name.c_str(), t->id.c_str(), t->bgrp.c_str());
		print(t->left);
		print(t->right);
	}
}

void Bloodbank ::search_key(string id)
{
	if (!contains(id))
	{
		cout << id << " is not present!!\n";
		return;
	}
	cout << endl;
	cout << "Name : " << root->name << endl;
	cout << "Blood group : " << root->bgrp << endl;
	root->ct++;
}

bool Bloodbank ::bgrp_found(node *n, const string &str)
{
	if (n == nullRecord)
		return false;

	string t = n->bgrp;
	transform(t.begin(), t.end(), t.begin(), ::tolower);
	if (t.compare(str) == 0)
		return true;

	return bgrp_found(n->left, str) || bgrp_found(n->right, str);
}

bool Bloodbank ::bgrp_found(string &n)
{
	transform(n.begin(), n.end(), n.begin(), ::tolower);

	if (root == nullRecord)
		return false;
	return bgrp_found(root, n);
}

void Bloodbank ::search_by_bgrp(node *n, const string &search_string)
{
	if (n == nullRecord)
		return;

	string s = n->bgrp;
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	if (s.compare(search_string) == 0)
	{
		cout << n->name << "\t\t" << n->id << endl;
		n->ct++;
	}

	search_by_bgrp(n->left, search_string);
	search_by_bgrp(n->right, search_string);
}

void Bloodbank ::search_by_bgrp(const string &search_name)
{
    search_by_bgrp(root, search_name);
}