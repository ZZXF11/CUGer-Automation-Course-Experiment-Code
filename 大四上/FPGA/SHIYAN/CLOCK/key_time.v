module  key_time(
					input key_time_adj,          		//消除抖动后按键输入,按键输入
					input key_time_switch,          	//消除抖动后按键输入,决定数字前进是时钟还是按键
					input key_clk_timer,             //消除抖动后按键输入,时间输入  
					output key_o    		//经过选择后的按键输出
					);
	assign  key_o=(key_time_switch ? key_time_adj:key_clk_timer);
endmodule
