#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ResourcePath.h"

using namespace std;

/**
 * @brief Abstract Base for managing resources across program
 * 
 * @tparam Derived The derived class type e.g textureManager
 * @tparam T The return type of the derived class
 */
template <typename Derived, typename T>
class ResourceManager
{
public:
    /**
     * @brief Construct a new Resource Manager object
     * 
     * @param pathFile name of manifest file containing keys and paths to resources
     */
    ResourceManager(const string &pathFile)
    {
        loadPaths(pathFile);
        loadResources();
    }
    /**
     * @brief Destroy the Resource Manager object
     * 
     */
    virtual ~ResourceManager()
    {
        // purgeResources();
    }
    /**
     * @brief Get the Resource object
     * 
     * @param id key of desired resource
     * @return T* pointer to resource requested, null if not found
     */
    T *getResource(const string &id)
    {
        auto res = resources_.find(id);
        return (res != resources_.end() ? res->second : nullptr);
    }
    /**
     * @brief Get the Path to a specified resource
     * 
     * @param id key of resource
     * @return string Path to resource on filesystem
     */
    string getPath(const string &id)
    {
        auto path = paths_.find(id);
        return (path != paths_.end() ? resourcePath() + path->second : "");
    }

    /**
    * @brief Deletes all managed resources
    * 
    */
    void purgeResources()
    {
        while (resources_.begin() != resources_.end())
        {
            delete resources_.begin()->second;
            resources_.erase(resources_.begin());
        }
    }
    /**
    * @brief calls load function of derived class
    * 
    * @param path path of resource to load
    * @return T* pointer to resource loaded
    */
    T *load(const string &path)
    {
        return static_cast<Derived *>(this)->load(path);
    }

private:
    /**
    * @brief loads paths and keys from manifest into memory
    * 
    * @param pathFile name of manifest file
    */
    void loadPaths(const string &pathFile)
    {
        ifstream paths;
        paths.open(resourcePath() + pathFile);
        if (paths.is_open())
        {
            string line;
            while (getline(paths, line))
            {
                stringstream keyStream(line);
                string pathName;
                string path;
                keyStream >> pathName;
                keyStream >> path;
                paths_.emplace(pathName, path);
            }
            paths.close();
            return;
        }
        else
        {
            cerr << "Could not load path file " << pathFile << endl;
        }
    }
    /**
    * @brief loads resources listed in paths_ data member into resources_
    * 
    */
    void loadResources()
    {
        for (auto i : paths_)
        {
            resources_.emplace(i.first, load(i.second));
        }
    }
    /**
     * @brief map of keys and corresponding pointers to resources
     * 
     */
    unordered_map<string, T *> resources_;
    /**
     * @brief map of keys and corresponding resource paths
     * 
     */
    unordered_map<string, string> paths_;
};