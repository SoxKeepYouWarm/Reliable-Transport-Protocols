#include <list>
#include <iostream>


struct Event {
	int val;
};


int main() {
	
	std::list<Event> vals;
	
	struct Event one;
	one.val = 1;
	
	struct Event two;
	two.val = 2;
	
	struct Event three;
	three.val = 3;
	
	struct Event four;
	four.val = 4;
	
	vals.push_back(one);
	vals.push_back(two);
	vals.push_back(three);
	vals.push_back(four);
	
	//std::list<struct Event>::iterator it = vals.begin();
	
	for (std::list<struct Event>::iterator iter = vals.begin(); iter != vals.end(); std::advance(iter, 1)) {
		
		if (iter->val != 2) { 
			iter->val = iter->val * 10; 
		} else {
			iter = vals.erase(iter);
			iter --;
		}
		
	}
	
	//vals.erase(it);
	
	for (std::list<struct Event>::iterator iter = vals.begin(); iter != vals.end(); iter++) {
		
		std::cout << iter->val << std::endl;
		
	}
	
}