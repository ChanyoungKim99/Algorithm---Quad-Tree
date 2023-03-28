#include <iostream>
#include "QuadTree.h"

QuadTree::QuadTree() : 
	topLeft{ Point() }, 
	bottomRight{ Point() }, 
	node{},
	nw{}, ne{}, sw{}, se{}
{
}

QuadTree::QuadTree(Point topLeft, Point bottomRight) : QuadTree()
{
	this->topLeft = topLeft; 
	this->bottomRight = bottomRight;
}

void QuadTree::Insert(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	if (!IsInBound(node->position))		// 영역 밖의 노드를 넣을려고 할때
	{
		return;
	}

	// base case
	// 픽셀은 공간의 개념, 좌표는 정수 = 픽셀이 1 X 1 일 때
	if (std::abs(bottomRight.x - topLeft.x) <= 1 &&
		std::abs(bottomRight.y - topLeft.y) <= 1)		// absolute = 절댓값
	{
		if (this->node == nullptr)		// 노드에 아무것도 없을때만 추가
		{								// 그냥 덮어쓰기로 하고싶다면 if제거
			this->node = node;
		}
		return;
	}

	// recursive case		영역을 나누는것 만으로도 재귀가 성립한다
	if (node->position.x <= (topLeft.x + bottomRight.x) / 2)			// 서쪽
	{
		if (node->position.y <= (topLeft.y + bottomRight.y) / 2)	// 북서 (왼쪽 위가 0,0이다)
		{															
			if (nw == nullptr)	// 북서에 아무것도 없으면 생성
			{
				nw = std::make_unique<QuadTree>	// 영역 생성
				(
					topLeft,
					Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2)
				);
			}

			nw->Insert(node);	// 북서에 있으면 재귀
								// nw->Insert 이므로 재귀형태가 되는것이다.
		} 
		else														// 남서
		{
			if (sw == nullptr)
			{
				sw = std::make_unique<QuadTree>
				(
					Point(topLeft.x, (topLeft.x + bottomRight.y) / 2),
					Point((topLeft.x + bottomRight.x) / 2, bottomRight.y)
				);
			}

			sw->Insert(node);
		}
	}
	else														// 동쪽
	{
		if (node->position.y <= (topLeft.y + bottomRight.y) / 2)	// 북동
		{	
			if (ne == nullptr)
			{
				ne = std::make_unique<QuadTree>
				(
					Point((topLeft.x + bottomRight.x) / 2, topLeft.y),
					Point(bottomRight.x, (topLeft.y + bottomRight.y) / 2)
				);
			}

			ne->Insert(node);
		}
		else														// 남동		 
		{
			if (se == nullptr)
			{
				se = std::make_unique<QuadTree>
				(
					Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2),
					bottomRight
				);
			}

			se->Insert(node);
		}
	}
}

Node* QuadTree::Search(Point pt)
{
	if (node != nullptr)	// 트리 속 데이터가 없을 때
	{
		return node;
	}

	if (!IsInBound(pt))		// 영역 밖의 노드를 넣을려고 할때
	{
		return nullptr;
	}
	
	if (pt.x <= (topLeft.x + bottomRight.x) / 2)			// 서쪽
	{
		if (pt.y <= (topLeft.y + bottomRight.y) / 2)		// 북서
		{
			if (nw == nullptr)	
			{
				return nullptr;
			}

			return nw->Search(pt);
		}
		else												// 남서
		{
			if (sw == nullptr)
			{
				return nullptr;
			}

			return sw->Search(pt);
		}
	}
	else													// 동쪽
	{
		if (pt.y <= (topLeft.y + bottomRight.y) / 2)		// 북동
		{
			if (ne == nullptr)
			{
				return nullptr;
			}

			return ne->Search(pt);
		}
		else												// 남동
		{
			if (se == nullptr)
			{
				return nullptr;
			}

			return se->Search(pt);
		}
	}
}

bool QuadTree::IsInBound(Point pt)
{
	return pt.x >= topLeft.x && pt.x <= bottomRight.x &&
			pt.y >= topLeft.y && pt.y <= bottomRight.y;	
}
