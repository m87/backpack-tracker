#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H 
#include "cvcommon.h"
#include "FrameBuffer.h"
#include "Group.h"
#include <vector>
#include <map>
#include "Utils.h"

class DataManager : public FrameBuffer
{
    std::vector<Group> groups;
    //std::map<long, Person> people;
 //   std::map<BackPack, People> backpacks;

    DataManager ();
public:
    static DataManager & getDataManager();
    void addGroup(Group group);
    void clean(); 
    std::vector<Group> getGroups();
    cv::Mat mask;
    cv::Mat cBG;


    ~DataManager ();

};

#endif
