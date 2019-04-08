#ifndef PROJECTPARTB_CACHEMANAGER_H
#define PROJECTPARTB_CACHEMANAGER_H

#define IN_MAP 1

#include <string>
#include <map>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
using std::ifstream;
using std::ofstream;
using std::unordered_map;
using std::string;
using std::map;
class CacheManager {
    virtual void loadSolutionsFromFileToMap() = 0;

public:
    virtual bool isSolutionExist(string problem) = 0;
    virtual string getSolution(string problem) = 0;
    virtual void saveSolution(string problem, string solution) = 0;
    virtual ~CacheManager() = default;
};

/*
 * responsibles to write problem & solution on a file.
 */
class FileCacheManager : public CacheManager {
private:
    std::unordered_map<string, string> solutionMap;
    std::map<string,string> mapOfSolutionToSave;
    string fileName;
    virtual void loadSolutionsFromFileToMap();
    virtual void saveSolutionsToFile();

public:
    FileCacheManager(string fileName);
    virtual bool isSolutionExist(string problem);
    virtual string getSolution(string problem);
    virtual void saveSolution(string problem, string solution);
    ~FileCacheManager(){
        saveSolutionsToFile();
    }
};

#endif //PROJECTPARTB_CACHEMANAGER_H
