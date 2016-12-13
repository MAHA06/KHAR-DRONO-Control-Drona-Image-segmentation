/*********************************************************************
 * This file is distributed as part of the C++ port of the APRIL tags
 * library. The code is licensed under GPLv2.
 *
 * Original author: Edwin Olson <ebolson@umich.edu>
 * C++ port and modifications: Matt Zucker <mzucker1@swarthmore.edu>
 ********************************************************************/

#include "Refine.h"
#include <iostream>
//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

at::Point interpolateH(const at::Mat& H, const at::Point& uv, at::Mat* pdxydh) {

  at::real hx = H[0][0]*uv.x + H[0][1]*uv.y + H[0][2];
  at::real hy = H[1][0]*uv.x + H[1][1]*uv.y + H[1][2];
  at::real hw = H[2][0]*uv.x + H[2][1]*uv.y + H[2][2];

  if (pdxydh) {

    at::Mat& dxydh = *pdxydh;
    if (dxydh.rows != 2 || dxydh.cols != 8) { dxydh = at::Mat(2,8); }

    dxydh[0][0] = uv.x/hw;
    dxydh[0][1] = uv.y/hw;
    dxydh[0][2] = 1/hw;
    dxydh[0][3] = 0;
    dxydh[0][4] = 0;
    dxydh[0][5] = 0;
    at::real tmp0 = hw*hw;
    dxydh[0][6] = -(hx*uv.x)/tmp0;
    dxydh[0][7] = -(hx*uv.y)/tmp0;
    dxydh[1][0] = 0;
    dxydh[1][1] = 0;
    dxydh[1][2] = 0;
    dxydh[1][3] = uv.x/hw;
    dxydh[1][4] = uv.y/hw;
    dxydh[1][5] = 1/hw;
    dxydh[1][6] = -(hy*uv.x)/tmp0;
    dxydh[1][7] = -(hy*uv.y)/tmp0;
    

  }

  return at::Point(hx/hw, hy/hw);


}

// MZ notes: Pretty sure this code is autogenerated. Too bad I might
// have lost the program that did this :)
void computeH(const at::Point p[4], at::Mat& H, at::Mat* pdhdp) {

  if (H.rows != 3 || H.cols != 3) { H = at::Mat(3,3); }

  at::real tmp0 = p[0].x*p[2].x;
  at::real tmp1 = tmp0*p[1].y;
  at::real tmp2 = p[1].x*p[2].x;
  at::real tmp3 = p[0].x*p[3].x;
  at::real tmp4 = p[1].x*p[3].x;
  at::real tmp5 = tmp4*p[0].y;
  at::real tmp6 = tmp0*p[3].y;
  at::real tmp7 = tmp4*p[2].y;
  at::real tmp8 = tmp1 - tmp2*p[0].y - tmp3*p[1].y + tmp5 - tmp6 + tmp3*p[2].y + tmp2*p[3].y - tmp7;
  at::real tmp9 = p[1].x*p[2].y;
  at::real tmp10 = p[2].x*p[1].y;
  at::real tmp11 = tmp9 - tmp10;
  at::real tmp12 = p[1].x*p[3].y;
  at::real tmp13 = tmp11 - tmp12;
  at::real tmp14 = p[3].x*p[1].y;
  at::real tmp15 = p[2].x*p[3].y;
  at::real tmp16 = p[3].x*p[2].y;
  at::real tmp17 = tmp13 + tmp14 + tmp15 - tmp16;
  H[0][0] = tmp8/tmp17;
  at::real tmp18 = p[0].x*p[1].x;
  at::real tmp19 = p[2].x*p[3].x;
  at::real tmp20 = tmp18*p[2].y - tmp1 - tmp18*p[3].y + tmp5 + tmp6 - tmp19*p[0].y - tmp7 + tmp19*p[1].y;
  H[0][1] = -tmp20/tmp17;
  H[0][2] = p[0].x;
  at::real tmp21 = p[0].x*p[1].y;
  at::real tmp22 = p[1].x*p[0].y;
  at::real tmp23 = tmp22*p[2].y;
  at::real tmp24 = tmp21*p[3].y;
  at::real tmp25 = p[2].x*p[0].y;
  at::real tmp26 = p[3].x*p[0].y;
  at::real tmp27 = tmp26*p[2].y;
  at::real tmp28 = tmp10*p[3].y;
  at::real tmp29 = tmp21*p[2].y - tmp23 - tmp24 + tmp22*p[3].y - tmp25*p[3].y + tmp27 + tmp28 - tmp14*p[2].y;
  H[1][0] = tmp29/tmp17;
  at::real tmp30 = p[0].x*p[2].y;
  at::real tmp31 = tmp23 - tmp25*p[1].y - tmp24 + tmp26*p[1].y + tmp30*p[3].y - tmp27 - tmp9*p[3].y + tmp28;
  H[1][1] = -tmp31/tmp17;
  H[1][2] = p[0].y;
  at::real tmp32 = p[0].x*p[3].y;
  at::real tmp33 = tmp30 - tmp25 - tmp32 - tmp9 + tmp10 + tmp26 + tmp12 - tmp14;
  H[2][0] = tmp33/tmp17;
  at::real tmp34 = tmp21 - tmp22;
  at::real tmp35 = tmp34 - tmp30 + tmp25 + tmp12 - tmp14 - tmp15 + tmp16;
  H[2][1] = tmp35/tmp17;
  H[2][2] = 1;


  if (pdhdp) {

    at::Mat& dhdp = *pdhdp;
    if (dhdp.rows != 8 || dhdp.cols != 8) { dhdp = at::Mat(8,8); }

    dhdp[0][0] = (tmp10 - tmp14 - tmp15 + tmp16)/tmp17;
    dhdp[0][1] = (-tmp2 + tmp4)/tmp17;
    at::real tmp36 = p[2].y - p[3].y;
    at::real tmp37 = tmp17*tmp17;
    dhdp[0][2] = ((-tmp25 + tmp26 + tmp15 - tmp16)*tmp17 - tmp8*tmp36)/tmp37;
    at::real tmp38 = -p[2].x + p[3].x;
    dhdp[0][3] = ((tmp0 - tmp3)*tmp17 - tmp8*tmp38)/tmp37;
    at::real tmp39 = -p[1].y + p[3].y;
    dhdp[0][4] = ((tmp34 - tmp32 + tmp12)*tmp17 - tmp8*tmp39)/tmp37;
    at::real tmp40 = p[1].x - p[3].x;
    dhdp[0][5] = ((tmp3 - tmp4)*tmp17 - tmp8*tmp40)/tmp37;
    at::real tmp41 = -tmp21 + tmp22;
    at::real tmp42 = p[1].y - p[2].y;
    dhdp[0][6] = ((tmp41 + tmp30 - tmp9)*tmp17 - tmp8*tmp42)/tmp37;
    at::real tmp43 = -p[1].x + p[2].x;
    dhdp[0][7] = ((-tmp0 + tmp2)*tmp17 - tmp8*tmp43)/tmp37;
    dhdp[1][0] = -(tmp13 + tmp15)/tmp17;
    dhdp[1][1] = -(tmp4 - tmp19)/tmp17;
    at::real tmp44 = tmp30 - tmp32;
    dhdp[1][2] = -((tmp44 + tmp26 - tmp16)*tmp17 - tmp20*tmp36)/tmp37;
    dhdp[1][3] = -((-tmp0 + tmp19)*tmp17 - tmp20*tmp38)/tmp37;
    dhdp[1][4] = -((-tmp21 + tmp32 - tmp26 + tmp14)*tmp17 - tmp20*tmp39)/tmp37;
    dhdp[1][5] = -((tmp18 - tmp4)*tmp17 - tmp20*tmp40)/tmp37;
    dhdp[1][6] = -((tmp22 - tmp25 - tmp9 + tmp10)*tmp17 - tmp20*tmp42)/tmp37;
    dhdp[1][7] = -((-tmp18 + tmp0)*tmp17 - tmp20*tmp43)/tmp37;
    dhdp[2][0] = 1;
    dhdp[2][1] = 0;
    dhdp[2][2] = 0;
    dhdp[2][3] = 0;
    dhdp[2][4] = 0;
    dhdp[2][5] = 0;
    dhdp[2][6] = 0;
    dhdp[2][7] = 0;
    at::real tmp45 = p[1].y*p[2].y;
    at::real tmp46 = p[1].y*p[3].y;
    dhdp[3][0] = (tmp45 - tmp46)/tmp17;
    dhdp[3][1] = (-tmp9 + tmp12 - tmp15 + tmp16)/tmp17;
    at::real tmp47 = p[0].y*p[2].y;
    at::real tmp48 = p[0].y*p[3].y;
    dhdp[3][2] = ((-tmp47 + tmp48)*tmp17 - tmp29*tmp36)/tmp37;
    dhdp[3][3] = ((tmp44 + tmp15 - tmp16)*tmp17 - tmp29*tmp38)/tmp37;
    dhdp[3][4] = ((-tmp48 + tmp46)*tmp17 - tmp29*tmp39)/tmp37;
    dhdp[3][5] = ((tmp34 + tmp26 - tmp14)*tmp17 - tmp29*tmp40)/tmp37;
    dhdp[3][6] = ((tmp47 - tmp45)*tmp17 - tmp29*tmp42)/tmp37;
    dhdp[3][7] = ((tmp41 - tmp25 + tmp10)*tmp17 - tmp29*tmp43)/tmp37;
    at::real tmp49 = p[2].y*p[3].y;
    dhdp[4][0] = -(-tmp46 + tmp49)/tmp17;
    dhdp[4][1] = -(tmp11 + tmp14 - tmp16)/tmp17;
    dhdp[4][2] = -((tmp47 - tmp49)*tmp17 - tmp31*tmp36)/tmp37;
    dhdp[4][3] = -((-tmp25 - tmp32 + tmp26 + tmp15)*tmp17 - tmp31*tmp38)/tmp37;
    at::real tmp50 = p[0].y*p[1].y;
    dhdp[4][4] = -((-tmp50 + tmp46)*tmp17 - tmp31*tmp39)/tmp37;
    dhdp[4][5] = -((tmp22 + tmp32 - tmp26 - tmp12)*tmp17 - tmp31*tmp40)/tmp37;
    dhdp[4][6] = -((tmp50 - tmp47)*tmp17 - tmp31*tmp42)/tmp37;
    dhdp[4][7] = -((-tmp21 + tmp30 - tmp9 + tmp10)*tmp17 - tmp31*tmp43)/tmp37;
    dhdp[5][0] = 0;
    dhdp[5][1] = 1;
    dhdp[5][2] = 0;
    dhdp[5][3] = 0;
    dhdp[5][4] = 0;
    dhdp[5][5] = 0;
    dhdp[5][6] = 0;
    dhdp[5][7] = 0;
    dhdp[6][0] = tmp36/tmp17;
    dhdp[6][1] = tmp38/tmp17;
    dhdp[6][2] = ((-p[2].y + p[3].y)*tmp17 - tmp33*tmp36)/tmp37;
    dhdp[6][3] = ((p[2].x - p[3].x)*tmp17 - tmp33*tmp38)/tmp37;
    dhdp[6][4] = ((-p[0].y + p[1].y)*tmp17 - tmp33*tmp39)/tmp37;
    dhdp[6][5] = ((p[0].x - p[1].x)*tmp17 - tmp33*tmp40)/tmp37;
    dhdp[6][6] = ((p[0].y - p[1].y)*tmp17 - tmp33*tmp42)/tmp37;
    dhdp[6][7] = ((-p[0].x + p[1].x)*tmp17 - tmp33*tmp43)/tmp37;
    dhdp[7][0] = tmp42/tmp17;
    dhdp[7][1] = tmp43/tmp17;
    dhdp[7][2] = ((-p[0].y + p[3].y)*tmp17 - tmp35*tmp36)/tmp37;
    dhdp[7][3] = ((p[0].x - p[3].x)*tmp17 - tmp35*tmp38)/tmp37;
    dhdp[7][4] = ((p[0].y - p[3].y)*tmp17 - tmp35*tmp39)/tmp37;
    dhdp[7][5] = ((-p[0].x + p[3].x)*tmp17 - tmp35*tmp40)/tmp37;
    dhdp[7][6] = ((-p[1].y + p[2].y)*tmp17 - tmp35*tmp42)/tmp37;
    dhdp[7][7] = ((p[1].x - p[2].x)*tmp17 - tmp35*tmp43)/tmp37;

  }

}

// MZ notes: Pretty sure this code is autogenerated. Too bad I might
// have lost the program that did this :)

at::Point interpolate(const at::Point p[4], const at::Point& uv, at::Mat* pJ) {

  at::real tmp0 = p[1].x*p[2].y;
  at::real tmp1 = p[2].x*p[1].y;
  at::real tmp2 = tmp0 - tmp1;
  at::real tmp3 = p[1].x*p[3].y;
  at::real tmp4 = tmp2 - tmp3;
  at::real tmp5 = p[3].x*p[1].y;
  at::real tmp6 = p[2].x*p[3].y;
  at::real tmp7 = p[3].x*p[2].y;
  at::real tmp8 = tmp4 + tmp5 + tmp6 - tmp7;
  at::real tmp9 = p[0].x*p[2].x;
  at::real tmp10 = tmp9*p[1].y;
  at::real tmp11 = p[1].x*p[2].x;
  at::real tmp12 = p[0].x*p[3].x;
  at::real tmp13 = p[1].x*p[3].x;
  at::real tmp14 = tmp13*p[0].y;
  at::real tmp15 = tmp9*p[3].y;
  at::real tmp16 = tmp13*p[2].y;
  at::real tmp17 = tmp10 - tmp11*p[0].y - tmp12*p[1].y + tmp14 - tmp15 + tmp12*p[2].y + tmp11*p[3].y - tmp16;
  at::real tmp18 = p[0].x*p[1].x;
  at::real tmp19 = p[2].x*p[3].x;
  at::real tmp20 = tmp18*p[2].y - tmp10 - tmp18*p[3].y + tmp14 + tmp15 - tmp19*p[0].y - tmp16 + tmp19*p[1].y;
  at::real tmp21 = p[0].x*p[1].y;
  at::real tmp22 = p[1].x*p[0].y;
  at::real tmp23 = tmp22*p[2].y;
  at::real tmp24 = tmp21*p[3].y;
  at::real tmp25 = p[2].x*p[0].y;
  at::real tmp26 = p[3].x*p[0].y;
  at::real tmp27 = tmp26*p[2].y;
  at::real tmp28 = tmp1*p[3].y;
  at::real tmp29 = tmp21*p[2].y - tmp23 - tmp24 + tmp22*p[3].y - tmp25*p[3].y + tmp27 + tmp28 - tmp5*p[2].y;
  at::real tmp30 = p[0].x*p[2].y;
  at::real tmp31 = tmp23 - tmp25*p[1].y - tmp24 + tmp26*p[1].y + tmp30*p[3].y - tmp27 - tmp0*p[3].y + tmp28;
  at::real tmp32 = p[0].x*p[3].y;
  at::real tmp33 = tmp30 - tmp25 - tmp32 - tmp0 + tmp1 + tmp26 + tmp3 - tmp5;
  at::real tmp34 = tmp21 - tmp22;
  at::real tmp35 = tmp34 - tmp30 + tmp25 + tmp3 - tmp5 - tmp6 + tmp7;
  at::real hx = (tmp17/tmp8)*uv.x - (tmp20/tmp8)*uv.y + p[0].x;
  at::real hy = (tmp29/tmp8)*uv.x - (tmp31/tmp8)*uv.y + p[0].y;
  at::real hw = (tmp33/tmp8)*uv.x + (tmp35/tmp8)*uv.y + 1;

  if (pJ) {

    at::Mat& J = *pJ;
    if (J.rows != 2 || J.cols != 8) { J = at::Mat(2,8); }

    at::real tmp36 = tmp8*tmp8;
    at::real tmp37 = p[2].y - p[3].y;
    at::real tmp38 = p[1].y - p[2].y;
    at::real tmp39 = ((tmp37*tmp8)/tmp36)*uv.x + ((tmp38*tmp8)/tmp36)*uv.y;
    at::real tmp40 = hw*hw;
    J[0][0] = (((((tmp1 - tmp5 - tmp6 + tmp7)*tmp8)/tmp36)*uv.x - (((tmp4 + tmp6)*tmp8)/tmp36)*uv.y + 1)*hw - hx*tmp39)/tmp40;
    at::real tmp41 = -p[2].x + p[3].x;
    at::real tmp42 = -p[1].x + p[2].x;
    at::real tmp43 = ((tmp41*tmp8)/tmp36)*uv.x + ((tmp42*tmp8)/tmp36)*uv.y;
    J[0][1] = (((((-tmp11 + tmp13)*tmp8)/tmp36)*uv.x - (((tmp13 - tmp19)*tmp8)/tmp36)*uv.y)*hw - hx*tmp43)/tmp40;
    at::real tmp44 = tmp30 - tmp32;
    at::real tmp45 = (((-p[2].y + p[3].y)*tmp8 - tmp33*tmp37)/tmp36)*uv.x + (((-p[0].y + p[3].y)*tmp8 - tmp35*tmp37)/tmp36)*uv.y;
    J[0][2] = (((((-tmp25 + tmp26 + tmp6 - tmp7)*tmp8 - tmp17*tmp37)/tmp36)*uv.x - (((tmp44 + tmp26 - tmp7)*tmp8 - tmp20*tmp37)/tmp36)*uv.y)*hw - hx*tmp45)/tmp40;
    at::real tmp46 = (((p[2].x - p[3].x)*tmp8 - tmp33*tmp41)/tmp36)*uv.x + (((p[0].x - p[3].x)*tmp8 - tmp35*tmp41)/tmp36)*uv.y;
    J[0][3] = (((((tmp9 - tmp12)*tmp8 - tmp17*tmp41)/tmp36)*uv.x - (((-tmp9 + tmp19)*tmp8 - tmp20*tmp41)/tmp36)*uv.y)*hw - hx*tmp46)/tmp40;
    at::real tmp47 = -p[1].y + p[3].y;
    at::real tmp48 = (((-p[0].y + p[1].y)*tmp8 - tmp33*tmp47)/tmp36)*uv.x + (((p[0].y - p[3].y)*tmp8 - tmp35*tmp47)/tmp36)*uv.y;
    J[0][4] = (((((tmp34 - tmp32 + tmp3)*tmp8 - tmp17*tmp47)/tmp36)*uv.x - (((-tmp21 + tmp32 - tmp26 + tmp5)*tmp8 - tmp20*tmp47)/tmp36)*uv.y)*hw - hx*tmp48)/tmp40;
    at::real tmp49 = p[1].x - p[3].x;
    at::real tmp50 = (((p[0].x - p[1].x)*tmp8 - tmp33*tmp49)/tmp36)*uv.x + (((-p[0].x + p[3].x)*tmp8 - tmp35*tmp49)/tmp36)*uv.y;
    J[0][5] = (((((tmp12 - tmp13)*tmp8 - tmp17*tmp49)/tmp36)*uv.x - (((tmp18 - tmp13)*tmp8 - tmp20*tmp49)/tmp36)*uv.y)*hw - hx*tmp50)/tmp40;
    at::real tmp51 = -tmp21 + tmp22;
    at::real tmp52 = (((p[0].y - p[1].y)*tmp8 - tmp33*tmp38)/tmp36)*uv.x + (((-p[1].y + p[2].y)*tmp8 - tmp35*tmp38)/tmp36)*uv.y;
    J[0][6] = (((((tmp51 + tmp30 - tmp0)*tmp8 - tmp17*tmp38)/tmp36)*uv.x - (((tmp22 - tmp25 - tmp0 + tmp1)*tmp8 - tmp20*tmp38)/tmp36)*uv.y)*hw - hx*tmp52)/tmp40;
    at::real tmp53 = p[1].y*p[2].y;
    at::real tmp54 = (((-p[0].x + p[1].x)*tmp8 - tmp33*tmp42)/tmp36)*uv.x + (((p[1].x - p[2].x)*tmp8 - tmp35*tmp42)/tmp36)*uv.y;
    J[0][7] = (((((-tmp9 + tmp11)*tmp8 - tmp17*tmp42)/tmp36)*uv.x - (((-tmp18 + tmp9)*tmp8 - tmp20*tmp42)/tmp36)*uv.y)*hw - hx*tmp54)/tmp40;
    at::real tmp55 = p[1].y*p[3].y;
    at::real tmp56 = p[2].y*p[3].y;
    J[1][0] = (((((tmp53 - tmp55)*tmp8)/tmp36)*uv.x - (((-tmp55 + tmp56)*tmp8)/tmp36)*uv.y)*hw - hy*tmp39)/tmp40;
    J[1][1] = (((((-tmp0 + tmp3 - tmp6 + tmp7)*tmp8)/tmp36)*uv.x - (((tmp2 + tmp5 - tmp7)*tmp8)/tmp36)*uv.y + 1)*hw - hy*tmp43)/tmp40;
    at::real tmp57 = p[0].y*p[2].y;
    at::real tmp58 = p[0].y*p[3].y;
    J[1][2] = (((((-tmp57 + tmp58)*tmp8 - tmp29*tmp37)/tmp36)*uv.x - (((tmp57 - tmp56)*tmp8 - tmp31*tmp37)/tmp36)*uv.y)*hw - hy*tmp45)/tmp40;
    J[1][3] = (((((tmp44 + tmp6 - tmp7)*tmp8 - tmp29*tmp41)/tmp36)*uv.x - (((-tmp25 - tmp32 + tmp26 + tmp6)*tmp8 - tmp31*tmp41)/tmp36)*uv.y)*hw - hy*tmp46)/tmp40;
    at::real tmp59 = p[0].y*p[1].y;
    J[1][4] = (((((-tmp58 + tmp55)*tmp8 - tmp29*tmp47)/tmp36)*uv.x - (((-tmp59 + tmp55)*tmp8 - tmp31*tmp47)/tmp36)*uv.y)*hw - hy*tmp48)/tmp40;
    J[1][5] = (((((tmp34 + tmp26 - tmp5)*tmp8 - tmp29*tmp49)/tmp36)*uv.x - (((tmp22 + tmp32 - tmp26 - tmp3)*tmp8 - tmp31*tmp49)/tmp36)*uv.y)*hw - hy*tmp50)/tmp40;
    J[1][6] = (((((tmp57 - tmp53)*tmp8 - tmp29*tmp38)/tmp36)*uv.x - (((tmp59 - tmp57)*tmp8 - tmp31*tmp38)/tmp36)*uv.y)*hw - hy*tmp52)/tmp40;
    J[1][7] = (((((tmp51 - tmp25 + tmp1)*tmp8 - tmp29*tmp42)/tmp36)*uv.x - (((-tmp21 + tmp30 - tmp0 + tmp1)*tmp8 - tmp31*tmp42)/tmp36)*uv.y)*hw - hy*tmp54)/tmp40;

  }

  return at::Point(hx/hw, hy/hw);

}



void drawPoint(cv::Mat& m, const at::Point& p, 
               const cv::Scalar& color, at::real sz, int thickness) {
  //cv::Point dp(sz, sz);
  //cv::rectangle(m, p-dp, p+dp, color, 1, 4);
  const int shift = 2;
  const int ss = (1 << shift);
  cv::circle(m, p*ss, sz*ss, color, thickness, CV_AA, shift);
}

void drawArrow(cv::Mat& m, const at::Point& p, const at::Point& g, 
               const cv::Scalar& color, at::real scl) {

  const int shift = 2;
  const int ss = (1 << shift);

  cv::line(m, ss*p, ss*(p+g*scl), color, 1, CV_AA, shift);

}

void dilate(cv::Rect& r, int b, const cv::Size& sz) {

  int x0 = r.x;
  int y0 = r.y;

  int x1 = x0 + r.width - 1;
  int y1 = y0 + r.height - 1;

  x0 = borderInterpolate(x0-b, sz.width, cv::BORDER_REPLICATE);
  x1 = borderInterpolate(x1+b, sz.width, cv::BORDER_REPLICATE);

  y0 = borderInterpolate(y0-b, sz.height, cv::BORDER_REPLICATE);
  y1 = borderInterpolate(y1+b, sz.height, cv::BORDER_REPLICATE);

  r.x = x0;
  r.y = y0;
  r.width = x1-x0+1;
  r.height = y1-y0+1;

}

cv::Rect boundingRect(const at::Point p[4], const cv::Size& sz) {

  // get the rectangle
  int x0 = p[0].x, x1 = p[0].x, y0 = p[0].y, y1 = p[0].y;
  
  for (int i=0; i<4; ++i) {

    x0 = std::min(x0, int(p[i].x));
    y0 = std::min(y0, int(p[i].y));

    x1 = std::max(x1, int(p[i].x)+1);
    y1 = std::max(y1, int(p[i].y)+1);

  }

  x0 = std::max(x0, 0);
  x1 = std::min(x1, sz.width);

  y0 = std::max(y0, 0);
  y1 = std::min(y1, sz.height);

  int w = x1-x0;
  int h = y1-y0;

  return cv::Rect(x0, y0, w, h);

}


#define NEWINTERP
//#define OLDINTERP

static cv::Mat enlarge(const cv::Mat& image, int scl) {
  cv::Mat big;
  cv::resize(image, big, cv::Size(scl*image.cols, scl*image.rows), 
             0, 0, CV_INTER_CUBIC);
  return big;
}

int refineQuad(const cv::Mat& gmat,
               const at::Mat& gx,
               const at::Mat& gy,
               at::Point p[4],
               const TPointArray& tpoints,
               bool debug,
               int max_iter,
               at::real max_grad) {

  assert( gmat.type() == CV_8UC1 );

  cv::Mat_<unsigned char> gimage = gmat;

  cv::Rect rect = boundingRect(p, gimage.size());

  cv::Mat subimage(gimage, rect);
  double dmin, dmax;
  cv::minMaxLoc(subimage, &dmin, &dmax);
  at::real amin = dmin;
  at::real amax = dmax;
  at::real ascl = 255 / (amax - amin);

  at::real gnscl = at::real(1) / (tpoints.size() * 255 * 255);

  bool done = false;
  int iter;


#ifdef NEWINTERP
  at::Mat H(3,3), dhdp(8,8), dxydh(2,8), didh(1,8), didp(8,1);
#endif

#ifdef OLDINTERP
  at::Mat dxydp(2,8), didp2(8,1);
#endif
  
  for (iter=0; iter<max_iter && !done; ++iter) {

    at::Mat g = at::Mat::zeros(8, 1);
    at::real err = 0;

    cv::Mat debug_big;
    int debug_scl = 16;
    at::Point debug_delta;

    if (debug) {

      int border = 4;

      cv::Mat gsmall = subimageWithBorder(gimage, rect, border);
      gsmall = (gsmall - amin) * ascl;

      cv::Mat gbig = enlarge(gsmall, debug_scl);

      debug_delta = at::Point(border-rect.x, border-rect.y);

      cv::cvtColor(gbig, debug_big, CV_GRAY2RGB);
      for (int i=0; i<4; ++i) {
        drawPoint(debug_big, (p[i]+debug_delta)*debug_scl, CV_RGB(255,0,0));
      }
      
    }

#ifdef NEWINTERP
    computeH(p, H, &dhdp);
#endif

    for (size_t i=0; i<tpoints.size(); ++i) {

      const TPoint& tpi = tpoints[i];

#ifdef NEWINTERP
      at::Point pi = interpolateH(H, tpi.p, &dxydh);
#endif

#ifdef OLDINTERP
      at::Point pi2 = interpolate(p, tpi.p, &dxydp);
#ifndef NEWINTERP
      at::Point pi = pi2;
#endif
#endif

#if defined(NEWINTERP) && defined(OLDINTERP)
      std::cout << "these should be equal:\n";
      std::cout << pi << "\n";
      std::cout << pi2 << "\n";

      std::cout << "these should be equal:\n";
      std::cout << dxydh * dhdp << "\n";
      std::cout << dxydp << "\n";
#endif

      at::real oi = (bicubicInterpolate(gimage, pi) - amin) * ascl;
      
      at::Point didxy = at::Point( bicubicInterpolate(gx, pi), 
                                   bicubicInterpolate(gy, pi) ) * ascl;
      
      at::real ti = tpi.t;
      
      at::real ei = ti - oi;
      err += ei * ei;

#ifdef NEWINTERP

      didh(0) = didxy.x*dxydh[0][0];
      didh(1) = didxy.x*dxydh[0][1];
      didh(2) = didxy.x*dxydh[0][2];
      didh(3) = didxy.y*dxydh[1][3];
      didh(4) = didxy.y*dxydh[1][4];
      didh(5) = didxy.y*dxydh[1][5];
      didh(6) = didxy.x*dxydh[0][6] + didxy.y*dxydh[1][6];
      didh(7) = didxy.x*dxydh[0][7] + didxy.y*dxydh[1][7];

      didp(0) = didh(0)*dhdp[0][0] + didh(1)*dhdp[1][0] + didh(2)*dhdp[2][0] + didh(3)*dhdp[3][0] + didh(4)*dhdp[4][0] + didh(6)*dhdp[6][0] + didh(7)*dhdp[7][0];
      didp(1) = didh(0)*dhdp[0][1] + didh(1)*dhdp[1][1] + didh(3)*dhdp[3][1] + didh(4)*dhdp[4][1] + didh(5)*dhdp[5][1] + didh(6)*dhdp[6][1] + didh(7)*dhdp[7][1];
      didp(2) = didh(0)*dhdp[0][2] + didh(1)*dhdp[1][2] + didh(3)*dhdp[3][2] + didh(4)*dhdp[4][2] + didh(6)*dhdp[6][2] + didh(7)*dhdp[7][2];
      didp(3) = didh(0)*dhdp[0][3] + didh(1)*dhdp[1][3] + didh(3)*dhdp[3][3] + didh(4)*dhdp[4][3] + didh(6)*dhdp[6][3] + didh(7)*dhdp[7][3];
      didp(4) = didh(0)*dhdp[0][4] + didh(1)*dhdp[1][4] + didh(3)*dhdp[3][4] + didh(4)*dhdp[4][4] + didh(6)*dhdp[6][4] + didh(7)*dhdp[7][4];
      didp(5) = didh(0)*dhdp[0][5] + didh(1)*dhdp[1][5] + didh(3)*dhdp[3][5] + didh(4)*dhdp[4][5] + didh(6)*dhdp[6][5] + didh(7)*dhdp[7][5];
      didp(6) = didh(0)*dhdp[0][6] + didh(1)*dhdp[1][6] + didh(3)*dhdp[3][6] + didh(4)*dhdp[4][6] + didh(6)*dhdp[6][6] + didh(7)*dhdp[7][6];
      didp(7) = didh(0)*dhdp[0][7] + didh(1)*dhdp[1][7] + didh(3)*dhdp[3][7] + didh(4)*dhdp[4][7] + didh(6)*dhdp[6][7] + didh(7)*dhdp[7][7];

      g += ei * didp;

#endif

#ifdef OLDINTERP
      for (int j=0; j<8; ++j) {
        at::real Jij = didxy.x * dxydp(0, j) + didxy.y * dxydp(1, j);
        didp2(j,0) = Jij;
      }
#ifndef NEWINTERP
      g += ei * didp2;
#endif
#endif
      
      if (debug) {

        cv::Scalar color = tpi.t ? CV_RGB(0,255,0) : CV_RGB(0,0,255);

        drawPoint( debug_big, (pi+debug_delta)*debug_scl, color );
        drawArrow( debug_big, (pi+debug_delta)*debug_scl, ei * didxy, color, 1e-3 );

      }
      
    }
    
    at::real gn = cv::norm(g)*gnscl;

    if (gn < max_grad || iter+1 == max_iter) { done = true; }

    at::real ss = 4e-6;

    for (int i=0; i<4; ++i) {
      p[i].x += ss*g(2*i+0, 0);
      p[i].y += ss*g(2*i+1, 0);
    }

    if (debug) {

      if (iter == 0 || done) {

        std::cout << "at iter " << iter+1 << ":\n";
        std::cout << "err = " << err << "\n";
        std::cout << "grad. norm = " << gn << " (scaled=" << gn/gnscl << ")\n";
        std::cout << "\n";

      }

      //cv::namedWindow("image");
      //cv::imshow("image", debug_big);
      //cv::waitKey();

    }

  }

  return iter;

}
