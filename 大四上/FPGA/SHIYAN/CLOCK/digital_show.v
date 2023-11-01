module  digital_show(
                        input  clk_timer,		// 计数时钟信号输入			
                        input  nRST,			// 复位信号输入
								output [3:0]disp_dat_0,		// 显示数值
								output [3:0]disp_dat_1,
								output [3:0]disp_dat_2,
								output [3:0]disp_dat_3,
								output [3:0]disp_dat_4,
								output [3:0]disp_dat_5,
								output reg LED
                    );
reg [4:0]hour;      	//0-23小时
reg [5:0]minute;     	//0-59分钟
reg [5:0]second;     	//0-59秒						

// 时钟计数
always @(posedge clk_timer or negedge nRST)
begin 
	if(!nRST)					// 时分秒复位
		begin
			hour <= 5'd0;
			minute <= 6'd0;
			second <= 6'd0;
		end
	else
		begin
			second <= second + 1;	// 每个时钟信号到来时，秒+1
            // 如果时间到达59分59秒，点亮LED，否则熄灭LED
			if(second == 6'd59 & minute == 6'd59)	LED = 1'b1;	else LED = 1'b0;
            // 如果秒到达59，对其清零且分钟+1
			if(second == 6'd59)	begin second <= 6'd0; minute <= minute+1'b1; end
            // 如果分钟到达59，对其清零且小时+1
			if(minute == 6'd59) 	begin minute <= 6'd0; hour <= hour + 1'b1;	end
            // 如果小时到达24，对其清零
         if(hour == 5'd24)		begin hour <= 5'd0;	end
		end
end		

			  
assign disp_dat_0 = second % 10;	// 秒个位		
assign disp_dat_1 = second / 10;	// 秒十位		
assign disp_dat_2 = minute % 10;	// 分个位		
assign disp_dat_3 = minute / 10;	// 分十位		
assign disp_dat_4 = hour % 10;		// 时个位	
assign disp_dat_5 = hour / 10;		// 时十位

endmodule
