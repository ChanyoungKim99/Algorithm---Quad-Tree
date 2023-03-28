#pragma once
#include <memory>								// 스마트포인터의 헤더

// 좌표
struct Point
{
	int x;
	int y;
		
	Point() : x{}, y{}							// 기본생성자
	{
	}

	Point(int x, int y) : x{ x }, y{ y }		// 이런 표기 가능하다!!!
	{
		// x = x;	여기선 안된다
	}
};

// 노드
struct Node
{
	Point position;
	int data;

	Node() : position{}, data{}			// 모두 기본생성자
	{
	}

	Node(Point p, int data) : position{ p }, data{ data }
	{
	}
};

class QuadTree
{
	Point topLeft;
	Point bottomRight;			// 좌상단, 우하단 좌표만 있으면 현재 트리의 영역을 알 수 있다.

	Node* node;					// root

	// 객체 자체를 재귀적으로 디자인
	// QuadTree가 QuadTree를 가짐
	std::unique_ptr<QuadTree> nw;
	std::unique_ptr<QuadTree> ne;
	std::unique_ptr<QuadTree> sw;
	std::unique_ptr<QuadTree> se;

public:
	QuadTree();
	QuadTree(Point topLeft, Point bottomRight);

	void Insert(Node* node);
	Node* Search(Point pt);

	bool IsInBound(Point pt);		// 사각형 영역 안에 점이 있는가?
};

