`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/27 17:17:27
// Design Name: 
// Module Name: ext16
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module ext16(
input [15:0]a,
output reg [31:0]b
    );
always@(*)
begin
    if(a[15:12]!=4'hf)
begin
b[31:0]=32'h00000000;
b[15:0]=a;
end
else 
begin
b[31:0]=32'hffffffff;
b[15:0]=a;
end
end
endmodule
