#include <string>
#include <iterator>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <assert.h>
#include <zlib.h>
#include "Zipper.h"

using namespace std;

vector<char> readFile(const string& fileName)
{
	ifstream file(fileName, ios_base::binary);
	if (!file)
	{
		cout << "failed\n";
		return vector<char>();
	}
	string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
	vector<char> v(content.size() + 1);
	copy(content.begin(), content.end(), back_inserter(v));
	return v;
}

bool compare(const vector<char>& v1, const vector<char>& v2)
{
	if (v1.size() != v2.size())
		return false;
	for(auto i = 0; i != v1.size(); ++i)
	{
		if (v1[i] != v2[i])
			return false;
	}	
	return true;
}

vector<char> zip(const vector<char>& v)
{
	auto size = compressBound(v.size());
	vector<char> compressed(size);
	auto ret = compress((Bytef*)&compressed[0], &size, (Bytef*)&v[0], v.size());
	if (ret != Z_OK)
		return vector<char>();
	//vector<char> original(v.size() );
	//uLong length = original.size();
	//ret = uncompress((Bytef*)&original[0], &length, (Bytef*)compressed, length);
	//if (ret == Z_OK)
	//{
	//	cout << "uncompress succeeded.\n";
	//}
	//else
	//{
	//	cout << "Uncompress failed:" << ret << endl;
	//	cout << "original size:" << original.size() << endl;
	//}
	//copy(compressed, compressed + size, back_inserter(vret));
	return compressed;
	//return vector<char>(compressed.begin(), compressed.begin() + size);
}

vector<char> unzip(const vector<char>& compressed, uLong compressedLength)
{
	vector<char> uncompressed(compressedLength);
	uLong length = 0;
	auto ret = uncompress((Bytef*)&uncompressed[0], &length, (Bytef*)&compressed[0], compressed.size());
	if (ret != Z_OK)
	{
		cout << "uncompress failed:" << ret  << endl;
		return vector<char>();
	}
	return uncompressed;
}

string compressfile(string &str) 
{ 	
	string strcom;
	uLong srclen = str.length();
	char *buf;
	uLong buflen = compressBound(srclen);
	buf = new char[buflen];
	if (compress((Bytef*)buf, &buflen, (Bytef*)str.c_str(),srclen) == Z_OK)
       	{ 
		strcom.assign(buf, buflen);
       	} 
	delete[]buf;
	cout << "buflen:" << buflen << endl;
       	return strcom; 
}

string compressData(const string& content)
{
	string target;
	auto length = compressBound(content.size());
	vector<char> buffer(length);
	auto ret = compress((Bytef*)&buffer[0], &length, (Bytef*)content.c_str(), content.size());
	if (ret != Z_OK)
	{
		cout << "compress failed:" << ret << endl;
		return string();
	}
	return string(buffer.begin() , buffer.begin() + length);
}

string uncompressfile(string &str)
{
       	string struncom;
       	uLong strlen = str.length();
       	char *buf;
       	uLong buflen = strlen * 10;
       	buf = new char[buflen];
       	if (uncompress((Bytef*)buf, &buflen, (Bytef*)str.c_str(), strlen) == Z_OK)
       	{ 
		struncom.assign(buf,buflen);
       	} 
	delete[]buf;
       	return struncom;
}

string uncompressData(const string& data, size_t originalSize)
{
	vector<char> buffer(originalSize);
	uLong size = originalSize;
	auto ret = uncompress((Bytef*)&buffer[0], &size, (Bytef*)data.c_str(), data.size());
	if (ret != 0)
	{
		cout << "uncompress failed:" << ret << endl;
		return string();
	}
	assert(size == originalSize);
	return string(buffer.begin(), buffer.begin() + size);
}

string readContent(const string& fileName)
{

	ifstream file(fileName, ios_base::binary);
	if (!file)
	{
		cout << "failed\n";
		return string();
	}
	string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
	return content;
}


int main(int,char**)
{
	string path ="d:\\zmp\\Projects\\Spring\\SpringAccelerator\\Debug\\Spring.exe";
	auto v = readContent(path);
	auto compressed = Zipper::zip(v);
	auto uncompressed = Zipper::unzip(compressed, v.size());
	cout << (v == uncompressed) << endl;
	return 0;
}
