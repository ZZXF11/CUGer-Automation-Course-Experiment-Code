//*****************文件信息*********************************************
//**创建日期：   2021.09.08
//**版本号：     version 1.0
//**功能描述：   led灯驱动实验
//**********************************************************************/


module led_twinkle(LEDR,CLOCK_50);
   output [9:0] LEDR;                             //十个LED0-9
	input CLOCK_50;                                   //50M时钟
	reg[9:0] LEDR;                                    // 输出端口定义为寄存器型
	reg[29:0] counter;                                // 中间变量counter定义为寄存器型
	always@(posedge CLOCK_50)                         //在时钟负延跳变
	    begin                                         // 顺序语句，到end止
	    counter<=counter+1;                           //<=与 =区别
			if(counter==30'd25000000) 
			 begin
				LEDR <= 10'b0000000000; 
			 end
			if(counter==30'd50000000) 
			 begin
				LEDR <= 10'b0000000001; 
			 end
			if(counter==30'd75000000) 
			 begin
				LEDR <= 10'b0000000010; 
			 end
			if(counter==30'd100000000) 
			 begin
				LEDR <= 10'b0000000100; 
			 end
			if(counter==30'd125000000) 
			 begin
				LEDR <= 10'b0000001000; 
			 end
			if(counter==30'd150000000) 
			 begin
				LEDR <= 10'b0000010000; 
			 end
			if(counter==30'd175000000) 
			 begin
				LEDR <= 10'b0000100000; 
			 end
			if(counter==30'd200000000) 
			 begin
				LEDR <= 10'b0001000000; 
			 end
			if(counter==30'd225000000) 
			 begin
				LEDR <= 10'b0010000000; 
			end
			if(counter==30'd250000000) 
			 begin
				LEDR <= 10'b0100000000; 
			end
			if(counter==30'd275000000) 
			 begin
				LEDR <= 10'b1000000000; 
				counter<=0;
			end
	    end                      
endmodule