#include<iostream>
#include<fstream>
#include<string>
#include<cstring>

using namespace std;

void OpenReadFile(string &mlf_path, fstream &ReadFromHere) {
	ReadFromHere.open(mlf_path.c_str(), ios::in);
	if(!ReadFromHere) cout << "Open " << mlf_path << " failed.\n";
	else cout << "Open " << mlf_path << " successful.\n";
}

void OpenWriteFile(fstream &WriteToHere) {
	WriteToHere.open("UpgradeSW.sh", ios::out | ios::trunc);
	if(!WriteToHere) cout << "Open UpgradeSW.sh failed.\n";
	else cout << "Open UpgradeSW.sh successful.\n\n";
}

string SelectOpt(string &Opt) {
	if(!(Opt.compare("0x2"))) Opt.assign("flash") ;
	if(!(Opt.compare("0x1000"))) Opt.assign("flash");
	if(!(Opt.compare("0x4"))) Opt.assign("erase");
	if(!(Opt.compare("0x8"))) Opt.assign("erase");
	if(!(Opt.compare("0x1000000000000000"))) Opt.assign("IgnoreOpt");
	if(!(Opt.compare("0x1"))) Opt.assign("skip");
	return Opt;
}

void ParseInfo(fstream &ReadFromHere, string &line, string &PktName, string &Opt, string &ImgFile) {
	string Act;
	PktName = line.substr(16);
	PktName.erase(PktName.length() - 1);
	getline(ReadFromHere, line);	// skip BOOT_NAME
	getline(ReadFromHere, line);
	Act.assign(line.substr(9));
	Opt = SelectOpt(Act);
	getline(ReadFromHere, line);
	ImgFile = line.substr(14);
	ImgFile.erase(ImgFile.length() - 1);
}

void Parser(fstream &ReadFromHere, fstream &WriteToHere, string &MlfFolder) {
	string line;
	string PktName;
	string Opt;
	string ImgFile;

	while(getline(ReadFromHere, line)) {
		if(line.find("PACKAGE_NAME") != string::npos) {
			ParseInfo(ReadFromHere, line, PktName, Opt, ImgFile);
			if(!(Opt.compare("IgnoreOpt"))) WriteToHere << "fastboot -i 0x489 " << PktName << endl;
			else if(!(Opt.compare("erase"))) WriteToHere << "fastboot -i 0x489 " << Opt << " " << PktName << endl;
			else if(Opt.compare("skip")) WriteToHere << "fastboot -i 0x489 " << Opt << " " << PktName << " " << MlfFolder << ImgFile << endl;
		}
	}
}

int main(int argc, char* argv[]) {
//int main() {
//	string MlfFolder = argv[1];
//	string MlfFile = argv[2];
//	string MlfPath =  MlfFolder + MlfFile;
	string MlfFolder = "good/god/";
	string MlfPath = "VNA-1560-0-00WW-A01.mlf";
	fstream ReadFromHere;
	fstream WriteToHere;

	OpenReadFile(MlfPath, ReadFromHere);
	OpenWriteFile(WriteToHere);
	WriteToHere << "adb reboot bootloader\n";
	Parser(ReadFromHere, WriteToHere, MlfFolder);
	WriteToHere << "fastboot -i 0x489 reboot\n";
	ReadFromHere.close();
	WriteToHere.close();
	return 0;
}
