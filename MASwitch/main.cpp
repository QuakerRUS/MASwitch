#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Mouse Acceleration Switch, ver 0.1, (C) 2021 by QuakerRUS" << endl << endl;
	int mouse_info[3], mouse_new_info[3];

	for (int i = 0; argc == 4 && i < 3; i++)
		mouse_info[i] = atoi(argv[i + 1]);

	if (argc != 4 || mouse_info[0] + mouse_info[1] + mouse_info[2] == 0 || mouse_info[0] < 0 || mouse_info[1] < 0 || mouse_info[2] < 0)
	{
		cout << "Usage: MASwitch <MouseThreshold1> <MouseThreshold2> <MouseSpeed>" << endl << endl;
		cout << "MouseThreshold and MouseSpeed is restore options for program completion" << endl << endl;
		cout << "Example: MASwitch 6 10 1" << endl << endl;

		SystemParametersInfo(SPI_GETMOUSE, NULL, mouse_new_info, NULL);
		cout << "Current settings: " << mouse_new_info[0] << ' ' << mouse_new_info[1] << ' ' << mouse_new_info[2] << endl;
		cout << " Common settings: 6 10 1" << endl;
		
		return 0;
	}

	cout << "Press Esc to end program and restore mouse settings..." << endl << endl;

	while (true)
	{
		if (_kbhit() && _getch() == 27)
			break;

		SystemParametersInfo(SPI_GETMOUSE, NULL, mouse_new_info, NULL);

		if (mouse_new_info[0] + mouse_new_info[1] + mouse_new_info[2] > 0)
		{
			cout << "{" << mouse_new_info[0] << ", " << mouse_new_info[1] << ", " << mouse_new_info[2] << "} settings changed to {0, 0, 0}" << endl;
			mouse_new_info[0] = mouse_new_info[1] = mouse_new_info[2] = 0;
			SystemParametersInfo(SPI_SETMOUSE, NULL, mouse_new_info, SPIF_UPDATEINIFILE);
		}

		Sleep(1000);
	}

	SystemParametersInfo(SPI_SETMOUSE, NULL, mouse_info, SPIF_UPDATEINIFILE);
	cout << endl << "Mouse settings restored to {" << mouse_info[0] << ", " << mouse_info[1] << ", " << mouse_info[2] << "}" << endl;

	return 0;
}