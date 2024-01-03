`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/27 22:58:58
// Design Name: 
// Module Name: mux2_jump
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


module mux2_jump(
input jump,
input [31:0]addrjump,
input [31:0]addr1,
output [31:0]nextaddr
    );
    assign nextaddr=(jump!=0)?addrjump:addr1;
endmodule
