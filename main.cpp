#include "QuadTree.h"
#include <iostream>

int main()
{
	QuadTree tree(Point(0, 0), Point(8, 8));

	std::unique_ptr<Node> a = std::make_unique<Node>(Point(1, 1), 1);
	std::unique_ptr<Node> b = std::make_unique<Node>(Point(2, 2), 2);
	std::unique_ptr<Node> c = std::make_unique<Node>(Point(3, 3), 3);
	std::unique_ptr<Node> d = std::make_unique<Node>(Point(4, 4), 4);

	tree.Insert(a.get());		// 스마트포인터니까 Get을 사용
	tree.Insert(b.get());
	tree.Insert(c.get());
	tree.Insert(d.get());

	auto result = tree.Search(Point(2, 2));
	if (result == nullptr)
	{
		std::cout << "NOT FOUND" << std::endl;
	} else
	{
		std::cout << result->data << std::endl;
	}
}
