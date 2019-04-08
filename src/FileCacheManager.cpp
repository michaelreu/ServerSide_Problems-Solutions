
#include "CacheManager.h"
#define SEPARATOR_CHAR '$'
#define ENDLINE_CHAR '\n'

FileCacheManager::FileCacheManager(string fileName){
    this->fileName = fileName;
    loadSolutionsFromFileToMap();
}

void FileCacheManager::loadSolutionsFromFileToMap() {
    ifstream fin;
    string problem = "", solution="";
    fin.open(this->fileName);
    if (fin.good()) {
        while (getline(fin, problem, SEPARATOR_CHAR ) && getline(fin, solution, ENDLINE_CHAR)) {
            this->solutionMap[problem] = solution;

        }
    }
    fin.close();
}


void FileCacheManager::saveSolutionsToFile(){
    // save on file
    ofstream fout(this->fileName, std::ios::app); //fout.open(this->fileName); // be sure that the argument is a c string
    if(fout.good()) {
        //for (const auto& it : this->solutionMap) {
        for (const auto& it : this->mapOfSolutionToSave) {
            fout << it.first << SEPARATOR_CHAR << it.second << ENDLINE_CHAR;
        }
    }
    fout.close();
}


bool FileCacheManager::isSolutionExist(string problem){
    return (solutionMap.count(problem) == IN_MAP);
}

string FileCacheManager::getSolution(string problem){
    if (isSolutionExist(problem)) {
        return (solutionMap.at(problem));
    }
    return nullptr;
}

void FileCacheManager::saveSolution(string problem, string solution){
    // add to map
    this->solutionMap[problem] = solution;
    this->mapOfSolutionToSave[problem] = solution;
}