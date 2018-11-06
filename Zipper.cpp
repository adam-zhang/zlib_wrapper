#include "Zipper.h"
#include <zlib.h>
#include <iostream>
#include <vector>

using namespace std;

string Zipper::zip(const string& content)
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


string Zipper::unzip(const string& data, size_t originalSize)
{
	vector<char> buffer(originalSize);
	uLong size = originalSize;
	auto ret = uncompress((Bytef*)&buffer[0], &size, (Bytef*)data.c_str(), data.size());
	if (ret != 0)
	{
		cout << "uncompress failed:" << ret << endl;
		return string();
	}
	return string(buffer.begin(), buffer.begin() + size);
}
