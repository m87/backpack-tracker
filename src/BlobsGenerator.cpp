#include "BlobsGenerator.h"

BlobsGenerator::BlobsGenerator() {
    VERBOSE("BlobsGenerator: Loading blobs ...");

    ConfigManager &configManager = ConfigManager::getConfigManager();

    for(unsigned long b = 0; b < configManager.blobs.size(); b++) {
        std::string src = configManager.blobs[b][ConfigManager::BLOBS_IMG].as<std::string>();
        VERBOSE("BlobsGenerator: using " + src);

        cv::Mat img = cv::imread(src,-1);
        resize(img,img,cv::Size(configManager.blobs[b][ConfigManager::BLOBS_W].as<int>(),
                                configManager.blobs[b][ConfigManager::BLOBS_H].as<int>()));
        blobs.push_back(std::unique_ptr<Blob>(new Blob("blob", img ,configManager.blobs[b][ConfigManager::BLOBS_X].as<int>(),
                                              configManager.blobs[b][ConfigManager::BLOBS_Y].as<int>(),
                                              configManager.blobs[b][ConfigManager::BLOBS_W].as<int>(),
                                              configManager.blobs[b][ConfigManager::BLOBS_H].as<int>(),
                                              configManager.blobs[b][ConfigManager::BLOBS_START].as<long>(),
                                              configManager.blobs[b][ConfigManager::BLOBS_TIME].as<long>())));

    }

    VERBOSE("BlobsGenerator: Blobs loaded");
    MEMORY("BlobsGenerator created");
}

BlobsGenerator::~BlobsGenerator() {

    MEMORY("BlobsGenerator deleted");
}


void overlayImage(const cv::Mat &background, const cv::Mat &foreground,
                  cv::Mat &output, cv::Point2i location)
{
    background.copyTo(output);


    for(int y = std::max(location.y , 0); y < background.rows; ++y)
    {
        int fY = y - location.y; // because of the translation

        if(fY >= foreground.rows)
            break;

        for(int x = std::max(location.x, 0); x < background.cols; ++x)
        {
            int fX = x - location.x; // because of the translation.

            if(fX >= foreground.cols)
                break;

            double opacity =
                ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])

                / 255.;



            for(int c = 0; opacity > 0 && c < output.channels(); ++c)
            {
                unsigned char foregroundPx =
                    foreground.data[fY * foreground.step + fX * foreground.channels() + c];
                unsigned char backgroundPx =
                    background.data[y * background.step + x * background.channels() + c];
                output.data[y*output.step + output.channels()*x + c] =
                    backgroundPx * (1.-opacity) + foregroundPx * opacity;

            }

        }

    }

}

void BlobsGenerator::merge(cv::Mat& ref) {
    long time = TimeManager::getTimeManager().time();
    for(unsigned long i=0; i<blobs.size(); i++) {
        if(blobs[i]->_start <= time && blobs[i]->_time+blobs[i]->_start >= time) {
            long x = blobs[i]->_x+blobs[i]->_w;
            long y = blobs[i]->_y+blobs[i]->_h;
            cv::Mat im(blobs[i]->_img);
            cv::Mat im2;
            overlayImage(ref.rowRange(blobs[i]->_y,y).colRange(blobs[i]->_x,x),im,im2, cv::Point(0,0));
            //overlayImage(ref.rowRange(blobs[i]->_y,y).colRange(blobs[i]->_x,x),im,im, Point(30,30));
            im2.copyTo(ref.rowRange(blobs[i]->_y,y).colRange(blobs[i]->_x,x));
        }
    }

    VERBOSE_O("BlobsGenerator: BlobsMerged");
    display(ConfigManager::VIEW_BLOBS, ref);
}

