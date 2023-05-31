#include <ocr_engine.h>

#include <fstream>

bool is_file_exist(std::string filename)
{
    std::ifstream file(filename);
    return !file ? false : true;
}

void file_load(cv::Mat& classifications, cv::Mat& training_img)
{
    
}