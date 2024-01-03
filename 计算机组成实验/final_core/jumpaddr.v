`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/27 18:28:42
// Design Name: 
// Module Name: jumpaddr
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


module jump_addr(
input [3:0]a,
input [27:0]b,
 output [31:0]c
    );
    assign c[31:28]=a;
    assign c[27:0]=b;
endmodule
