//train.cpp for triplet loss  --sibin

#include<io.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>    //使用stringstream需要引入这个头文件  
using namespace std;
void getFiles(string path, vector<string>& files)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
vector<string> split(const string &s, const string &seperator){
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()){
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0){
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]){
					++i;
					flag = 0;
					break;
				}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0){
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]){
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j){
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}
//模板函数：将string类型变量转换为常用的数值类型（此方法具有普遍适用性）  
template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}
int main(){
	char * filePath = "gait";
	vector<string> files;
	ofstream outfile;
	outfile.open("train.txt");

	////获取该路径下的所有文件  
	getFiles(filePath, files);

	char str[30];
	int size = files.size();


	//string tmpname = files[45].c_str();
	//cout << tmpname.c_str() << endl;
	//string tmp = tmpname.substr(tmpname.find_last_of("\\") + 1, tmpname.find_last_of(".") - tmpname.find_last_of("\\") - 1);
	////将图片名分为三部分
	//string number = tmpname.substr(tmpname.find_last_of("\\") + 1, 3);
	//cout << number.c_str() << endl;
	//string type = tmp.substr(tmp.find_first_of("-") + 1, 2);
	//string angle = tmp.substr(tmp.find_last_of("-") + 1, 3);
	//if (strcmp(type.c_str(), "nm") == 0) 
	//	cout << type.c_str() << endl;
	//cout << angle.c_str() << endl;




	for (int i = 0; i < size; i++)
	{
		string tmpname1 = files[i].c_str();
		string tmp1 = tmpname1.substr(tmpname1.find_last_of("\\") + 1, tmpname1.find_last_of(".") - tmpname1.find_last_of("\\") - 1);

		//将图片名分为三部分
		//第一
		//第二部分表示图片的类型：有遮挡bg/cl 正常nm
		//第三部分表示图片的角度
		string number1 = tmpname1.substr(tmpname1.find_last_of("\\") + 1, 3);
		string type1 = tmp1.substr(tmp1.find_first_of("-") + 1, 5);
		string angle1 = tmp1.substr(tmp1.find_last_of("-") + 1, 3);
		string check1 = tmp1.substr(tmp1.find_first_of("-") + 1, 9);
		if (strcmp(type1.c_str(), "nm-06") == 0) continue; //将第一个字符串保存nm类型的图片
		//if (i == 3) break;

		for (int j = i; j < size; j++)
		{
			string tmpname2 = files[j].c_str();
			string tmp2 = tmpname2.substr(tmpname2.find_last_of("\\") + 1, tmpname2.find_last_of(".") - tmpname2.find_last_of("\\") - 1);

			string number2 = tmpname2.substr(tmpname2.find_last_of("\\") + 1, 3);
			string type2 = tmp2.substr(tmp2.find_first_of("-") + 1, 2);
			string angle2 = tmp2.substr(tmp2.find_last_of("-") + 1, 3);
			string check2 = tmp2.substr(tmp2.find_first_of("-") + 1, 9);
			if (strcmp(check1.c_str(), check2.c_str()) == 0) continue; //将第一个字符串保存nm类型的图片
			//cout << "number1" << number1.c_str() << ",number2=" << number2.c_str() << endl;
			if (strcmp(type1.c_str(), "nm-06") == 0) continue; //将第一个字符串保存nm类型的图片
			if (strcmp(angle1.c_str(),"000") == 0 || strcmp(angle1.c_str(),"018") == 0 || 
					strcmp(angle1.c_str(),"162") == 0 || strcmp(angle1.c_str(),"180") == 0) continue;
			if (strcmp(number1.c_str(), number2.c_str()) == 0)
				if (strcmp(angle1.c_str(), angle2.c_str()) != 0)//如果两个字符串角度相等
				{
					//cout << stringToNum<int>(number2) << endl;
					//break;
					outfile << files[i].c_str() << " "  <<files[i].c_str() << " " << stringToNum<int>(number1)-1 << endl;
					outfile << files[j].c_str() << " " << files[j].c_str() << " " << stringToNum<int>(number1)-1 << endl;
				}

		}
	}

	outfile.close();
	system("pause");
	return 0;
}
