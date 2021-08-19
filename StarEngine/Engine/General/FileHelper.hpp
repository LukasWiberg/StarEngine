//
// Created by ReSung on 2021-08-17.
//

#ifndef STARENGINE_FILEHELPER_HPP
#define STARENGINE_FILEHELPER_HPP

#include <vector>
#include <string>
class FileHelper {
public:
    static std::vector<char> ReadFile(const std::string &filename);
};
#endif //STARENGINE_FILEHELPER_HPP
