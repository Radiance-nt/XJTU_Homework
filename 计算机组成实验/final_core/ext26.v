`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/29 21:15:23
// Design Name: 
// Module Name: ext26
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


module ext26(
input [25:0]a,
output reg [31:0]b
    );
always@(*)
begin
b[31:0]=32'h00000000;
b[25:0]=a;
end
endmodule
