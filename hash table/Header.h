#ifndef Header_h
#define Header_h

#include <iostream>	
#include "TreeNode.h"
#include "AVLTree.h"
#include "HashNode.h"
#include "HashMap.h"

const std::string _THIS_PATH_ = __FILE__;

std::string parent_path(const std::string& path = _THIS_PATH_) {
	size_t pos = path.find_last_of("\\");

	if (pos == std::string::npos) {
		return path;
	}
	return path.substr(0, pos);
}

const std::string _SOURCE_PATH_ = parent_path(_THIS_PATH_);

const std::string _RESULT_PATH_ = parent_path(_SOURCE_PATH_) + "\\result";

#endif // !Header_h