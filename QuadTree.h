#pragma once
#include <memory>								// ����Ʈ�������� ���

// ��ǥ
struct Point
{
	int x;
	int y;
		
	Point() : x{}, y{}							// �⺻������
	{
	}

	Point(int x, int y) : x{ x }, y{ y }		// �̷� ǥ�� �����ϴ�!!!
	{
		// x = x;	���⼱ �ȵȴ�
	}
};

// ���
struct Node
{
	Point position;
	int data;

	Node() : position{}, data{}			// ��� �⺻������
	{
	}

	Node(Point p, int data) : position{ p }, data{ data }
	{
	}
};

class QuadTree
{
	Point topLeft;
	Point bottomRight;			// �»��, ���ϴ� ��ǥ�� ������ ���� Ʈ���� ������ �� �� �ִ�.

	Node* node;					// root

	// ��ü ��ü�� ��������� ������
	// QuadTree�� QuadTree�� ����
	std::unique_ptr<QuadTree> nw;
	std::unique_ptr<QuadTree> ne;
	std::unique_ptr<QuadTree> sw;
	std::unique_ptr<QuadTree> se;

public:
	QuadTree();
	QuadTree(Point topLeft, Point bottomRight);

	void Insert(Node* node);
	Node* Search(Point pt);

	bool IsInBound(Point pt);		// �簢�� ���� �ȿ� ���� �ִ°�?
};

