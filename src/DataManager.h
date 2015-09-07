#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H 
#include "FrameBuffer.h"
#include "Group.h"
#include <vector>
#include <map>
#include "Backpack.h"
#include "Person.h"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
#include <memory>
#include "Utils.h"

/** Manages all data important for processing
 * @see FrameBuffer
 */
class DataManager : public FrameBuffer
{
    std::vector<Group> groups;
    DataManager ();

public:
    std::map<int, Person> people;
    std::vector<Backpack> backpacks;
    std::map<int, Backpack> stableBackpacks;
    static DataManager & getDataManager();
    void addGroup(Group group);
    void addBacpack(Backpack backpack);
    void clean(); 
    std::vector<Group> getGroups();
    std::vector<Backpack> getBackpacks();

    cv::Mat mask;
    cv::Mat cBG;
    FrameBuffer patchBuffer;
    ~DataManager ();

};

#endif
