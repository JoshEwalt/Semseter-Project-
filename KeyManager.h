#ifndef KEYMANGER_H
#define KEYMANGER_H
#include <iostream>

using namespace std;
class KeyManger{
public:
	bool a = false;
	bool s = false;
	bool w = false;
	bool d = false;
	bool space = false;
	void manageKey(int keyCode, bool value) {
		//cout << keyCode << endl;
		switch (keyCode) {
		case 0:
			a = value;
			break;
		case 3:
			d = value;
			break;
		case 18:
			s = value;
			break;
		case 22:
			w = value;
			break;

		case 57:
			space = value;
			break;
		}
	}


};


#endif
