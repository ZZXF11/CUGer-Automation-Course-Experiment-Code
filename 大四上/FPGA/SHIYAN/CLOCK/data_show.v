module  data_show(
								input [3:0]disp_dat,		// 显示数值
								output reg [6:0]disp_show
                    );
							

always @(disp_dat)
begin
    case(disp_dat)		// 将显示的数值映射为对应段码			
		4'h0:disp_show = 7'b100_0000;	// 0		
		4'h1:disp_show = 7'b111_1001;	// 1		
		4'h2:disp_show = 7'b010_0100;	// 2		
		4'h3:disp_show = 7'b011_0000;	// 3		
		4'h4:disp_show = 7'b001_1001;	// 4		
		4'h5:disp_show = 7'b001_0010;	// 5		
		4'h6:disp_show = 7'b000_0010;	// 6		
		4'h7:disp_show = 7'b111_1000;	// 7		
		4'h8:disp_show = 7'b000_0000;	// 8		
		4'h9:disp_show = 7'b001_0000;	// 9
		default:disp_show = 7'b100_0000;
	endcase
end			  
endmodule

