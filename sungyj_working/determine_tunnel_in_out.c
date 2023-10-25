// 파일명 : determine_tunnel_in_out.c

/*
	[터널 진입/출차 판단 모듈]
	위쪽 초음파센서, 조도센서 값에 따라 터널 내부인지 판별하는 함수
	출력: 터널 내부인 경우 1,  터널 외부이면 2 (센서값 에러이면 -1)
*/

#include <stdint.h>
#include "determine_tunnel_in_out.h"

int16_t determine_tunnel_in_out() {
	if (lux < 0 || upUltra < 0) return -1;
	else if (  (upUltra < boundary_tunnel_upUltraValue) && (lux > boundary_tunnel_CdsValue)  ) return 1;
	else return 2;
}