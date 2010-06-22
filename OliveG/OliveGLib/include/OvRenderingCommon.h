#pragma once
#include <vector>


class OvPoint3;
struct OvFace
{
	OvFace():_1(0),_2(0),_3(0){};
	short _1;
	short _2;
	short _3;
};

typedef std::vector<OvPoint3> vertex_buffer;
typedef std::vector<OvFace>	  face_buffer;