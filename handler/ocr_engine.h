#pragma once

#include <opencv2/opencv.hpp>

// Training model
void training_model();

// Levenshtein distance
bool is_same_str(std::string original_str, std::string &token, int max_distance = 2);

// Utility
void splitter(std::string input, std::vector<std::string>& output, char delimiter);
bool is_same_word(std::string str_1, std::string str_2);

// Preprocessing
extern int MIN_CONTOUR_AREA;
extern int IMG_RESIZE_WIDTH;
extern int IMG_RESIZE_HEIGHT;

class ContourData
{
public:
    std::vector<cv::Point> ptr_Contour;
    cv::Rect bounding;
    float f_area;

    bool is_valid();
};

bool is_valid_contour(int width, int height);
int get_horizontal_space(int height);

void remove_table(cv::Mat& bw_img);
void sigmoid_threshold(cv::Mat& img, int threshold);
void split_contour(cv::Mat& original_img, ContourData contour, std::vector<ContourData>& all_contours);
void contour_sort(std::vector<ContourData> valid_contours, std::map<int, std::map<int, ContourData>>& sorted_contours);
void validation(std::map<int, std::map<int, ContourData>>& sorted_contours);
void merge_contours(std::map<int, std::map<int, ContourData>>& sorted_contour);
void trim_img(cv::Mat& original_img);

// Ocr engine
void extract(cv::Mat& grayscale_img, cv::Mat& threshold_img, std::vector<ContourData>& all_contours, int x_offset = 0, int y_offset = 0, bool recursive = false);
void extract_contours(cv::Mat& origin_img, ContourData contour, std::vector<ContourData>& all_contours);
void prediction(std::string filename, std::map<int, std::map<int, std::string>>& result, bool display_img = true);