#ifndef _DDS_WAVEFORMS_H_
#define _DDS_WAVEFORMS_H_ 1

const int8_t DDS_fullSine[256] = {
  0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 34, 37, 39, 42, 45, 48, 51, 54, 57,
  60, 62, 65, 68, 70, 73, 75, 78, 80, 83, 85, 87, 90, 92, 94, 96, 98, 100, 102,
  104, 106, 107, 109, 110, 112, 113, 115, 116, 117, 118, 120, 121, 122, 122,
  123, 124, 125, 125, 126, 126, 126, 127, 127, 127, 127, 127, 127, 127, 126,
  126, 126, 125, 125, 124, 123, 122, 122, 121, 120, 118, 117, 116, 115, 113,
  112, 110, 109, 107, 106, 104, 102, 100, 98, 96, 94, 92, 90, 87, 85, 83, 80,
  78, 75, 73, 70, 68, 65, 62, 60, 57, 54, 51, 48, 45, 42, 39, 37, 34, 30, 27,
  24, 21, 18, 15, 12, 9, 6, 3, 0, -4, -7, -10, -13, -16, -19, -22, -25, -28,
  -31, -35, -38, -40, -43, -46, -49, -52, -55, -58, -61, -63, -66, -69, -71,
  -74, -76, -79, -81, -84, -86, -88, -91, -93, -95, -97, -99, -101, -103, -105,
  -107, -108, -110, -111, -113, -114, -116, -117, -118, -119, -121, -122, -123,
  -123, -124, -125, -126, -126, -127, -127, -127, -128, -128, -128, -128, -128,
  -128, -128, -127, -127, -127, -126, -126, -125, -124, -123, -123, -122, -121,
  -119, -118, -117, -116, -114, -113, -111, -110, -108, -107, -105, -103, -101,
  -99, -97, -95, -93, -91, -88, -86, -84, -81, -79, -76, -74, -71, -69, -66,
  -63, -61, -58, -55, -52, -49, -46, -43, -40, -38, -35, -31, -28, -25, -22,
  -19, -16, -13, -10, -7, -4
};

const int8_t DDS_fullSaw[256] = { 0, 1, 3, 4, 5, 6, 7, 7, 7, 7, 7, 7, 8, 9, 10,
  12, 13, 15, 17, 18, 20, 21, 21, 22, 22, 22, 22, 22, 22, 23, 24, 25, 27, 29,
  31, 33, 34, 35, 36, 36, 36, 36, 36, 36, 36, 37, 38, 39, 41, 43, 45, 47, 48,
  50, 51, 51, 51, 51, 51, 51, 51, 51, 52, 53, 54, 56, 58, 61, 63, 64, 66, 66,
  67, 66, 66, 65, 65, 65, 65, 66, 68, 70, 72, 75, 77, 79, 81, 82, 82, 82, 81,
  80, 79, 78, 78, 78, 80, 82, 85, 88, 92, 95, 97, 99, 100, 99, 98, 95, 93, 90,
  88, 88, 89, 91, 96, 101, 108, 115, 121, 125, 127, 125, 119, 108, 93, 74, 51,
  26, 0, -27, -52, -75, -94, -109, -120, -126, -128, -126, -122, -116, -109,
  -102, -97, -92, -90, -89, -89, -91, -94, -96, -99, -100, -101, -100, -98,
  -96, -93, -89, -86, -83, -81, -79, -79, -79, -80, -81, -82, -83, -83, -83,
  -82, -80, -78, -76, -73, -71, -69, -67, -66, -66, -66, -66, -67, -67, -68,
  -67, -67, -65, -64, -62, -59, -57, -55, -54, -53, -52, -52, -52, -52, -52,
  -52, -52, -52, -51, -49, -48, -46, -44, -42, -40, -39, -38, -37, -37, -37,
  -37, -37, -37, -37, -36, -35, -34, -32, -30, -28, -26, -25, -24, -23, -23,
  -23, -23, -23, -23, -22, -22, -21, -19, -18, -16, -14, -13, -11, -10, -9, -8,
  -8, -8, -8, -8, -8, -7, -6, -5, -4, -2
};

#endif /* _DDS_WAVEFORMS_H_ */