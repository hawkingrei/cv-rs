#include "imgproc.h"
#include <iostream>
#include <stdio.h>
#include <vector>

extern "C" {

void cv_line(cv::Mat* mat, Point2i pt1, Point2i pt2, Scalar color, int thickness, int linetype, int shift) {
    cv::Point point1(pt1.x, pt1.y);
    cv::Point point2(pt2.x, pt2.y);
    cv::Scalar colour(color.v0, color.v1, color.v2, color.v3);
    cv::line(*mat, point1, point2, colour, thickness, linetype, shift);
}

void cv_rectangle(cv::Mat* mat, Rect crect, Scalar color, int thickness, int linetype) {
    cv::Rect rect(crect.x, crect.y, crect.width, crect.height);
    cv::Scalar colour(color.v0, color.v1, color.v2, color.v3);
    cv::rectangle(*mat, rect, colour, thickness, linetype);
}

void cv_ellipse(cv::Mat* mat,
                Point2i center,
                Size2i axes,
                double angle,
                double start_angle,
                double end_angle,
                Scalar color,
                int thickness,
                int linetype,
                int shift) {
    cv::Point cv_center(center.x, center.y);
    cv::Size cv_axes(axes.width, axes.height);
    cv::Scalar cv_color(color.v0, color.v1, color.v2, color.v3);

    cv::ellipse(*mat, cv_center, cv_axes, angle, start_angle, end_angle, cv_color, thickness, linetype, shift);
}

void cv_cvt_color(cv::Mat* mat, cv::Mat* out, int code) {
    cv::cvtColor(*mat, *out, code);
}

void cv_pyr_down(cv::Mat* mat, cv::Mat* out) {
    cv::pyrDown(*mat, *out);
}

void cv_resize(cv::Mat* from, cv::Mat* to, Size2i dsize, double fx, double fy, int interpolation) {
    cv::Size cv_dsize(dsize.width, dsize.height);
    cv::resize(*from, *to, cv_dsize, fx, fy, interpolation);
}

void cv_calc_hist(const cv::Mat* images,
                  int nimages,
                  const int* channels,
                  cv::Mat* mask,
                  cv::Mat* hist,
                  int dims,
                  const int* hist_size,
                  const float** ranges) {
    cv::calcHist(images, nimages, channels, *mask, *hist, dims, hist_size, ranges);
}

void cv_calc_back_project(const cv::Mat* images,
                          int nimages,
                          const int* channels,
                          cv::Mat* hist,
                          cv::Mat* back_project,
                          const float** ranges) {
    cv::calcBackProject(images, nimages, channels, *hist, *back_project, ranges);
}

void cv_compare_hist(cv::Mat* first_image, cv::Mat* second_image, int method, Result<double>* result) {
    *result = Result<double>::FromFunction(
        [first_image, second_image, method]() { return cv::compareHist(*first_image, *second_image, method); });
}
}

void cv_cvtColor(int* src, int src_len, int* dst, int dst_len, int code, int dstCn) {
    std::vector<int> vsrc(src, src + src_len);
    std::vector<int> vdst(dst, dst + dst_len);
    cv::cvtColor(vsrc, vdst, code, dstCn);
}

unsigned long gif_frame_resize(unsigned char* ptr, unsigned long length, int width, int height, uchar* rptr) {
    std::vector<unsigned char> vptr(ptr, ptr + length);
    cv::Mat r;
    cv::cvtColor(vptr, r, cv::COLOR_RGBA2RGB, 0);
    printf("%s \n", "hello");
    cv::Size dsize = cv::Size(width, height);
    cv::Mat rf = cv::Mat(dsize, CV_32SC3);
    cv::resize(r, rf, dsize);

    cv::Mat rrf = cv::Mat(dsize, CV_32SC4);
    cv::cvtColor(rf, rrf, cv::COLOR_RGB2RGBA, 0);
    rptr = (&rrf)->data;
    return sizeof((&rrf)->data) / sizeof(uchar);
}