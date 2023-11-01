module clock(
	input wire clk_50MHz,//50MHz信号输入
	input wire key_A,//速度调节键1
	input wire key_B,//速度调节键2
	input wire time_switch,//时钟与按键选择
	input wire time_adj,//按键选择
	input wire nRST,//复位信号
	output [6:0]HEX0,
	output [6:0]HEX1,
	output [6:0]HEX2,
	output [6:0]HEX3,
	output [6:0]HEX4,
	output [6:0]HEX5,
	output wire LED//LED输出
);

wire key_key_A;
wire key_key_B;
wire key_time_adj;
wire key_time_switch;
wire time_set;
wire time_devide;

wire [3:0]disp_dat_0;
wire [3:0]disp_dat_1;
wire [3:0]disp_dat_2;
wire [3:0]disp_dat_3;
wire [3:0]disp_dat_4;
wire [3:0]disp_dat_5;
////////////////////////////////////////
eliminate_jitters u1(
	.clk(clk_50MHz),
	.key(key_A),
	.nRST(nRST),
	.key_o(key_key_A)
);


eliminate_jitters u2(
	.clk(clk_50MHz),
	.key(key_B),
	.nRST(nRST),
	.key_o(key_key_B)
);


eliminate_jitters u3(
	.clk(clk_50MHz),
	.key(time_adj),
	.nRST(nRST),
	.key_o(key_time_adj)
);

eliminate_jitters u4(
	.clk(clk_50MHz),
	.key(time_switch),
	.nRST(nRST),
	.key_o(key_time_switch)
);

time_devide_timer u5(
	.clk(clk_50MHz),          		//50MHz时钟
	.switch_1(key_key_A),				// 切换频率
	.switch_2(key_key_B),
	.clk_timer(time_devide)
);

key_time u6(
	.key_time_adj(key_time_adj),          		//消除抖动后按键输入,按键输入
	.key_time_switch(key_time_switch),          	//消除抖动后按键输入,决定数字前进是时钟还是按键
	.key_clk_timer(time_devide),             //消除抖动后按键输入,时间输入  
	.key_o(time_set)
);

digital_show u7(
	.clk_timer(time_set),		// 计数时钟信号输入			
   .nRST(nRST),			// 复位信号输入
	.disp_dat_0(disp_dat_0),		// 显示数值
	.disp_dat_1(disp_dat_1),
	.disp_dat_2(disp_dat_2),
	.disp_dat_3(disp_dat_3),
	.disp_dat_4(disp_dat_4),
	.disp_dat_5(disp_dat_5),
	.LED(LED)
);

data_show u8(
	.disp_dat(disp_dat_0),		// 显示数值
	.disp_show(HEX0)
);

data_show u9(
	.disp_dat(disp_dat_1),		// 显示数值
	.disp_show(HEX1)
);

data_show u10(
	.disp_dat(disp_dat_2),		// 显示数值
	.disp_show(HEX2)
);

data_show u11(
	.disp_dat(disp_dat_3),		// 显示数值
	.disp_show(HEX3)
);

data_show u12(
	.disp_dat(disp_dat_4),		// 显示数值
	.disp_show(HEX4)
);

data_show u13(
	.disp_dat(disp_dat_5),		// 显示数值
	.disp_show(HEX5)
);
////////////////////////////////////////

endmodule

