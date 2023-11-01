module time_devide_timer(
					input clk,          		//50MHz时钟
					input switch_1,				// 切换频率
					input switch_2,
					output clk_timer
					);

reg [24:0]count_1 = 25'd0;//计数器
reg [24:0]count_10 = 25'd0;
reg [24:0]count_100 = 25'd0;

reg clk_1_r = 0;//控制电平
reg clk_10_r = 0;
reg clk_100_r = 0;
reg clk_timer_r =0;
assign clk_timer = clk_timer_r; 
////////////////////////////////////////
always @(posedge clk)//0.5s反转一次
begin
	if(count_1 == 25'd24999999)
	begin
		count_1 <= 25'd0;
		clk_1_r <= ~clk_1_r;
	end
	else
		count_1 <= count_1 + 1;
end

always @(posedge clk)//0.05s反转一次
begin
	if(count_10 == 25'd2499999)
	begin
		count_10 <= 25'd0;
		clk_10_r <= ~clk_10_r;
	end
	else
		count_10 <= count_10 + 1;
end

always @(posedge clk)//0.005s反转一次
begin
	if(count_100 == 25'd249999)
	begin
		count_100 <= 25'd0;
		clk_100_r <= ~clk_100_r;
	end
	else
		count_100 <= count_100 + 1;
end
////////////////////////////////////////

always @(clk_1_r or clk_10_r or clk_100_r or switch_1 or switch_2)
	begin
		case({switch_1,switch_2})
			2'b00 :clk_timer_r <= clk_1_r;
			2'b01 :clk_timer_r <= clk_10_r;
			2'b11 :clk_timer_r <= clk_100_r;
			default:clk_timer_r <= clk_1_r;
		endcase
	end
endmodule
