#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	char line[100] = {0};

	fstream ReadFromHere;
	ReadFromHere.open("VNA-1500-0-00WW-A01.mlf", ios::in);
	if(!ReadFromHere) cout << "Open VNA-1500-0-00WW-A01.mlf failed.\n";
	else cout << "Open VNA-1500-0-00WW-A01.mlf successful.\n";

	fstream WriteToHere;
	WriteToHere.open("UpgradeSW.sh", ios::out | ios::trunc);
	if(!ReadFromHere) cout << "Open UpgradeSW.sh failed.\n";
	else cout << "Open UpgradeSW.sh successful.\n";

	while(ReadFromHere.getline(line, sizeof(line), '\n'))
	{

		WriteToHere << line << endl;
	}

	ReadFromHere.close();
	WriteToHere.close();
	return 0;
}
