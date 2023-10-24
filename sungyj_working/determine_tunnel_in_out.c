// 파일명 : determine_tunnel_in_out.c

#include "determine_tunnel_in_out.h"

int determine_tunnel_in_out() {
	/*
		위쪽 초음파센서, 조도센서 값에 따라 터널 내부인지 판별하는 함수
		센서값 에러인 경우 -1 반환, 터널 내부인 경우 1,  외부인 경우 2 출력
	*/
	if (lux < 0 || upUltra < 0) return -1;
	else if (  (upUltra < boundary_tunnel_upUltraValue) && (lux > boundary_tunnel_CdsValue)  ) return 1;
	else return 2;
}
