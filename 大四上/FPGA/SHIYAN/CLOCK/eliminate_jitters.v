module  eliminate_jitters(
					input clk,          		//50MHz时钟
					input key,          		//原始的按键输入
					input nRST,
					output clk_5KHz,     
					output reg key_o    		//经过消抖后的按键输出
					);

reg [20:0]cnt;									//定义一个21位宽的计数器
reg  key_d1;									//定义一个位宽为1位的寄存器
reg  key_d2;									//定义一个位宽为1位的寄存器
//模块一：时钟分频模块
always @(posedge clk or negedge nRST)
begin
	if(!nRST)
		cnt <= 21'd0;
	else
		begin
			if(cnt<21'd9999)							
				cnt <= cnt + 1'b1;   				//计数器在小于9999时，每来一个时钟，就加1
			else
				cnt <= 21'd0;							//当计数器等于9999时，清零
		end
end
assign  clk_5KHz = (cnt<21'd5000)? 1'b1:1'b0;   //得到一个5KHz（50MHz/10000）的分频时钟
//模块二：移位模块
always @(posedge clk_5KHz or negedge nRST)
begin
	if(!nRST)
		begin
			key_d1 <= 0;
			key_d2 <= 0;
		end
	else
		begin
			key_d1 <= key;                 		//D触发器
			key_d2 <= key_d1;             		//D触发器
		end
end
//模块三：按键消抖模块
always @(posedge clk_5KHz or negedge nRST)
begin
	if(!nRST)
		key_o <= 1'b0;
	else
		begin
			if(key_d1 & key_d2 & key)           //只有连续出现3个1，才认为是1，因此偶尔出现一个高脉冲干扰，系统会自动过滤掉
				key_o <= 1'b1;
			else if(!key_d1 & !key_d2 & !key)   //只有连续出现3个0，才认为是0，因此偶尔出现一个低脉冲干扰，系统会自动过滤掉
				key_o <= 1'b0;
		end
end
endmodule
