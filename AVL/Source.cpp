#include <iostream>
#include <math.h>

using namespace std;

struct BinaryNode {
	BinaryNode(int weight) :data(weight) {};
	int data;
	int bf = 0;
	BinaryNode* lchild = nullptr;
	BinaryNode* rchild = nullptr;
};

// ������������� �������� ������ �������
void rotateRight(BinaryNode*& root) {
	
	BinaryNode* lchild = root->lchild;
	root->lchild = lchild->rchild;
	lchild->rchild = root;
	root = lchild;
}

// ������������� �������� ������ ������
void rotateLeft(BinaryNode*& root) {
	BinaryNode* rchild = root->rchild;
	root->rchild = rchild->lchild;
	rchild->lchild = root;
	root = rchild;
}

// ��������� ������ ������� (������)
void balanceLeft(BinaryNode*& root) {
	BinaryNode* L = root->lchild;
	switch (L->bf) {
	case -1:
	{
		BinaryNode* Lr = L->rchild;
		switch (Lr->bf) {
		case -1:
			root->bf = 0;
			L->bf = 1;
			break;
		case 0:
			root->bf = 0;
			L->bf = 0;
			break;
		case 1:
			root->bf = -1;
			L->bf = 0;
			break;
		}
		Lr->bf = 0;
		rotateLeft(L);
		rotateRight(root);
		break;
	}
	case 1:
	{
		root->bf = 0;
		L->bf = 0;
		rotateRight(root);
		break;
	}
	}
}


// ��������� ������� ������� (�����)
void balanceRight(BinaryNode*& root) {
	BinaryNode* R = root->rchild;
	switch (R->bf) {
	case 1:
	{
		BinaryNode* Rl = R->lchild;
		switch (Rl->bf) {
		case -1:
			root->bf = 1;
			R->bf = 0;
			break;
		case 0:
			root->bf = 0;
			R->bf = 0;
			break;
		case 1:
			root->bf = 0;
			R->bf = -1;
			break;
		}
		Rl->bf = 0;
		rotateRight(R);
		rotateLeft(root);
		break;
	}
	case -1:
	{
		root->bf = 0;
		R->bf = 0;
		rotateLeft(root);
		break;
	}
	}
}

// ���������������� ������� ��������� ������
bool insertAVL(BinaryNode*& node, int data, bool* taller) {
	if (node == nullptr) {
		node = new BinaryNode(data);
		*taller = true;
		return true;
	}
	else if (data < node->data) {
		if (!insertAVL(node->lchild, data, taller)) {
			return false;
		}
		if (*taller) {
			switch (node->bf) {
			case -1:
				node->bf = 0;
				*taller = false;
				break;
			case 0:
				node->bf = 1;
				*taller = true;
				break;
			case 1:
				balanceLeft(node);
				*taller = false;
				break;
			}
		}
	}
	else {
		if (!insertAVL(node->rchild, data, taller)) {
			return false;
		}
		if (*taller) {
			switch (node->bf) {
			case -1:
				balanceRight(node);
				*taller = false;
				break;
			case 0:
				node->bf = -1;
				*taller = true;
				break;
			case 1:
				node->bf = 0;
				*taller = false;
				break;
			}
		}
	}
	return true;
}

bool h = false;
void Search(int x, BinaryNode*& p)
// x - ���� �������, ���������� � ���-������.
// *p - ��������� �� ������ ���-������.
// h - ����, ��������������� �� ���������� ������ ���������:
// TRUE - ������ ��������� �����������, 
// FALSE - ������ ��������� �� �����������.
// ��� ������ ��������� � ������� Search() h=FALSE.
{
	BinaryNode* p1, * p2;
	h = false;
	if (p == NULL)
	{ // ������� � ������ ���; �������� ��... 
		p = new BinaryNode(x);
		h = true; 
		(*p).data = x;
		(*p).lchild = (*p).rchild = NULL;
		(*p).bf = 0; // ������� ��������� ������� ������.
	}
	else
		if (x <= (*p).data)
		{
			Search(x, p->lchild); // ������� ��� �������� � ������.
			if (h == true)
				// ���� ������ ��������� �����������, 
				// �� ������� ����� ����.
				switch ((*p).bf)
				{
				case 1:  (*p).bf = 0; h = false; break;
					// ���������� �������������������� ��������������.
				case  0: (*p).bf = -1; break; // ��� "���������" �����.
				case -1:
					//������������.
					p1 = (*p).lchild;
					if ((*p1).bf == -1)
					{//����������� LL-�������.
						(*p).lchild = (*p1).rchild;
						(*p1).rchild = p;
						(*p).bf = 0; 
						p = p1;
					}
					else
					{//���������� LR-�������.
						p2 = (*p1).rchild;
						(*p1).rchild = (*p2).lchild;
						(*p2).lchild = p1;
						(*p).lchild = (*p2).rchild;
						(*p2).rchild = p;
						//�������� ������� ������� � ���������� p.
						if ((*p2).bf == -1) (*p).bf = 1;
						else (*p).bf = 0;
						// �������� ������� ������� � ���������� p1.
						if ((*p2).bf == 1) (*p1).bf = -1;
						else (*p1).bf = 0;
						p = p2;
					}
					(*p).bf = 0; h = false;
					break;
				}
		}
		else //... ����� ������� ������ ����.
			if (x > (*p).data)
			{
				Search(x, p->rchild);
				// ������� ��� �������� � ������.
				if (h == true)
					// ���� ������ ��������� �����������, 
					// �� ������� ������ ����.
					switch ((*p).bf)
					{
					case -1:  (*p).bf = 0; h = false; break;
					case  0: (*p).bf = 1; break;
					case  1:
						//������������.
						p1 = (*p).rchild;
						if ((*p1).bf == 1)
						{ //����������� RR-�������.
							(*p).rchild = (*p1).lchild;
							(*p1).lchild = p; 
							(*p).bf = 0; 
							p = p1;
						}
						else
						{ //����������� RL-�������.
							p2 = (*p1).lchild; (*p1).lchild = (*p2).rchild;
							(*p2).rchild = p1; (*p).rchild = (*p2).lchild;
							(*p2).lchild = p;
							// �������� ������� ������� � ���������� p.
							if ((*p2).bf == 1) (*p).bf = -1;
							else (*p).bf = 0;
							//�������� ������� ������� � ���������� p1.
							if ((*p2).bf == -1) (*p1).bf = 1;
							else (*p1).bf = 0; p = p2;
						}
						(*p).bf = 0; h = false; break;
					}
			}
}

void PrintTree(BinaryNode*& root, int r, int ch)
{
	//������ ���������
	if (root->rchild)
	{
		PrintTree(root->rchild, r + 10, 2);
	}

	for (int i = 0; i < r - 1; i++)
		cout << " ";

	if (ch == 0)
		cout << "";
	else if (ch == 1)
		cout << "\\";
	else if (ch == 2)
		cout << "/";

	cout << root->data << endl;

	//����� ���������
	if (root->lchild)
	{
		PrintTree(root->lchild, r + 10, 1);
	}
}

int main(int argc, const char* argv[]) {
	//int datas[10] = { 3,2,1,4,5,6,7,10,9,8 };
	//int datas[7] = { 4, 5, 7, 2, 1, 3, 6 };

	bool status = false;
	/*BinaryNode* tree = new BinaryNode(datas[0]);
	for (int i = 1; i < 7; ++i) {
		insertAVL(tree, datas[i], &status);
	}*/
	
	/*cout << endl << "������� 4" << endl;
	BinaryNode* tree = new BinaryNode(4);
	PrintTree(tree, 0, 1);

	cout << endl << "������� 5" << endl;
	insertAVL(tree, 5, &status); PrintTree(tree, 0, 1);
	
	cout << endl << "������� 7" << endl;
	insertAVL(tree, 7, &status); PrintTree(tree, 0, 1);

	cout << endl << "������� 2" << endl;
	insertAVL(tree, 2, &status); PrintTree(tree, 0, 1);

	cout << endl << "������� 1" << endl;
	insertAVL(tree, 1, &status); PrintTree(tree, 0, 1);

	cout << endl << "������� 3" << endl;
	insertAVL(tree, 3, &status); PrintTree(tree, 0, 1);

	cout << endl << "������� 6" << endl;
	insertAVL(tree, 6, &status); PrintTree(tree, 0, 1);*/

	int datas[12] = { 1, 15, 7, 2, 3, 4, 9, 8, 5, 6, 11, 13 };
	
	
	BinaryNode* tree = new BinaryNode(datas[0]);
	for (int i = 1; i < 3; ++i) {
		Search(datas[i], tree);
	}

	cout << endl << "INTERNET" << endl;
	PrintTree(tree, 0, 1);


	BinaryNode* MYtree = new BinaryNode(datas[0]);
	for (int i = 1; i < 3; ++i) {
		insertAVL(MYtree, datas[i], &status);
	}
	
	cout << endl << "////////////////MY///////////////////////" << endl;
	PrintTree(MYtree, 0, 1);
	
	return 0;
}