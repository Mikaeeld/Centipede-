#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ResourcePath.h"

using namespace std;

template <typename Derived, typename T>
class ResourceManager
{
public:
    ResourceManager(const string &pathFile)
    {
        loadPaths(pathFile);
    }
    virtual ~ResourceManager()
    {
        purgeResources();
    }
    T *getResource(const string &id)
    {
        auto res = find(id);
        return (res ? res->first : nullptr);
    }
    string getPath(const string &id)
    {
        auto path = paths_.find(id);
        return (path != paths_.end() ? path->second : "");
    }
    bool requireResource(const string &id)
    {
        auto res = find(id);
        if (res)
        {
            ++res->second;
            return true;
        }
        auto path = paths_.find(id);
        if (path == paths_.end())
        {
            return false;
        }
        T *resource = load(path->second);
        if (!resource)
        {
            return false;
        }
        resources_.emplace(id, make_pair(resource, 1));
        return true;
    }
    bool releaseResource(const string &id)
    {
        auto res = find(id);
        if (!res)
        {
            return false;
        }
        --res->second;
        if (!res->second)
        {
            unload(id);
        }
        return true;
    }

    void purgeResources()
    {
        while (resources_.begin() != resources_.end())
        {
            delete resources_.begin()->second.first;
            resources_.erase(resources_.begin());
        }
    }

    T *load(const string &path)
    {
        return static_cast<Derived *>(this)->load(path);
    }

private:
    pair<T *, unsigned int> *find(const string &id)
    {
        auto iterator = resources_.find(id);
        return (iterator != resources_.end() ? &iterator->second : nullptr);
    }

    bool unload(const string &id)
    {
        auto iterator = resources_.find(id);
        if (iterator == resources_.end())
        {
            return false;
        }
        delete iterator->second.first;
        resources_.erase(iterator);
        return true;
    }

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
    unordered_map<string, pair<T *, unsigned int>> resources_;
    unordered_map<string, string> paths_;
};