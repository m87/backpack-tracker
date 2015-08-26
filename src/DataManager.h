#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H 
#include "cvcommon.h"
#include "FrameBuffer.h"
#include "Group.h"
#include <vector>
#include <map>
#include "Utils.h"
#include "Backpack.h"
#include "Person.h"

class DataManager : public FrameBuffer
{
    std::vector<Group> groups;
 //   std::map<BackPack, People> backpacks;

    DataManager ();
public:
    std::map<int, Person> people;
    std::vector<Backpack> backpacks;
    //static FrameBuffer bgBuffer;
    static DataManager & getDataManager();
    void addGroup(Group group);
    void addBacpack(Backpack backpack);
    void clean(); 
    std::vector<Group> getGroups();
    std::vector<Backpack> getBackpacks();

    cv::Mat mask;
    cv::Mat cBG;


    ~DataManager ();

};

#endif
