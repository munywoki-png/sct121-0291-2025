#include <iostream>
using namespace std;
class Rectangle{
	public:void computeArea(int length,int width)
	{int area = length * width;
	cout <<"Area is :" <<area <<endl;
	}
};
int main(int argc,char** argv)
{Rectangle rectObj;
rectObj.computeArea(14,3);
return 0;
}