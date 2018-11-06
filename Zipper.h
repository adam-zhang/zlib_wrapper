#ifndef __ZIPPER__H
#define __ZIPPER__H

#include <string>

class Zipper
{
	private:
		Zipper();
		~Zipper();
	public:
		static std::string zip(const std::string& content);
		static std::string unzip(const std::string& content, size_t originalSize);
};

#endif//__ZIPPER__H
