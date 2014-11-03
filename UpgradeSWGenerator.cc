#include<iostream>
#include<fstream>
#include<string>
#include<cstring>

using namespace std;

int main(int argc, char* argv[])
{
	char line[100] = {0};
	string temp;
	string pkt_name;
	string opt;
	string img;
	string act;
	string mlf_folder = argv[1];
	string mlf_file = argv[2];
	string mlf_path = mlf_folder + mlf_file;

	cout << mlf_path << endl;

	fstream ReadFromHere;
	ReadFromHere.open(mlf_path.c_str(), ios::in);
	if(!ReadFromHere) cout << "Open " << mlf_path << " failed.\n";
	else cout << "Open " << mlf_path << " successful.\n";

	fstream WriteToHere;
	WriteToHere.open("UpgradeSW.sh", ios::out | ios::trunc);
	if(!ReadFromHere) cout << "Open UpgradeSW.sh failed.\n";
	else cout << "Open UpgradeSW.sh successful.\n\n";

	WriteToHere << "# upgrade\nadb reboot bootloader\n";


	while(ReadFromHere.getline(line, sizeof(line), '\n'))
	{
		temp.assign(line);
		if(!(temp.compare(0, 12, "PACKAGE_NAME")))
		{
			pkt_name = temp.substr(16);
			pkt_name.erase(pkt_name.length()-1);

			while(temp.compare(0, 10, "IMAGE_FILE"))
			{
				ReadFromHere.getline(line, sizeof(line), '\n');
				temp.assign(line);

				if(!(temp.compare(0, 6, "OPTION")))
				{
					opt = temp.substr(9);
					act = "";
					if(!(opt.compare("0x2"))) act = "flash";
					if(!(opt.compare("0x1000"))) act = "flash";
					if(!(opt.compare("0x4"))) act = "erase";
					if(!(opt.compare("0x8")))
						{
							if(argv[3] && (!strcmp(argv[3], "1"))) act = "erase";
							else act = "0x1";
						}
					if(!(opt.compare("0x1"))) act = "0x1";
				}
				if(!(temp.compare(0, 10, "IMAGE_FILE")))
				{
					img = temp.substr(14);
					img.erase(img.length()-1);
				}
			}
			if(!(act.compare("0x1"))) continue;
			if(!(act.compare(""))) WriteToHere << "fastboot -i 0x489 " << pkt_name << endl;
			else if(!(act.compare("erase"))) WriteToHere << "fastboot -i 0x489 " << act << " " << pkt_name << endl;
			else WriteToHere << "fastboot -i 0x489 " << act << " " << pkt_name << " " << mlf_folder << img << endl;
		}
	}

	// reboot
	WriteToHere << "\necho Update Complete. Reboot.\n"
				<< "# reboot\n"
				<< "fastboot -i 0x489 reboot\n"
				<< "adb wait-for-device\n"
				<< "sleep 60\n"
				<< "echo \"\"\n"
				<< "echo Reboot Success. Install AutoTestiong\n"
				<< "echo \"\"";

	ReadFromHere.close();
	WriteToHere.close();
	return 0;
}
