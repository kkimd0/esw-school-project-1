// 파일명 : determine_tunnel_in_out.h

/*
  실험을 통해 터널 내/외부에서의 초음파센서, 조도센서의 임계값을 찾아야 함.
*/

#define boundary_tunnel_upUltraValue  15  	// (실험을 통해 정해야 함)
//  [초음파센서 값은 cm에 가까움]

#define boundary_tunnel_CdsValue  200  		// (실험을 통해 정해야 함)
/*  
	[조도센서 간이 실험 결과]
    손으로 가렸을 때 : 500
		평소 실내에서 : 160
    후레시 가까이서 비췄을 때 : 10
*/


int16_t determine_tunnel_in_out();