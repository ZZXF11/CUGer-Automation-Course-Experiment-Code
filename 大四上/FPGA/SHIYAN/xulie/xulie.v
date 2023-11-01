module xulie(CLOCK_50,x,z,rst,ns);
input CLOCK_50,x,rst;
output z;
output[2:0]ns;
reg[2:0]ns;
wire z;
parameter S0=3'd0,S1=3'd1,S2=3'd2,S3=3'd3,S4=3'd4,S5=3'd5; 
assign z=~((ns==S4)&&x==0); 
always @(posedge CLOCK_50)
begin
if(!rst)
   ns<=S0;
else              
case(ns)
    S0: if (x==1) ns <= S1; else ns <= S0;
    S1: if (x==0) ns <= S2; else ns <= S1; 
    S2: if (x==0) ns <= S3; else ns <= S1; 
    S3: if (x==1) ns <= S4; else ns <= S0;
	 S4: if (x==0) ns <= S5; else ns <= S1;
	 S5: if (x==1) ns <= S1; else ns <= S3;
	 default: ns <= S0;
endcase
end 
endmodule